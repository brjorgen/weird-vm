/**
 * @file    generic-header.h
 * @author  brjorgen <www.github.com/brjorgen>
 * @version 0.01-a
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 **/

#ifndef BULLSHIT_SRC_H_
#define BULLSHIT_SRC_H_

/* ------------------------------------------------------------------------------
** INCLUDES
* ---------------------------------------------------------------------------- */
#include <stdint.h>

/* ------------------------------------------------------------------------------
** LOCAL CONSTANTS
* ---------------------------------------------------------------------------- */
/* N/A */

/* ------------------------------------------------------------------------------
** EXTERNAL CONSTANTS
* ---------------------------------------------------------------------------- */
/* N/A */

/* ------------------------------------------------------------------------------
** ENUMERATIONS
* ---------------------------------------------------------------------------- */

typedef enum STACK_ENTRY_TYPE {
	STACK_ENTRY_TYPE_STR,
	STACK_ENTRY_TYPE_NUM,
} e_stack_entry_type;

/* ------------------------------------------------------------------------------
** TYPE DEFINITIONS
* ---------------------------------------------------------------------------- */

typedef struct s_screen {
	uint16_t height;
	uint16_t width;
	uint16_t offset;
} t_screen;

typedef struct s_stack_entry {
	e_stack_entry_type type;
	uint16_t	   size;

	union {
		int  integer;
		char string[];
	};
} t_stack_entry;

typedef struct s_stack {
	uint32_t	   capacity;
	t_stack_entry	   *stack_entry;
} t_stack;

typedef struct s_program_info {
	char *title;
	char *path;
	char *author;
	char *email;
	uint32_t size;
	uint32_t offset;
}	t_program_info;

typedef struct	weird_cpu {
	t_program_info proginfo;
	uint8_t	       *mem;

	struct {
		uint64_t pc;
		uint64_t a;
		uint64_t b;
		uint64_t c;
		uint64_t d;
		uint64_t res;
		uint64_t tmp;
	} registers;

	struct {
		t_screen *screen;
		t_stack  *stack;
	} handles;
}	       t_weird_cpu;

/* ------------------------------------------------------------------------------
** MACRO FUNCTIONS
* ---------------------------------------------------------------------------- */

# define _LOG(l, s) printf("[%s : %s] : %s\n", l, __FUNCTION__, s)
# define LOG_ERR(s) _LOG("E", s)
# define LOG_INFO(s) _LOG("I", s)
# define LOG_WARN(s) _LOG("W", s)

/* ------------------------------------------------------------------------------
** PUBLIC FUNCTION PROTOTYPES
* ---------------------------------------------------------------------------- */
/* N/A */

#endif /* BULLSHIT_SRC_H_ */
