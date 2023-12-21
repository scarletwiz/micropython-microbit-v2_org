/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Options to control how MicroPython is built.

#ifndef MICROPY_INCLUDED_CODAL_PORT_MPCONFIGPORT_H
#define MICROPY_INCLUDED_CODAL_PORT_MPCONFIGPORT_H

#include <stdint.h>

// Memory allocation policy
#define MICROPY_ALLOC_PATH_MAX                  (128)

// MicroPython emitters
#define MICROPY_EMIT_INLINE_THUMB               (1)

// Python internal features
#define MICROPY_VM_HOOK_COUNT                   (64)
#define MICROPY_VM_HOOK_INIT \
    static unsigned int vm_hook_divisor = MICROPY_VM_HOOK_COUNT;
#define MICROPY_VM_HOOK_POLL \
    if (--vm_hook_divisor == 0) { \
        vm_hook_divisor = MICROPY_VM_HOOK_COUNT; \
        extern void microbit_hal_background_processing(void); \
        microbit_hal_background_processing(); \
    }
#define MICROPY_VM_HOOK_LOOP                    MICROPY_VM_HOOK_POLL
#define MICROPY_VM_HOOK_RETURN                  MICROPY_VM_HOOK_POLL
#define MICROPY_ENABLE_GC                       (1)
#define MICROPY_STACK_CHECK                     (1)
#define MICROPY_KBD_EXCEPTION                   (1)
#define MICROPY_HELPER_REPL                     (1)
#define MICROPY_REPL_AUTO_INDENT                (1)
#define MICROPY_LONGINT_IMPL                    (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_ENABLE_SOURCE_LINE              (1)
#define MICROPY_FLOAT_IMPL                      (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_STREAMS_NON_BLOCK               (1)
#define MICROPY_MODULE_BUILTIN_INIT             (1)
#define MICROPY_MODULE_WEAK_LINKS               (1)
#define MICROPY_MODULE_FROZEN_MPY               (1)
#define MICROPY_QSTR_EXTRA_POOL                 mp_qstr_frozen_const_pool
#define MICROPY_USE_INTERNAL_ERRNO              (1)
#define MICROPY_ENABLE_SCHEDULER                (1)

// Fine control over Python builtins, classes, modules, etc
#define MICROPY_PY_BUILTINS_STR_UNICODE         (1)
#define MICROPY_PY_BUILTINS_MEMORYVIEW          (1)
#define MICROPY_PY_BUILTINS_FROZENSET           (1)
#define MICROPY_PY_BUILTINS_INPUT               (1)
#define MICROPY_PY_BUILTINS_HELP                (1)
#define MICROPY_PY_BUILTINS_HELP_TEXT           microbit_help_text
#define MICROPY_PY_BUILTINS_HELP_MODULES        (1)
#define MICROPY_PY___FILE__                     (0)
#define MICROPY_PY_MICROPYTHON_MEM_INFO         (1)
#define MICROPY_PY_COLLECTIONS_ORDEREDDICT      (1)
#define MICROPY_PY_IO                           (1) // 0 -> 1 for. json
#define MICROPY_PY_SYS_MAXSIZE                  (1)
#define MICROPY_PY_SYS_PLATFORM                 "microbit"

// Extended modules
#define MICROPY_PY_UERRNO                       (1)
#define MICROPY_PY_UTIME_MP_HAL                 (1)
#define MICROPY_PY_URANDOM                      (1)
#define MICROPY_PY_URANDOM_SEED_INIT_FUNC       (rng_generate_random_word())
#define MICROPY_PY_URANDOM_EXTRA_FUNCS          (1)
#define MICROPY_PY_MACHINE                      (1)
#define MICROPY_PY_MACHINE_PULSE                (1)

// WIZNET5K Network

#define MICROPY_PY_NETWORK          (1)

#define WIZCHIP_PREFIXED_EXPORTS  	(1) 

#define MICROPY_PY_NETWORK_WIZNET5K (1)
#define WIZCHIP_PREFIXED_EXPORTS 	(1)
#define _WIZCHIP_ 5500
#define WIZCHIP_YIELD mpy_wiznet_yield

#define MICROPY_PY_NETWORK              (1)


#ifndef MICROPY_PY_USOCKET
#define MICROPY_PY_USOCKET              (1)
#endif
#ifndef MICROPY_PY_USSL
#define MICROPY_PY_USSL                 (1)
#endif
#ifndef MICROPY_PY_UWEBSOCKET
#define MICROPY_PY_UWEBSOCKET           (0)
#endif
#ifndef MICROPY_PY_WEBREPL
#define MICROPY_PY_WEBREPL              (0) 
#endif

	// Wiznet HW config.
