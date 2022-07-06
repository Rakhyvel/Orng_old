#ifndef POSITION_H
#define POSITION_H

// Used to store where a token/ast/symbol comes from in a file
typedef struct position {
    char* filename;
    int start_line;
    int start_span;
    int end_line;
    int end_span;
} Position;

#define invalid_pos \
    ((struct position) { NULL, 0, 0, 0, 0})

Position merge(Position a, Position b);

#endif