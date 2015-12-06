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
int main ()
{
    // Basically, we reset the console to unbuffered
    #ifdef  OS_WIN
    DWORD        mode;
    HANDLE       hstdin;
    hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );
    SetConsoleMode( hstdin, 0 );
    #else

    #endif // OS_WIN

    int arr[R][C];

    /* random number generator */
    srand (time(NULL));

    // Δημιουργία κουτιού
    for (int i=0;i<R;i++)
        for (int j=0;j<C;j++)
            if(i==0 || i==R-1 || j==0 || j==C-1){
                arr[i][j]=OBSTACLE;
            }else{
                arr[i][j]=SPACE;
            }
    // Βάλε τον παίκτη σε μια τυχαία θέση
    int pi=rand() % (R-2) + 1, pj=rand() % (C-2) + 1;
    arr[pi][pj]==3;

    // δημιουργία εμπορδίων
    for (int i=0;i<OBSTACLES;i++){
        int k=rand() % (R-2) + 1, l=rand() % (C-2) + 1;
        int flag = 1;
        while(flag){
            flag=0;

            // έλεγχος αν η θέση ειναι πάικτης
            if(arr[k][l]==3){
                flag=1;
                continue;
            }
            // γίνεται έλεγχος για γειτονικά εμπόδια
            for(int a=k-1;a<=k+1;a++)
                for(int s=l-1;s<=l+1;s++){
                    //printf("k=%i-%i l=%i-%i arr=%i\n",k,a,l,s,arr[a][s]);
                    if(arr[a][s]==1){
                        flag = 1;
                        break;
                    }
                }

            // εάν υπάρχει έστω και ένα κοντινό δώσε καινούργιες τιμές στα K,L
            if(flag){
                k=rand() % (R-2) + 1;
                l=rand() % (C-2) + 1;
            }
        }
        // θέσε το τυχαίο εμππόδιο
        arr[k][l]=1;
    }

    // δημιουργία θησαυρού
    for (int i=0;i<TREASURES;i++){
        int k=rand() % (R-2) + 1, l=rand() % (C-2) + 1;
        while(arr[k][l]==1 || arr[k][l]==3)
        {
            k=rand() % (R-2) + 1;
            l=rand() % (C-2) + 1;
        }
        arr[k][l]=2;
    }

    // Ξεκινάει το παιχνίδι
    char result = '1';
    int treasure=TREASURES;
    while(result!='0' && treasure>0){
        int Vflag = 0;
        int Hflag = 0;
        switch(result) {
            case '8' :
                if(arr[pi-1][pj]==SPACE || arr[pi-1][pj]==HIDDEN_TREASURE || arr[pi-1][pj]==PLAYER || arr[pi-1][pj]==FOUND_TREASURE){
                    if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                    pi--;
                    Vflag=1;
                }
                break;
            case '2' :
                if(arr[pi+1][pj]==SPACE || arr[pi+1][pj]==HIDDEN_TREASURE || arr[pi+1][pj]==PLAYER || arr[pi+1][pj]==FOUND_TREASURE){
                    if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                    pi++;
                    Hflag=1;
                }
                break;
            case '4' :
                if(arr[pi][pj-1]==SPACE || arr[pi][pj-1]==HIDDEN_TREASURE || arr[pi][pj-1]==PLAYER || arr[pi][pj-1]==FOUND_TREASURE){
                    if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                    pj--;
                    Vflag=1;
                }
                break;
            case '6':
                if(arr[pi][pj+1]==SPACE || arr[pi][pj+1]==HIDDEN_TREASURE || arr[pi][pj+1]==PLAYER || arr[pi][pj+1]==FOUND_TREASURE){
                    if(arr[pi][pj]==PLAYER) arr[pi][pj]=SPACE;
                    pj++;
                    Hflag=1;
                }
                break;
        }

        if(Vflag || Hflag){
            if(arr[pi][pj]==HIDDEN_TREASURE){
                arr[pi][pj]=4;
                treasure--;
            }else if(arr[pi][pj]!=FOUND_TREASURE){
                arr[pi][pj]=PLAYER;
            }
            Vflag=0;
            Hflag=0;
        }

        // τύπωσε ταμπλό
        for (int i=0;i<R;i++){
            for (int j=0;j<C;j++){
                if(arr[i][j]==OBSTACLE){
                    printf("X");
                }else if(arr[i][j]==HIDDEN_TREASURE){
                    printf(" ");
                }else if(arr[i][j]==FOUND_TREASURE){
                    printf("T");
                }else if(arr[i][j]==PLAYER){
                    printf("O");
                }else if(arr[i][j]==SPACE){
                     printf(" ");
                }
            }
            printf("\n");
        }

        printf("Έχεις ακόμα %i θησαυρούς να βρεις!",treasure);
        // Escape character to help clear the buffer
        printf("\n");
        if(treasure==0){
            system("cls");
            printf("Συγχαρητήρια βρήκες όλους τους θησαυρούς!!!");
            break;
        }
        result = getchar();
    }
    #ifdef OS_WIN
    // Reset to normal input
    SetConsoleMode(hstdin, mode);
    #endif // OS_WIN
}
