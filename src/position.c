// © 2021-2022 Joseph Shimel. All rights reserved.
// Represents a position in a file

#include "position.h"
#include <stdlib.h>

// Takes two positions and Position_Merges them so that the resulting position starts where the earlier position started, and ends where the later position ended
Position Position_Merge(Position a, Position b)
{
    int start_line = 0;
    int start_span = 0;
    int end_line = 0;
    int end_span = 0;

    if (a.start_line == b.start_line) {
        start_line = a.start_line;
        start_span = min(a.start_span, b.start_span);
    } else if (a.start_line < b.start_line) {
        start_line = a.start_line;
        start_span = a.start_span;
    } else if (a.start_line > b.start_line) {
        start_line = b.start_line;
        start_span = b.start_span;
    }

    if (a.end_line == b.end_line) {
        end_line = a.end_line;
        end_span = max(a.end_span, b.end_span);
    } else if (a.end_line > b.end_line) {
        end_line = a.end_line;
        end_span = a.end_span;
    } else if (a.end_line < b.end_line) {
        end_line = b.end_line;
        end_span = b.end_span;
    }

    return (Position) {
        a.filename,
        start_line,
        start_span,
        end_line,
        end_span
    };
}