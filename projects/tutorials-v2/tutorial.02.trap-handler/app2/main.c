#include "s3k.h"
#include "utils.h"
#include <stdio.h>

extern char __uart_base[]; // UART base address

// Enable memory at mem capability idx
void setup_uart(int idx) {
    s3k_word_t base = (s3k_word_t)__uart_base;
	s3k_word_t size = 0x20;
	s3k_word_t slot = 2;
	s3k_word_t perm = S3K_MEM_PERM_RW; // Read/Write permissions
	s3k_word_t addr = s3k_pmp_napot_encode(base, size);
	s3k_mem_pmp_set(idx, slot, perm, addr);
    s3k_sync();
    puts("uart set up!");
    return;
}

int uart_idx;
char trap_stack[1024];

void trap_handler(void) __attribute__((interrupt("machine")));
void trap_handler(void) {
    setup_uart(uart_idx);
    default_trap_handler();
}

void main(int idx) {
    uart_idx = idx;
    // Don't set up uart yet
    // setup_uart(idx);
    setup_trap(trap_handler, trap_stack, 1024);
    puts("Hello world from app2!");
}
