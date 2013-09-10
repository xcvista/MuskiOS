TARGET := muskios.elf
ISO_TARGET := muskios.iso
ISO_DIR := .iso

CC := clang
CXX := clang++
AR := ar
AS := as
NASM := nasm

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)
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

WARNFLAGS := -Wall -Wformat

ADDITIONAL_INCLUDEDIR := -I./include
ADDITIONAL_CPPFLAGS := $(CPPFLAGS) -nostdinc $(ADDITIONAL_INCLUDEDIR)
ADDITIONAL_CFLAGS := $(CFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(ADDITIONAL_CPPFLAGS) -target i586-elf -ffreestanding -std=gnu99
ADDITIONAL_CXXFLAGS := $(CFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(CXXFLAGS) $(ADDITIONAL_CPPFLAGS) -target i586-elf -ffreestanding -std=gnu++11 -fno-exceptions -fno-rtti
ADDITIONAL_OBJCFLAGS := $(ADDITIONAL_CFLAGS) -fobjc-runtime=gnustep-1.7 -fobjc-arc -Xclang -fobjc-default-synthesize-properties
ADDITIONAL_OBJCXXFLAGS := $(ADDITIONAL_CXXFLAGS) -fobjc-runtime=gnustep-1.7 -fobjc-arc -Xclang -fobjc-default-synthesize-properties
ADDITIONAL_LDFLAGS := $(LDFLAGS) $(OPTFLAGS) -ffreestanding -nostdlib

BOOT_OBJS := ${BOOT_C_FILES:.c=.c.o} ${BOOT_S_FILES:.s=.o} ${BOOT_ASM_FILES:.asm=.o}
OBJS := ${C_FILES:.c=.c.o} ${CXX_FILES:.cc=.cc.o} ${OBJC_FILES:.m=.m.o} ${OBJCXX_FILES:.mm=.mm.o} ${S_FILES:.s=.o} ${ASM_FILES:.asm=.asm.o}
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

all: before-all $(TARGET)

.PHONY: all clean run debug before-all iso

before-all:
ifeq ($(debug),yes)
	@[ -e $(TARGET) -a ! -e .debug ] && $(MAKE) clean; true;
else
	@[ -e $(TARGET) -a -e .debug ] && $(MAKE) clean; true;
endif

$(TARGET): $(OBJS) $(BOOT_OBJS) kernel.ld
	@echo "  CCLD\t\t$@"
	@$(CC) -Wl,-T,kernel.ld $(ADDITIONAL_LDFLAGS) boot/boot.o boot/crt0.o $(CRTBEGIN_OBJ) boot/kernel-start.c.o ${OBJS} -lgcc $(CRTEND_OBJ) boot/crtn.o -o $(TARGET)
ifeq ($(debug),yes)
	@echo "  TOUCH\t\t.debug"
	@touch .debug
endif

%.c.o: %.c include/muskios/version.h $(HEADERS)
	@echo "  CC\t\t$<"
	@$(CC) $(ADDITIONAL_CFLAGS) -c $< -o $@

%.cc.o: %.cc $(HEADERS)
	@echo "  CXX\t\t$<"
	@$(CXX) $(ADDITIONAL_CXXFLAGS) -c $< -o $@

%.m.o: %.m $(HEADERS)
	@echo "  CC\t\t$<"
	@$(CC) $(ADDITIONAL_OBJCFLAGS) -c $< -o $@

%.mm.o: %.mm $(HEADERS)
	@echo "  CXX\t\t$<"
	@$(CXX) $(ADDITIONAL_OBJCXXFLAGS) -c $< -o $@

%.o: %.s
	@echo "  AS\t\t$<"
	@$(AS) $(ADDITIONAL_CPPFLAGS) $< -o $@

%.o: %.asm
	@echo "  NASM\t\t$<"
	@$(NASM) $(ADDITIONAL_INCLUDEDIR) -felf $< -o $@

include/muskios/version.h:
	@echo "  GEN\t\t$@"
	@echo "#ifndef _MUSKIOS_VERSION_H_" > $@
	@echo "#define _MUSKIOS_VERSION_H_" >> $@
	@echo "#define MUSKIOS_VERSION \"$(shell git rev-parse --short HEAD)\"" >> $@
	@echo "#endif" >> $@

clean:
	@echo "  CLEAN"
	@-rm -r $(OBJS) $(BOOT_OBJS) include/muskios/version.h $(TARGET) .debug $(ISO_TARGET) $(ISO_DIR) > /dev/null 2>&1

debug:
	@$(MAKE) debug=yes

debug-iso:
	@$(MAKE) iso debug=yes

iso: $(ISO_TARGET)

$(ISO_TARGET): $(ISO_DIR)/boot/grub/grub.cfg $(ISO_DIR)/boot/$(TARGET)
	@echo "  MKRESCUE\t$@"
	@grub-mkrescue -o $@ $(ISO_DIR) > /dev/null 2>&1

$(ISO_DIR)/boot/grub/grub.cfg: grub.cfg $(ISO_DIR)/boot/grub
	@echo "  CP\t\tgrub.cfg"
	@cp grub.cfg $(ISO_DIR)/boot/grub

$(ISO_DIR)/boot/$(TARGET): $(TARGET) $(ISO_DIR)/boot/grub
	@echo "  CP\t\t$(TARGET)"
	@cp $(TARGET) $(ISO_DIR)/boot

$(ISO_DIR)/boot/grub:
	@echo "  MKDIR\t\t$@"
	@mkdir -p $@

run: $(TARGET)
	@echo "  QEMU\t\t$(TARGET)"
	@if [ -e .debug ]; then export QEMU_ARGS="-S -s"; fi; if [ -e $(ISO_TARGET) ]; then export QEMU_IMG="-cdrom $(ISO_TARGET)"; else export QEMU_IMG="-kernel $(TARGET)"; fi; qemu-system-i386 $$QEMU_IMG $$QEMU_ARGS > /dev/null 2>&1 &
	@[ -e .debug ] && echo "  GDB\t\t$(TARGET)" && gdb $(TARGET) -ex "target remote :1234"; true

