#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "Lista.h"
#include "Estufa.h"
#include "ficheiros.h"


void Imprimir_Lista(lista_t *lista, int estado); //Imprime o conteúdo da lista
void Pede_Parametros_para_Preencher_Estufa(lista_t *lista, char nome[30], float *temperaturaint, float *temperaturaext, int *humidade, int *areasuperficial, float *k, int *tipodefruta);//Pede os parametros que o utilizador deseja inserir na nova estufa criada
void Parametros_para_Alterar_Estufa(lista_t *lista, estufa_t *estufa); //Altera os parametros da estufa que o utilizador quiser para os valores que o mesmo escolher
void Humidade_Verificada(int h1);//Consoante o valor de h1 transmite ao utilizador se o valor da humidade é adequada ao tipo de fruta que se encontra dentro da estufa
void Temperatura_Verificada(int t1);//Consoante o valor de t1 transmite ao utilizador se o valor da temperatura é adequada ao tipo de fruta que se encontra dentro da estufa
void Para_e_Limpa();//Espera que o utilizafor clique numa tecla e depois limpa o terminal.

int Comparar_Nome_Menor_Igual_Maior_Apontado(void* data1, void* data2); //Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Nome_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int CompararTipodeFruta_Menor_Igual_Maior_Apontado(void* data1, void* data2); //Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Tipo_de_Fruta_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int CompararTemperaturar_Exterior_Menor_Igual_Maior_Apontado(void* data1, void* data2);//Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Exterior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int CompararTemperatura_Interior_Menor_Igual_Maior_Apontado(void* data1, void* data2);//Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int CompararHumidade_Menor_Igual_Maior_Apontado(void* data1, void* data2);//Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Humidade_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int CompararK_Menor_Igual_Maior_Apontado(void* data1, void* data2);//Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int CompararArea_Superficial_Paredes_Menor_Igual_Maior_Apontado(void* data1, void* data2);//Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)
int Encontrar_Estufa_Nome_Apontado(void* data, char nome[]);//Recebe um apontador generico e um char como parâmetro e retorna o resultado de Encontrar_Estufa_Nome(Obter_Conteudo_do_Node(data), nome)

int Guardar_na_Lista_Compacto(void* lista, char *nomeficheiro, int modo);//Se o modo for igual de 0 abre o ficheiro com o nome recebido limpando que tem no seu interior e caso seja diferente de 0 abre o ficheiro no modo append e guarda a lista no mesmo


