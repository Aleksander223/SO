#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    const char msg[] = "Hello ";
    write(1, msg, strlen(msg));
    write(1, argv[1], strlen(argv[1]));
    write(1, "\n", strlen("\n"));
    return 0;
}
