#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

typedef int (*Tremove)(const char *path);

int remove(const char *path) {
    Tremove true_remove;
    true_remove = (Tremove)dlsym(RTLD_NEXT, "remove");
    if(strstr(path, "PROTECT")) {
        return 0;
    }
    true_remove(path);
    return errno;
}
