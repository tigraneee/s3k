#include <stdio.h>

#include "s3k.h"
#include "utils.h"

// See common/init2.c
extern void app2_init(void);

/* 
 * Init and launch app2 on hart 2
 */
int main() {
    puts("Initializing app2");
    app2_init();
    // Grant time slice capability on hart 2 to app 2
    // Granting a time slice capability does not automatically enable it
    s3k_mon_tsl_grant(APP2_MON_IDX, HART2_TSL_IDX);
    // Enable the time slot
    s3k_mon_tsl_set(APP2_MON_IDX, HART2_TSL_IDX, true);
    // s3k_cap_tsl_t cap_tsl;
    // s3k_mon_tsl_get(APP2_MON_IDX, HART2_TSL_IDX, &cap_tsl);
    // Resume app 2
    puts("Resume app2");
    s3k_mon_resume(APP2_MON_IDX);
    puts("Bye from app1");
}
