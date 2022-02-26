.PHONY = all clean

CC = i686-elf-gcc
LINKER = i686-elf-ld
ASM = nasm
CFLAGS = -c	# compiler flags
LDFLAGS = -T linker_script/ethKernelLinkerScript.ld	#text 0x1000# for the linker
NFLAGS = -f elf32		# for nasm assembler
BUILD_DIR = build

C_SOURCES = $(wildcard ethKernel/*.c drivers/*.c include/gui/*.c drivers/video/*.c include/*.c tools/*.c ethKernel/memory/*.c drivers/file_system/*.c drivers/console/*.c ethKernel/interrupts/*.c drivers/keyboard/*.c include/gui/font/*.c)
HEADERS = $(wildcard ethKernel/*.h drivers/*.h include/gui/*.h driver/video/*.h include/*.h tools/*.h ethKernel/memory/*.h drivers/file_system/*.h drivers/console/*.h ethKernel/interrupts/*.h drivers/keyboard/*.h include/gui/font/*.h)

OBJ = $(C_SOURCES:.c=.o)

all: bootloader.bin ethLoader.bin ethKernelEntry.o ethKernel.bin os-image.img runos

runos:
	echo "c" | bochs -f bochs.bxrc

debug:
	echo "C" | bochs -f debug.bxrc

os-image.img: ${BUILD_DIR}/bootloader.bin	# building the os image with file system.
	dd if=/dev/zero	of=${BUILD_DIR}/os-image.img bs=512 count=2880
	mkfs.fat -F 12 -n "Alazar" ${BUILD_DIR}/os-image.img
	dd if=${BUILD_DIR}/bootloader.bin of=${BUILD_DIR}/os-image.img bs=512 conv=notrunc
	mcopy -i ${BUILD_DIR}/os-image.img ${BUILD_DIR}/ethLoader.bin "::ethLdr.bin"
	mcopy -i ${BUILD_DIR}/os-image.img ${BUILD_DIR}/ethKernel.bin "::ethKrnl.bin"
	mcopy -i ${BUILD_DIR}/os-image.img initram/initram.tar "::initram.tar"

ethKernel.bin: build/ethKernelEntry.o ${OBJ}
	${LINKER} -o ${BUILD_DIR}/$@ ${LDFLAGS} $^ --oformat binary

ethKernel.o: ethKernel/ethKernel.asm
	nasm -f bin ethKernel/ethKernel.asm -o ${BUILD_DIR}/ethKernel.bin

ethKernelEntry.o:	boot/ethKernel_entry.asm
	nasm -f elf32 boot/ethKernel_entry.asm -o ${BUILD_DIR}/ethKernelEntry.o

ethLoader.bin: boot/2nd_stage/ethLoader.asm
	nasm -f bin boot/2nd_stage/ethLoader.asm -o ${BUILD_DIR}/ethLoader.bin

bootloader.bin:	boot/1st_stage/bootloader.asm
	nasm -f bin boot/1st_stage/bootloader.asm -o ${BUILD_DIR}/bootloader.bin

mkdir:
	mkdir build
	
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm ${BUILD_DIR}/*.*
	rm ethKernel/*.o tools/*.o 
