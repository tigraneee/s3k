#include "s3k.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

// See common/init2.c
extern void app2_init(void);
extern void app2_schedule(uint32_t type);

int main() {
    puts("Initializing app2");
    app2_init();
    
    // Create ipc capabilities
    // Leave space for deriving the client capability
    s3k_fuel_t fuel = 2;
    // Synchronous bidirectional ipc
    s3k_ipc_mode_t mode = S3K_IPC_MODE_BSYNC;
    // Make sender yield its remaining major frame for the receiver
    s3k_ipc_flag_t flag = S3K_IPC_FLAG_YIELD;
    
    // sink/server capability
    int server = s3k_ipc_derive(ROOT_IPC_IDX, fuel, mode, flag);
    // source/client capability
    int client = s3k_ipc_derive(server, 1, mode, flag);
    printf("server idx: %d, client idx: %d\n", server, client);

    // Send the client capability index to app2
    s3k_mon_reg_set(APP2_MON_IDX, S3K_REG_A0, client);
    // Transfer client capability to app2
    s3k_mon_ipc_grant(APP2_MON_IDX, client);
    // Schedule and start app2
    app2_schedule(ROUND_ROBIN);

    int ret;
    s3k_msg_t msg;
    while(1) {
        memcpy(msg.data, "pong", 5);
        do {
            // Reply to client, also receive a new message from client
            msg.capty = 0;
            msg.capidx = 0;
            ret = s3k_ipc_replyrecv(server, &msg);
            if (ret) {
                printf(">app1 ret: %d\n", ret);
            }
        } while(ret);
        puts((char*)msg.data);
        delay(10000000);
    }

    return 0;
}
