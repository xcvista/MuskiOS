
#ifndef _MUSKIOS_VGA_H_
#define _MUSKIOS_VGA_H_

#include <stddef.h>
#include <stdint.h>

typedef struct _vga_loc
{
	uint8_t x;
	uint8_t y;
} vga_loc;

typedef struct _vga_size
{
	uint8_t width;
	uint8_t height;
} vga_size;

typedef struct _vga_colorset
{
	uint8_t foreground : 4;
	uint8_t background : 4;
} __attribute__((packed)) vga_colorset;

typedef struct _vga_char
{
	char ch;
	vga_colorset color;
} __attribute__((packed)) vga_char;

typedef enum _vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
} vga_color;

#define VGA_CONTROL (0x3d4)
#define VGA_DATA (0x3d5)


extern vga_char *vga_mem;
extern vga_loc vga_cursor;
extern vga_size vga_screen_size;
extern vga_colorset vga_current_color;

extern void vga_init(void);
extern void vga_clear(void);
extern void vga_set_cursor(vga_loc);
extern vga_loc vga_get_cursor(void);

inline __attribute__((always_inline)) vga_colorset vga_mkcolor(vga_color bg, vga_color fg)
{
	vga_colorset set;
	
	set.background = bg;
	set.foreground = fg;
	
	return set;
}

inline __attribute__((always_inline)) vga_size vga_mksize(uint8_t w, uint8_t h)
{
	vga_size size;
	
	size.width = w;
	size.height = h;
	
	return size;
}

inline __attribute__((always_inline)) vga_loc vga_mkloc(uint8_t x, uint8_t y)
{
	vga_loc loc;
	
	loc.x = x;
	loc.y = y;
	
	return loc;
}

#endif
