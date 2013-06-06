#include "pasteboard.h"
#include <stdio.h>
#include <stdarg.h>

#define ERROR_FILE "/tmp/my_set_pasteboard"

void error(const char* fmt, ...) {
    va_list ap;
    FILE *f = fopen(ERROR_FILE, "a");

    va_start(ap, fmt); 
    vfprintf(f, fmt, ap);
    va_end(ap);

    fclose(f);
}

/**
 * Because working with the X clipboard sucks, I use a call to xsel.
 */
void setPasteboard(PasteboardRef pasteboard, const char* data, size_t len) {
    FILE* fp;
    int status;
    char* cmd = "xsel --clipboard --input";

    fp = popen(cmd, "w");
    if (!fp) {
        error("popen");
    }

    fwrite(data, sizeof(*data), len, fp);

    status = pclose(fp);
    if (-1 == status) {
        error("pclose");
    }
}
