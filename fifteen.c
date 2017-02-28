/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality 
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
    return;
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // int board[DIM_MAX][DIM_MAX];
    
    // d — размерность доски, d <= MAX
    
    int d_cube = d * d - 1;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = d_cube;
            d_cube--;
        } 
    }
    // В случае, если кол плиток(без пустой) нечетное - меняем местами 1 и 2
    if ((d - 1) % 2 != 0) 
    {
        int k = board[d - 1][d - 3];
        board[d - 1][d - 3] = board[d - 1][d - 2];
        board[d - 1][d - 2] = k;
    }
    return;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++) 
    // каждой строки 
    {
        for(int j = 0; j < d; j++) 
        // for каждого элемента строки 
        { 
            if (board[i][j] == 0)
                printf("_\t");
            else
                printf("%2d\t", board[i][j]); 
                // printf значение и пробел 
        }
        printf("\n");
    }
    return;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int now_i, now_j, o_i, o_j; 
    for(int i = 0; i < d; i++) 
    // каждой строки 
    {
        for(int j = 0; j < d; j++) 
        // for каждого элемента строки 
        {
            // int tile-Приним.ном.плитки,который пользователь хочет подвинуть
            // Ищет положение в массиве (на игровом поле) этой плитки
            if (board[i][j] == tile)
            {
                now_i = i;
                now_j = j;
            }
            // Запоминает позицию пустой плитки    
            if (board[i][j] == 0)
            {
                o_i = i;
                o_j = j;
            }    
        }
    }
    
    // Если пустая плитка соседствует с той, которую пользователь
    // хочет подвинуть, они меняются местами в массиве.
    if ( ((o_i == now_i) && ((o_j == now_j + 1) || (o_j == now_j - 1))) || 
        ((o_j == now_j) && ((o_i == now_i + 1) || (o_i == now_i - 1))) )
    {
        board[o_i][o_j] = tile;
        board[now_i][now_j] = 0;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int d_cub = d * d - 1;
    int d_c = 1;
    // 3*3-1 = 8
    for(int i = 0; i < d; i++) 
    // каждой строки 
    {
        // printf("\n i=%i", i);usleep(5000);
        for(int j = 0; j < d; j++) 
        // for каждого элемента строки 
        { 
            // printf("\n j=%i", j);usleep(5000);
            if ( !( (board[i][j] == d_c) && (board[d - 1][d - 1] == 0)
                 && (board[d - 1][d - 2] == d_cub) ) )
            {
                if ( (j != 0) && (board[i][j - 1] == d_cub) ) 
                    return true;
                // printf("\n(board[%i][%i] != %i) return false\n",i,j,d_c);usleep(5000);
                return false;
            }
            d_c++;
        }
    
    }
    // printf("\n(board[i][j] == d_cub) return true!!!!\n");usleep(500000000);
    return true;
}