int main(void){
	setlocale(LC_ALL, "portuguese");//Serve para Conhecer os é,ç,etcs
	
	//Lista Principal:
	lista_t *lista= Nova_Lista(),*ListaAuxiliar=Nova_Lista(); 

	//Listas Secundárias:
	lista_t *Lista_Ordenada_Alfabeticamente = Nova_Lista();
	lista_t *Lista_Ordenada_por_Temperatura_Exterior = Nova_Lista();
	lista_t *Lista_Ordenada_por_Temperatura_Interior = Nova_Lista();
	lista_t *Lista_Ordenada_por_Humidade = Nova_Lista();
	lista_t *Lista_Ordenada_por_K = Nova_Lista();
	lista_t *Lista_Ordenada_por_Area_Superficial_Paredes = Nova_Lista();
	lista_t *Lista_Ordenada_por_Tipo = Nova_Lista();


	node_t *node = NULL;
	node_t *apontador = NULL;
	estufa_t *estufa = NULL;

	char Ficheiro_Nome[30]; 
	char nomeficheiro[30];
	char nome[30];
	float temperaturaint=0, temperaturaext=0, k=0,Potencia=0;
	int humidade=0, areasuperficial=0, tipodefruta=0;
	int resposta = 0;
	int valido = -1;
	char nomeestufa[50];
	int i = 0;
	int Encontrou = -1;
	int Switch_Case_Number = 0,numero=0;
	int Carregou = 0;

	FILE *ficheiro=NULL;
	FILE *fp2 = Abrir_Ficheiro("Lista_de_Ficheiros.txt");
	  
	/*******************************************************************************************************************************************************************/

	//Carrega o que se encontra guardado da última vez que foi executado o código
	ficheiro = Abrir_Ficheiro("Estufas.txt");
	if (ficheiro == NULL)
		printf("Erro a abrir o ficheiro!\n");
	else
		printf("Sucesso a abrir o ficheiro!\n");
	estufa = NULL;
	node = Criar_Node();
	estufa = Criar_Estufa();

	while (Ler_Ficheiro(ficheiro, estufa, Obter_Tamanho_da_Estrutura_Estufa(), numero)) {
		Inserir_na_Lista_Topo(lista, node, (estufa_t *)estufa);
		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_Alfabeticamente, apontador, (node_t*)node, &Comparar_Nome_Menor_Igual_Maior_Apontado);

		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Tipo, apontador, (node_t*)node, &CompararTipodeFruta_Menor_Igual_Maior_Apontado);

		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Temperatura_Exterior, apontador, (node_t*)node, &CompararTemperaturar_Exterior_Menor_Igual_Maior_Apontado);

		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Temperatura_Interior, apontador, (node_t*)node, &CompararTemperatura_Interior_Menor_Igual_Maior_Apontado);

		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Humidade, apontador, (node_t*)node, &CompararHumidade_Menor_Igual_Maior_Apontado);

		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_K, apontador, (node_t*)node, &CompararK_Menor_Igual_Maior_Apontado);

		apontador = Criar_Node();
		Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Area_Superficial_Paredes, apontador, (node_t*)node, &CompararArea_Superficial_Paredes_Menor_Igual_Maior_Apontado);

		node = Criar_Node();
		estufa = Criar_Estufa();

		numero++;

	}
	Fechar_Ficheiro(ficheiro);
	numero = 0;

	/*******************************************************************************************************************************************************************/
	
	
	Para_e_Limpa();


	while (valido==-1) {
		printf("***************************************************************\nFuncionalidades:\n***************************************************************\n->Estufa e Lista:\n***************************************************************\n1->Criar Estufa\n2->Alterar Estufa\n3->Remover Estufa\n4->Organizar Lista\n5->Imprimir Lista\n6->Verificar Humidade\n7->Verificar Temperatura\n8->Aquecimento\n9->Limpar Lista\n***************************************************************\n->Ficheiros:\n***************************************************************\n10->Carregar Lista Guardada\n11->Limpar Ficheiro\n12->Guardar Lista\n***************************************************************\n13-Sair\n");
		
		while (scanf("%d", &resposta) != 1) {
			while (getchar() != '\n');
		}
		printf("***************************************************************\n");
		switch (resposta) {

		case 1 :
/*******************************************************************************************************************************************************************/
				//Caso de Criar uma Estufa
				Para_e_Limpa();
				//São pedidos os parâmetros para criar uma estufa
				Pede_Parametros_para_Preencher_Estufa(lista,nome, &temperaturaint, &temperaturaext, &humidade, &areasuperficial, &k, &tipodefruta);
				estufa = Criar_Estufa();
				//É preenchida a estufa com os parâmetroes recebidos pela funºão anterior
				estufa = Preencher_Estufa(estufa,nome, temperaturaint, temperaturaext, humidade, areasuperficial, k, tipodefruta);
				
				//A estufa criada é inserida na Lista Principal
				node = Criar_Node();
				Inserir_na_Lista_Topo(lista,node,(estufa_t *)estufa);
				
				//Nas Listas Secundárias é Inserido um Apontador que aponta para o node que contem a estufa criada
				/************************************************************************************************/
				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_Alfabeticamente, apontador, (node_t*)node,&Comparar_Nome_Menor_Igual_Maior_Apontado);
				
				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Tipo, apontador, (node_t*)node, &CompararTipodeFruta_Menor_Igual_Maior_Apontado);
				
				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Temperatura_Exterior, apontador, (node_t*)node, &CompararTemperaturar_Exterior_Menor_Igual_Maior_Apontado);

				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Temperatura_Interior, apontador, (node_t*)node, &CompararTemperatura_Interior_Menor_Igual_Maior_Apontado);

				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Humidade, apontador, (node_t*)node, &CompararHumidade_Menor_Igual_Maior_Apontado);
				
				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_K, apontador, (node_t*)node, &CompararK_Menor_Igual_Maior_Apontado);
				
				apontador = Criar_Node();
				Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Area_Superficial_Paredes, apontador, (node_t*)node, &CompararArea_Superficial_Paredes_Menor_Igual_Maior_Apontado);
				/************************************************************************************************/

				
				Para_e_Limpa();
				break;
/*******************************************************************************************************************************************************************/
		case 2:
