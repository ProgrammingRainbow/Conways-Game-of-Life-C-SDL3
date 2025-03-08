#include "board.h"

bool board_new(struct Board **board, SDL_Renderer *renderer) {
    *board = calloc(1, sizeof(struct Board));
    if (*board == NULL) {
        fprintf(stderr, "Error in Calloc of New Board.\n");
        return false;
    }
    struct Board *b = *board;

    b->renderer = renderer;
    b->rows = WINDOW_HEIGHT / CELL_SIZE;
    b->columns = WINDOW_WIDTH / CELL_SIZE;

    b->board = calloc(1, sizeof(bool) * (size_t)(b->rows * b->columns));
    if (b->board == NULL) {
        fprintf(stderr, "Error in Calloc of new board.\n");
        return false;
    }

    b->next_board = calloc(1, sizeof(bool) * (size_t)(b->rows * b->columns));
    if (b->next_board == NULL) {
        fprintf(stderr, "Error in Calloc of new board.\n");
        return false;
    }

    board_reset(b);

    return true;
}

void board_free(struct Board **board) {
    if (*board) {
        struct Board *b = *board;

        if (b->board) {
            free(b->board);
            b->board = NULL;
        }
        if (b->next_board) {
            free(b->next_board);
            b->next_board = NULL;
        }

        b->renderer = NULL;

        free(*board);
        *board = NULL;
        b = NULL;

        printf("clean board.\n");
    }
}

void board_reset(struct Board *b) {
    for (int row = 0; row < b->rows; row++) {
        for (int column = 0; column < b->columns; column++) {
            b->board[row * b->columns + column] = (rand() % 2) ? true : false;
        }
    }
}

void board_clear(struct Board *b) {
    for (int row = 0; row < b->rows; row++) {
        for (int column = 0; column < b->columns; column++) {
            b->board[row * b->columns + column] = false;
        }
    }
}

void board_edit(struct Board *b, float x, float y) {
    int column = (int)x / CELL_SIZE;
    int row = (int)y / CELL_SIZE;
    int index = row * b->columns + column;
    b->board[index] = !b->board[index];
}

void board_update(struct Board *b) {
    for (int row = 0; row < b->rows; ++row) {
        for (int column = 0; column < b->columns; ++column) {
            int index = row * b->columns + column;
            int count = 0;
            for (int r = row - 1; r <= row + 1; ++r) {
                for (int c = column - 1; c <= column + 1; ++c) {
                    if (r != row || c != column) {
                        int wrap_r = (r + b->rows) % b->rows;
                        int wrap_c = (c + b->columns) % b->columns;
                        count += b->board[wrap_r * b->columns + wrap_c];
                    }
                }
            }
            if (count == 3) {
                b->next_board[index] = 1;
            } else if (b->board[index] && count == 2) {
                b->next_board[index] = 1;
            } else {
                b->next_board[index] = 0;
            }
        }
    }

    bool *old = b->board;
    b->board = b->next_board;
    b->next_board = old;
}

void board_draw(const struct Board *b) {
    SDL_SetRenderDrawColor(b->renderer, CELL_COLOR);
    SDL_FRect rect = {0, 0, CELL_SIZE - CELL_PADDING, CELL_SIZE - CELL_PADDING};
    for (int row = 0; row < b->rows; row++) {
        rect.y = CELL_SIZE * (float)row;
        for (int column = 0; column < b->columns; column++) {
            rect.x = CELL_SIZE * (float)column;
            if (b->board[row * b->columns + column]) {
                SDL_RenderFillRect(b->renderer, &rect);
            }
        }
    }
}
