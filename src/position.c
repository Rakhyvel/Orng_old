#include "position.h"
#include <stdlib.h>

Position merge(Position a, Position b)
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