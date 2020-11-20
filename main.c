#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAP_SIZE = 10;
const int N_BOMB = 10;

// PROTOTYPE
void MenuTitle(int*, char[MAP_SIZE][MAP_SIZE], char[MAP_SIZE][MAP_SIZE]);
void QuitTitle();

void GetAnswer(int*);
void InitMap(char[MAP_SIZE][MAP_SIZE]);
void InitBomb(char[MAP_SIZE][MAP_SIZE]);
void PlaceBomb(char[MAP_SIZE][MAP_SIZE]);
void PrintMap(char[MAP_SIZE][MAP_SIZE]);
void Action(char[MAP_SIZE][MAP_SIZE], char[MAP_SIZE][MAP_SIZE], int*);
void Tester(char[MAP_SIZE][MAP_SIZE], char[MAP_SIZE][MAP_SIZE], int*);
void Drapeau(char[MAP_SIZE][MAP_SIZE], char[MAP_SIZE][MAP_SIZE]);
void GetCoord(int*, int*);
int Analyse(int, int, char[MAP_SIZE][MAP_SIZE]);
void AnalyseVictory(char[MAP_SIZE][MAP_SIZE], char[MAP_SIZE][MAP_SIZE], int*);
void DefeatTitle(int*);
void VictoryTitle(int*);

int main()
{
    srand(GetTickCount());

    char map[MAP_SIZE][MAP_SIZE];
    char playerMap[MAP_SIZE][MAP_SIZE];
    int gameState = 0;

    while (gameState != -1){
        switch (gameState){
        case 0 :
            //MENU
            MenuTitle(&gameState, map, playerMap);
            break;
        case 1 :
            // GAME
            system("cls");
            PrintMap(playerMap);

            Action(map, playerMap, &gameState);
            AnalyseVictory(map, playerMap, &gameState);
            break;
        case 2 :
            // VICTORY
            VictoryTitle(&gameState);
            break;
        case 3 :
            // DEFEAT
            DefeatTitle(&gameState);
            break;
        default : gameState = -1;
        }
    }
    QuitTitle();

    return 0;
}

void AnalyseVictory(char map[MAP_SIZE][MAP_SIZE], char playerMap[MAP_SIZE][MAP_SIZE], int *g){
    int victory = 1;
    for (int x = 0; x < MAP_SIZE; x++)
        for (int y = 0; y < MAP_SIZE; y++)
            if (map[x][y] == 'x' && playerMap[x][y] != 244)
                victory = 0;
    if (victory == 1)
        *g = 2;
}

// DEFEAT
void DefeatTitle(int *g){
    system("cls");
    printf("Vous avez perdu...");
    fflush(stdin);
    getchar();
    *g = 0;
}

void VictoryTitle(int *g){
    system("cls");
    printf("Vous avez gagne");
    fflush(stdin);
    getchar();
    *g = 0;
}

// ACTION
void Action(char map[MAP_SIZE][MAP_SIZE], char playerMap[MAP_SIZE][MAP_SIZE], int *g){
    char action;

    printf("Tester [T] | Drapeau [D]\n");
    fflush(stdin);
    action = getchar();

    if (action == 't' || action == 'T')
        Tester(map, playerMap, g);
    else if (action == 'd' || action == 'D')
        Drapeau(map, playerMap);
}

void Tester(char map[MAP_SIZE][MAP_SIZE], char playerMap[MAP_SIZE][MAP_SIZE], int *g){
    int x, y;
    GetCoord(&x, &y);

    if (map[x][y] == 'x')
        *g = 3;
    else
        playerMap[x][y] = Analyse(x, y, map) + 48;
}

int Analyse(int x, int y, char map[MAP_SIZE][MAP_SIZE]){
    int nBomb = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (map[x-1+i][y-1+j] == 'x')
                nBomb++;
    return nBomb;
}

void Drapeau(char map[MAP_SIZE][MAP_SIZE], char playerMap[MAP_SIZE][MAP_SIZE]){
    int x, y;
    GetCoord(&x, &y);
    playerMap[x][y] = 244;
}

void GetCoord(int *x, int *y){
    int tx, ty;
    printf("Ligne numero : ");
    fflush(stdin);
    scanf("%d", &tx);

    printf("Colonne numero : ");
    fflush(stdin);
    scanf("%d", &ty);

    *x = tx-1;
    *y = ty-1;
}

// MENU TITLE
void MenuTitle(int *g, char map[MAP_SIZE][MAP_SIZE], char playerMap[MAP_SIZE][MAP_SIZE]){
    // CLEAR SCREEN
    system("cls");

    // INIT
    InitMap(map);
    InitMap(playerMap);

    // INIT BOMBS
    InitBomb(map);

    printf("### DEMINEUR ###\n");
    printf("Voulez-vous commencer ? [Y/N]\n");

    GetAnswer(g);
}

// SEND GAME STATE
void GetAnswer(int *a){
    char answer = ' ';

    // Request valid answer
    while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
        fflush(stdin);
        scanf("%c", &answer);
    }

    // Return integer (game state)
    if (answer == 'y' || answer == 'Y')
        *a = 1; // return 1;
    else
        *a = -1; // return -1;
}

// INIT MAP
void InitMap(char map[MAP_SIZE][MAP_SIZE]){
    for (int x = 0; x < MAP_SIZE; x++)
        for (int y = 0; y < MAP_SIZE; y++)
            map[x][y] = '.';
}

// INIT BOMBS
void InitBomb(char map[MAP_SIZE][MAP_SIZE]){
    for (int i = 0; i < N_BOMB; i++){
        PlaceBomb(map);
    }
}

// PLACE BOMB
void PlaceBomb(char map[MAP_SIZE][MAP_SIZE]){
    int x = (rand() % MAP_SIZE);
    int y = (rand() % MAP_SIZE);
    if (map[x][y] != 'x')
        map[x][y] = 'x';
    else
        PlaceBomb(map);
}

void PrintMap(char map[MAP_SIZE][MAP_SIZE]){
    for (int x = 0; x < MAP_SIZE; x++){
        for (int y = 0; y < MAP_SIZE; y++)
            printf("%c", map[x][y]);
        printf("\n");
    }
}

void QuitTitle(){
    system("cls");
    printf("Au revoir.\n");
}
