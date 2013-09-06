TARGET := muskios.elf

CC := clang
CXX := clang++
AR := ar
AS := as
NASM := nasm

HEADERS := $(wildcard include/*.h)
C_FILES := $(wildcard src/*.c)
CXX_FILES := $(wildcard src/*.cc)
OBJC_FILES := $(wildcard src/*.m)
OBJCXX_FILES := $(wildcard src/*.mm)
S_FILES := $(wildcard src/*.s)
ASM_FILES := $(wildcard src/*.asm)
BOOT_C_FILES := $(wildcard boot/*.c)
BOOT_S_FILES := $(wildcard boot/*.s)
BOOT_ASM_FILES := $(wildcard boot/*.asm)

ifeq ($(debug),yes)
CFLAGS += -g
OPTFLAGS := -O0
else
OPTFLAGS := -Os
endif

WARNFLAGS := -Wall

ADDITIONAL_CPPFLAGS := $(CPPFLAGS) -I./include
ADDITIONAL_CFLAGS := $(CFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(ADDITIONAL_CPPFLAGS) -target i586-elf -ffreestanding -std=gnu99
ADDITIONAL_CXXFLAGS := $(CFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(CXXFLAGS) $(ADDITIONAL_CPPFLAGS) -target i586-elf -ffreestanding -std=gnu++11
ADDITIONAL_OBJCFLAGS := $(ADDITIONAL_CFLAGS) -fobjc-runtime=gnustep-1.7 -fobjc-arc -Xclang -fobjc-default-synthesize-properties
ADDITIONAL_OBJCXXFLAGS := $(ADDITIONAL_CXXFLAGS) -fobjc-runtime=gnustep-1.7 -fobjc-arc -Xclang -fobjc-default-synthesize-properties
ADDITIONAL_LDFLAGS := $(LDFLAGS) $(OPTFLAGS) -ffreestanding -nostdlib

BOOT_OBJS := ${BOOT_C_FILES:.c=.c.o} ${BOOT_S_FILES:.s=.o} ${BOOT_ASM_FILES:.asm=.o}
OBJS := ${C_FILES:.c=.c.o} ${CXX_FILES:.cc=.cc.o} ${OBJC_FILES:.m=.m.o} ${OBJCXX_FILES:.mm=.mm.o} ${S_FILES:.s=.o} ${ASM_FILES:.asm=.asm.o}
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

all: $(TARGET)
.PHONY: all clean

$(TARGET): $(OBJS) $(BOOT_OBJS) kernel.ld
	$(CC) -Wl,-T,kernel.ld $(ADDITIONAL_LDFLAGS) boot/boot.o boot/crt0.o $(CRTBEGIN_OBJ) boot/kernel.c.o ${OBJS} -lgcc $(CRTEND_OBJ) boot/crtn.o -o $(TARGET)

%.c.o: %.c $(HEADERS)
	$(CC) $(ADDITIONAL_CFLAGS) -c $< -o $@

%.cc.o: %.cc $(HEADERS)
	$(CXX) $(ADDITIONAL_CXXFLAGS) -c $< -o $@

%.m.o: %.m $(HEADERS)
	$(CC) $(ADDITIONAL_OBJCFLAGS) -c $< -o $@

%.mm.o: %.mm $(HEADERS)
	$(CXX) $(ADDITIONAL_OBJCXXFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ADDITIONAL_CPPFLAGS) $< -o $@

%.o: %.asm
	$(NASM) $(ADDITIONAL_CPPFLAGS) -felf $< -o $@

clean:
	-rm $(OBJS) $(BOOT_OBJS) $(TARGET)

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -S -s & > /dev/null
	gdb $(TARGET) -ex "target remote :1234"

