#include <stdio.h>

#include "s3k.h"
#include "utils.h"

int main() {
    puts("Hello world from app2");
    // Delete app2's time slice capability on hart 2
    s3k_tsl_delete(HART2_TSL_IDX);
    // Yield to scheduler
    s3k_sync();
    puts("Gone forever");
}
