BUILD_DIR = build

all: bootloader.bin boot2.bin kernel.bin os-image.img runos

runos:
	echo "c" | bochs -f bochs.bxrc
	
os-image.img: ${BUILD_DIR}/bootloader.bin
	dd if=/dev/zero	of=${BUILD_DIR}/os-image.img bs=512 count=2880
	mkfs.fat -F 12 -n "Alazar" ${BUILD_DIR}/os-image.img
	dd if=${BUILD_DIR}/bootloader.bin of=${BUILD_DIR}/os-image.img bs=512 conv=notrunc
	mcopy -i ${BUILD_DIR}/os-image.img ${BUILD_DIR}/boot2.bin "::boot2.bin"
	mcopy -i ${BUILD_DIR}/os-image.img ${BUILD_DIR}/kernel.bin "::kernel.bin"

kernel.bin:	kernel/test.asm
	nasm -f bin kernel/test.asm -o ${BUILD_DIR}/kernel.bin

boot2.bin: boot/2nd_stage/boot2.asm
	nasm -f bin boot/2nd_stage/boot2.asm -o ${BUILD_DIR}/boot2.bin

bootloader.bin:	boot/1st_stage/bootloader.asm
	nasm -f bin boot/1st_stage/bootloader.asm -o ${BUILD_DIR}/bootloader.bin

clean:
	rm ${BUILD_DIR}/*.*
