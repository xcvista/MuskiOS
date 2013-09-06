
#include <kernel.h>
#include <string.h>
#include <muskios/vga.h>
#include <muskios/kstdio.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

void kernel_main()
{
	vga_init();
	kprintf("hello, world: ox%x\n", (size_t)kernel_main);
}

void halt(void)
{
	asm ("cli");
	for (;;)
		asm ("hlt");
}
