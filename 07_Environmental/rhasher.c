#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <rhash.h>

#include "config.h"

#ifdef HAVE_READLINE
#include <readline/readline.h>
#define GET_STRING(out_line, out_len) (out_line = readline(NULL)) != NULL
#else
#define GET_STRING(out_line, out_len) getline(&out_line, &out_len, stdin) != -1
#endif

int main() {
    rhash_library_init();
    const unsigned char digest[64];
    char output[130];

    char* line = NULL;
    size_t line_size = 0;
    while (printf("> "), GET_STRING(line, line_size)) {
        char* hash_name = strtok(line, " \n");
        if (hash_name == NULL) {
            continue;
        }

        char* second_word = strtok(NULL, " \n");
        if (second_word == NULL) {
            fprintf(stderr, "No string/file to hash!\n");
            continue;
        }

        int hash_representation;
        if (isupper(hash_name[0])) {
            hash_representation = RHPR_HEX;
        } else {
            hash_representation = RHPR_BASE64;
        }

        for (int i = 0; hash_name[i] != '\0'; ++i) {
            hash_name[i] = tolower(hash_name[i]);
        }

        int hash_algorithm;
        if (strcmp(hash_name, "md5") == 0) {
            hash_algorithm = RHASH_MD5;
        } else if (strcmp(hash_name, "tth") == 0) {
            hash_algorithm = RHASH_TTH;
        } else if (strcmp(hash_name, "sha1") == 0) {
            hash_algorithm = RHASH_SHA1;
        } else if (strcmp(hash_name, "sha256") == 0) {
            hash_algorithm = RHASH_SHA256;
        } else {
            fprintf(stderr, "Wrong hash algorithm: %s\n", hash_name);
            continue;
        }

        if (second_word[0] != '"') {
            if (rhash_file(hash_algorithm, second_word, digest) < 0) {
                fprintf(stderr, "Wrong file: %s\n", second_word);
                continue;
            }
            rhash_print_bytes(output, digest, rhash_get_digest_size(hash_algorithm), hash_representation);
            printf("%s\n", output);
        } else {
            ++second_word;
            if (rhash_msg(hash_algorithm, second_word, strlen(second_word), digest) < 0) {
                fprintf(stderr, "Can't hash string: %s\n", second_word);
                continue;
            }
            rhash_print_bytes(output, digest, rhash_get_digest_size(hash_algorithm), hash_representation);
            printf("%s\n", output);
        }
    }
    free(line);
    return 0;
}
