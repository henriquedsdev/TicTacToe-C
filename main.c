#include <stdio.h>
#include <stdlib.h>
#include <time.h> //biblioteca para funções de tempo de espera
#include <locale.h> //biblioteca para funções de tradução de linguagem
#include <windows.h> //biblioteca para funções de tempo de espera
#include <limits.h> //biblioteca para adicionar os limites max e min dos tipos de variáveis

#define COLOR_ON "\e[1;96m" //constante que contem código de cor para destaque do ganhador
#define COLOR_OFF "\e[m"    //constante que contem código de cor para tirar destaque do ganhador

int gboard[3][3]; //vetor representante do tabuleiro

void init_board() {                 //função para iniciar o tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gboard[i][j] = 0;
        }
    }
}

void clean_buf() {   //função para limpar buffer de entrada do teclado
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void print_board() {       //função para imprimir tabuleiro
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

int choose_player() {     //função para escolher primeiro jogador
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

int check_move(int row, int column) {      //função para checar se movimento pode ocorrer e é válido
    int r = row - 1, c = column - 1;
    if(r < 0 || r > 2 || c < 0 || c > 2)
        return 0;
    else if(gboard[r][c] != 0)
        return 0;
    else 
        return 1;
}

void player_move(int move[2]) {       //função para captar jogada do jogador humano
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

void exec_move(int move[2], int player) {     //função para executar movimento, seja da máquina ou do jogador humano
    gboard[move[0]][move[1]] = player;
}

int check_winner(int player) {               //função para verificar se houve ganhador
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
 
int check_draw() {             //função para verificar se houve empate
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(gboard[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

int check_pontuation() {         //função para retornar quem ganhou no algoritmo minimax
    if(check_winner(1) == 1)
        return 1;
    if(check_winner(2) == 1)
        return -1;
    return 0;
}

int minimax(int maxmin) {          //função minimax, a qual gera as possibilidades de jogada para a máquina
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

void pc_move(int move[2]) {      //função para captar jogada da máquina, que chama a função minimax para realizar a lógica minimax
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

void highligh_win(int winner) {           //função de destaque da linha ganhadora do tabuleiro
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

int main() {        //função principal, a qual ocorre o jogo
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls");

    int player = choose_player();   //variavel que armazena o jogador
    int end = 0, move[2];      //end = variavel que verifica a condição de fim de jogo   move = vetor que guarda posições do tabuleiro para executar jogadas
    int winner;            //variavel que guarda quem foi o jogador
    init_board();

    do {                        //loop do jogo, o qual ocorre os movimentos da máquina e do jogador humano e termina ao final do jogo
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
    
    if(check_draw() == 1) {           //laço if-else para verificar o fim do jogo e se houve empate ou um ganhador.
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