#define MICROPY_HW_WIZNET_SPI_ID            (0)
#define MICROPY_HW_WIZNET_SPI_BAUDRATE      (70*1000*1000)
#define MICROPY_HW_WIZNET_SPI_SCK           (18)
#define MICROPY_HW_WIZNET_SPI_MOSI          (19)
#define MICROPY_HW_WIZNET_SPI_MISO          (16)
#define MICROPY_HW_WIZNET_PIN_CS            (17)
#define MICROPY_HW_WIZNET_PIN_RST           (20)
	// Connecting the INTN pin enables RECV interrupt handling of incoming data.
#define MICROPY_HW_WIZNET_PIN_INTN          (21)

#ifndef MICROPY_PY_NETWORK_HOSTNAME_DEFAULT
#define MICROPY_PY_NETWORK_HOSTNAME_DEFAULT "W5500-EVB"
#endif

#ifndef MICROPY_BOARD_NETWORK_INTERFACES
#define MICROPY_BOARD_NETWORK_INTERFACES
#endif

#define MICROPY_PORT_NETWORK_INTERFACES \
    MICROPY_HW_NIC_WIZNET5K \
    MICROPY_BOARD_NETWORK_INTERFACES \


#if MICROPY_PY_NETWORK_WIZNET5K
extern const struct _mp_obj_type_t mod_network_nic_type_wiznet5k;
#define MICROPY_HW_NIC_WIZNET5K             { MP_ROM_QSTR(MP_QSTR_WIZNET5K), MP_ROM_PTR(&mod_network_nic_type_wiznet5k) },
#else
#define MICROPY_HW_NIC_WIZNET5K
#endif

#ifndef MICROPY_PY_SOCKET
#define MICROPY_PY_SOCKET               (1)
#endif
#ifndef MICROPY_BOARD_NETWORK_INTERFACES
#define MICROPY_BOARD_NETWORK_INTERFACES
#endif


#define MICROPY_PY_UJSON 						(1)
#define MICROPY_PY_UJSON_SEPARATORS				(1)
#define MICROPY_PY_UBINASCII					(1)
#define MICROPY_PY_BUILTINS_BYTES_HEX			(1)



#define MICROPY_HW_ENABLE_RNG                   (1)
#define MICROPY_MBFS                            (1)

// Custom errno list.
#define MICROPY_PY_UERRNO_LIST \
    X(EPERM) \
    X(ENOENT) \
    X(EIO) \
    X(EBADF) \
    X(EAGAIN) \
    X(ENOMEM) \
    X(EACCES) \
    X(EEXIST) \
    X(ENODEV) \
    X(EISDIR) \
    X(EINVAL) \
    X(ENOSPC) \
    X(EOPNOTSUPP) \
    X(ENOTCONN) \
    X(ETIMEDOUT) \
    X(EALREADY) \
    X(EINPROGRESS) \

// extra built in names to add to the global namespace
#if MICROPY_MBFS
#define MICROPY_PORT_BUILTINS \
    { MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&mp_builtin_open_obj) },
#endif

#define MICROBIT_RELEASE "2.1.1"
#define MICROBIT_BOARD_NAME "micro:bit"
#define MICROPY_HW_BOARD_NAME MICROBIT_BOARD_NAME " v" MICROBIT_RELEASE
#define MICROPY_HW_MCU_NAME "nRF52833"

#define MP_STATE_PORT MP_STATE_VM

// These functions allow nested calls.
extern void target_disable_irq(void);
extern void target_enable_irq(void);

static inline uint32_t disable_irq(void) {
    target_disable_irq();
    return 0;
}

static inline void enable_irq(uint32_t state) {
    (void)state;
    target_enable_irq();
}

#define MICROPY_BEGIN_ATOMIC_SECTION() disable_irq()
#define MICROPY_END_ATOMIC_SECTION(state) enable_irq(state)

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void *)((uint32_t)(p) | 1))

#define MP_SSIZE_MAX (0x7fffffff)

// Type definitions for the specific machine
typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

// Needed for MICROPY_PY_URANDOM_SEED_INIT_FUNC.
extern uint32_t rng_generate_random_word(void);

// Needed for microbitfs.c:microbit_file_open.
void microbit_file_opened_for_writing(const char *name, size_t name_len);

#endif
