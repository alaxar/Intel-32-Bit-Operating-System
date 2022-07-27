.PHONY = all clean

CC = i686-elf-gcc
LINKER = i686-elf-ld
ASM = nasm
CFLAGS = -c	-I include/ -nostdinc# compiler flags
LDFLAGS = -T linker_script/ethKernelLinkerScript.ld	#text 0x1000# for the linker
NFLAGS = -f elf32		# for nasm assembler
BUILD_DIR = build
GRUB_BOOT = disk/boot

C_SOURCES = $(wildcard ethKernel/*.c drivers/*.c include/gui/*.c drivers/video/*.c include/*.c tools/*.c ethKernel/memory/*.c drivers/file_system/*.c drivers/console/*.c ethKernel/interrupts/*.c drivers/keyboard/*.c drivers/mouse_driver/*.c include/gui/font/*.c include/gui/testProgram/*.c include/gui/event_handling/*.c programs/*.c ethKernel/memory_mgr/*.c ethKernel/cpu/*.c include/gui/window_system/*.c drivers/pci/*.c)
HEADERS = $(wildcard ethKernel/*.h drivers/*.h include/gui/*.h driver/video/*.h include/*.h tools/*.h ethKernel/memory/*.h drivers/file_system/*.h drivers/console/*.h ethKernel/interrupts/*.h drivers/keyboard/*.h drivers/mouse_driver/*.h include/gui/font/*.h include/gui/testProgram/*.h include/gui/event_handling/*.h programs/*.h ethKernel/memory_mgr/*.h ethKernel/cpu/*.h include/gui/window_system/*.h drivers/pci/*.h)

OBJ = $(C_SOURCES:.c=.o)

all: grub_boot.o ethKernel.bin EthiopicOS.iso runos

runos:
	VBoxManage startvm "ostest"
	# echo "c" | bochs -f bochs.bxrc

debug:
	echo "C" | bochs -f debug.bxrc


EthiopicOS.iso: ${GRUB_BOOT}/ethKernel.bin
	grub-mkrescue -o ${BUILD_DIR}/EthiopicOS.iso disk

ethKernel.bin: boot/multiboot/grub_boot.o ${OBJ}
	${LINKER} -o ${GRUB_BOOT}/$@ ${LDFLAGS} $^ #--oformat elf32

# multiboot assemble
grub_boot.o: boot/multiboot/boot.asm
	nasm -f elf boot/multiboot/boot.asm -o boot/multiboot/grub_boot.o

mkdir:
	mkdir build
	
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} $< -o $@

clean:
	rm ethKernel/*.o tools/*.o disk/boot/os-image.img ${BUILD_DIR}/*.* boot/multiboot/*.o