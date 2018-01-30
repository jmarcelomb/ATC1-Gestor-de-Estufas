

/********************************************************************************************************************************************************************

Nome: Ficheiros

Propósito: 
		Este módulo tem de propósito manusear ficheiros.



*//*******************************************************************************************************************************************************************/


FILE *Abrir_Ficheiro(char *filename);//Abre o ficheiro indicado pelo apontador (filename)
int Adicionar_a_Ficheiro (FILE *fp, void *buffer, unsigned int size);//Adiciona ao ficheiro apontado por fp o que se encontra no buffer no espaço indicado no size 
int Ler_Ficheiro (FILE *fp, void *buffer, unsigned int size, unsigned int pos);//	Consuante a dispusição(disp) lê o tamanho (size) para o buffer do ficheiro apontado por fp
int Fechar_Ficheiro (FILE *fp);//Fecha o ficheiro apontado por fp
int Limpar_Ficheiro(char *filename);//Limpa o ficheiro com o nome indicado pelo apontador nomeficheiro


/*******************************************************************************************************************************************************************
*******************************************************************************************************************************************************************/