/*
 *  Chap4Project1/src/main.c  
 *
 *  Programming Project Chap.4 Project 1
 *  Sudoku solution validator
 * 
 *  108590002 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

const int solution[9][9] = {{6, 2, 4, 5, 3, 9, 1, 8, 7},
                            {5, 1, 9, 7, 2, 8, 6, 3, 4},
                            {8, 3, 7, 6, 1, 4, 2, 9, 5},
                            {1, 4, 3, 8, 6, 5, 7, 2, 9},
                            {9, 5, 8, 2, 4, 7, 3, 6, 1},
                            {7, 6, 2, 3, 9, 1, 4, 5, 8},
                            {3, 7, 1, 9, 5, 6, 8, 4, 2},
                            {4, 9, 6, 1, 8, 2, 5, 7, 3},
                            {2, 8, 5, 4, 7, 3, 9, 1, 6}};

/* structure for passing data to threads */
typedef struct {
    int row;
    int col;
} params_t;

int sudoku[9][9];

void usage(char *programName)
{
    printf("Usage:\n\t%s\n", programName);
}

void printSudoku(int sudoku[9][9]) {
    printf("┌───┬───┬───┬┬───┬───┬───┬┬───┬───┬───┐\n");
    for (int r=0; r<9; ++r) {
        for (int c=0; c<9; ++c) {
            printf("│ %d ", sudoku[r][c]);
            if (c != 8 && c%3 == 2) printf("│");
        }
        if (r == 8) printf("│\n");
        else if (r%3 == 2) printf("│\n├===========┼┼===========┼┼===========┤\n");
        else printf("│\n├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤\n");

    }
    printf("└───┴───┴───┴┴───┴───┴───┴┴───┴───┴───┘\n");
}

void* checkRow(void* args) {
    // Get the row that need to check
    params_t *params = args;
    int row = params->row;
    uint64_t flag = 0x000;  // Here, we use uint64, since size(void*) = 8 bytes

    /* store 9 flags in bit
     * example:
     *  let sudoku[row][0] = 6
     *  then flag = flag or 1 << (6-1) (=100000)
     *  that is    000000000
     *          or 000100000
     *          ------------
     *      flag = 000100000
     * 
     *  also let sudoku[row][1] = 2
     *  then flag = flag or 1 << (2-1) (=10)
     *  that is    000100000
     *          or 000000010
     *          ------------
     *      flag = 000100010
     * 
     * if the row is valid, then flag = 111111111 = 511 = 0x1FF
     * otherwise < 0x1FF
     * 
     * checking order as follow
     *  ┌───┬───┬───┬┬───┬───┬───┬┬───┬───┬───┐
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├===========┼┼===========┼┼===========┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├===========┼┼===========┼┼===========┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 1 │ 2 │ 3 ││ 4 │ 5 │ 6 ││ 7 │ 8 │ 9 │
     *  └───┴───┴───┴┴───┴───┴───┴┴───┴───┴───┘
     */
    for (int c=0; c<9; ++c)
        flag |= 1 << (sudoku[row][c]-1);

    pthread_exit((void*)flag);  // return flag (warp as void pointer)
}

void* checkCol(void* args) {
    // Get the column that need to check
    params_t *params = args;
    int col = params->col;
    uint64_t flag = 0x000;  // Here, we use uint64, since size(void*) = 8 bytes

    /* store 9 flags in bit
     * example:
     *  let sudoku[0][col] = 6
     *  then flag = flag or 1 << (6-1) (=100000)
     *  that is    000000000
     *          or 000100000
     *          ------------
     *      flag = 000100000
     * 
     *  also let sudoku[1][col] = 5
     *  then flag = flag or 1 << (5-1) (=10000)
     *  that is    000100000
     *          or 000010000
     *          ------------
     *      flag = 000110000
     * 
     * if the col is valid, then flag = 111111111 = 511 = 0x1FF
     * otherwise < 0x1FF
     * 
     * checking order as follow
     *  ┌───┬───┬───┬┬───┬───┬───┬┬───┬───┬───┐
     *  │ 1 │ 1 │ 1 ││ 1 │ 1 │ 1 ││ 1 │ 1 │ 1 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 2 │ 2 │ 2 ││ 2 │ 2 │ 2 ││ 2 │ 2 │ 2 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 3 │ 3 │ 3 ││ 3 │ 3 │ 3 ││ 3 │ 3 │ 3 │
     *  ├===========┼┼===========┼┼===========┤
     *  │ 4 │ 4 │ 4 ││ 4 │ 4 │ 4 ││ 4 │ 4 │ 4 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 5 │ 5 │ 5 ││ 5 │ 5 │ 5 ││ 5 │ 5 │ 5 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 6 │ 6 │ 6 ││ 6 │ 6 │ 6 ││ 6 │ 6 │ 6 │
     *  ├===========┼┼===========┼┼===========┤
     *  │ 7 │ 7 │ 7 ││ 7 │ 7 │ 7 ││ 7 │ 7 │ 7 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 8 │ 8 │ 8 ││ 8 │ 8 │ 8 ││ 8 │ 8 │ 8 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 9 │ 9 │ 9 ││ 9 │ 9 │ 9 ││ 9 │ 9 │ 9 │
     *  └───┴───┴───┴┴───┴───┴───┴┴───┴───┴───┘
     */
    for (int r=0; r<9; ++r)
        flag |= 1 << (sudoku[r][col]-1);
    
    pthread_exit((void*)flag);  // return flag (warp as void pointer)
}

