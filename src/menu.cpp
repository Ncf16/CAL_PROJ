#include "menu.h"

using namespace std;
void menu() {
	Graph grafo;
	//string nodes = "Nodes", roads="Roads",edges="Edges";
	vector<string> menu_options = getDirFiles();
	int opcao = 0;

	if (menu_options.empty()) {
		system("cls");
		cout << " Nao existem mapas disponiveis" << endl << endl;
		cout << " Prima (Esc) para regressar  " << endl << endl;

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 27) { // Enquanto nao carregar no escape, nao sai
				tecla = getch();
			}

		}
		//Sair do programa
	} else {

		cout << " Escolha um mapa" << endl << endl;
		cout << " Prima (Enter) para selecionar ou (Esc) para sair  " << endl
				<< endl;
		printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);

		int tecla;
		tecla = getch();
		if (tecla != 0) {
			while (tecla != 13 && tecla != 27) //ENQUANTO DIFERENTE DE ENTER E ESCAPE
			{
				tecla = getch();
				if (tecla == 72) //ACIMA
						{
					opcao--;
					if (opcao < 0)
						opcao = menu_options.size() - 1; // se subir mais que o inicio, passa para o fim
					system("cls");
					cout << " Escolha um mapa " << endl << endl;
					cout
							<< " Prima (Enter) para selecionar ou (Esc) para sair  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
				if (tecla == 80) //ABAIXO
						{
					opcao++;
					if (opcao > (menu_options.size() - 1))
						opcao = 0; // se passar o fim, volta ao inicio
					system("cls");
					cout << " Escolha um mapa " << endl << endl;
					cout
							<< " Prima (Enter) para selecionar ou (Esc) para sair  "
							<< endl << endl;
					printMenuScroll(menu_options, opcao, MAX_PER_SCREEN);
				}
			}
		}
		if (tecla == 13) {

			system("cls");
			cout << "  A processar..." << endl << endl << endl << endl;
			loadParse(menu_options[opcao] + "Nodes",
					menu_options[opcao] + "Roads",
					menu_options[opcao] + "Edges", grafo);

//			try {  DESCOMENTAR SE QUISERMOS GRAVAR FICHEIROS
//				//gravar stuff
//			} catch (File_Exp& exp) {
//				cor(BLACK, RED);
//				cerr << "Error" + exp.getIdErro() << endl;
//				cerr << exp.getDescricaoErro() << endl;
//				cor(BLACK, WHITE); //reset a� cor
//			}

		}
		if (tecla == 27) {
			//sair
		}
	}
}

void gotoxy(int xpos, int ypos)  // just take this function as it is.
		{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

vector<string> getDirFiles() {
	vector<string> files;
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir("../files/"))) {
		while ((entry = readdir(dir))) {
			if (strcmp(entry->d_name, ".") != 0
					&& strcmp(entry->d_name, "..") != 0)
				files.push_back(entry->d_name);
		}
	}
	return files;
}

void printMenuScroll(vector<string> options, int selected_option,
		const unsigned int max_per_screen) {
	int min = selected_option - (max_per_screen / 2);
	unsigned int max = selected_option + ((max_per_screen + 1) / 2);

	if (max < max_per_screen)
		max = max_per_screen;

	if (max > options.size())
		max = options.size();

	unsigned int range = max - min;

	if (range < max_per_screen)
		min = options.size() - max_per_screen;

	if (min < 0)
		min = 0;

	string temp;

	for (unsigned int i = min; i < max; i++) {
		if (i == selected_option) {
			cout << " ";
			cor(WHITE, BLACK);
			cout << options[i];
			cout << endl << endl;
			cor(BLACK, WHITE);  // reset a cor
		} else {
			temp = "  " + options[i];
			cout << temp;
			cout << endl << endl;
		}

	}
}

// First 4 bits are background, last 4 bits are foreground
void cor(int background, int foreground) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreground + 16 * background);
}

int teclas() {
	int tecla;
	tecla = getch();
	if (tecla != 0) {
		while (tecla != 13) //ENQUANTO DIFERENTE DE ENTER
		{
			tecla = getch();
			if (tecla == 72) //ACIMA
				return 1;
			if (tecla == 80) //ABAIXO
				return -1;
			if (tecla == 75) //ESQUERDA
				return 4;
			if (tecla == 77) //DIREITA
				return -4;
		}
		return 13;
	}
	return -1;
}

//FUNCAO RESPONSAVEL POR RESTRINGIR A VARIAVEL "opcao"
int RestringeOpcaoTeclas(int min, int max, int opcao) {
	if (opcao > min && opcao < ((max * -1) + 13))
		return opcao = (-1 * max); //reinicia a variavel na ultima opcao do menu
	else if (opcao < (max * -1) || opcao > (min + 13)) //Situação em que Sai fora da gama de opções possiveis (valor > que nº de opcoes possiveis)
		return opcao = min; //reinicia a variavel na 1a opção do menu
	else
		return opcao; //se não se verificam as restrições, entao devolve-se novamente a variavel intacta
}