/*******************************************************************************************************************************************************************/
			//Caso de Alterar uma Estufa

			Para_e_Limpa();

			//É perguntado ao utilizador qual o nome da estufa que deseja remover
			printf("Qual o nome da estufa que deseja alterar?\n");
			scanf("%s", nomeestufa);
			//Confirma-se se existe uma estufa com este nome
			node = Encontrar_Node(lista, &Encontrar_Estufa_Nome, (char*)nomeestufa);
				
			if (node) {
					//Se existir 
					Parametros_para_Alterar_Estufa(lista,Obter_Conteudo_do_Node(node));				
					Encontrou = 1;
				}
				else Encontrou = 0; //Se não existir
		
		
			if(!Encontrou)
			printf("Não foi encontrada a estufa.\n"); //Não foi encontrada uma estufa
			else printf("Encontrada com Sucesso!!\n");	//Foi mudada com Sucesso
			
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 3:
/*******************************************************************************************************************************************************************/
			//Caso de Remover uma estufa
			Para_e_Limpa();
			
			//Recebe o nome da estufa que o utilizador deseja romover
			printf("Qual o nome da estufa que deseja remover?\n");
			scanf("%s", nomeestufa);
			//Remove nas listas secundárias primeiro e por ultimo na principal, e caso remova com sucesso imprime no ecrã que removeu com sucesso.
			if (Remover_da_Lista(Lista_Ordenada_Alfabeticamente, &Encontrar_Estufa_Nome_Apontado, nomeestufa)&& (Remover_da_Lista(Lista_Ordenada_por_Temperatura_Interior, &Encontrar_Estufa_Nome_Apontado, nomeestufa))&& (Remover_da_Lista(Lista_Ordenada_por_Temperatura_Exterior, &Encontrar_Estufa_Nome_Apontado, nomeestufa))&& (Remover_da_Lista(Lista_Ordenada_por_Humidade, &Encontrar_Estufa_Nome_Apontado, nomeestufa))&& (Remover_da_Lista(Lista_Ordenada_por_K, &Encontrar_Estufa_Nome_Apontado, nomeestufa))&& (Remover_da_Lista(Lista_Ordenada_por_Area_Superficial_Paredes, &Encontrar_Estufa_Nome_Apontado, nomeestufa))&& (Remover_da_Lista(Lista_Ordenada_por_Tipo, &Encontrar_Estufa_Nome_Apontado, nomeestufa))&& (Remover_da_Lista(lista, &Encontrar_Estufa_Nome, nomeestufa))) {
				printf("Removida com sucesso!!\n");
				
			}
			else printf("Estufa não existe!\n"); //Caso não conseguiu remover, é porque a estufa não existe.
			
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 4:
/*******************************************************************************************************************************************************************/
			/*Caso de Ordenar a Lista Principal
			Consoante a escolha do utilizador ordena a lista principal. 
			*/
			Para_e_Limpa();
			
			printf("Rretende organizar a lista?\n");
			printf("1->K\n");
			printf("2->Humidade\n");
			printf("3->Tipo de Fruta\n");
			printf("4->Alfabeticamente\n");
			printf("5->Temperatura Exterior\n");
			printf("6->Temperatura Interior\n");
			printf("7->Area Superficial das Paredes\n");

			scanf("%d", &Switch_Case_Number);
			Para_e_Limpa();

			switch (Switch_Case_Number) {
			
			case 1:
			{	if (Ordenar_Lista(lista, &Comparar_K_Menor_Igual_Maior))
				printf("Ordenada lista por K com Sucesso!!");
			break; }

			case 2:
			{	if (Ordenar_Lista(lista, &Comparar_Humidade_Menor_Igual_Maior))
				printf("Ordenada lista por Humidade com Sucesso!!");
			break; }
			
			case 3:
			{	if (Ordenar_Lista(lista, &Comparar_Tipo_de_Fruta_Menor_Igual_Maior))
				printf("Ordenada lista por Tipo de Fruta com Sucesso!!");
			break; }

			case 4:
			{
				if (Ordenar_Lista(lista, &Comparar_Nome_Menor_Igual_Maior))
					printf("Ordenada Alfabeticamente com Sucesso!!");
				break; }
			
			case 5:
			{	if (Ordenar_Lista(lista, &Comparar_Temperatura_Exterior_Menor_Igual_Maior))
				printf("Ordenada lista por Temperatura Exterior com Sucesso!!");
			break; }
			case 6:
			{	if (Ordenar_Lista(lista, &Comparar_Temperatura_Interior_Menor_Igual_Maior))
				printf("Ordenada lista por Temperatura Interior com Sucesso!!");
			break; }
			case 7:
			{	if (Ordenar_Lista(lista, &Comparar_Area_Superficial_Paredes_Menor_Igual_Maior))
				printf("Ordenada lista por Area Superficial das Paredes com Sucesso!!");
			break; }
			default: break;
			}

			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 5:
/*******************************************************************************************************************************************************************/
			/*Caso de Imprimir a Lista
			Consoante a escolha do utilizador imprime no ecrã ou a lista principal ou as listas secundárias(quais estão organizadas de formas diferentes).
			*/
			Para_e_Limpa();
			
			printf("Como pretende imprimir as estufas?\n");
			printf("1->Normal\n");
			printf("2->Organizada por K\n");
			printf("3->Organizada por Humidade\n");
			printf("4->Organizada Alfabeticamente\n");
			printf("5->Organizada por Tipo de Fruta\n");
			printf("6->Organizada por Temperatura Exterior\n");
			printf("7->Organizada por Temperatura Interior\n");
			printf("8->Organizada Area Superficial das Paredes\n");
			
			scanf("%d", &Switch_Case_Number);
			
			Para_e_Limpa();

			switch (Switch_Case_Number) {
			case 1:
			{
				Imprimir_Lista(lista, 0);
				break; }

			case 2:
			{	Imprimir_Lista(Lista_Ordenada_por_K, 1);
				break; }

			case 3:
			{	Imprimir_Lista(Lista_Ordenada_por_Humidade, 1);
				
				break; }
			
			case 4:
			{	Imprimir_Lista(Lista_Ordenada_Alfabeticamente, 1);
				break; }

			case 5:
			{	Imprimir_Lista(Lista_Ordenada_por_Tipo, 1);
				break; }

			case 6:
			{	Imprimir_Lista(Lista_Ordenada_por_Temperatura_Exterior, 1);
				break; }

			case 7:
			{	Imprimir_Lista(Lista_Ordenada_por_Temperatura_Interior, 1);
				break; }

			case 8:
			{	Imprimir_Lista(Lista_Ordenada_por_Area_Superficial_Paredes, 1);
				break; }
	
			default: break;
			}
			
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 6:
/*******************************************************************************************************************************************************************/
			//Caso de Verificar Humidade
			//Verifica a humidade da estufa que o utilizador deseja verificar.
			Para_e_Limpa();
			
			if (Obter_Cabeca_da_Lista(lista)) {
				printf("Qual o nome da estufa que deseja verificar a humidade?\n");
				scanf("%s", nomeestufa);
				node = Encontrar_Node(lista, &Encontrar_Estufa_Nome, nomeestufa);
				if(node)
				Humidade_Verificada(Verificar_Humidade((estufa_t*)Obter_Conteudo_do_Node(node)));
				else printf("\nNão existe a estufa na lista!\n");
			}
			else printf("\nCrie primeiro uma estufa ou de load de uma.\n");


			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 7:
