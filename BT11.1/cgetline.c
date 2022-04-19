#include "stdio.h"
#define CGEN_DEFAULT_IO_BUFF_SIZE
#define CGEN_IO_BUF_SIZE 1024
static char *cgetline(char **lineptr, long n, FILE *inp) {
    char buff[CGEN_IO_BUF_SIZE];
    long idx = 0, len, tmp;
    while (fgets(buff, CGEN_IO_BUF_SIZE, inp)) {
        len = strlen(buff);
        tmp = idx + len + 1;
        if (tmp > n) {
            *lineptr = realloc(*lineptr, tmp);
            if (*lineptr == NULL) {
                return NULL;  // Lỗi cấp phát bộ nhớ
            }
            n = tmp;
        }
        if (idx == 0) {
            *lineptr[0] = 0;
        }
        strcat(*lineptr, buff);
        idx += len;
        if (buff[len - 1] == '\n') {
            break;
        }
    }
    return idx > 0? *lineptr: NULL;
}