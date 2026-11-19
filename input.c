#include "input.h"

#include <stdio.h>
#include <string.h>

#define LINE_SIZE 128

/* Reads a full line into buf. Returns 0 on end of input. Discards overlong input. */
static int read_line(char *buf, size_t size)
{
    if (fgets(buf, (int)size, stdin) == NULL)
        return 0;

    if (strchr(buf, '\n') == NULL) {
        /* The line was longer than the buffer: drop the rest of it. */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
    return 1;
}

InputStatus input_read_move(int *r1, int *c1, int *r2, int *c2)
{
    char line[LINE_SIZE];
    char extra;

    if (!read_line(line, sizeof line))
        return INPUT_EOF;

    /* Exactly four integers; anything after them makes the move invalid. */
    if (sscanf(line, "%d %d %d %d %c", r1, c1, r2, c2, &extra) != 4)
        return INPUT_BAD_FORMAT;

    return INPUT_OK;
}

int input_read_yes_no(void)
{
    char line[LINE_SIZE];

    for (;;) {
        if (!read_line(line, sizeof line))
            return -1;
        if (line[0] == 'y' || line[0] == 'Y')
            return 1;
        if (line[0] == 'n' || line[0] == 'N')
            return 0;
        printf("Please answer y or n: ");
        fflush(stdout);
    }
}
