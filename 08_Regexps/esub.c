#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>

void push_back(char** result, char c, int* result_size, int* result_capacity) {
    if (*result_size < *result_capacity - 1) {
        (*result)[*result_size] = c;
        (*result)[*result_size + 1] = '\0';
        *result_size += 1;
    } else {
        *result_capacity *= 2;
        *result = realloc(*result, *result_capacity * sizeof(char));
        push_back(result, c, result_size, result_capacity);
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "Params needed\n");
        return -1;
    }
    if (argc == 2) {
        fprintf(stderr, "Substitution and string params needed\n");
        return -1;
    }
    if (argc == 3) {
        fprintf(stderr, "String param needed\n");
        return -1;
    }
    if (argc > 4) {
        fprintf(stderr, "To many params\n");
        return -1;
    }


    char* regexp = argv[1];
    char* substitution = argv[2];
    char* string = argv[3];

    if (substitution[strlen(substitution) - 1] == '\\') {
        fprintf(stderr, "Wrong regexp: \\ at the end of substitution\n");
        return -1;
    }

    char error_string[100];

    regex_t r;
    const int pm_len = 10;
    regmatch_t pm[pm_len];
    int reg_status;

    if (reg_status = regcomp(&r, regexp, REG_EXTENDED)) {
        regerror(reg_status, &r, error_string, sizeof(error_string));
        fprintf(stderr, "Regex compile error: %s\n", error_string);
        return -1;
    }

    if (reg_status = regexec(&r, string, pm_len, pm, 0)) {
        if(reg_status == REG_NOMATCH) {
            fprintf(stderr, "No regexp match\n");
        } else {
            regerror(reg_status, &r, error_string, sizeof(error_string));
            fprintf(stderr, "Regex compile error: %s\n", error_string);
        }
        regfree(&r);
        return -1;
    }

    const int buffsize = 100;
    char* result = malloc(buffsize*sizeof(char));
    result[0] = '\0';
    int result_size = 0;
    int result_capacity = buffsize;

    char state = 'd';
    for (int i = 0; i < pm[0].rm_so; ++i) {
        push_back(&result, string[i], &result_size, &result_capacity);
    }
    for (int i = 0; i < strlen(substitution); ++i) {
        if (state == 'd' && substitution[i] != '\\') {
            push_back(&result, substitution[i], &result_size, &result_capacity);
            continue;
        }

        if (state == 'd') {
            state = '\\';
            continue;
        }

        if (state == '\\') {
            if (isdigit(substitution[i])) {
                int digit = substitution[i] - '0';
                if (pm[digit].rm_so == -1 || pm[digit].rm_eo == -1) {
                    fprintf(stderr, "Invalid group \\%d\n", digit);
                    regfree(&r);
                    return -1;
                }

                for (int j = pm[digit].rm_so; j < pm[digit].rm_eo; ++j) {
                    push_back(&result, string[j], &result_size, &result_capacity);
                }
            } else {
                push_back(&result, substitution[i], &result_size, &result_capacity);
            }
            state = 'd';
        }
    }
    for (int i = pm[0].rm_eo; i < strlen(string); ++i) {
        push_back(&result, string[i], &result_size, &result_capacity);
    }
    puts(result);
    regfree(&r);
    return 0;
}