/*******************************************************************************************************************************************************************/
			//Caso de Verificar a Temperatura
			//Verifica a Temperatura da estufa que o utilizador deseja verificar.

			Para_e_Limpa();
			if (Obter_Cabeca_da_Lista(lista)) {
				printf("Qual estufa deseja verificar a temperatura?\n");
				scanf("%s", nomeestufa);
				node = Encontrar_Node(lista, &Encontrar_Estufa_Nome, nomeestufa);
				if (node)
				Temperatura_Verificada(Verificar_Temperatura((estufa_t*)Obter_Conteudo_do_Node(node)));
				else printf("\nNão existe a estufa na lista!\n");
			}
			else printf("\nCrie primeiro uma estufa ou de load de uma.\n");
			
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 8:
/*******************************************************************************************************************************************************************/
			//Caso do Aquecimento
			//Retorna o aquecimento, que é a potencia necessário para subir 1 grau na estufa. 
			
			Para_e_Limpa();

			if (Obter_Cabeca_da_Lista(lista)) {
				printf("Qual estufa deseja saber a potencia necessária para a aquecer?\n");
				scanf("%s", nomeestufa);
				node = Encontrar_Node(lista, &Encontrar_Estufa_Nome, nomeestufa);
				if (node) {
					Potencia = Aquecimento(Obter_Conteudo_do_Node(node));
					if (Potencia < 0)
						printf("Potência necessária para subir um grau é: %2.2f\n", (-Potencia));
					else
						printf("Potência necessária para subir um grau é: %2.2f\n", Potencia);
				}

				else printf("\nCrie primemiro uma estufa ou de load de uma.\n");
			}
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 9: 
/*******************************************************************************************************************************************************************/
			//Caso de Limpar a lista
			
			Para_e_Limpa();
			//Limpa Primeiro as Listas Secundárias
			Limpar_Lista(Lista_Ordenada_Alfabeticamente);
			Limpar_Lista(Lista_Ordenada_por_Temperatura_Exterior);
			Limpar_Lista(Lista_Ordenada_por_Temperatura_Interior);
			Limpar_Lista(Lista_Ordenada_por_Humidade);
			Limpar_Lista(Lista_Ordenada_por_K);
			Limpar_Lista(Lista_Ordenada_por_Area_Superficial_Paredes);
			Limpar_Lista(Lista_Ordenada_por_Tipo);
			//E por fim a lista principal.
			Limpar_Lista(lista);
			
			printf("\nLista limpa!!\n");
		
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 10:
/*******************************************************************************************************************************************************************/
			//Caso de Carregar estufas de um ficheiro
			Para_e_Limpa();
			
			numero = 0;
			//Imprime no ecrã a lista de ficheiros contido no Lista_de_Ficheiros.txt, para auxiliar o utilizador
			printf("Nome de Ficheiros:\n");
			while (Ler_Ficheiro(fp2, nomeficheiro, (sizeof(nomeficheiro) / sizeof(nomeficheiro[0])), numero)) {
				printf("%d->%s\n", numero+1, nomeficheiro);
				numero++;
			}
			numero = 0;
			
			//Pergunta ao utilizador qual o nome do ficheiro que pretende carregar
			printf("Qual o nome do ficheiro do qual pretende carregar as estufas?\n");
			
			//Limpa o \n (enter)
			while (getchar() != '\n');
			//Le o nome do ficheiro escolhido pelo utilazor
			scanf("%s", nomeficheiro);
			//Limpa o \n(enter)
			while (getchar() != '\n');

			while (Ler_Ficheiro(fp2, Ficheiro_Nome, (sizeof(nomeficheiro) / sizeof(nomeficheiro[0])), numero)) {
				//Caso o ficheiro escolhido esteja no ficheiro Lista_de_Ficheiros.txt, quer dizer que o ficheiro exista, logo abre-o
				if (strcmp(nomeficheiro, Ficheiro_Nome) == 0) {
					ficheiro = Abrir_Ficheiro(Ficheiro_Nome);
					//Caso haja um problema a abrir avisa o utilizador e sai.
					if (ficheiro == NULL) {
						printf("Erro a abrir o ficheiro!\n");
						Para_e_Limpa();
						break;
					}
					else//Caso abra com sucesso avisa o utilizador e continua para a inserção das estufas contidas no ficheiro.
						printf("Sucesso a abrir o ficheiro!\n");
					//Inserção das estufas nas listas
					estufa = NULL;
					node = Criar_Node();
					estufa = Criar_Estufa();
					numero = 0;
					while (Ler_Ficheiro(ficheiro, estufa, Obter_Tamanho_da_Estrutura_Estufa(), numero)) {
						//Caso na lista já exista uma estufa com o mesmo nome, não a insere
						if (!Encontrar_Node(lista, &Encontrar_Estufa_Nome, Obter_Nome_Estufa(estufa))) {
							/************************************************************************************************/
							Inserir_na_Lista_Topo(lista, node, (estufa_t *)estufa);
							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_Alfabeticamente, apontador, (node_t*)node, &Comparar_Nome_Menor_Igual_Maior_Apontado);

							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Tipo, apontador, (node_t*)node, &CompararTipodeFruta_Menor_Igual_Maior_Apontado);

							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Temperatura_Exterior, apontador, (node_t*)node, &CompararTemperaturar_Exterior_Menor_Igual_Maior_Apontado);

							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Temperatura_Interior, apontador, (node_t*)node, &CompararTemperatura_Interior_Menor_Igual_Maior_Apontado);

							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Humidade, apontador, (node_t*)node, &CompararHumidade_Menor_Igual_Maior_Apontado);

							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_K, apontador, (node_t*)node, &CompararK_Menor_Igual_Maior_Apontado);

							apontador = Criar_Node();
							Inserir_na_Lista_Ordenadamente(Lista_Ordenada_por_Area_Superficial_Paredes, apontador, (node_t*)node, &CompararArea_Superficial_Paredes_Menor_Igual_Maior_Apontado);

							node = Criar_Node();
							estufa = Criar_Estufa();
							/************************************************************************************************/
						}
						numero++;

					}
					//Fecha o ficheiro
					Fechar_Ficheiro(ficheiro);
					
					Para_e_Limpa();
					Carregou = 1;
					break;
					
				}
				numero++;
			}
			if (!Carregou) //Se não carregou avisa o utilizador que não teve sucesso.
				printf("Sem Sucesso a Carregar!\n");
			else //Se carregou avisa o utilizador que teve sucesso.
				printf("Com Sucesso a Carregar!\n");
			Carregou = 0;
				
			Para_e_Limpa();
			break;
