#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

#define  QUEEN      ('Q')
#define  ROOK       ('R')
#define  BISHOP     ('B')
#define  KNIHHT     ('N')
#define  EMPTY      (0)

#define  WHITE      ('W')
#define  BLACK      ('B')

typedef struct 
{
    char type;
    char color;
}Piece;


typedef struct 
{
    char row;
    char col;
}Square;


void printBoard(Piece (*board)[4])
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%c%c ", board[i][j].color, board[i][j].type);
        }
        printf("\n");
    }
}

Square* piexeNextSqr(Piece (*board)[4], Square sq, int *resultCount)
{
    static const Square knightOfst[8] = {
        {.row  =  2, .col  =  1},
        {.row  =  2, .col  = -1},
        {.row  = -2, .col  =  1},
        {.row  = -2, .col  = -1},
        {.row  =  1, .col  =  2},
        {.row  =  1, .col  = -2},
        {.row  = -1, .col  =  2},
        {.row  = -1, .col  = -2}
    };
    
    Square* res = malloc(16 * sizeof(Square)); 
    *resultCount = 0;
    
    Square* tmp; 
    int tmpSize = 0;
    
    char i, j;
    switch (board[sq.row][sq.col].type)
    {
        case KNIHHT:
            for(i = 0; i < 8; i++)
            {
                int r = sq.row + knightOfst[i].row;
                int c = sq.col + knightOfst[i].col;
                
                if(r < 0 || r > 3 || c < 0 || c > 3)
                    continue;
                
                if(board[r][c].type == 0 || board[r][c].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = r;
                    res[*resultCount].col = c;
                    (*resultCount)++;
                }
            }
        break;
        
        
        case ROOK:
            //down
            for(i = sq.row + 1; i < 4; i++)
            {
                if(board[i][sq.col].type == 0 || board[i][sq.col].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = i;
                    res[*resultCount].col = sq.col;
                    (*resultCount)++;
                }
                
                if(board[i][sq.col].type)     break;
            }
            
            //up
            for(i = sq.row - 1; i >= 0; i--)
            {
                if(board[i][sq.col].type == 0 || board[i][sq.col].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = i;
                    res[*resultCount].col = sq.col;
                    (*resultCount)++;
                }
                
                if(board[i][sq.col].type)      break;
            }
            
            
            //right
            for(j = sq.col + 1; j < 4; j++)
            {
                if(board[sq.row][j].type == 0 || board[sq.row][j].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = sq.row;
                    res[*resultCount].col = j;
                    (*resultCount)++;
                }
                
                if(board[sq.row][j].type)     break;
            }
            
            //left
            for(j = sq.col - 1; j >= 0; j--)
            {
                if(board[sq.row][j].type == 0 || board[sq.row][j].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = sq.row;
                    res[*resultCount].col = j;
                    (*resultCount)++;
                }
                
                if(board[sq.row][j].type)    break;
            }
        break;
        
        
        case BISHOP:
            //down right
            for(i = sq.row + 1, j = sq.col + 1; i < 4 && j < 4; i++, j++)
            {
                if(board[i][j].type == 0 || board[i][j].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = i;
                    res[*resultCount].col = j;
                    (*resultCount)++;
                }
                
                if(board[i][j].type)    break;
            }
            
            //up right
            for(i = sq.row - 1, j = sq.col + 1; i >= 0 && j < 4; i--, j++)
            {
                if(board[i][j].type == 0 || board[i][j].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = i;
                    res[*resultCount].col = j;
                    (*resultCount)++;
                }
                
                if(board[i][j].type)    break;
            }
            
            
            //down left
            for(i = sq.row + 1, j = sq.col - 1; i < 4 && j >= 0; i++, j--)
            {
                if(board[i][j].type == 0 || board[i][j].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = i;
                    res[*resultCount].col = j;
                    (*resultCount)++;
                }
                
                if(board[i][j].type)    break;
            }
            
            //up left
            for(i = sq.row - 1, j = sq.col - 1; i >= 0 && j >= 0; i--, j--)
            {
                if(board[i][j].type == 0 || board[i][j].color != board[sq.row][sq.col].color)
                {
                    res[*resultCount].row = i;
                    res[*resultCount].col = j;
                    (*resultCount)++;
                }
                
                if(board[i][j].type)    break;
            }
        break;
        
        
        case QUEEN:
            free(res);
            
            board[sq.row][sq.col].type = ROOK;
            res = piexeNextSqr(board, sq, resultCount);
            
            board[sq.row][sq.col].type = BISHOP;
            tmp = piexeNextSqr(board, sq, &tmpSize);
            
            board[sq.row][sq.col].type = QUEEN;
            
            for(i = 0; i < tmpSize; i++)
            {
                res[*resultCount] = tmp[i];
                (*resultCount)++;
            }
            
            free(tmp);
        break;
    }
    
    return res;
}


