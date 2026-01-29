TIC-TAC-TOE - CIÊNCIA DA COMPUTAÇÃO

INTEGRANTES:
1 - Henrique Soares;
2 - João Vitor Mariani;
3 - João Paulo Lopes;

INTRODUÇÃO E APRESENTAÇÃO DE ESTRATÉGIAS:

O jogo Tic-Tac-Toe produzido pelo grupo é do tipo Computador (Máquina) vs Jogador Humano, no qual o jogador humano enfrenta uma inteligência artificial capaz de analisar o tabuleiro e tomar decisões estratégicas. O objetivo do jogo segue as regras tradicionais do jogo da velha.
Para o comportamento do computador, foi utilizado o algoritmo Minimax, um algoritmo clássico de tomada de decisão aplicado em jogos de dois jogadores. Esse algoritmo funciona simulando todas as jogadas possíveis a partir do estado atual do tabuleiro, considerando que ambos os jogadores sempre escolhem a melhor jogada disponível. Assim, o Computador torna-se imbatível.

INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO:
O programa Tic-Tac-Toe foi desenvolvido em linguagem C no Visual Studio Code. Para compilar e executar o programa da forma correta, siga os seguintes passos:
1. Instalar o Visual Studio Code;
2. Instalar as seguintes extensões no VS Code:
     - C/C++ --> criador Microsoft;
     - C/C++ Compile Run --> criador danielpinto8zz6;
3. Baixar o MinGW no computador no link: https://sourceforge.net/projects/mingw/files/latest/download;
4. Executar o instalador do MinGW;
5. No instalador clicar em "install" e depois em "continue", lembrando de gravar o diretório de instalação do programa;
6. Após isso, será aberto um configurador de instalação, onde deve ser selecionado as seguintes opções de instalação:
     - mingw32-base-bin;
     - mingw32-gcc-g++;
7. Marque as opções e vá em "installation" no canto esquerdo e depois em "Apply Changes";
8. Após isso, abra o "Pesquisar" do Windows e procure "Editar variáveis de ambiente";
9. Na aba avançado, Clique em "Variáveis de Ambiente";
10. Na seção de "Variáveis do Sistema", clique em Path, depois em editar;
11. Adicione um novo caminho e coloque o caminho da pasta "bin" do mingw (geralmente será: C:\MinGW\bin);
12. Depois apenas aplique as modificações clicando em "ok";

Em caso de dúvida, acesse o vídeo no link a seguir: https://www.youtube.com/watch?v=Mook-z2uvpM;

Após isso, o programa deve estar funcionando no VS Code, basta apenas abrir o arquivo main.c no Visual Studio e executa-lo apertando "F6". também é recomendável exportar a pasta do projeto para o computador e abrir a própria pasta no Visual Studio.