/*******************************************************************************************************************************************************************/
		case 11:
/*******************************************************************************************************************************************************************/
			//Caso de Limpar o Conteúdo de um Ficheiro

			Para_e_Limpa();
			
			numero = 0;
			//Imprime no ecrã a lista de ficheiros contido no Lista_de_Ficheiros.txt, para auxiliar o utilizador
			printf("Nome de Ficheiros:\n");
			while (Ler_Ficheiro(fp2, nomeficheiro, (sizeof(nomeficheiro) / sizeof(nomeficheiro[0])), numero)) {
				printf("%d->%s\n",numero,nomeficheiro);
				numero++;
			}
			numero = 0;

			//Pergunta ao utilizador o nome do ficheiro que pretende apagar o conteudo.
			printf("Qual o nome do ficheiro que pretende apagar o conteúdo?\n");

			//Limpa o \n (enter)
			while (getchar() != '\n');
			//Lê a resposta do utilizador.
			scanf("%s", nomeficheiro);
			//Limpa o \n (enter)
			while (getchar() != '\n');

			if (Limpar_Ficheiro(nomeficheiro))
				printf("Ficheiro Limpo com Sucesso!!\n"); //Avisa o utilizador caso tenha conseguido limpar o ficheiro com sucesso.
			else 
				printf("Ficheiro Limpo com Insucesso!!\n"); //Avisa o utilizador caso não tenha conseguido limpar o ficheiro com sucesso.
			
			Para_e_Limpa();
			break;

/*******************************************************************************************************************************************************************/
		case 12:
/*******************************************************************************************************************************************************************/
			//Caso de Guardar a Lista Principal Num Ficheiro			
			
			Para_e_Limpa();

			//Pergunta ao utlizador qual o nome do ficheiro que pretende guardar a lista atual e le o mesmo.
			printf("Qual o nome do ficheiro que pretende guardar a lista atual?\n");
			scanf("%s", nomeficheiro);
			//Limpa o \n (enter)
			while (getchar() != '\n');
			
			//Guarda a lista no nome do ficheiro recebido
			if (Guardar_na_Lista_Compacto(lista, nomeficheiro, 0)) {
				printf("Guardada com Sucesso!\n");
				//Adiciona o nome do ficheiro ao ficheiro Lista_de_Ficheiros.txt
				Adicionar_a_Ficheiro(fp2, nomeficheiro, (sizeof(nomeficheiro)/sizeof(nomeficheiro[0])));
				
				Para_e_Limpa();
				break;
			}else
			printf("Não guardada com sucesso!");
			
			Para_e_Limpa();
			break;

/*******************************************************************************************************************************************************************/
		default:
			valido = 1;
		}
	}

	
	
	Guardar_na_Lista_Compacto(lista, "estufas.txt",0); //Guardar lista no ficheiro antes de sair
	Fechar_Ficheiro(fp2); //Fecha o ficheiro apontado por fp2.

	Destruir_Estufa(estufa); //Liberta a memória dinâmica reservada para a estufa.
	//Limpam-se as listas, ou seja, liberta-se a memória dinâmica reservada para as mesmas(os nodes).
	Limpar_Lista(Lista_Ordenada_Alfabeticamente); 
	Limpar_Lista(Lista_Ordenada_por_Temperatura_Exterior);
	Limpar_Lista(Lista_Ordenada_por_Temperatura_Interior);
	Limpar_Lista(Lista_Ordenada_por_Humidade);
	Limpar_Lista(Lista_Ordenada_por_K);
	Limpar_Lista(Lista_Ordenada_por_Area_Superficial_Paredes);
	Limpar_Lista(Lista_Ordenada_por_Tipo);
	Limpar_Lista(lista);

	 //Liberta-se as memórias dinâmicas reservadas para as cabeças das listas. 
	free(Lista_Ordenada_Alfabeticamente);
	free(Lista_Ordenada_por_Temperatura_Exterior);
	free(Lista_Ordenada_por_Temperatura_Interior);
	free(Lista_Ordenada_por_Humidade);
	free(Lista_Ordenada_por_K);
	free(Lista_Ordenada_por_Area_Superficial_Paredes);
	free(Lista_Ordenada_por_Tipo);

	free(lista);
	
	return 0;
}



