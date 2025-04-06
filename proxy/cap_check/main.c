#define _GNU_SOURCE
#include <stdio.h>
#include <sys/capability.h>
#include <string.h>
#include <errno.h>

int main() {
    struct __user_cap_header_struct cap_hdr = {
        .version = _LINUX_CAPABILITY_VERSION_3,
        .pid = 0 // 0 = self
    };
    struct __user_cap_data_struct cap_data[2]; // For 64 capabilities

    memset(cap_data, 0, sizeof(cap_data));

    if (capget(&cap_hdr, cap_data) < 0) {
        perror("capget");
        return 1;
    }

    printf("Effective capabilities (lower 32): 0x%x\n", cap_data[0].effective);
    printf("Effective capabilities (upper 32): 0x%x\n", cap_data[1].effective);

    // Example: check CAP_SYS_ADMIN (index 21)
    if (cap_data[0].effective & (1 << CAP_SYS_ADMIN)) {
        printf("CAP_SYS_ADMIN is present\n");
    } else {
        printf("CAP_SYS_ADMIN is NOT present\n");
    }

    return 0;
}
