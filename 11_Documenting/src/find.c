#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <libintl.h>

#define _(string) gettext(string)

char* str_tolower(char* str) {
    for (int i = 0; i < strlen(str); ++i) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("find", "po");
    textdomain("find");

    printf(_("Guess number from 1 to 100\n"));
    int middle;
    int left_bound = 1, right_bound = 100;
    while (left_bound < right_bound) {
        middle = (int)((right_bound + left_bound) / 2);
        printf(_("Number greater, than %d? (yes/no)\n"), middle);

        char* answer;
        size_t answer_len = 0;
        int res = getline(&answer, &answer_len, stdin);
        puts(str_tolower(answer));
        if (strcmp(str_tolower(answer), _("yes\n")) == 0) {
            left_bound = ++middle;
        } else if (strcmp(str_tolower(answer), _("no\n")) == 0) {
            right_bound = middle;
        } else {
            printf(_("Wrong input!\n"));
        }
        free(answer);       
    }
    printf(_("The number is %d!\n"), middle);
    return 0;
}