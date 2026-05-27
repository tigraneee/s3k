#include "s3k.h"

#include <stdio.h>

extern char __uart_base[]; // UART base address

void mem_init(s3k_word_t mon_idx, s3k_word_t idx, s3k_word_t slot, s3k_word_t cfree, s3k_word_t perm, s3k_word_t base,
	      s3k_word_t size)
{
	idx = s3k_mon_mem_derive(mon_idx, idx, cfree, perm, base, size);
	if (idx < 0) {
		printf("Failed to derive memory capability %lx\n", base);
		return;
	}

	s3k_word_t addr = s3k_pmp_napot_encode(base, size);
	int err = s3k_mon_mem_pmp_set(mon_idx, idx, slot, perm, addr);
	if (err < 0) {
		printf("Failed to set PMP for derived memory %lx, err=%d\n", base, err);
		return;
	}
}

void delay(int n) {
    volatile int x = 0;
    for (int i = 0; i < n; i++) {
        x++;
    }
    return;
}

void setup_trap(void (*trap_handler)(void), void * trap_stack_base, uint64_t trap_stack_size)
{
	// Sets the trap handler
	s3k_vreg_set(S3K_VREG_TPC, (uint64_t)trap_handler);
	// Set the trap stack
	s3k_vreg_set(S3K_VREG_TSP, ((uint64_t)trap_stack_base) + trap_stack_size);
}

void default_trap_handler(void) {
	s3k_word_t epc = s3k_vreg_get(S3K_VREG_EPC);
	s3k_word_t esp = s3k_vreg_get(S3K_VREG_ESP);
	s3k_word_t ecause = s3k_vreg_get(S3K_VREG_ECAUSE);
	s3k_word_t eval = s3k_vreg_get(S3K_VREG_EVAL);

	printf("error info:\n- epc: 0x%lx\n- esp: 0x%lx\n- ecause: 0x%lx\n- eval: 0x%lx\n",
			   epc, esp, ecause, eval);
	printf("restoring pc and sp\n\n");
}
