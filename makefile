BUILD_DIR = build

all: bootloader.bin kernel.bin floppy_image.img

floppy_image.img: ${BUILD_DIR}/bootloader.bin
	dd if=/dev/zero	of=${BUILD_DIR}/floppy_image.img bs=512 count=2880
	mkfs.fat -F 12 -n "ETHIOPIC" ${BUILD_DIR}/floppy_image.img
	dd if=${BUILD_DIR}/bootloader.bin of=${BUILD_DIR}/floppy_image.img bs=512 conv=notrunc
	mcopy -i ${BUILD_DIR}/floppy_image.img ${BUILD_DIR}/kernel.bin "::kernel.bin"

kernel.bin:	kernel/test.asm
	nasm -f bin kernel/test.asm -o ${BUILD_DIR}/kernel.bin

bootloader.bin:	boot/1st_stage/bootloader.asm
	nasm -f bin boot/1st_stage/bootloader.asm -o ${BUILD_DIR}/bootloader.bin

clean:
	rm ${BUILD_DIR}/*.*
