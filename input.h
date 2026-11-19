#ifndef INPUT_H
#define INPUT_H

typedef enum {
    INPUT_OK,
    INPUT_BAD_FORMAT,  /* the line did not contain exactly four integers */
    INPUT_EOF          /* standard input was closed */
} InputStatus;

/* Reads one line holding four integers: r1 c1 r2 c2. */
InputStatus input_read_move(int *r1, int *c1, int *r2, int *c2);

/* Reads a yes/no answer. Returns 1 for yes, 0 for no, -1 on end of input. */
int input_read_yes_no(void);

#endif
