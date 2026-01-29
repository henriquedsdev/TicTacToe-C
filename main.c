#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <limits.h>

#define COLOR_ON "\e[1;96m"
#define COLOR_OFF "\e[m"

int gboard[3][3];

void init_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gboard[i][j] = 0;
        }
    }
}

void clean_buf() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void print_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(gboard[i][j] == 1) {
                printf("X");
            }
            else if(gboard[i][j] == 2) {
                printf("O");
            }
            else if(gboard[i][j] == 10) {
                printf(COLOR_ON "X" COLOR_OFF);
            }
            else if(gboard[i][j] == 20) {
                printf(COLOR_ON "O" COLOR_OFF);
            }
            else {
                printf(" ");
            }
            if(j != 2) printf(" | ");
        }
        if(i != 2) printf("\n---------\n");
    }
    printf("\n\n");
}

int choose_player() {
    int choose;
    do {
        printf("Quem será o primeiro jogador: \n1 - COMPUTADOR\n2 - JOGADOR HUMANO\n\n");
        scanf("%d", &choose);
        clean_buf();

        if(choose != 1 && choose != 2) {
            printf("Opção inválida! Tente novamente...");
            Sleep(2000);
        }

        system("cls");
    } while (choose != 1 && choose != 2);

    return choose;
}

int check_move(int row, int column) {
    int r = row - 1, c = column - 1;
    if(r < 0 || r > 2 || c < 0 || c > 2)
        return 0;
    else if(gboard[r][c] != 0)
        return 0;
    else 
        return 1;
}

void player_move(int move[2]) {
    int column, row, flag;
    do {
        system("cls");
        print_board();
        printf("Digite a linha em que deseja jogar (1 a 3): ");
        scanf("%d", &row);
        clean_buf();

        printf("Digite a coluna em que deseja jogar (1 a 3): ");
        scanf("%d", &column);
        clean_buf();

        flag = check_move(row, column);

        if(flag) {
            move[0] = row - 1;
            move[1] = column - 1;
            return;
        }

        printf("\n\nJogada inválida! Tente novamente...");
        Sleep(2000);
    } while(!flag);
}

void exec_move(int move[2], int player) {
    gboard[move[0]][move[1]] = player;
}

int check_winner(int player) {
    for(int i = 0; i < 3; i++) {
        if(gboard[i][0] == player && gboard[i][1] == player && gboard[i][2] == player)
            return 1;
    }
    for(int i = 0; i < 3; i++) {
        if(gboard[0][i] == player && gboard[1][i] == player && gboard[2][i] == player)
            return 1;
    }
    if(gboard[0][0] == player && gboard[1][1] == player && gboard[2][2] == player)
        return 1;
    if(gboard[0][2] == player && gboard[1][1] == player && gboard[2][0] == player)
        return 1;
    return 0;
}

int check_draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(gboard[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

int check_pontuation() {
    if(check_winner(1) == 1)
        return 1;
    if(check_winner(2) == 1)
        return -1;
    return 0;
}

int minimax(int maxmin) {
    int value = check_pontuation();

    if(value != 0)
        return value;

    if(check_draw() == 1)
        return 0;

    if(maxmin == 0) {
        int tempValue = INT_MAX;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(gboard[i][j] == 0) {
                    gboard[i][j] = 2;
                    int v = minimax(1);
                    gboard[i][j] = 0;

                    if(v < tempValue) {
                        tempValue = v;
                    }
                }
            }
        }

        return tempValue;
    }
    else {
        int tempValue = INT_MIN;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(gboard[i][j] == 0) {
                    gboard[i][j] = 1;
                    int v = minimax(0);
                    gboard[i][j] = 0;

                    if(v > tempValue) {
                        tempValue = v;
                    }
                }
            }
        }

        return tempValue;
    }
}

void pc_move(int move[2]) {
    int finalValue = INT_MIN;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(gboard[i][j] == 0) {
                gboard[i][j] = 1;
                int value = minimax(0);
                gboard[i][j] = 0;

                if(value > finalValue){
                    finalValue = value;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
}

void highligh_win(int winner) {
    for(int i = 0; i < 3; i++) {
        if(gboard[i][0] == winner && gboard[i][1] == winner && gboard[i][2] == winner) {
            gboard[i][0] = winner * 10;
            gboard[i][1] = winner * 10;
            gboard[i][2] = winner * 10;
        }
    }
    for(int i = 0; i < 3; i++) {
        if(gboard[0][i] == winner && gboard[1][i] == winner && gboard[2][i] == winner) {
            gboard[0][i] = winner * 10;
            gboard[1][i] = winner * 10;
            gboard[2][i] = winner * 10;
        }
    }
    if(gboard[0][0] == winner && gboard[1][1] == winner && gboard[2][2] == winner) {
        gboard[0][0] = winner * 10;
        gboard[1][1] = winner * 10;
        gboard[2][2] = winner * 10;
    }
    if(gboard[0][2] == winner && gboard[1][1] == winner && gboard[2][0] == winner) {
        gboard[0][2] = winner * 10;
        gboard[1][1] = winner * 10;
        gboard[2][0] = winner * 10;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");

    int player = choose_player();
    int end = 0, move[2];
    int winner;
    init_board();

    do {
        if(player == 1) {
            pc_move(move);
            exec_move(move, player);
            end = check_winner(player);
            winner = (end == 1) ? player : 0;
            end = (end == 1) ? 1 : check_draw();
            player++;
        }
        else {
            player_move(move);
            exec_move(move, player);
            end = check_winner(player);
            winner = (end == 1) ? player : 0;
            end = (end == 1) ? 1 : check_draw();
            player--;
        }
    } while(end == 0);

    system("cls");
    
    if(check_draw() == 1) {
        print_board();
        printf("EMPATE!!!\n\n");
    }
    else if(winner == 1){
        highligh_win(winner);
        print_board();
        printf("VENCEDOR: COMPUTADOR!!!\n\n");
    }
    else {
        highligh_win(winner);
        print_board();
        printf("VENCEDOR: JOGADOR HUMANO!!!\n\n");
    }

    return 0;
}