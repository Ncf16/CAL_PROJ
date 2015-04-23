//#include <stdio.h>
//#include <tchar.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
//#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include "menu.h"
//
//using namespace std;
//int menu(){
//	vector<string> menu_options= getDirFiles();
//	int opcao=0;
//	if (apps_ordenadas.empty()) {
//		system("cls");
//		cout << "  Nao existem mapas disponiveis" << endl << endl;
//		cout << "  Prima (Esc) para regressar  " << endl << endl;
//
//		cout << endl << endl << endl << "  Nao ha Apps para mostrar  " << endl;
//
//		int tecla;
//		tecla = getch();
//		if (tecla != 0) {
//			while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
//				tecla = getch();
//			}
//
//		}
//		//Sair do programa
//	} else {
//
//		cout << "  Escolha um mapa" << endl << endl;
//		cout << "  Prima (Enter) para selecionar ou (Esc) para sair  "
//				<< endl << endl;
//		printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
//
//		int tecla;
//		tecla = getch();
//		if (tecla != 0) {
//			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
//			{
//				tecla = getch();
//				if (tecla == 72) //ACIMA
//						{
//					opcao--;
//					if (opcao < 0)
//						opcao = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
//					system("cls");
//					cout << " Escolher mapa " << endl << endl;
//					cout
//							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
//							<< endl << endl;
//					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
//				}
//				if (tecla == 80) //ABAIXO
//						{
//					opcao++;
//					if (opcao > (menu_options.size() - 1))
//						opcao = 0; // se passar o fim, volta ao inicio
//					system("cls");
//					cout << " Escolher mapa " << endl << endl;
//					cout
//							<< "  Prima (Enter) para selecionar ou (Esc) para regressar  "
//							<< endl << endl;
//					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
//				}
//			}
//		}
//		if (tecla == 13) {
//
//				system("cls");
//				cout << "  A processar..." << endl << endl << endl
//						<< endl;
//
//				//correr API
//
//				try {
//					//gravar stuff
//				} catch (File_Exp& exp) {
//					cor(BLACK, RED);
//					cerr << "Error" + exp.getIdErro() << endl;
//					cerr << exp.getDescricaoErro() << endl;
//					cor(BLACK, WHITE); //reset a� cor
//				}
//
//
//		}
//		if (tecla == 27) {
//			//sair
//		}
//
//
//void gotoxy(int xpos, int ypos)  // just take this function as it is.
//		{
//	COORD scrn;
//	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
//	scrn.X = xpos;
//	scrn.Y = ypos;
//	SetConsoleCursorPosition(hOuput, scrn);
//}
//
//int getDirFiles() {
//	DIR *dir;
//	struct dirent *entry;
//	if ((dir = opendir("./files/"))) {
//		while ((entry = readdir(dir))) {
//			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
//				cout << entry->d_name << "\n";
//		}
//	}
//	return 0;
//}
//
//void porDataNoCanto(Date data, int xpos, int ypos) {
//	gotoxy(xpos, ypos);
//	cout << "derp";
//	gotoxy(0, 0);
//}
//
//void printMenuScroll(vector<string> options, int selected_option,
//		const unsigned int max_per_screen) {
//	int min = selected_option - (max_per_screen / 2);
//	unsigned int max = selected_option + ((max_per_screen + 1) / 2);
//
//	if (max < max_per_screen)
//		max = max_per_screen;
//
//	if (max > options.size())
//		max = options.size();
//
//	unsigned int range = max - min;
//
//	if (range < max_per_screen)
//		min = options.size() - max_per_screen;
//
//	if (min < 0)
//		min = 0;
//
//	string temp;
//
//	for (unsigned int i = min; i < max; i++) {
//		if (i == selected_option) {
//			cor(WHITE, BLACK);
//			temp = "  " + options[i];
//			cout << temp;
//			cout << endl << endl;
//			cor(BLACK, WHITE);  // reset a cor
//		} else {
//			temp = "  " + options[i];
//			cout << temp;
//			cout << endl << endl;
//		}
//
//	}
//}
//
//// First 4 bits are background, last 4 bits are foreground
//void cor(int background, int foreground) {
//	HANDLE hConsole;
//	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, foreground + 16 * background);
//}
//
//int teclas() {
//	int tecla;
//	tecla = getch();
//	if (tecla != 0) {
//		while (tecla != 13) //ENQUANTO DIFERENTE DE ENTER
//		{
//			tecla = getch();
//			if (tecla == 72) //ACIMA
//				return 1;
//			if (tecla == 80) //ABAIXO
//				return -1;
//			if (tecla == 75) //ESQUERDA
//				return 4;
//			if (tecla == 77) //DIREITA
//				return -4;
//		}
//		return 13;
//	}
//}
//
////FUNCAO RESPONSAVEL POR RESTRINGIR A VARIAVEL "opcao"
//int RestringeOpcaoTeclas(int min, int max, int opcao) {
//	if (opcao > min && opcao < ((max * -1) + 13))
//		return opcao = (-1 * max); //reinicia a variavel na ultima opcao do menu
//	else if (opcao < (max * -1) || opcao > (min + 13)) //Situação em que Sai fora da gama de opções possiveis (valor > que nº de opcoes possiveis)
//		return opcao = min; //reinicia a variavel na 1a opção do menu
//	else
//		return opcao; //se não se verificam as restrições, entao devolve-se novamente a variavel intacta
//}
//
//void menuInicial(AppStore& mieic) {
//	//----------------------------------------------------------------------//
//	/*-------------------INICIALIZACAO VARIAVEIS TESTES---------------------*/
//	//----------------------------------------------------------------------//
//	// CRIAR APP QUE VAI SER INSERIDA NAS APPS APAGADAS DO 1o DEVELOPER
////	Date date_temp(2014, 11, 7, 10, 10);
////	Developer * dev_temp1 = new Empresa(1, "teste", 100, "1", "morada teste",
////			"123123123", "extra");
////
////	App* app_temp = new App(10, "App rem. da store no.1", "jogo",
////			"jogo futebol", 10, 4, 10, 1, date_temp, 1);
////	app_temp->setDev(mieic.dev[0]);
////
////	mieic.apps_apagadas.insert(*app_temp);
//	//----------------------------------------------------------------------//
//	//----------------------------------------------------------------------//
//	//----------------------------------------------------------------------//
//	system("cls");
//
//	dev_act = NULL; // da reset aos indicadores de login atual, ou seja, faz logout
//	cli_act = NULL;
//	unsigned int state = 0; //state 0 is guest
//	int opcao = 0;
//
//	for (;;) {
//		system("cls");
//		porDataNoCanto(mieic.DataAtual(), 1, 23);
//		cout << "  Bem-vindo a AppStore MIEICPlay  " << endl << endl;
//
//		if (opcao == 0)
//			cor(WHITE, BLACK);
//		cout << "  Visitar AppStore  " << endl;
//		cor(BLACK, WHITE); // apos imprimir com a cor anterior, da reset à cor para o normal
//		if (opcao == -1)
//			cor(WHITE, BLACK);
//		cout << "  Login na AppStore  " << endl;
//		cor(BLACK, WHITE);
//		if (opcao == -2)
//			cor(WHITE, BLACK);
//		cout << "  Registar na AppStore  " << endl;
//		cor(BLACK, WHITE);
//		if (opcao == -3)
//			cor(WHITE, BLACK);
//		cout << "  Validar Apps  " << endl;
//		cor(BLACK, WHITE);
//		if (opcao == -4)
//			cor(WHITE, LIGHT_RED);
//		cout << "  SAIR  " << endl;
//		cor(BLACK, WHITE);
//
//		opcao += teclas();
//		opcao = RestringeOpcaoTeclas(0, 4, opcao); //MUDAR  de 3 para o numero total de opções-1 do menu.
//
//		switch (opcao - 13) //sempre que se adicionar mais opções, adicionar mais um case (ex: case -4: return 0; break;)
//		{
//		case 0:
//			menuVisitaStore(mieic, state);
//			system("pause");
//			break;
//		case -1: // 2a opcao
//			menuLogin(mieic);
//			opcao = 0;
//			break;
//		case -2: // 3a opcao
//			menuRegistar(mieic);
//			opcao = 0;
//			break;
//		case -3:
//			menuAppsEmEspera(mieic);
//			opcao = 0;
//			break;
//		case -4: // ultima opcao
//			try {
//				mieic.save_all();
//			} catch (File_Exp& exp) {
//				cor(BLACK, RED);
//				cerr << "Error" + exp.getIdErro() << endl;
//				cerr << exp.getDescricaoErro() << endl;
//				cor(BLACK, WHITE); //reset à cor
//			}
//			exit(0);
//			break;
//		}
//	}
//}