/**********************************************************************************************************************************************/
/*
 Nome:
		 Guardar_na_Lista_Compacto

 Descrição:
		Se o modo for igual de 0 abre o ficheiro com o nome recebido limpando que tem no seu interior e caso seja diferente de 0 abre o ficheiro no modo append e guarda a lista no mesmo

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		lista           Apontador para void           I       Um apontador para void
		nomeficheiro	Apontador para char			  I       Um apontador para char
		modo            Int							  I		  Um numero natural		

 Retorna:
		Retorna um inteiro
*/

int Guardar_na_Lista_Compacto(void* lista,char *nomeficheiro,int modo) {
	FILE *fp1=NULL;

	if (modo) {
		fp1 = Abrir_Ficheiro(nomeficheiro);   //modo!= 0 guarda no final em append
	}	
	else { 
	fp1 = fopen(nomeficheiro, "w+b");	//modo ==0 limpa o ficheiro e guarda.
		}

	node_t *node = NULL;

	if (fp1 == NULL) {
		printf("\nErro a abrir o ficheiro!\n");
		return 0;
	}
	else 
		printf("\nSucesso a abrir o ficheiro!\n");

	node = Obter_Cabeca_da_Lista(lista);
	while (node) {
		Adicionar_a_Ficheiro(fp1, Obter_Conteudo_do_Node(node), Obter_Tamanho_da_Estrutura_Estufa());
		node = Obter_Node_Seguinte(node);
	}
	fclose(fp1); 

	return 1;
}
/**********************************************************************************************************************************************/
/*
 Nome:
		 Para_e_Limpa

 Descrição:
		Espera que o utilizafor clique numa tecla e depois limpa o terminal. 

 Argumentos:
		Argumento       Tipo		 I/O      Descrição	

 Retorna:
		Nao retorna nada
*/
void Para_e_Limpa() {
	system("pause");
	system("CLS");
	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Nome_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Nome_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int Comparar_Nome_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return (Comparar_Nome_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));
}
/***********************************************************************************************************************************************/
/*
 Nome:
		CompararTipodeFruta_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Tipo_de_Fruta_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int CompararTipodeFruta_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return(Comparar_Tipo_de_Fruta_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));
}
/***********************************************************************************************************************************************/
/*
 Nome:
		CompararTemperaturar_Exterior_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Exterior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int CompararTemperaturar_Exterior_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return(Comparar_Temperatura_Exterior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));
}
/***********************************************************************************************************************************************/
/*
 Nome:
		CompararTemperatura_Interior_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int CompararTemperatura_Interior_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return(Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));
}
/***********************************************************************************************************************************************/
/*
 Nome:
		CompararHumidade_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Humidade_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int CompararHumidade_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return(Comparar_Humidade_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));
}
/***********************************************************************************************************************************************/
/*
 Nome:
		CompararK_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_K_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int CompararK_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return(Comparar_K_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));
}
/***********************************************************************************************************************************************/
/*
 Nome:
		CompararArea_Superficial_Paredes_Menor_Igual_Maior_Apontado

 Descrição:
		Recebe dois apontadores genericos como parâmetro e retorna o resultado de Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data1				Apontador para void           I       Um apontador para void
		data2    			Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/
int CompararArea_Superficial_Paredes_Menor_Igual_Maior_Apontado(void* data1, void* data2) {
	return(Comparar_Temperatura_Interior_Menor_Igual_Maior(Obter_Conteudo_do_Node(data1), Obter_Conteudo_do_Node(data2)));

}
/***********************************************************************************************************************************************/
/*
 Nome:
		Encontrar_Estufa_Nome_Apontado

 Descrição:
		Recebe um apontador generico e um char como parâmetro e retorna o resultado de Encontrar_Estufa_Nome(Obter_Conteudo_do_Node(data), nome)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		data				Apontador para void           I       Um apontador para void
		nome    			char                          I       Um array

 Retorna:
		Retorna um inteiro
*/
int Encontrar_Estufa_Nome_Apontado(void* data, char nome[]) {
	return(Encontrar_Estufa_Nome(Obter_Conteudo_do_Node(data), nome));

}

/**********************************************************************************************************************************************/
/*
 Nome:
		 Imprimir_Lista

 Descrição:
		Imprime o conteúdo da lista 

 Argumentos:
		Argumento       Tipo						 I/O      Descrição	
		lista           Apontador para lista_t        I       Um apontador para lista_t
		estado          Int                           I       Um numero natural

 Retorna:
		Nao retorna nada
*/

void Imprimir_Lista(lista_t *lista, int estado) {
	node_t *node = NULL;
	
	node = Obter_Cabeca_da_Lista(lista);
	
		if (Obter_Cabeca_da_Lista(lista) == NULL) {
			printf("\n   A lista está vazia!!\n\n");
			return;
		}
		while (node) {

		estufa_t *estufa= NULL;
		if (!estado)
		estufa = (estufa_t *)Obter_Conteudo_do_Node(node);
		else 
		estufa = (estufa_t *)Obter_Conteudo_do_Node(Obter_Conteudo_do_Node(node));
		printf("----------->INICIO DA ESTUFA: %s\n", Obter_Nome_Estufa(estufa));
		printf("Nome: %s\n", Obter_Nome_Estufa(estufa));
		printf("Temperatura interior: %2.2f\n", Obter_Temperatura_Interior(estufa));
		printf("Temperatura exterior: %2.2f\n", Obter_Temperatura_Exterior(estufa));
		printf("Area Superficial: %d\n", Obter_Area_Superficial_Paredes((estufa)));
		printf("Humidade: %d\n", Obter_Humidade(estufa));
		printf("K: %2.2f\n", Obter_K(estufa));
		printf("Tipo de fruta: %d\n", Obter_Tipo_de_Fruta(estufa));
		printf("-----------FIM DA ESTUFA %s\n\n\n\n", Obter_Nome_Estufa(estufa));

		node = Obter_Node_Seguinte(node);
	
	}

	return;
	

	}
