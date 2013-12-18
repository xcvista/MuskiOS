
#include <muskios/vga.h>
#include <muskios/kstdio.h>
#include <muskios/io.h>
#include <string.h>

vga_char *vga_mem;
vga_loc vga_cursor;
vga_size vga_screen_size;
vga_colorset vga_current_color;

int vga_putchar(int c)
{
	if (c == '\n')
	{
		if (vga_cursor.y < vga_screen_size.height - 1)
		{
			vga_set_cursor(vga_mkloc(0, vga_cursor.y + 1));
		}
		else
		{
			// Screen scroll
			memmove(vga_mem, (const char *)vga_mem + vga_screen_size.width * sizeof(vga_char), vga_screen_size.width * (vga_screen_size.height - 1) * sizeof(vga_char));
			vga_set_cursor(vga_mkloc(0, vga_cursor.y));
		}
	}
	else if (c == '\r')
	{
		vga_set_cursor(vga_mkloc(0, vga_cursor.y));
	}
	else if (c == '\t')
	{
		do
		{
			vga_putchar(' ');
		}
		while (vga_cursor.x % 8 == 0);
	}
	else
	{
		vga_char ch;
		ch.ch = c;
		ch.color = vga_current_color;
		
		if (vga_cursor.x >= vga_screen_size.width - 1)
		{
			vga_putchar('\n');
		}
		
		vga_mem[vga_cursor.y * vga_screen_size.width + vga_cursor.x] = ch;
		vga_set_cursor(vga_mkloc(vga_cursor.x + 1, vga_cursor.y));
	}
	return 0;
}

void vga_init(void)
{
	vga_mem = (vga_char *)0xb8000;
	vga_screen_size = vga_mksize(80, 25);
	vga_clear();
	vga_current_color = vga_mkcolor(COLOR_BLACK, COLOR_LIGHT_GREY);
	kputchar = vga_putchar;
}

void vga_clear(void)
{
	memset(vga_mem, 0, vga_screen_size.height * vga_screen_size.width * sizeof(vga_char));
	vga_set_cursor(vga_mkloc(1, 1));
}

void vga_set_cursor(vga_loc loc)
{
	vga_cursor = loc;
	
	int offset = loc.y * vga_screen_size.width + loc.x;
	
	io_out8(VGA_CONTROL, 14);
	io_out8(VGA_DATA, offset >> 8);
	io_out8(VGA_CONTROL, 15);
	io_out8(VGA_DATA, offset & 0xff);
}

vga_loc vga_get_cursor(void)
{
	io_out8(VGA_CONTROL, 14);
	int offset = io_in8(VGA_DATA) << 8;
	io_out8(VGA_CONTROL, 15);
	offset |= io_in8(VGA_DATA);
	
	vga_loc loc = vga_mkloc(offset % vga_screen_size.width, offset / vga_screen_size.width);
	vga_cursor = loc;
	
	return loc;
}
