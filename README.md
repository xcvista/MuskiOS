# MuskiOS

__MuskiOS__ is an experimental operating system written in (mostly) Objective-C programming language. It is a UNIX-like operating system with a microkernel.

## Components

*	MuskiOS Kernel

	*	Memory management and memory-mapped hardware support

	*	Kernel `libobjc2`

	*	Kernel `CoreFoundation` and `Foundation`

	*	MKDevicePort and MKDeviceStream classes (Hardware IO)

	*	MKDispatchScheduler class (GCD and process scheduler)

		*	MKDispatch class (GCD-based Process model)

		*	MKDispatchMessage class (GCD-based IPC)

*	MuskiOS `dyld` (dynamic linker)

	*	Supports Apple-styled versioned library placement and FatELF.

*	MuskiOS `init`

	*	MSCallCenter class (Syscall entry point & driver registration)

	*	Various device driver daemons

*	MuskiOS `libc` and `libobjc2`

	*	Based on newlib and GNUstep code

