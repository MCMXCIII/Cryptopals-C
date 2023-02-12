#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CIPHER_LEN 48

char hex_to_char(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

void hex_decode(const char *hex, unsigned char *out) {
    int i, j;
    for (i = j = 0; hex[j] && hex[j + 1]; i++, j += 2) {
        out[i] = (hex_to_char(hex[j]) << 4) | hex_to_char(hex[j + 1]);
    }
    out[i] = '\0';
}

int score_text(const char *text) {
    int score = 0;
    int length = strlen(text);
    int i;
    for (i = 0; i < length; i++) {
        char c = tolower(text[i]);
        if (c == 'e' || c == 't' || c == 'a' || c == 'o' || c == 'i' || c == 'n') {
            score++;
        }
    }
    return score;
}
char single_xor_decrypt(const char *ciphertext, char *plaintext) {
    unsigned char data[CIPHER_LEN];
    hex_decode(ciphertext, data);

    int best_score = -1;
    char best_key = 0;
    char best_plaintext[CIPHER_LEN];
    memset(best_plaintext, 0, CIPHER_LEN);

    int i;
    for (i = 0; i < 256; i++) {
        char key = i;
        int j;
        for (j = 0; j < CIPHER_LEN / 2; j++) {
            plaintext[j] = data[j] ^ key;
        }
        int score = score_text(plaintext);
        if (score > best_score) {
            best_score = score;
            best_key = key;
            strcpy(best_plaintext, plaintext);
        }
    }
    strcpy(plaintext, best_plaintext);
    return best_key;
}
int main(int argc, char *argv[]) {
    char plaintext[CIPHER_LEN];
    memset(plaintext, 0, CIPHER_LEN);

    char key = single_xor_decrypt("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", plaintext);
    printf("Key: %c\nPlaintext: %s\n", key, plaintext);

    return 0;
}

