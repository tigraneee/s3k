#define APP_RAM_SIZE 0x10000
#define UART_SIZE 0x20

#define APP2_RAM_BASE 0x80020000

// TODO: move these definitions to libs3k?
#define NUM_MONITOR_FUEL 8
#define NUM_TIME_FUEL 32
#define NUM_IPC_FUEL 16
#define NUM_MEM_FUEL 16
#define NUM_TIME_SLOT 32

// Index of proc 1's monitor capability over proc 2
#define APP2_MON_IDX NUM_MONITOR_FUEL
// Index of the initial time slice capability for hart 2, initial owner of this capability is proc 1
#define HART1_TSL_IDX 0
#define HART2_TSL_IDX NUM_TIME_FUEL

// Index of memory capability for the ram / uart owned by proc 1
#define RAM_IDX 0
#define UART_IDX NUM_MEM_FUEL

#define ROOT_IPC_IDX 0

// Schedule types
#define ROUND_ROBIN 1
#define PARALLEL 2

void mem_init(s3k_word_t mon_idx, s3k_word_t idx, s3k_word_t slot, s3k_word_t cfree, s3k_word_t perm, s3k_word_t base,
	      s3k_word_t size);

void delay(int time);

void default_trap_handler();
void setup_trap(void (*trap_handler)(void), void * trap_stack_base, s3k_word_t trap_stack_size);
