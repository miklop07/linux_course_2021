#include <stdio.h>
#include <errno.h>

int drop_errno() {
    if (errno) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc > 3) {
        fprintf(stderr, "Too many arguments\n");
        return -1;
    }
    if (argc < 3) {
        fprintf(stderr, "Not enougth arguments\n");
        return -1;
    }

    FILE* in;
    if (!(in = fopen(argv[1], "r"))) {
        return errno;
    }

    FILE* out;
    if (!(out = fopen(argv[2], "w"))) {
        fclose(in);
        if (drop_errno()) {
            perror("fclose error");
            return errno;
        }
        return errno;
    }

    char c;
    while((c = fgetc(in)) != EOF){
        if(fputc(c, out) == EOF){
            fclose(in);
            if (drop_errno()) {
                perror("fclose error");
                return errno;
            }
            fclose(out);
            if (drop_errno()) {
                perror("fclose error");
                return errno;
            }
            remove(argv[2]);
            if (drop_errno()) {
                perror("remove error");
                return errno;
            }
            return errno;
        }
    }
    if (errno) {
        fclose(in);
        if (drop_errno()) {
            perror("fclose error");
            return errno;
        }
        fclose(out);
        if (drop_errno()) {
            perror("fclose error");
            return errno;
        }
        remove(argv[2]);
        if (drop_errno()) {
            perror("remove error");
            return errno;
        }
        return errno;
    }

    fclose(in);
    if (drop_errno()) {
        perror("fclose error");
        return errno;
    }
    fclose(out);
    if (drop_errno()) {
        perror("fclose error");
        return errno;
    }
    remove(argv[1]);
    if (drop_errno()) {
        perror("remove error");
        return errno;
    }
    return errno;

    return 0;
}