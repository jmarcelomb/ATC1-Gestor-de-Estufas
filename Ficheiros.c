

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include "ficheiros.h"

/**********************************************************************************************************************************************/
/*
 Nome:
		 Abrir_Ficheiro

 Descrição:
		Abre o ficheiro indicado pelo apontador (filename)

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		filename        Apontador para char           I       Um apontador para um char 

 Retorna:
		Retorna um apontador para um file
*/

FILE *Abrir_Ficheiro (char *filename) {
	FILE *fp;
	
	fp = fopen(filename, "r+b");
	if (fp == NULL) {
		fp = fopen (filename, "a+b");
		if (fp == NULL) 
			perror("Erro a abrir!");
    }
    return (fp);
}
/**********************************************************************************************************************************************/
/*
 Nome:
		Adicionar_a_Ficheiro

 Descrição:
		Adiciona ao ficheiro apontado por fp o que se encontra no buffer no espaço indicado no size

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		fp              Apontador para file           I       Um apontador para um file 
		buffer			Apontador para void           I       Um apontador para void
		size			unsigned size                 I		  Um numero natural

 Retorna:
		Retorna um inteiro
*/

int Adicionar_a_Ficheiro (FILE *fp, void *buffer, unsigned int size) {
	
	if (fseek(fp, 0 ,SEEK_END) != 0) 
		return 0;
	fwrite (buffer, size, 1, fp);
	if (ferror (fp)) {
		perror ("Erro a escrever!");
		clearerr (fp);
		return 0;
	}
	return 1;
}
/**********************************************************************************************************************************************/
/*
 Nome:
		Ler_Ficheiro

 Descrição:
		Consuante a disposição(disp) lê o tamanho (size) para o buffer do ficheiro apontado por fp

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		fp              Apontador para file           I       Um apontador para um file 
		buffer			Apontador para void           I       Um apontador para void
		size			Unsigned size                 I		  Um numero natural
		disp			Unsigned size                 I		  Um numero natural

 Retorna:
		Retorna um inteiro
*/

int Ler_Ficheiro (FILE *fp, void *buffer, unsigned int size, unsigned int disp) {
	
	if (fseek(fp, disp * size ,SEEK_SET) != 0) 
		return 0;
	return (fread (buffer, size, 1, fp));
}
/**********************************************************************************************************************************************/
/*
 Nome:
		 Fechar_Ficheiro

 Descrição:
		Fecha o ficheiro apontado por fp

 Argumentos:
		Argumento       Tipo						 I/O      Descrição
		fp              Apontador para file           I       Um apontador para um file 

 Retorna:
		Retorna um inteiro
*/

int Fechar_Ficheiro (FILE *fp) {
	
	if (fclose(fp)){
		perror ("Erro a fechar!");
		return 0;
	}
	return 1;
}
/**********************************************************************************************************************************************/
/*
 Nome:
		Limpar_Ficheiro

 Descrição:
		Limpa o ficheiro com o nome indicado pelo apontador nomeficheiro

 Argumentos:
		Argumento			Tipo						 I/O      Descrição
		nomeficheiro        Apontador para char           I       Um apontador para um array 

 Retorna:
		Retorna um inteiro
*/
int Limpar_Ficheiro(char *nomeficheiro) {
	FILE *fp1 = fopen(nomeficheiro, "w");

	if (fp1 == NULL)
		return 0;
	else
		return 1;
	fclose(fp1);
	return 0;
}
