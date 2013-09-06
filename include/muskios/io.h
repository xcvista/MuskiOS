
#ifndef _MUSKIOS_IO_H_
#define _MUSKIOS_IO_H_

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

extern uint8_t io_in8(uint16_t);
extern uint16_t io_in16(uint16_t);
extern void io_out8(uint16_t, uint8_t);
extern void io_out16(uint16_t, uint16_t);

__END_DECLS

#endif
