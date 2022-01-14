#include <stdio.h>
#include <stdlib.h>

void show_help() {
    puts("range help");
    puts("All params are integer");
    puts("./range N     : [0, 1,     ..., N - 1]");
    puts("./range M N   : [M, M + 1, ..., N - 1]");
    puts("./range M N S : [M, M + S, ..., N - 1]");
}

int main(int argc, char** argv) {
    if (argc == 1) {
        show_help();
        return 0;
    }

    int m = 0, n = 0, s = 1;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    if (argc > 2) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }
    if (argc > 3) {
        s = atoi(argv[3]);
    }
    if (argc > 4) {
        return 0;
    }

    int i = 0;
    for (i = m; i < n; i += s) {
        printf("%d\n", i);
    }

    return 0;
}