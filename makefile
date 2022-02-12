BUILD_DIR = build

all: bootloader.bin ethLoader.bin ethKernel.bin os-image.img runos

runos:
	echo "c" | bochs -f bochs.bxrc
	
os-image.img: ${BUILD_DIR}/bootloader.bin
	dd if=/dev/zero	of=${BUILD_DIR}/os-image.img bs=512 count=2880
	mkfs.fat -F 12 -n "Alazar" ${BUILD_DIR}/os-image.img
	dd if=${BUILD_DIR}/bootloader.bin of=${BUILD_DIR}/os-image.img bs=512 conv=notrunc
	mcopy -i ${BUILD_DIR}/os-image.img ${BUILD_DIR}/ethLoader.bin "::ethLdr.bin"
	mcopy -i ${BUILD_DIR}/os-image.img ${BUILD_DIR}/ethKernel.bin "::ethKrnl.bin"

ethKernel.bin:	ethKernel/ethKernel.asm
	nasm -f bin ethKernel/ethKernel.asm -o ${BUILD_DIR}/ethKernel.bin

ethLoader.bin: boot/2nd_stage/ethLoader.asm
	nasm -f bin boot/2nd_stage/ethLoader.asm -o ${BUILD_DIR}/ethLoader.bin

bootloader.bin:	boot/1st_stage/bootloader.asm
	nasm -f bin boot/1st_stage/bootloader.asm -o ${BUILD_DIR}/bootloader.bin

clean:
	rm ${BUILD_DIR}/*.*
