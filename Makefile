GNU_PREFIX = ../arm-gnu-toolchain-13.3.rel1-aarch64-aarch64-none-elf/bin/aarch64-none-elf-

CC = $(GNU_PREFIX)g++
CCFLAGS = \
	-march=armv8-a+nofp \
	-mno-outline-atomics \
	-std=c++20 \
	-O1 \
	-g \
	-ffreestanding \
	-fno-exceptions \
	-fno-rtti \
	-nostdlib \
	-Wall \
	-Wextra

LD = $(GNU_PREFIX)ld
LDFLAGS = \
	-T linker.ld

SRC_DIR = src
SRC = \
	$(wildcard $(SRC_DIR)/*.s) \
	$(wildcard $(SRC_DIR)/*.cpp)

OBJ_DIR = build
OBJ = \
	$(filter %.o, $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRC))) \
	$(filter %.o, $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC)))

ELF = $(OBJ_DIR)/kernel.elf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p build
	$(CC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p build
	$(CC) $(CCFLAGS) -c $< -o $@

$(ELF): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(ELF)

clean:
	rm -rf build

build:
	make build/kernel.elf
	$(GNU_PREFIX)gcc -s -Os -nostdlib -mcpu=cortex-a72+nofp usr/crt0.s usr/system_calls.s usr/shell.c -o usr/shell
	$(GNU_PREFIX)gcc -s -Os -nostdlib -mcpu=cortex-a72+nofp usr/crt0.s usr/system_calls.s usr/ls.c -o usr/ls
	$(GNU_PREFIX)gcc -s -Os -nostdlib -mcpu=cortex-a72+nofp usr/crt0.s usr/system_calls.s usr/cat.c -o usr/cat
	$(GNU_PREFIX)gcc -s -Os -nostdlib -mcpu=cortex-a72+nofp usr/crt0.s usr/system_calls.s usr/pong.c -o usr/pong
	$(GNU_PREFIX)gcc -s -Os -nostdlib -mcpu=cortex-a72+nofp usr/crt0.s usr/system_calls.s usr/server.c -o usr/server
	$(GNU_PREFIX)gcc -s -Os -nostdlib -mcpu=cortex-a72+nofp usr/crt0.s usr/system_calls.s usr/client.c -o usr/client
	g++ mkfs.cpp -o mkfs
	./mkfs usr/shell usr/ls usr/cat usr/pong usr/server usr/client test.txt

dump:
	$(GNU_PREFIX)objdump -D build/kernel.elf > build/kernel.asm

qemu: $(ELF)
	qemu-system-aarch64 \
		-machine virt,gic-version=3,highmem=off \
		-cpu cortex-a72 \
		-kernel build/kernel.elf \
		-m 128M \
		-smp 4 \
		-nographic \
		-drive file=fs.img,if=none,format=raw,id=x0 \
		-device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 \
		-netdev user,id=net0,hostfwd=udp::2000-:2000,hostfwd=tcp::2000-:2000 -object filter-dump,id=net0,netdev=net0,file=packets.pcap \
		-device e1000,netdev=net0,bus=pcie.0

qemu-gdb: $(ELF)
	qemu-system-aarch64 \
		-s \
		-S \
		-machine virt,gic-version=3,highmem=off \
		-cpu cortex-a72 \
		-kernel build/kernel.elf \
		-m 128M \
		-smp 4 \
		-nographic \
		-drive file=fs.img,if=none,format=raw,id=x0 \
		-device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 \
		-netdev user,id=net0,hostfwd=udp::2000-:2000,hostfwd=tcp::2000-:2000 -object filter-dump,id=net0,netdev=net0,file=packets.pcap \
		-device e1000,netdev=net0,bus=pcie.0

test:
	make clean
	make build
	make dump
	make qemu

test-gdb:
	make clean
	make build
	make dump
	make qemu-gdb