char canWhiteWin(Piece (*board)[4], int moves, char player)
{
    if(moves == 0 || (moves == 1 && player == BLACK))
        return 0;
    
    Square  sq;
    Square* nextPos = NULL;
    int nextPosCnt = 0;
    
    char res = 0;
    
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(board[i][j].type == 0 || board[i][j].color != player)
                continue;
            
            sq.row = i;
            sq.col = j;
            nextPos = piexeNextSqr(board, sq, &nextPosCnt);
            
            for(int k = 0; k < nextPosCnt; k++)
            {
                int r = nextPos[k].row;
                int c = nextPos[k].col;
                
                if(board[r][c].type == QUEEN)
                    return (player == WHITE);
                
                if(player == WHITE && moves <= 2)
                    continue;
                
                //copy intial sq (i, j) & (r, c) 
                Piece initRC = board[r][c];
                Piece initIJ = board[i][j];
                //move piece from (i, j) to (r, c)
                board[r][c] = board[i][j]; 
                //sq (i, j) is empty now
                board[i][j].type  = 0;
                board[i][j].color = 0;
                
                if(player == WHITE)
                    res = canWhiteWin(board, moves - 1, BLACK);
                else 
                    res = canWhiteWin(board, moves - 1, WHITE);
                
                //return piece back from (r, c) to (i, j)
                board[i][j] = initIJ;
                board[r][c] = initRC;
                
                if(player == WHITE && res)
                    return 1;
                else if(player == BLACK && !res)
                    return 0;
            }
            
            free(nextPos);
        }
    }
    
    return res;
}


/*
 * Complete the simplifiedChessEngine function below.
 */

/*
 * Please either make the string static or allocate on the heap. For example,
 * static char str[] = "hello world";
 * return str;
 *
 * OR
 *
 * char* str = "hello world";
 * return str;
 *
 */
char* simplifiedChessEngine(int whites_rows, int whites_columns, char** whites, int blacks_rows, int blacks_columns, char** blacks, int moves) {
    /*
     * Write your code here.
     */
    
    static char res[2][4] = {"NO", "YES"};
    
    Piece board[4][4] = {0};
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            board[i][j].type  = EMPTY;
            board[i][j].color = EMPTY;
        }
    }
    
    for(int i = 0; i < whites_rows; i++)
    {
        int r = whites[i][2] - '1';
        int c = whites[i][1] - 'A';
        board[r][c].type  = whites[i][0];
        board[r][c].color = WHITE;
    }
    
    for(int i = 0; i < blacks_rows; i++)
    {
        int r = blacks[i][2] - '1';
        int c = blacks[i][1] - 'A';
        board[r][c].type  = blacks[i][0];
        board[r][c].color = BLACK;
    }
    
    return res[canWhiteWin(board, moves, WHITE)];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* g_endptr;
    char* g_str = readline();
    int g = strtol(g_str, &g_endptr, 10);

    if (g_endptr == g_str || *g_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int g_itr = 0; g_itr < g; g_itr++) {
        char** wbm = split_string(readline());

        char* w_endptr;
        char* w_str = wbm[0];
        int w = strtol(w_str, &w_endptr, 10);

        if (w_endptr == w_str || *w_endptr != '\0') { exit(EXIT_FAILURE); }

        char* b_endptr;
        char* b_str = wbm[1];
        int b = strtol(b_str, &b_endptr, 10);

        if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

        char* m_endptr;
        char* m_str = wbm[2];
        int m = strtol(m_str, &m_endptr, 10);

        if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

        char** whites = malloc(w * sizeof(char*));

        for (int whites_row_itr = 0; whites_row_itr < w; whites_row_itr++) {
            whites[whites_row_itr] = malloc(3 * (sizeof(char)));

            char** whites_item_temp = split_string(readline());

            for (int whites_column_itr = 0; whites_column_itr < 3; whites_column_itr++) {
                char* whites_item_str = whites_item_temp[whites_column_itr];
                char whites_item = *whites_item_str;

                whites[whites_row_itr][whites_column_itr] = whites_item;
            }
        }

        char** blacks = malloc(b * sizeof(char*));

        for (int blacks_row_itr = 0; blacks_row_itr < b; blacks_row_itr++) {
            blacks[blacks_row_itr] = malloc(3 * (sizeof(char)));

            char** blacks_item_temp = split_string(readline());

            for (int blacks_column_itr = 0; blacks_column_itr < 3; blacks_column_itr++) {
                char* blacks_item_str = blacks_item_temp[blacks_column_itr];
                char blacks_item = *blacks_item_str;

                blacks[blacks_row_itr][blacks_column_itr] = blacks_item;
            }
        }

        char* result = simplifiedChessEngine(w, 3, whites, b, 3, blacks, m);
        
        fprintf(fptr, "%s\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
