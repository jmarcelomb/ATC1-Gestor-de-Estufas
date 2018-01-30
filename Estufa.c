#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estufa.h"


typedef struct estufa {
	char nome[30];
	float temperaturaext, temperaturaint;
	int humidade;
	float k; //coeficiente de transmissão da cobertura, varia de 2,5 a 7
	int areasuperficieparedes; //area da superficie das paredes da esufa
	int tipodefruta;
}estufa_t;

/**********************************************************************************************************************************************/
/*
 Nome:
		 Criar_Estufa

 Descrição:
		Reserva espaço de memória dinâmica do tamanho da struct estufa num apontador para estufa_t e retorna o apontador do tipo estufa_t.

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		EstufaNova      Apontador para estufa_t       O      Um apontador para estufa_t 

 Retorna:
		Retorna um apontador do tipo estufa_t
*/

estufa_t*  Criar_Estufa() {
	struct estufa *EstufaNova = NULL;
	EstufaNova = (estufa_t*)malloc(sizeof(struct estufa));
	return(EstufaNova);
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Destruir_Estufa

 Descrição:
		Recebe uma estufa por referencia e liberta o espaço de memoria dinamico da mesma.

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		estufa      Apontador para estufa_t           I      Um apontador para estufa_t

 Retorna:
	Nao retorna  nada
*/
void Destruir_Estufa(estufa_t *estufa) {
	if (estufa) {
		free(estufa);
	}

	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Preencher_Estufa

 Descrição:
		Reserva espaço de memória dinâmica do tamanho da struct estufa num apontador para estufa_t , preenche a struct estufa com os parâmetros recebidos e retorna o apontador do tipo estufa_t.

Argumentos:
		Argumento				Tipo						 I/O      Descrição
		EstufaNova				Apontador para estufa_t       O       Um apontador para estufa_t
		nome					Char						  I		  Um array
		temperaturaint			float						  I       um valor racional
		temperaturaext			float						  I       um valor racional
		humidade				int                           I       um valor natural
		areasuperficialparedes  int							  I       um valor natural
		k                       int                           I       um valor natural
		tipodefruta             int                           I       um valor natural

Retorna:
	Retorna um apontador to tipo estufa_t
*/

estufa_t* Preencher_Estufa(estufa_t* estufa,char nome[], float temperaturaint, float temperaturaext, int humidade, int areasuperficial, float k, int tipodefruta) {
	strcpy(estufa->nome, nome);
	estufa->temperaturaext = temperaturaext;
	estufa->temperaturaint = temperaturaint;
	estufa->humidade = humidade;
	estufa->areasuperficieparedes = areasuperficial;
	estufa->k = k;
	estufa->tipodefruta = tipodefruta;
	return (estufa);
}

/***********************************************************************************************************************************************/
/*
 Nome:
		Alterar_Estufa

 Descrição:
		Recebe um apontador estufa_t, parâmetros que se pode mudar, e no vetor de tamanho 7, recebe os parâmetros que se deseja alterar, a posição a 1 altera, a 0 não altera, v[0]=nome, v[1]=Temperatura Interior, v[2]=Temperatura Exterior,v[3]=Humidade,v[4]=Area Superficial das Paredes,v[5]=K,v[6]= Tipo de Fruta.

 Argumentos:
		Argumento				Tipo						 I/O      Descrição
		Estufa_Alt				Apontador para estufa_t       I       Um apontador para estufa_t
		nome					Char						  I		  Um array
		temperaturaint			float						  I       um valor racional
		temperaturaext			float						  I       um valor racional
		humidade				int                           I       um valor natural
		areasuperficialparedes  int							  I       um valor natural
		k                       int                           I       um valor natural
		tipodefruta             int                           I       um valor natural

 Retorna:
		Não retorna nada
*/
void Alterar_Estufa(estufa_t *Estufa_Alt, char nome[], float temperaturaint, float temperaturaext, int humidade, int areasuperficial, float k, int tipodefruta, int v[]) {

	if (v[0] == 1)
		strcpy(Estufa_Alt->nome, nome);
	if (v[1] == 1)
		Estufa_Alt->temperaturaext = temperaturaext;
	if (v[2] == 1)
		Estufa_Alt->temperaturaint = temperaturaint;
	if (v[3] == 1)
		Estufa_Alt->humidade = humidade;
	if (v[4] == 1)
		Estufa_Alt->areasuperficieparedes = areasuperficial;
	if (v[5] == 1)
		Estufa_Alt->k = k;
	if (v[6] == 1)
		Estufa_Alt->tipodefruta = tipodefruta;

	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Verificar_Humidade

 Descrição:
		Recebe a estufa que se pretende Verificar a Humidade e retorna um inteiro, 1 se a humidade for menor que a mínima, 2 se a humidade for maior que a máxima, -1 se a humidade for a recomendada para o Tipo de Fruta.

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Verificar_Humidade(estufa_t *estufa) {

	int w[13][2] = { { 60,80 },{ 60, 80 },{ 65, 75 },{ 60, 70 },{ 65, 80 },{ 60, 75 },{ 50, 60 },{ 50, 60 },{ 70, 90 },{ 50, 60 },{ 65, 75 },{ 60, 70 },{ 65, 80 } };

	if (estufa->humidade < w[estufa->tipodefruta][0])
		return 1;
	else if (estufa->humidade > w[estufa->tipodefruta][1])
		return 2;
	else return-1;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Verificar_Temperatura

 Descrição:
		Recebe a estufa que se pretende Verificar a Temperatura Interior e retorna um inteiro, 1 se a Temperatura Interior for menor que a mínima, 2 se a Temperatura Interior for maior que a máxima, -1 se a Temperatura Interior for a recomendada, 3 se a Temperatura Interior esteja a baixo da temperatura critica para o Tipo de Fruta.

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Verificar_Temperatura(estufa_t *estufa) {

	int w[13][3] = { { 14,18,10 },{ 15, 18,-2 },{ 16, 20,3 },{ 18, 22,-4 },{ 18, 25,5 },{ 18, 30,8 },{ 20, 24,7 },{ 20, 25,8 },{ 20, 25,10 },{ 22, 27,9 },{ 23, 28,10 },{ 25, 30,9 },{ 25, 35,8 } };

	if (estufa->temperaturaint < w[estufa->tipodefruta][0])
		return 1;
	else if (estufa->temperaturaint > w[estufa->tipodefruta][1])
		return 2;
	else return -1;
	if (estufa->temperaturaint <= w[estufa->tipodefruta][2])
		return 3;

}
/***********************************************************************************************************************************************/
/*
 Nome:
		Aquecimento

 Descrição:
		Recebe a estufa que se pretende Verificar a potencia necessária para subir 1 grau, pela equação : P=K*AreaSuperficialdasParedes*(Temperatura Interior-Temperatura Exterior) e retorna-a o resultado em float.

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um float
*/
float Aquecimento(estufa_t *estufa) {
	return ((float)(estufa->k*estufa->areasuperficieparedes*(estufa->temperaturaint - (estufa->temperaturaext))));
}
/***********************************************************************************************************************************************/



/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Nome_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas como parâmetro e retorna o resultado strcmp(nome da estufa1,nomeestufa2)

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_Nome_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	
	if (_stricmp(estufa1->nome, estufa2->nome) == 0)  //Iguais
		return 0;
	
	if (_stricmp(estufa1->nome, estufa2->nome) < 0)   //Primeiro é menor que o segundo
		return -1;

	if (_stricmp(estufa1->nome, estufa2->nome) > 0)  //Primeiro é maior que o segundo
		return 1;
	
	return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Encontrar_Estufa_Nome

 Descrição:
		Compara o nome da estufa recebida com o nome recebido e caso seja igual retorna -1 e caso não retorna 0.

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Retorna um inteiro
*/


int Encontrar_Estufa_Nome(estufa_t *estufa, void *Data) {
	if (_stricmp(estufa->nome, Data) == 0)
		return -1;
	else return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Tipo_de_Fruta_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas, e retorna 1 caso o tipo de fruta da estufa 1 seja maior que o da estufa 2, -1 caso o tipo de fruta da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais 

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_Tipo_de_Fruta_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	if (estufa1->tipodefruta > estufa2->tipodefruta) {
		return 1;
	}
	else if(estufa1->tipodefruta < estufa2->tipodefruta)
		return -1;
	return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Temperatura_Exterior_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas como parãmetro, retorna 1 caso a temperatura exterior da estufa 1 seja maior que o da estufa 2, -1 caso a temperatura exterior da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_Temperatura_Exterior_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	if (estufa1->temperaturaext > estufa2->temperaturaext) {
		return 1;
	}
	else if (estufa1->temperaturaext< estufa2->temperaturaext)
		return -1;
	return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Temperatura_Interior_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas como parãmetro, retorna 1 caso a temperatura interior da estufa 1 seja maior que o da estufa 2, -1 caso a temperatura interior da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_Temperatura_Interior_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	if (estufa1->temperaturaint> estufa2->temperaturaint) {
		return 1;
	}
	else if (estufa1->temperaturaint< estufa2->temperaturaint)
		return -1;
	return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Humidade_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas como parâmetro, retorna 1 caso a humidade da estufa 1 seja maior que o da estufa 2,-1 caso a humidade da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_Humidade_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	if (estufa1->humidade> estufa2->humidade) {
		return 1;
	}
	else if (estufa1->humidade< estufa2->humidade)
		return -1;
	return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_K_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas como parámetro, retorna 1 caso o k da estufa 1 seja maior que o da estufa 2, -1 caso o k da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais 

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_K_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	if (estufa1->k> estufa2->k) {
		return 1;
	}
	else if (estufa1->k< estufa2->k)
		return -1;
	return 0;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Comparar_Area_Superficial_Paredes_Menor_Igual_Maior

 Descrição:
		Recebe duas estufas como parãmetro, retorna 1 caso a area superficial das paredes da estufa 1 seja maior que o da estufa 2, -1 caso a area superfial das paredes da estufa 1 seja menor que a da estufa 2, 0 caso sejam iguais

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa1				Apontador para estufa_t       I       Um apontador para estufa_t
		estufa2				Apontador para estufa_t       I       Um apontador para estufa_t

 Retorna:
		Retorna um inteiro
*/
int Comparar_Area_Superficial_Paredes_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2) {
	if (estufa1->areasuperficieparedes> estufa2->areasuperficieparedes) {
		return 1;
	}
	else if (estufa1->areasuperficieparedes< estufa2->areasuperficieparedes)
		return -1;
	return 0;
}
/***********************************************************************************************************************************************/






//Gets
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Nome_Estufa

 Descrição:
		Recebe a estufa e retorna o nome da mesma.

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		estufa		    Apontador para estufa_t	      I       Um apontador para estufa_t
		estfa->nome		char                          O       Um array 
 
 Retorna:
		Retorna um apontador para char
*/

char *Obter_Nome_Estufa(estufa_t *estufa) {
	return(estufa->nome);
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Temperatura_Exterior

 Descrição:
		Recebe a estufa e retorna a temperatura exterior da mesma.

 Argumentos:
		Argumento				 Tipo						  I/O      Descrição
		estufa					 Apontador para estufa_t	   I       Um apontador para estufa_t
		estfa->temperaturaext	 float                         O       Um numero racional 
 
 Retorna:
		Retorna um apontador para char
*/

float Obter_Temperatura_Exterior(estufa_t *estufa) {
	return estufa->temperaturaext;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Temperatura_Interior

 Descrição:
		Recebe a estufa e retorna a temperatura interior da mesma.

 Argumentos:
		Argumento				 Tipo						  I/O      Descrição
		estufa					 Apontador para estufa_t	   I       Um apontador para estufa_t
		estfa->temperaturaint	 float                         O       Um numero racional 
 
 Retorna:
		Retorna um apontador para float
*/
float Obter_Temperatura_Interior(estufa_t *estufa) {
	return estufa->temperaturaint;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Humidade

 Descrição:
		Recebe a estufa e retorna a humidade da mesma.

 Argumentos:
		Argumento				 Tipo						  I/O      Descrição
		estufa					 Apontador para estufa_t	   I       Um apontador para estufa_t
		estfa->´humidade     	 int                           O       Um numero natural 
 
 Retorna:
		Retorna um apontador para int
*/
int Obter_Humidade(estufa_t *estufa) {
	return estufa->humidade;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_K

 Descrição:
		Recebe a estufa e retorna o k da mesma.

 Argumentos:
		Argumento		 Tipo						  I/O      Descrição
		estufa			 Apontador para estufa_t	   I       Um apontador para estufa_t
		estfa->k		 float                         O       Um numero racional 
 
 Retorna:
		Retorna um apontador para float
*/
float Obter_K(estufa_t *estufa) {
	return estufa->k;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Area_Superficial_Paredes

 Descrição:
		Recebe a estufa e retorna a Area Superfical das Paredes da mesma.

 Argumentos:
		Argumento						 Tipo						  I/O      Descrição
		estufa							 Apontador para estufa_t	   I       Um apontador para estufa_t
		estfa->areasuperficieparedes	 int                           O       Um numero natural 
 
 Retorna:
		Retorna um apontador para int
*/
int Obter_Area_Superficial_Paredes(estufa_t *estufa) {
	return estufa->areasuperficieparedes;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Tipo_de_Fruta

 Descrição:
		Recebe a estufa e retorna o tipo de fruta da mesma.

 Argumentos:
		Argumento				 Tipo						  I/O      Descrição
		estufa					 Apontador para estufa_t	   I       Um apontador para estufa_t
		estfa->tipodefruta  	 int                           O       Um numero natural 
 
 Retorna:
		Retorna um apontador para int
*/
int Obter_Tipo_de_Fruta(estufa_t *estufa) {
	return estufa->tipodefruta;;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		Obter_Tamanho_da_Estrutura_Estufa

 Descrição:
		Retorna o tamanho da estrutura estufa.

 Argumentos:
		Argumento		 Tipo						  I/O      Descrição

 Retorna:
		Retorna um inteiro
*/
int Obter_Tamanho_da_Estrutura_Estufa(void) {
	return(sizeof(estufa_t));
}
/***********************************************************************************************************************************************/








//Sets
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_Nome_Estufa

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um fchar e altera o nome da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		nome				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_Nome_Estufa(estufa_t *estufa, void* nome) {
	strcpy(estufa->nome, (char*)nome);
}
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_Temperatura_Exterior

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um float e altera a temperatura exterior da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_Temperatura_Exterior(estufa_t *estufa, void* Data) {
	estufa->temperaturaext = *(float*)Data;
	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_Temperatura_Interior

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um float e altera a temperatura interior da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_Temperatura_Interior(estufa_t *estufa, void* Data) {
	estufa->temperaturaint = *(float*)Data;
	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_Humidade

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um int e altera a humidade da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_Humidade(estufa_t *estufa, void* Data) {
	estufa->humidade = (int)Data;
	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_K

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um float e altera o k da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_K(estufa_t *estufa, void* Data) {
	estufa->k = *(float*)Data;
	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_Area_Superficial_Paredes

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um int e altera a area superficial das paredes da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_Area_Superficial_Paredes(estufa_t *estufa, void* Data) {
	estufa->areasuperficieparedes = (int)Data;
	return;
}
/***********************************************************************************************************************************************/
/*
 Nome:
		 Alterar_Tipo_de_Fruta

 Descrição:
		 Recebe um apontador para uma estufa_t e um apontador generico que aponta para um int e altera o tipo de fruta da estufa apontada

 Argumentos:
		Argumento				Tipo				     I/O      Descrição
		estufa				Apontador para estufa_t       I       Um apontador para estufa_t
		Data				Apontador para void           I       Um apontador para void

 Retorna:
		Nao retorna nada
*/
void Alterar_Tipo_de_Fruta(estufa_t *estufa, void* Data) {
	estufa->tipodefruta = (int)Data;
	return;
}
/***********************************************************************************************************************************************/