/**********************************************************************************************************************************************/
/*
 Nome:
		 Pede_Parametros_para_Preencher_Estufa

 Descrição:
		Pede os parametros que o utilizador deseja inserir na nova estufa criada

 Argumentos:
		Argumento				Tipo						 I/O      Descrição
		lista     				Apontador para lista_t        I       Um apontador para lista_t
		nome					Apontador para char			  I		  Um ãpontador para um array
		temperaturaint			Apontador pra float			  I       um apontador para um valor racional
		temperaturaext			Apontador para float		  I       um apontador para um valor racional
		humidade				Apontador para int            I       um apontador para um valor natural
		areasuperficialparedes  Apontador para int 			  I       um apontador para um valor natural
		k                       Apontador para in             I       um apontador para um valor natural
		tipodefruta             Apontador para int            I       um apontador para um valor natural

 Retorna:
		Nao retorna nada
*/

	void Pede_Parametros_para_Preencher_Estufa(lista_t *lista,char nome[30], float *temperaturaint, float *temperaturaext, int *humidade, int *areasuperficial, float *k, int *tipodefruta) {
		
	
		do {
			printf("Qual e o nome da estufa?\n");
			while (getchar() != '\n');
			scanf("%s", nome);
		}while (Encontrar_Node(lista,&Encontrar_Estufa_Nome,(char*)nome));

	do {
		printf("Qual e a temperatura exterior?(entre -60 e 120 graus celcios)\n");
		while (getchar() != '\n');
		
	} while (scanf("%f", temperaturaext)!=1 || *(temperaturaext) > 120 || *(temperaturaext) < (-60) );

	do {
		printf("Qual e a temperatura interior?(entre -60 e 120 graus celcios)\n");
		while (getchar() != '\n');
		
	} while (scanf("%f", temperaturaint)!=1 || *temperaturaint > 120 || *temperaturaint < -60);

	do {
		printf("Qual e a humidade?(entre 0 e 100)\n");
		while (getchar() != '\n');
	} while (scanf("%d", humidade)!=1 || *humidade < 0 || *humidade > 100);

	do {
		printf("Qual e a area superficial da estufa?\n");
		while (getchar() != '\n');
	} while (scanf("%d", areasuperficial)!=1 ||*areasuperficial < 0);

	do {
		printf("Qual e o coeficiente de transmissao da cobertura?(entre 2.5 e 7)\n");
		while (getchar() != '\n');
	} while (scanf("%f", k)!=1 ||*k < (float)2.5 || *k > 7);

	do {
		printf("Qual e o tipo de fruta/legume na estufa?(entre 1 e 13 consulte a tabela)\n");
		while (getchar() != '\n');
	} while (scanf("%d", tipodefruta)!=1 ||*tipodefruta < 1 || *tipodefruta > 13);

	return;
}

/**********************************************************************************************************************************************/
/*
 Nome:
		Parametros_para_Alterar_Estufa

 Descrição:
		Altera os parametros da estufa que o utilizador quiser para os valores que o mesmo escolher 

 Argumentos:
		Argumento       Tipo						 I/O      Descrição	
		lista           Apontador para lista_t        I       Um apontador para lista_t
		estufa          Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Nao retorna nada
*/

