#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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
    uint8_t updated;        /* whether the last evolution updated the world */

    uint32_t column_count;  /* amount of rows */
    uint32_t row_count;     /* amount of columns */
};

/* utility function to create a random number
   the rand function is just garbling numbers, but it doesn't matter */
uint32_t rand_int(uint32_t a, uint32_t b) {
    return (rand() % (b - a)) + a;
}

/* gets a cell from its coordinates */
struct cell *get_cell(struct univ *world, uint32_t x, uint32_t y) {
    /* get the starting position of the row and the cell in the row
       (row_size * row_pos) + column_pos
       note that the cells are arranged in a MATRIX, meaning the first row is the top one */
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
    /* initially assume world was not updated */
    world->updated = 0;

    /* go through all cells */
    for (uint32_t i = 0; i < world->cell_count; i++) {
        /* get current cell and neighbors */
        struct cell *cell = &world->cells[i];
        uint32_t neighbors = count_neighbors(cell);

        /* if cell is alive */
        if (cell->alive) {
            /* handle overpopulation */
            if (neighbors > 3) {
                cell->alive = 0;
                world->updated = 1;

            /* handle underpopulation */
            } else if (neighbors < 2) {
                cell->alive = 0;
                world->updated = 1;
            }

        /* if cell is dead */
        } else {
            /* handle reproduction */
            if (neighbors == 3) {
                cell->alive = 1;
                world->updated = 1;
            }
        }
    }
}

/* creates a universe */
struct univ *create(uint32_t size_x, uint32_t size_y, uint32_t alive) {
    /* allocate universe */
    struct univ *world = (struct univ *)malloc(sizeof(struct univ));

    /* initailize members */
    world->cell_count = size_x * size_y;
    world->column_count = size_x;
    world->row_count = size_y;
    world->updated = 1;
    world->cells = (struct cell *)calloc(world->cell_count, sizeof(struct cell));

    /* initialize cells */
    for (uint32_t i = 0; i < world->cell_count; i++) {
        /* get cell */
        struct cell *cell = &world->cells[i];

        /* determine coordinates */
        uint32_t y = i / world->column_count;
        uint32_t x = i % world->column_count;

        /* initailize members */
        cell->x = x;
        cell->y = y;
    }

    /* make random cells alive */
    for (uint32_t i = 0; i < alive && i < world->cell_count; i++) {
        /* store the cell to make alive here */
        struct cell *cell;

        /* find a cell */
        do {
            /* find random cell */
            cell = world->cells[rand_int(0, world->cell_count-1)];

        /* keep repeating until alive cell found */
        } while (cell->alive);

        /* make cell alive */
        cell->alive = 1;
    }
}