#include "s3k.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>

extern char __uart_base[]; // UART base address

void app2_init(void)
{
	int mon_idx = APP2_MON_IDX;   // Monitor index
	int ram_idx = RAM_IDX;   // RAM index
	int uart_idx = UART_IDX; // UART index

	// RAM configuration
	s3k_word_t ram_base = APP2_RAM_BASE;
	s3k_word_t ram_size = APP_RAM_SIZE;
	s3k_word_t ram_perm = S3K_MEM_PERM_RWX; // Read/Write/Execute permissions
	s3k_word_t ram_fuel = 1;
	s3k_word_t ram_slot = 1;
	mem_init(mon_idx, ram_idx, ram_slot, ram_fuel, ram_perm, ram_base, ram_size);

	s3k_word_t uart_base = (s3k_word_t)__uart_base;
	s3k_word_t uart_size = UART_SIZE;
	s3k_word_t uart_perm = S3K_MEM_PERM_RW; // Read/Write permissions
	s3k_word_t uart_fuel = 1;
	s3k_word_t uart_slot = 2;
	mem_init(mon_idx, uart_idx, uart_slot, uart_fuel, uart_perm, uart_base, uart_size);

	if (s3k_mon_reg_set(mon_idx, S3K_REG_PC, ram_base) != 0) {
		printf("Failed to set program counter to RAM start\n");
		return;
	}
}

// Configure scheduling for app2 and launch it.
void app2_schedule(uint32_t type)
{
    if (type == PARALLEL) {
        s3k_mon_tsl_grant(APP2_MON_IDX, HART2_TSL_IDX);
        s3k_mon_tsl_set(APP2_MON_IDX, HART2_TSL_IDX, true);
        s3k_mon_resume(APP2_MON_IDX);
    }  else if (type == ROUND_ROBIN) {
        // s3k_tsl_derive(HART1_TSL_IDX, j, NUM_TIME_FUEL / 2, true, NUM_TIME_SLOT / 2);
        // s3k_mon_tsl_grant(APP2_MON_IDX, j);
        s3k_mon_tsl_derive(APP2_MON_IDX, HART1_TSL_IDX, NUM_TIME_FUEL / 2, true, NUM_TIME_SLOT / 2);
        s3k_mon_resume(APP2_MON_IDX);
    }
}
