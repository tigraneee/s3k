#include "s3k.h"
#include "utils.h"

#include <stdio.h>

extern char __uart_base[];
extern void app2_schedule(uint32_t type);

int app2_init_no_uart() {
	int mon_idx = 8;   // Monitor index
	int ram_idx = 0;   // RAM index
	int uart_idx = 16; // UART index

	// RAM configuration
	s3k_word_t ram_base = 0x80020000;
	s3k_word_t ram_size = 0x10000;
	s3k_word_t ram_perm = S3K_MEM_PERM_RWX; // Read/Write/Execute permissions
	s3k_word_t ram_fuel = 1;
	s3k_word_t ram_slot = 1;
	mem_init(mon_idx, ram_idx, ram_slot, ram_fuel, ram_perm, ram_base, ram_size);

	s3k_word_t uart_base = (s3k_word_t)__uart_base;
	s3k_word_t uart_size = 0x20;
	s3k_word_t uart_perm = S3K_MEM_PERM_RW; // Read/Write permissions
	s3k_word_t uart_fuel = 1;
	// s3k_word_t uart_slot = 2;
	int app2_uart_idx = s3k_mon_mem_derive(mon_idx, uart_idx, uart_fuel, uart_perm, uart_base, uart_size);
	// mem_init(mon_idx, uart_idx, uart_slot, uart_fuel, uart_perm, uart_base, uart_size);

	if (s3k_mon_reg_set(mon_idx, S3K_REG_PC, ram_base) != 0) {
		printf("Failed to set program counter to RAM start\n");
	}
    return app2_uart_idx;
}

int main() {
    // We init app2 without enabling the uart part of memory
    int app2_uart_idx = app2_init_no_uart();
    // Send app2 it's uart capability index
    s3k_mon_reg_set(APP2_MON_IDX, S3K_REG_A0, app2_uart_idx);
    app2_schedule(ROUND_ROBIN);
    puts("Bye from app1");
}
