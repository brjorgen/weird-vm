/**
 * @file generic-c-source.c
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
 *
 **/

/* ------------------------------------------------------------------------------
** INCLUDES
* ---------------------------------------------------------------------------- */

#include "../inc/generic-header.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/* ------------------------------------------------------------------------------
** LOCAL CONSTANTS
* ---------------------------------------------------------------------------- */
/* N/A */

/* ------------------------------------------------------------------------------
** EXTERNAL CONSTANTS
* ---------------------------------------------------------------------------- */
/* N/A */

/* ------------------------------------------------------------------------------
** PRIVATE FUNCTION DEFINITIONS
* ---------------------------------------------------------------------------- */

static void cpu_init(t_weird_cpu *cpu){
	cpu->registers.a = 0;
	cpu->registers.b = 0;
	cpu->registers.c = 0;
	cpu->registers.d = 0;
	cpu->registers.res = 0;
	cpu->registers.tmp = 0;

	LOG_INFO("- allocating mem...");
	cpu->mem = malloc(sizeof(uint8_t) * (1024 * 1024));
	if (!cpu->mem){
		LOG_ERR(" -- Couldn't allocate system memory");
		exit(EXIT_FAILURE);
	}

	LOG_INFO("-- bzero-ing mem...");
	bzero(cpu->mem, sizeof(uint8_t) * (1024 * 1024));

	LOG_INFO("- allocating stack...");
	cpu->handles.stack = malloc(sizeof(t_stack));
	if (!cpu->handles.stack)
		LOG_ERR("-- Couldn't allocate system memory");

	cpu->handles.stack->capacity = (1024 * 100);
	LOG_INFO("-- set capacity");

	LOG_INFO("- initializing mmio devices...");
	cpu->handles.screen = malloc(sizeof(t_screen));
	cpu->handles.screen->height = 100;
	cpu->handles.screen->width = 100;
	cpu->handles.screen->offset = 0;
}

static void cpu_teardown(t_weird_cpu *cpu){
	LOG_INFO("- tearing down CPU...");
	free(cpu->handles.stack);
	free(cpu->handles.screen);
	free(cpu->mem);
}

/* ------------------------------------------------------------------------------
** PUBLIC FUNCTION DEFINITIONS
* ---------------------------------------------------------------------------- */

enum OPCODE {
	NOP    =   0x00,
	ADD8   =   0x01,
	ADD16  =   0x11,
	INC    =   0x21,
	SUB8   =   0x02,
	SUB16  =   0x12,
	DEC    =   0x22,
	MUL8   =   0x03,
	MUL16  =   0x13,
	DIV8   =   0x04,
	DIV16  =   0x14,
	PSHDAT =   0x05,
	POPDAT =   0x15,
	PRINT  =   0x06,
	CMP    =   0x07,
	JIZ    =   0x17,
	JEQ    =   0x27,
	JIL    =   0x37,
	JIG    =   0x47,
	JTO    =   0x57,
	STO    =   0x08,
	DRW    =   0xDD,
	HLT    =   0xFF,
	__INSTRUCTION_MAX
};

void	add(t_weird_cpu *cpu, uint8_t operand){
	LOG_INFO("--- adding");
	switch (operand) {
	case (ADD8):
		cpu->registers.res = ((uint8_t)cpu->mem[cpu->registers.pc + 1]) + ((uint8_t)cpu->mem[cpu->registers.pc + 2]);
		break;
	case (ADD16):
		cpu->registers.res = ((uint16_t)cpu->mem[cpu->registers.pc + 1]) + ((uint16_t)cpu->mem[cpu->registers.pc + 4]);
		break;
	}
	cpu->registers.pc += 2;
}

void	print(t_weird_cpu *cpu, uint8_t operand){
	(void)operand;
	printf("> %d\n", (uint8_t)cpu->registers.res);
}

void	unimplemented(t_weird_cpu *cpu, uint8_t operand){
	(void)cpu;
	(void)operand;
	LOG_WARN("instruction unimplemented.");
}

void	(*instruction_jump_table[__INSTRUCTION_MAX + 1])(t_weird_cpu *cpu, uint8_t opcode) = {
	[NOP] = unimplemented,
	[ADD8] = add,
	[ADD16] = add,
	[INC] = unimplemented,
	[SUB8] = unimplemented,
	[SUB16] = unimplemented,
	[DEC] = unimplemented,
	[MUL8] = unimplemented,
	[MUL16] = unimplemented,
	[DIV8] = unimplemented,
	[DIV16] = unimplemented,
	[PSHDAT] = unimplemented,
	[POPDAT] = unimplemented,
	[PRINT] = print,
	[CMP] = unimplemented,
	[JIZ] = unimplemented,
	[JEQ] = unimplemented,
	[JIL] = unimplemented,
	[JIG] = unimplemented,
	[JTO] = unimplemented,
	[STO] = unimplemented,
	[DRW] = unimplemented,
	[__INSTRUCTION_MAX] = unimplemented,
};

void	exec(t_weird_cpu *cpu){
	LOG_INFO("- execution starting.");
	cpu->registers.pc = 0;
	while (cpu->mem[cpu->registers.pc] != 0x00){
		uint8_t current_instruction = cpu->mem[cpu->registers.pc];
		LOG_INFO("-- executing an instruction...");
		printf("---- %d %s\n", current_instruction, "placeholder str");
		instruction_jump_table[current_instruction](cpu, current_instruction);
		cpu->registers.pc++;
	}
	LOG_INFO("- execution completed.");
}

int	main(
	int	argc,
	char	*argv[]
	){
	(void)argc;
	(void)argv;
	LOG_INFO("Hello, world!");

	LOG_INFO("Initializing Weird CPU...");
	t_weird_cpu cpu;
	cpu_init(&cpu);
	LOG_INFO("... Done!");

	LOG_INFO("Executing program...");
	uint8_t prog[] = {0x01, 0x01, 0x02, 0x06, 0x00};
	memcpy(cpu.mem, prog, 5); 
	exec(&cpu);
	LOG_INFO("... Done!");

	LOG_INFO("Tearing down Weird CPU :( ...");
	cpu_teardown(&cpu);
	LOG_INFO("... Done!");
}
