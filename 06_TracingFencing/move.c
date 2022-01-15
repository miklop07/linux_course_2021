#include <stdio.h>
#include <errno.h>

int drop_errno() {
    if (errno) {
        return errno;
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

    int prev_errno;

    FILE* out;
    if (!(out = fopen(argv[2], "w"))) {
        perror("fopen out error");
        prev_errno = errno;
        fclose(in);
        if (drop_errno()) {
            perror("fclose in error");
            return prev_errno;
        }
        return prev_errno;
    }

    char c;
    while((c = fgetc(in)) != EOF) {
        if(fputc(c, out) == EOF){
            perror("fputc error");
            fclose(in);
            prev_errno = errno;
            if (drop_errno()) {
                perror("fclose in error");
                remove(argv[2]);
                if (drop_errno()) {
                    perror("remove error");
                    return prev_errno;
                }
                return prev_errno;
            }
            fclose(out);
            if (drop_errno()) {
                perror("fclose out error");
                remove(argv[2]);
                if (drop_errno()) {
                    perror("remove error");
                    return prev_errno;
                }
                return prev_errno;
            }
            remove(argv[2]);
            if (drop_errno()) {
                perror("remove out error");
                return prev_errno;
            }
            return prev_errno;
        }
    }
    if (errno) {
        prev_errno = errno;
        perror("fgetc error");
        fclose(in);
        if (drop_errno()) {
            perror("fclose in error");
            remove(argv[2]);
            if (drop_errno()) {
                perror("remove error");
                return prev_errno;
            }
            return prev_errno;
        }
        fclose(out);
        if (drop_errno()) {
            perror("fclose out error");
            remove(argv[2]);
            if (drop_errno()) {
                perror("remove error");
                return prev_errno;
            }
            return prev_errno;
        }
        remove(argv[2]);
        if (drop_errno()) {
            perror("remove out error");
            return prev_errno;
        }
        return prev_errno;
    }

    fclose(in);
    prev_errno = errno;
    if (drop_errno()) {
        perror("fclose in error");
        remove(argv[2]);
        if (drop_errno()) {
            perror("remove error");
            return prev_errno;
        }
        return prev_errno;
    }
    fclose(out);
    prev_errno = errno;
    if (drop_errno()) {
        perror("fclose out error");
        remove(argv[2]);
        if (drop_errno()) {
            perror("remove error");
            return prev_errno;
        }
        return prev_errno;
    }
    remove(argv[1]);
    prev_errno = errno;
    if (drop_errno()) {
        perror("remove in error");
        return prev_errno;
    }

    return 0;
}