#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <dirent.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include "parsing.h"

using namespace std;

/**< Macros de cores para usar no menu */
#define BLACK 0  // 0000
#define BLUE 1   // 0001
#define GREEN 2  // 0010
#define AQUA 3   // 0011
#define RED 4    // 0100        ----> MSB is the intensity and 3 LSB are the colors
#define PURPLE 5 // 0101
#define YELLOW 6 // 0110       Windows API has 8 bits for colors, 4 for the background and
#define WHITE 7  // 0111       then 4 for the foreground
#define GRAY 8   // 1000
#define LIGHT_GREEN 10 // 1010  -> GREEN with intensity at 1
#define LIGHT_RED 12  // 1100  -> RED with intensity at 1

/** Maximo de items a mostar no ecra, quando se usa o scroll */
const unsigned int MAX_PER_SCREEN = 6;

void menu();

/**
 * Mete o cursor numa posicao do ecra, para se poder escrever nesse local diretamente
 *
 * @param xpos  Coluna para a qual o cursor vai
 * @param ypos  Linha para a qual o cursor vai
 */
void gotoxy(int xpos, int ypos);
/**
 * Escreve a data atual na posicao indicada nos parametros
 * @param xpos Coluna onde e escrita a data
 * @param ypos Linha onde e escrita a data
 */
void porDataNoCanto(int xpos, int ypos);

/**
 * Janela/Menu para verificacao da password do cliente ou dev, consoante quem estiver logged in
 * @param dev_or_cli  Pointer para o cliente ou developer que estiver logged in
 * @return True, se a pass foi corretamente escrita. False, se a password estava errada
 */
template<typename T>
bool verificaPass(T* dev_or_cli);
/**
 * Funcao que imprime opcoes de um vetor, sendo possivel ao user fazer scroll atraves das opcoes.
 * Se houver mais opcoes do que as maximas que consegue mostrar, funciona como menu de scroll (como as mensagens num telemovel)
 * @param options Vetor de opcoes que vao ser exibidas no ecra
 * @param selected_option Opcao actual do vetor em que se esta - esta opcao esta highlighted com cor branca
 * @param max_per_screen Maximo de opcoes mostradas de cada vez no ecra
 */
void printMenuScroll(vector<string> options, int selected_option, const unsigned int max_per_screen);
/**
 *  Altera a cor do background e foreground para os valores/cores especificadas
 * @param background Cor para o fundo do API - usa-se aqui uma das macros definidas
 * @param foreground Cor para o foreground/letra do API - usa-se aqui uma das macros definidas
 */
void cor(int background, int foreground);
/**
 * Retorna um vetor com os nomes de todos os ficheiros e diretorios da pasta files
 */
vector<string> getDirFiles();

/**
 * Retorna um numero consoante a tecla premida
 * @return Se premir as setas de cima ou baixo, retorna 1 ou -1. Se premir as de lado, retorna 2 ou -2. Se premir enter, retorna 13.
 */
int teclas();
/**
 * Nos menus onde se chama a funcao teclas(), vai restringir as opcoes de maneira a que,
 * quando se chega a ultima opcao, volta a primeira, e quando se passa para cima da primeira, volta a ultima
 * @param min Nr. da opcao minima
 * @param max Nr. (valor absoluto) da opcao maxima
 * @param opcao Opcao atual em que se encontra o menu
 * @return Opcao na qual vai estar depois das restricoes
 */
int RestringeOpcaoTeclas(int min, int max, int opcao);

#endif /* MENU_H_ */