void* checkGrid(void* args) {
    // Get the grid that need to check (top-left)
    params_t *params = args;
    int row = params->row*3;
    int col = params->col*3;
    uint64_t flag = 0x000;  // Here, we use uint64, since size(void*) = 8 bytes

    /* store 9 flags in bit
     * example:
     *  let sudoku[row][0] = 6
     *  then flag = flag or 1 << (6-1) (=100000)
     *  that is    000000000
     *          or 000100000
     *          ------------
     *      flag = 000100000
     * 
     *  also let sudoku[row][1] = 2
     *  then flag = flag or 1 << (2-1) (=10)
     *  that is    000100000
     *          or 000000010
     *          ------------
     *      flag = 000100010
     * 
     * if the row is valid, then flag = 111111111 = 511 = 0x1FF
     * otherwise < 0x1FF
     * 
     * checking order as follow
     *  ┌───┬───┬───┬┬───┬───┬───┬┬───┬───┬───┐
     *  │ 1 │ 2 │ 3 ││ 1 │ 2 │ 3 ││ 1 │ 2 │ 3 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 4 │ 5 │ 6 ││ 4 │ 5 │ 6 ││ 4 │ 5 │ 6 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 7 │ 8 │ 9 ││ 7 │ 8 │ 9 ││ 7 │ 8 │ 9 │
     *  ├===========┼┼===========┼┼===========┤
     *  │ 1 │ 2 │ 3 ││ 1 │ 2 │ 3 ││ 1 │ 2 │ 3 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 4 │ 5 │ 6 ││ 4 │ 5 │ 6 ││ 4 │ 5 │ 6 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 7 │ 8 │ 9 ││ 7 │ 8 │ 9 ││ 7 │ 8 │ 9 │
     *  ├===========┼┼===========┼┼===========┤
     *  │ 1 │ 2 │ 3 ││ 1 │ 2 │ 3 ││ 1 │ 2 │ 3 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 4 │ 5 │ 6 ││ 4 │ 5 │ 6 ││ 4 │ 5 │ 6 │
     *  ├───┼───┼───┼┼───┼───┼───┼┼───┼───┼───┤
     *  │ 7 │ 8 │ 9 ││ 7 │ 8 │ 9 ││ 7 │ 8 │ 9 │
     *  └───┴───┴───┴┴───┴───┴───┴┴───┴───┴───┘
     */
    for (int r=0; r<3; ++r)
        for (int c=0; c<3; ++c)
            flag |= 1 << (sudoku[row+r][col+c]-1);

    pthread_exit((void*)flag);  // return flag (warp as void pointer)
}

int main(int argc, char* argv[])
{
    if (argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
    {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (argc == 2 && !(strcmp(argv[1], "random"))) {
        // Generate a random sudoku 
        // Normally incorrect, so we can test our program
        srand(time(NULL));
        for (int r=0; r<9; ++r)
            for (int c=0; c<9; ++c)
                sudoku[r][c] = (rand() % 9)+1;

    } else if (argc == 2 && !(strcmp(argv[1], "custom"))) {
        // Input a sudoku
        for (int r=0; r<9; ++r) {
            for (int c=0; c<9; ++c) {
                printf("Enter value for [%d][%d]: ", r, c);
                scanf("%d", &sudoku[r][c]);
            }
        }
    } else {
        // Use the solution provided by text book
        for (int r=0; r<9; ++r)
            for (int c=0; c<9; ++c)
                sudoku[r][c] = solution[r][c];
    }

    // Print out the pizzle
    printSudoku(sudoku);

    // 27 threads and params in total
    // 9 threads for row
    // 9 threads for column
    // 9 threads for grid
    pthread_t tRow[9], tCol[9], tGrid[9];
    params_t *paramsRow = malloc(9 * sizeof(params_t));
    params_t *paramsCol = malloc(9 * sizeof(params_t));
    params_t *paramsGrid = malloc(9 * sizeof(params_t));

    for (int i=0; i<9; ++i) {
        // params for row
        paramsRow[i].row = i;
        paramsRow[i].col = -1;

        // params for column
        paramsCol[i].row = -1;
        paramsCol[i].col = i;

        // params for grid
        paramsGrid[i].row = i/3;
        paramsGrid[i].col = i%3;

        pthread_create(&tRow[i], NULL, checkRow, &paramsRow[i]);    // row thread
        pthread_create(&tCol[i], NULL, checkCol, &paramsCol[i]);    // column thread
        pthread_create(&tGrid[i], NULL, checkGrid, &paramsGrid[i]); // grid thread
    }

    // free params pointers
    free(paramsRow);
    free(paramsCol);
    free(paramsGrid);

    int incorrectFlag = 0;
    for (int i=0; i<9; ++i) {
        void *rowParams = NULL;
        void *colParams = NULL;
        void *gridParams = NULL;

        pthread_join(tRow[i], &rowParams);      // Wait for row thread
        pthread_join(tCol[i], &colParams);      // Wait for column thread
        pthread_join(tGrid[i], &gridParams);    // Wait for grid thread

        if (rowParams != NULL && (uint64_t)rowParams != 0x1FF) {
            printf("Error row: %d\n", i+1);
            incorrectFlag++;
        }

        if (colParams != NULL && (uint64_t)colParams != 0x1FF) {
            printf("Error column: %d\n", i+1);
            incorrectFlag++;
        }

        if (gridParams != NULL && (uint64_t)gridParams != 0x1FF) {
            printf("Error grid: %d \n", i+1);
            incorrectFlag++;
        }
    }

    if (!incorrectFlag)
        printf("Sudoku correct!\n");

    exit(EXIT_SUCCESS);
}