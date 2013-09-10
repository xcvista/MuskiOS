
#include <muskios/kernel.h>
#include <muskios/kernel-start.h>
#include <muskios/kstdio.h>
#include <muskios/vga.h>
#include <muskios/version.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

uint32_t magic;
void *multiboot;

void kernel_prep(uint32_t _magic, void *_multiboot)
{
	magic = _magic;
	multiboot = _multiboot;
}

void kernel_start(void)
{

	vga_init();
	
	if (magic != 0x2badb002)
	{
		kpanic("We are not booting off a Multiboot bootloader.");
	}

	kprintf("muskios 0.1 (git %s)\nCopyright 2013 Maxthon Chan\n\n", MUSKIOS_VERSION);
	kprintf("Multiboot 0x%x", magic);
}

