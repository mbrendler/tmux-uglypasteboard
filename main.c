#include "pasteboard.h"
#include <string.h>


int main(int argc, char **argv) {
    const char* content = "hehe";

    if (argc > 1) {
        content = argv[1];
    }

    setPasteboard(0, content, strlen(content));

    return 0;
}
