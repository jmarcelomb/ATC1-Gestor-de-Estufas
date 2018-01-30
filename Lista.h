


/*

Nome: Lista 

Prop�sito:
			Este m�dulo tem de prop�sito manusear listas ligadas. 
			

/*******************************************************************************************************************************************************************
--->Data Structs:*/

//Estrutura de um n�

typedef struct node node_t;

//Estrutura lista
typedef struct lista lista_t;

/*******************************************************************************************************************************************************************
/*******************************************************************************************************************************************************************

--->Cabe�alhos das fun��es:*/

node_t* Criar_Node(); //Reserva espa�o de mem�ria din�mica do tamanho da struct node num apontador para node_t e coloca o node->next a NULL, retorna o apontador do tipo node_t.
void Destruir_Node(node_t *node); //Recebe um apontador para node_t e caso exista, liberta a mem�ria din�mica apontada pelo o *node. 
node_t* Obter_Node_Seguinte(node_t *node); //Recebe um apontador para node_t e retorna um apontador para o proximo n�
void* Obter_Conteudo_do_Node(node_t *node); //Recebe um apontador para node_t e retorna data do mesmo.
node_t *Encontrar_Node(lista_t *lista, int(*Encontrar_Estufa_Nome)(void* data1, void *data2), void* Data); //Recebe uma lista por referencia, e o endere�o da fun��o do m�dulo estufa int Encontrar_Estufa_Nome(estufa_t *estufa, char nome[]); que compara o nome da estufa recebida com o nome recebido e caso seja igual retorna -1 e caso n�o retorna 0. A fun��o retorna um apontador para node_t que tenha o nome recebido, e caso na lista n�o tenha o nome recebido retorna um apontador para NULL.  

lista_t* Nova_Lista();  //Cria um apontador head para um node, e armazena memoria dinamica para o mesmo, e retorna o apontador head.
node_t* Obter_Cabeca_da_Lista(lista_t *Lista);	//Retorna o apontador para a head da lista da lista recebida.
int Remover_da_Lista(lista_t *lista,  int(*Encontrar_Estufa_Nome)(void* data1, void *data2),void* Data ); //Recebe uma lista por referencia, o endere�o da fun��o Encontrar_Estufa_Nome do m�dulo Estufa, e um void* Data que  deseja remover, e caso exista remove o mesmo e retorna -1 caso remova e retorna 0 caso n�o remova.
void Inserir_na_Lista_Ordenadamente(lista_t *lista,node_t *node_recebido, void *DataRecebida, int(*ptr_Comparar_Menor_Igual_Maior)(void* data1, void *data2));//Recebe uma lista,um node e um apontador para uma fun��o, em que a fun��o deve retornar -1 caso a data recebida pela mesma sega menor a primeira que a segunda, 0 caso sejam iguais, ou um numero diferente de -1 ou 0 caso seja maior. E insere na lista ordenadamente consoante a fun��o recebida e a data.
void Inserir_na_Lista_Topo(lista_t *lista, node_t *node_recebido, void *DataRecebida); //Recebe uma lista, e um node e coloca no topo da lista o node recebido.
void Limpar_Lista(lista_t *lista); //Recebe uma lista por referencia, liberta os espa�os de mem�ria da mesma deixando-a com a head a apontar para NULL.
int Ordenar_Lista(lista_t *lista, int(*ptr_Comparar_Menor_Igual_Maior)(void* data1, void *data2));  //Recebe uma lista e um apontador para uma fun��o, em que a fun��o deve retornar -1 caso a data recebida pela mesma sega menor a primeira que a segunda, 0 caso sejam iguais, ou um numero diferente de -1 ou 0 caso seja maior. E coloca a lista ordenadam consoante a fun��o recebida. 
//void Ordenar_Lista_Por_Tipo_de_Fruta(lista_t *lista,int(*ptr_CompararTipodeFruta_Menor_Igual_Maior)(void* data1, void *data2)); //Recebe uma lista por referencia e um endere�o para a fun��o CompararTipodeFruta_Menor_Igual_Maior do M�dulo Estufa, e retorna alfabeticamente a lista ordenada. 

/*******************************************************************************************************************************************************************
*******************************************************************************************************************************************************************/

// 23-01-2018 Jo�o Borges,Jo�o Lu�s,Jo�o Gil,Miguel Silva  Cria��o