void Parametros_para_Alterar_Estufa(lista_t *lista,estufa_t *estufa) {
		char nome[30];
		float temperaturaint, temperaturaext, k;
		int humidade,areasuperficial, tipodefruta;
		int resposta = 0;
		int valido = -1;
		int NaoFoiEscolhido1 = 1, NaoFoiEscolhido2 = 1, NaoFoiEscolhido3 = 1, NaoFoiEscolhido4 = 1, NaoFoiEscolhido5 = 1, NaoFoiEscolhido6 = 1, NaoFoiEscolhido7 = 1;

		
		do {
			if (!NaoFoiEscolhido1 && !NaoFoiEscolhido2 && !NaoFoiEscolhido3 && !NaoFoiEscolhido4 && !NaoFoiEscolhido5 && !NaoFoiEscolhido6 && !NaoFoiEscolhido7)
				resposta = 8;
			else {
				printf("O que desja alterar?\n");
				if (NaoFoiEscolhido1)printf("1->Nome\n");
				if (NaoFoiEscolhido2)printf("2->Temperatura no exterior\n");
				if (NaoFoiEscolhido3)printf("3->Temperatura no interior\n");
				if (NaoFoiEscolhido4)printf("4->Humidade\n");
				if (NaoFoiEscolhido5)printf("5->Coeficiente de transmissao de cobertura\n");
				if (NaoFoiEscolhido6)printf("6->Area superficial das paredes\n");
				if (NaoFoiEscolhido7)printf("7->Tipo de Fruta ou Legume\n");
				printf("8->Voltar para tras\n\n");
				printf("Resposta: ");
				scanf("%d", &resposta);
			}
			printf("\n");
			
			switch (resposta)
			{
			case 1: {
				if (NaoFoiEscolhido1) {
					do {
						printf("Qual e o novo nome da estufa?\n");
						while (getchar() != '\n');
						scanf("%s", nome);
					} while (Encontrar_Node(lista, &Encontrar_Estufa_Nome, (char*)nome));
					Alterar_Nome_Estufa(estufa, nome);
					NaoFoiEscolhido1 = 0;
				}
				break;
			}
			case 2: {
				if (NaoFoiEscolhido2) {
					do {
						printf("Qual temperatura nova exterior deseja ?(entre -60 e 120 graus celcios)\n");
						while (getchar() != '\n');

					} while (scanf("%f", &temperaturaext) != 1 || temperaturaext > 120 || temperaturaext < (-60));

					NaoFoiEscolhido2 = 0;
					Alterar_Temperatura_Exterior(estufa, (float*)&temperaturaext);

				}
				printf("\n");
				break;
			}

			case 3: {
				if (NaoFoiEscolhido3) {
					do {
						printf("Qual temperatura nova interior deseja ?(entre -60 e 120 graus celcios)\n");
						while (getchar() != '\n');

					} while (scanf("%f", &temperaturaint) != 1 || temperaturaint > 120 || temperaturaint < -60);

					printf("\n");
					NaoFoiEscolhido3 = 0;
					Alterar_Temperatura_Interior(estufa, (float*)&temperaturaint);

				}
				break;
			}

			case 4: {
				if (NaoFoiEscolhido4) {
					do {
						printf("Qual é a nova humidade?(entre 0 e 100)\n");
						while (getchar() != '\n');
					} while (scanf("%d", &humidade) != 1 || humidade < 0 || humidade > 100);

					NaoFoiEscolhido4 = 0;
					Alterar_Humidade(estufa, (int*)humidade);
				}
				printf("\n");
				
				break;
			}

			case 5:
			{
				if (NaoFoiEscolhido5) {
					do {
						printf("Qual é o novo coeficiente de transmissao da cobertura?(entre 2.5 e 7)\n");
						while (getchar() != '\n');
					} while (scanf("%f", &k) != 1 || k < (float)2.5 || k > 7);
					
					printf("\n");
					NaoFoiEscolhido5 = 0;
					Alterar_K(estufa, (float*)&k);
					
				}
				break;
			}

			case 6: {
				if (NaoFoiEscolhido6) {
					do {
						printf("Qual é a nova area superficial da estufa?\n");
						while (getchar() != '\n');
					} while (scanf("%d", &areasuperficial) != 1 || areasuperficial < 0);

					NaoFoiEscolhido6 = 0;
					printf("\n");
					Alterar_Area_Superficial_Paredes(estufa, (int*)areasuperficial);
				}
				break;
			}

			case 7:
			{
				if (NaoFoiEscolhido7) {
					do {
						printf("Qual é o novo tipo de fruta ou legume?: (entre 1 e 13 consulte a tabela)\n");
						printf("\n1-> Alface\n2-> Espinafres\n3-> Ervilhas\n4-> Acelgas\n5-> Aipo\n6-> Feijoes\n7-> Tomates\n8-> Pimento\n9-> Pepino\n10-> Beringela\n11-> Melancia\n12-> Melão\n13-> Abobora\n");
						while (getchar() != '\n');
					} while (scanf("%d", &tipodefruta) != 1 || tipodefruta < 1 || tipodefruta > 13);
					NaoFoiEscolhido7 = 0;
					printf("\n");
					Alterar_Tipo_de_Fruta(estufa, (int*)tipodefruta);
				}
				break;

			}

			default:
				valido = 1;

			}
			printf("Carregue em qualquer tecla\n");
			system("pause");
			system("CLS");

		} while (valido == -1);

		return;
	}


/**********************************************************************************************************************************************/
/*
 Nome:
		Humidade_Verificada

 Descrição:
		Consoante o valor de h1 transmite ao utilizador se o valor da humidade é adequada ao tipo de fruta que se encontra dentro da estufa

 Argumentos:
		Argumento       Tipo		 I/O      Descrição	
		h1				int			  I		  Um numero natural

 Retorna:
		Nao retorna nada
*/
void Humidade_Verificada(int h1) {
	if (h1 == 1)
		printf("A humidade da estufa esta menor que a indicada.\n");
	if (h1 == 2)
		printf("A humidade da estufa esta maior que a indicada.\n");
	if (h1 == -1)
		printf("A humidade é a indicada.\n");
	return;
}
/**********************************************************************************************************************************************/
/*
 Nome:
		Temperatura_Verificada

 Descrição:
		Consoante o valor de t1 transmite ao utilizador se o valor da temperatura é adequada ao tipo de fruta que se encontra dentro da estufa

 Argumentos:
		Argumento       Tipo		 I/O      Descrição	
		t1				int			  I		  Um numero natural

 Retorna:
		Nao retorna nada
*/
void Temperatura_Verificada(int t1) {
	if (t1 == 1)
		printf("A temperatura da estufa esta menor que a indicada.\n");
	if (t1 == 2)
		printf("A temperatura da estufa esta maior que a indicada.\n");
	if (t1 == 3)
		printf("A temperatura esta em estado critico!!\n");
	if (t1 == -1)
		printf("A temperatura é a indicada.\n");
	return;
}
/**********************************************************************************************************************************************/