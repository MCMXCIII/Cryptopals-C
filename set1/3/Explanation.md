### Headers
```
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CIPHER_LEN 48
```

These are just Header files with a macro definition. <stdio.h> is the standard input/output header, 'string.c' is the string header, and 'ctype.h' is the character type header. The Macro 'CIPHER_LEN' defines the lenthg of the hex encoded string.


```
char hex_to_char(char c){
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 0;
}
```
This function 'hex_to_char' takes a singe hexadecimal character as input, and returns it's corresponing decimal respresentation.

```
void hex_decode(const char *hex, unsigned char *out) {
	int i, j;
	for (i = j = 0; hex[j] && hex[j + 1]; i++, j += 2) {
		out[i] = (hex_to_char(hex[j]) << 4) | hex_to_char(hex[j + 1]);
	}
	out[i] = '\0';
}
```

This function 'hex_decode' takes a hex encoded string and  an array 'out' as input, and converts the hex encoded string into a it's corresponding binary representation, stroed in the 'out' array. The conversion works by reading two hex characters at a time. using 'hex_to_char' to convert them to binary, and combingin them into a single byte.

```
int scroe_text(const char *text) {
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
```

This function 'score_text' takes a text string as input, and returns a score based on how english-like the text is. The Scores is calculated by counting the number of common English letter (in this case, 'e', 't', 'a', 'o', 'i', and 'n') in the text, and returning that count as the score.

```
char single_xor_decrypt(const char *ciphertext, char *plaintext) {
	unsigned char data[CIPHER_LEN];
	hex_decode(ciphertext, data);
	
	int best_score = -1;
	char best_key = 0;
	char best_plaintext[CIPHER_LEN];
	memset(best_plaintext, 0, CIPHER_LEN);
	
	int i;
```
