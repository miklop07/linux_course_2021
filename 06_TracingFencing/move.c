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
        perror("fopen in error");
        return errno;
    }

    FILE* out;
    if (!(out = fopen(argv[2], "w"))) {
        perror("fopen out error");
        fclose(in);
        if (drop_errno()) {
            perror("fclose in error");
            return errno;
        }
        return errno;
    }

    char c;
    while((c = fgetc(in)) != EOF){
        if(fputc(c, out) == EOF){
            perror("fputc error");
            fclose(in);
            if (drop_errno()) {
                perror("fclose in error");
                return errno;
            }
            fclose(out);
            if (drop_errno()) {
                perror("fclose out error");
                return errno;
            }
            remove(argv[2]);
            if (drop_errno()) {
                perror("remove out error");
                return errno;
            }
            return errno;
        }
    }
    if (errno) {
        perror("fgetc error");
        fclose(in);
        if (drop_errno()) {
            perror("fclose in error");
            return errno;
        }
        fclose(out);
        if (drop_errno()) {
            perror("fclose out error");
            return errno;
        }
        remove(argv[2]);
        if (drop_errno()) {
            perror("remove out error");
            return errno;
        }
        return errno;
    }

    fclose(in);
    if (drop_errno()) {
        perror("fclose in error");
        return errno;
    }
    fclose(out);
    if (drop_errno()) {
        perror("fclose out error");
        return errno;
    }
    remove(argv[1]);
    if (drop_errno()) {
        perror("remove in error");
        return errno;
    }
    return errno;

    return 0;
}