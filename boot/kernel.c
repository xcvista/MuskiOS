
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
	kprintf("%s <0x%x>: hello, world\n", __PRETTY_FUNCTION__, (size_t)kernel_main);
}

void halt(void)
{
	kprintf("%s <0x%x>: System halted.", __PRETTY_FUNCTION__, (size_t)halt);
	for (;;)
		asm ("hlt");
}
