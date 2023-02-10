#include <stdio.h>
#include <stdlib.h>

void xor_buffers(const unsigned char* buf1, const unsigned char* buf2, unsigned char* result, int len) {
    for (int i = 0; i < len; i++) {
        result[i] = buf1[i] ^ buf2[i];
    }
}

int main(int argc, char* argv[]) {
    const unsigned char buf1[] = {0x1c, 0x01, 0x11, 0x00, 0x1f, 0x01, 0x01, 0x00, 0x06, 0x1a, 0x02, 0x4b, 0x53, 0x53, 0x50, 0x09, 0x18, 0x1c};
    const unsigned char buf2[] = {0x68, 0x69, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62, 0x75, 0x6c, 0x6c, 0x27, 0x73, 0x20, 0x65, 0x79, 0x65};
    unsigned char result[19];
    int len = sizeof(buf1) / sizeof(unsigned char);

    xor_buffers(buf1, buf2, result, len);

    for (int i = 0; i < len; i++) {
        printf("%02x", result[i]);
    }
    printf("\n");

    return 0;
}

