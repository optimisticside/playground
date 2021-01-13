#include <stdint.h>

/* constant defenition */
#define CYCLE_TIME  1000    /* amount of ms for each cycle to take place */

/* cell */
struct cell {
    uint32_t x;     /* x value of cell */
    uint32_t y;     /* y value of cell */
    uint8_t alive;  /* whether or not the cell alive */
};

/* universe */
struct univ {
    struct cell *cells;     /* cells in the universe */
    uint32_t cell_count;    /* amount of cells */

    uint32_t column_count;  /* amount of rows */
    uint32_t row_count;     /* amount of columns */
};

/* gets a cell from its coordinates */
struct cell *get_cell(struct univ *world, uint32_t x, uint32_t y) {
    /* get the starting position of the row and the cell in the row
       (row_size * row_pos) + column_pos */
    return world->cells[world->column_count * x + y];
}

/* ensures a coordinate exists */
uint8_t ensure_bounds(struct univ *world, uint32_t x, uint32_t y) {
    /* makes sure that the x is less than the row size (same as amount of columns)
       and that the y is less than the column size (same as amount of rows) */
    return x <= world->column_count && y <= world->row_count;
}

/* counts the amount of neighbors a cell has */
uint32_t count_neighbors(struct univ *world, struct cell *cell) {
    /* keep track of count */
    uint32_t count = 0;

    /* top middle */
    if (ensure_bounds(world, cell->x, cell->y-1) && get_cell(cell->x, cell->y-1)->alive) count++;
    /* bottom middle */
    if (ensure_bounds(world, cell->x, cell->y+1) && get_cell(cell->x, cell->y+1)->alive) count++;
    /* middle left */
    if (ensure_bounds(world, cell->x-1, cell->y) && get_cell(cell->x-1, cell->y)->alive) count++;
    /* middle right */
    if (ensure_bounds(world, cell->x+1, cell->y) && get_cell(cell->x+1, cell->y)->alive) count++;

    /* top left */
    if (ensure_bounds(world, cell->x-1, cell->y-1) && get_cell(cell->x-1, cell->y-1)->alive) count++;
    /* bottom left */
    if (ensure_bounds(world, cell->x-1, cell->y+1) && get_cell(cell->x-1, cell->y+1)->alive) count++;
    /* top right */
    if (ensure_bounds(world, cell->x+1, cell->y-1) && get_cell(cell->x+1, cell->y-1)->alive) count++;
    /* bottom right */
    if (ensure_bounds(world, cell->x+1, cell->y+1) && get_cell(cell->x+1, cell->y+1)->alive) count++;

    /* return count */
    return count;
}

/* evolves the universe */
void evolve(struct univ *world) {
    /* go through all cells */
    for (uint32_t i = 0; i < world->cell_count; i++) {
        /* get current cell and neighbors */
        struct cell *cell = &world->cells[i];
        uint32_t neighbors = count_neighbors(cell);

        /* check if cell is alive */
        if (cell->alive) {
            /* handle overpopulation */
            if (neighbors > 3) {
                cell->alive = 0;

            /* handle underpopulation */
            } else if (neighbors < 2) {
                cell->alive = 0;
            }
        } else {
            /* handle reproduction */
            if (neighbors == 3) {
                cell->alive = 1;
            }
        }
    }
}