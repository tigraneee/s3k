#include "s3k.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

// Receives ipc capability 'client' from app1
int main(int client) {
    puts("Hello from app2");
    printf("Received client idx %d\n", client);
    int count = 0;
    s3k_msg_t msg;
    int ret;
    while(1) {
        count++;
        snprintf((char*)msg.data, sizeof(msg.data), "ping %d", count);
        do {
            // Call server
            // Might fail because not enough service time is left in our major frame.
            msg.capty = 0;
            msg.capidx = 0;
            ret = s3k_ipc_call(client, &msg);
            if (ret) {
                printf(">app2 ret: %d\n", ret);
            }
        } while(ret);
        puts((char*)msg.data);
        delay(10000000);
    }
    return 0;
}
