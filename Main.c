#include <stdio.h>
#include <windows.h>
#define R 23
#define C 79
#define SPACE 0
#define OBSTACLE 1
#define HIDDEN_TREASURE 2
#define PLAYER 3
#define FOUND_TREASURE 4
#define TREASURES 20
#define OBSTACLES 30
// Define the OS which gonna be compiled
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
#endif

int main () {
    // Show menu with game info
    printf("*****************************************");
    printf("\n*\t\tMade by Rambou\t\t*");
    printf("\n*\tGoal of the game if to find\t*");
    printf("\n*\tall the hidden treasures in\t*");
    printf("\n*\tthe game.\t\t\t*");
    printf("\n*\t\t\t\t\t*");
    printf("\n*\tMove by using:\t\t\t*");
    printf("\n*\t\t\t\t\t*");
    printf("\n*\t  w\t\t8\t\t*");
    printf("\n*\ta   d\tor   4     6\t\t*");
    printf("\n*\t  d\t\t2\t\t*");
    printf("\n*\t\t\t\t\t*");
    printf("\n*****************************************");
    printf("\n\nPress S, to start game.\n");
    setConsoleBuffered(0);
    char result;
    while(result!='s'&& result!='S') {
        result = getchar();
    }
    setConsoleBuffered(1);
    system("cls");

    int arr[R][C];

    /* random number generator */
    srand (time(NULL));

    /* Create game tablet
     * obstacles to the borders.
     */
    for (int i=0; i<R; i++)
        for (int j=0; j<C; j++)
            if(i==0 || i==R-1 || j==0 || j==C-1) {
                arr[i][j]=OBSTACLE;
            } else {
                arr[i][j]=SPACE;
            }
    /* Place player in a random position
     * in the range of [1,(R-2)]. Player
     * should be inside borders.
     */
    int pi=rand() % (R-2) + 1, pj=rand() % (C-2) + 1;
    arr[pi][pj]==3;

    // Create obstacles
    for (int i=0; i<OBSTACLES; i++) {
        /* Place obstacle in a random position
         * in the range of [1,(R-2)] for X axis and
         * [1,(C-2)] for Y axis. Obstacles should be
         * inside borders.
         */
        int k, l;
TryAgain:
        while(1) {
            k=rand() % (R-2) + 1;
            l=rand() % (C-2) + 1;

            // Check if coordinates is a player and try again
            if(arr[k][l]==PLAYER ) {
                continue;
            }
            // Check for neighbour obstacles
            for(int a=k-1; a<=k+1; a++)
                for(int s=l-1; s<=l+1; s++) {
                    // If you found at least one then try again
                    if(arr[a][s]==OBSTACLE) {
                        goto TryAgain;
                    }
                }
            break;
        }
        arr[k][l]=OBSTACLE; // Create obstacle
    }

    // Create treasures
    for (int i=0; i<TREASURES; i++) {
        int k,l;
        do {
            // Random coordinates between borders
            k=rand() % (R-2) + 1;
            l=rand() % (C-2) + 1;
        } while(arr[k][l]==OBSTACLE || arr[k][l]==PLAYER || arr[k][l]==HIDDEN_TREASURE);
        arr[k][l]=2; // Create treasure
    }

    // Start game
    result = '1';
    int tleft=TREASURES;
    while(result!='0' && tleft>0) {
        int moved = 0;
        switch(result) {
        case '8':
        case 'w':
        case 'W':
            if(arr[pi-1][pj]==SPACE || arr[pi-1][pj]==HIDDEN_TREASURE || arr[pi-1][pj]==PLAYER || arr[pi-1][pj]==FOUND_TREASURE) {
                if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                pi--;
                moved=1;
            }
            break;
        case '2':
        case 's':
        case 'S':
            if(arr[pi+1][pj]==SPACE || arr[pi+1][pj]==HIDDEN_TREASURE || arr[pi+1][pj]==PLAYER || arr[pi+1][pj]==FOUND_TREASURE) {
                if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                pi++;
                moved=1;
            }
            break;
        case '4':
        case 'a':
        case 'A':
            if(arr[pi][pj-1]==SPACE || arr[pi][pj-1]==HIDDEN_TREASURE || arr[pi][pj-1]==PLAYER || arr[pi][pj-1]==FOUND_TREASURE) {
                if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                pj--;
                moved=1;
            }
            break;
        case '6':
        case 'd':
        case 'D':
            if(arr[pi][pj+1]==SPACE || arr[pi][pj+1]==HIDDEN_TREASURE || arr[pi][pj+1]==PLAYER || arr[pi][pj+1]==FOUND_TREASURE) {
                if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                pj++;
                moved=1;
            }
            break;
        }

        if(moved) {
            if(arr[pi][pj]==HIDDEN_TREASURE) {
                arr[pi][pj]=4;
                printf("\a");
                tleft--;
            } else if(arr[pi][pj]!=FOUND_TREASURE) {
                arr[pi][pj]=PLAYER;
            }
            moved=0;
        }

        // Print game table
        for (int i=0; i<R; i++) {
            for (int j=0; j<C; j++) {
                if(arr[i][j]==OBSTACLE) {
                    printf("X");
                } else if(arr[i][j]==PLAYER) {
                    printf("O");
                } else if(arr[i][j]==FOUND_TREASURE) {
                    printf("T");
                } else{
                    printf(" ");
                }
            }
            printf("\n");
        }

        if(tleft==0) {
            system("cls");
            printf("Congratulations, You have found all treasures!!!");
            break;
        } else {
            printf("You still have %i treasures to find.",tleft);
        }

        // set console to unbuffered to read
        setConsoleBuffered(0);
        result = getchar();

        // set console to buffer to clear
        setConsoleBuffered(1);
        system("cls");
    }

    setConsoleBuffered(0);
    printf("\n\nPress X, to exit.");
    while(result!='x'&& result!='X') {
        result = getchar();
    }
}

// Basically, we reset the console to unbuffered
void setConsoleBuffered(int boolean) {
#ifdef  OS_WIN
    DWORD        mode;
    HANDLE       hstdin;
    hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );
    SetConsoleMode( hstdin, 0 );

    if(boolean)
        // Reset to normal input
        SetConsoleMode(hstdin, mode);
    else
        // Reset to unbuffered mode
        SetConsoleMode( hstdin, 0 );
#endif // OS_WIN
}
