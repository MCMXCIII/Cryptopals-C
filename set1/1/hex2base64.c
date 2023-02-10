#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char b64_table[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

int hex_to_dec(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

void hex_to_bin(const char* hex, char* bin) {
    for (int i = 0; i < strlen(hex); i += 2) {
        bin[i / 2] = (hex_to_dec(hex[i]) << 4) | hex_to_dec(hex[i + 1]);
    }
}

void base64_encode(const char* bin, int len, char* b64) {
    for (int i = 0, j = 0; i < len; i += 3, j += 4) {
        b64[j] = b64_table[bin[i] >> 2];
        b64[j + 1] = b64_table[((bin[i] & 0x03) << 4) | (bin[i + 1] >> 4)];
        b64[j + 2] = b64_table[((bin[i + 1] & 0x0f) << 2) | (bin[i + 2] >> 6)];
        b64[j + 3] = b64_table[bin[i + 2] & 0x3f];
    }
}

int main() {
    const char* hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    int len = strlen(hex) / 2;
    char bin[len];
    char b64[len * 4 / 3 + 4];

    hex_to_bin(hex, bin);
    base64_encode(bin, len, b64);

    printf("%s\n", b64);

    return 0;
}

