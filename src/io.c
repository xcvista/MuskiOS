
#include <muskios/io.h>

uint8_t io_in8(uint16_t port)
{
	uint8_t result;
	__asm__("in\t%%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

uint16_t io_in16(uint16_t port)
{
	uint16_t result;
	__asm__("in\t%%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void io_out8(uint16_t port, uint8_t data)
{
	__asm__("out\t%%al, %%dx" : :"a" (data), "d" (port));
}

void io_out16(uint16_t port, uint16_t data)
{
	__asm__("out\t%%ax, %%dx" : :"a" (data), "d" (port));
}
