#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"


//Estrutura  node
typedef struct node {
	void *data;
	struct node *next;
}node_t;

//Estrutura lista
typedef struct lista {
	struct node *head;
}lista_t;



/*******************************************************************************************************************************************************************

Nome: 
		Criar_Node

Descrição:
		Reserva espaço de memória dinâmica do tamanho da struct node num apontador para node_t e coloca o node->next a NULL, retorna o apontador do tipo node_t.

Argumentos:
		Argumento      Tipo						I/O     Descrição
		node         Apontador para node_t		 O		Um apontador para node_t


Retorna:
		Apontador que aponta para node_t, que é  um espaço de memoria dinamica armazenada do tamanho da struct node_t.

*/


node_t* Criar_Node() {
	node_t *node=NULL;
	node = (node_t*)malloc(sizeof(struct node));
	node->next = NULL;
	return node;
}
/*******************************************************************************************************************************************************************

Nome:  
		Destruir_Node

Descrição:
		Recebe um apontador para node_t e caso exista, liberta a memória dinâmica apontada pelo o *node.

Argumentos:
		Argumento      Tipo						I/O     Descrição
		node         Apontador para node_t		 I		Um apontador para node_t


Retorna:
		Não retorna nada.

*/


void Destruir_Node(node_t *node) {
	if (node) 
	free(node);
	return;
}

/*******************************************************************************************************************************************************************

Nome:
		Obter_Node_Seguinte

Descrição:
		Recebe um apontador para node_t e retorna um apontador para o proximo node.

Argumentos:
		Argumento      Tipo						I/O     Descrição
		node         Apontador para node	     I		Um apontador para node_t
		node->next	 Apontador para node_t		 O      Um apontador para node_t


Retorna:
		Retorna o apontador node->next do node recebido, que aponta para o node seguinte.

*/

node_t* Obter_Node_Seguinte(node_t *node) {
	return(node->next);
}

/*******************************************************************************************************************************************************************

Nome:
		Obter_Conteudo_do_Node

Descrição:
		Recebe um apontador para node_t e retorna data do mesmo.

Argumentos:
		Argumento      Tipo						I/O     Descrição
		node         Apontador para node	     I		Um apontador para node_t
		node->data	 Apontador para void*		 O      Um apontador void*


Retorna:
		Retorna o apontador node->data do node recebido.

*/

void* Obter_Conteudo_do_Node(node_t *node) {
	return(node->data);
}

/*******************************************************************************************************************************************************************

Nome:
		Encontrar_Node

Descrição:
		Recebe uma lista por referencia, e o endereço da função do módulo estufa int Encontrar_Estufa_Nome(estufa_t *estufa, char nome[]); que compara o nome da estufa recebida com o nome recebido e caso seja igual retorna -1 e caso não retorna 0. A função retorna um apontador para node_t que tenha o nome recebido, e caso na lista não tenha o nome recebido retorna um apontador para NULL.
Argumentos:
		Argumento						  Tipo						I/O     Descrição
		lista							Apontador para lista_t	     I		Um apontador para lista_t
		Encontrar_Estufa_Nome			Apontador para uma funcão	 I		Um apontador para uma função que tem dois parâmetros de entrada e retorna um inteiro.
		que tem dois parâmetros de
		entrada
Retorna:
		Retorna um inteiro.

*/

node_t *Encontrar_Node(lista_t *lista, int(*Encontrar_Estufa_Nome)(void* data1, void *data2), void* Data) {
	node_t *node = lista->head;;

	while (node) {

		if (Encontrar_Estufa_Nome(node->data, Data))
			return (node);

		node = node->next;
	}
	return NULL;


}

/*******************************************************************************************************************************************************************

Nome:
		Nova_Lista

Descrição:
		Cria um apontador head para um node, e armazena memoria dinamica para o mesmo, e retorna o apontador head.

Argumentos:
		Argumento      Tipo						I/O     Descrição
		ListaNova    Apontador para lista_t		 O		Um apontador para lista_t

Retorna:
		Retorna um apontador que aponta para uma lista_t, que tem armazenado espaço dinâmico do tamanho da lista_t.

*/



lista_t* Nova_Lista() {
	lista_t *ListaNova = NULL;
	ListaNova = (lista_t*)malloc(sizeof(struct lista));
	ListaNova->head = NULL;
	return ListaNova;
}

/*******************************************************************************************************************************************************************

Nome:
		Obter_Cabeca_da_Lista

Descrição:
		Retorna o apontador para a head da lista da lista recebida.

Argumentos:
	Argumento      Tipo						I/O     Descrição
	Lista         Apontador para lista_t	 I		Um apontador para lista_t
	Lista->head	  Apontador para node_t		 O      Um apontador para node_t


Retorna:
		O apontador apontado pela head da lista recebida. 

*/


node_t* Obter_Cabeca_da_Lista(lista_t *Lista) {
	return(Lista->head);
}


/*******************************************************************************************************************************************************************

Nome:
		Limpar_Lista

Descrição:
		Recebe uma lista por referencia, liberta os espaços de memória da mesma deixando-a com a head a apontar para NULL.

Argumentos:
		Argumento      Tipo						I/O     Descrição
		lista        Apontador para lista_t	     I		Um apontador para lista_t


Retorna:
		Não retorna nada.

*/

void Limpar_Lista(lista_t *lista) {
	node_t *node = lista->head ,*NodeAuxiliar= NULL;
	
	while (node) {
		NodeAuxiliar = node;
		node = node->next;
		lista->head = node;
		free(NodeAuxiliar);
	}
	
	return;
}

/*******************************************************************************************************************************************************************

Nome:
		Inserir_na_Lista_Ordenadamente

Descrição:
		Recebe uma lista,um node e um apontador para uma função, em que a função deve retornar -1 caso a data recebida pela mesma sega menor a primeira que a segunda, 0 caso sejam iguais, ou um numero diferente de -1 ou 0 caso seja maior. E insere na lista ordenadamente consoante a função recebida e a data.

Argumentos:
		Argumento						  Tipo						I/O     Descrição
		lista							Apontador para lista_t	     I		Um apontador para lista_t
		node_recebido					Apontador para node_t		 I      Um apontador para node_t
		DataRecebida					Apontador para void			 I      Um apontador para void
		ptr_Comparar_Menor_Igual_Maior	Apontador para uma função	 I		Um apontador para uma função que tem dois parâmetros de entrada e retorna um inteiro.
										que tem dois parâmetros de
										entrada
Retorna:
		Não retorna nada.

*/


void Inserir_na_Lista_Ordenadamente(lista_t *lista, node_t *node_recebido, void *DataRecebida, int(*ptr_Comparar_Menor_Igual_Maior)(void* data1, void *data2)) {
	
	node_t *node = lista->head, *node_auxiliar = lista->head;;
	node_recebido->data = DataRecebida;
	
	if (!lista->head) {
		lista->head = node_recebido;
		return;
	}
	
	
	while (node) {

			if (ptr_Comparar_Menor_Igual_Maior(DataRecebida, node->data) == -1 || ptr_Comparar_Menor_Igual_Maior(DataRecebida, node->data) == 0) {
				if (node == lista->head) {
					node_recebido->next = lista->head;  //Inserir no inicio
					lista->head = node_recebido;
					return;
				}
				node_auxiliar->next = node_recebido;   //Inserir no meio
				node_recebido->next = node;
				return;
			}

			if (node != lista->head)
				node_auxiliar = node_auxiliar->next;
			node = node->next;
		}
		//Inserir no fim
		node_auxiliar->next = node_recebido;
		node_recebido->next = NULL;
		return;
	
}

/*******************************************************************************************************************************************************************

Nome:
		Inserir_na_Lista_Topo

Descrição:
		Recebe uma lista, e um node e coloca no topo da lista o node recebido.

Argumentos:
		Argumento						  Tipo						I/O     Descrição
		lista							Apontador para lista_t	     I		Um apontador para lista_t
		node_recebido					Apontador para node_t		 I      Um apontador para node_t
		DataRecebida					Apontador para void			 I      Um apontador para void
		

Retorna:
		Não retorna nada.

*/


void Inserir_na_Lista_Topo(lista_t *lista, node_t *node_recebido, void *DataRecebida) {
	//Inserção no topo
	if (!lista->head) {
		lista->head = node_recebido;
		node_recebido->data = DataRecebida;
		return;
	}

	node_recebido->data = DataRecebida;
	node_recebido->next = lista->head;
	lista->head = node_recebido;
	return;

}

/*******************************************************************************************************************************************************************

Nome:
		Inserir_na_Lista_Ordenadamente

Descrição:
		Recebe uma lista por referencia, o endereço da função Encontrar_Estufa_Nome do módulo Estufa, e um void* Data que  deseja remover, e caso exista remove o mesmo e retorna -1 caso remova e retorna 0 caso não remova.

Argumentos:
		Argumento						  Tipo						I/O     Descrição
		lista							Apontador para lista_t	     I		Um apontador para lista_t
		nome							Char						 I      Um array
		Encontrar_Estufa_Nome			Apontador para uma funcão	 I		Um apontador para uma função que tem dois parâmetros de entrada e retorna um inteiro.
										que tem dois parâmetros de
										entrada
Retorna:
		Retorna um inteiro.

*/


int Remover_da_Lista(lista_t *lista, int(*Encontrar_Estufa_Nome)(void* data1, void *data2), void* Data) {
	node_t *NodeAtual= lista->head,*NodeAuxiliar= lista->head,*NodeAnterior= lista->head;

	
	if (lista->head == NULL)return 0;     //está vazia e não da para remover nada


	while (NodeAtual) {
		
		
		if (Encontrar_Estufa_Nome(NodeAtual->data, Data)) {
			if (NodeAtual->next != NULL) { //Não é o ultimo nó
				
				if (NodeAtual == lista->head) {  //O no a ser removido coincide com a cabeça da lista
					
					NodeAuxiliar = NodeAtual;
					lista->head = NodeAtual->next;
					free(NodeAuxiliar);
					return -1;
				}
				NodeAnterior->next = NodeAtual->next;
				free(NodeAtual);
				return -1;
			}
			else {  //Se não é um nó no meio
				if (NodeAtual == lista->head) {
					NodeAuxiliar = NodeAtual;
					lista->head = NodeAtual->next;
					free(NodeAuxiliar);
					return -1;
				}

				//No no fim
				NodeAuxiliar = NodeAtual;
				NodeAnterior->next = NULL;
				free(NodeAuxiliar);
				return -1;
			}
		}
		
		if (NodeAtual!=lista->head)
			NodeAnterior = NodeAnterior->next;
		
		NodeAtual = NodeAtual->next;
	}
	
	return 0;

}

/*******************************************************************************************************************************************************************

Nome:
		Ordenar_Lista

Descrição:
		Recebe uma lista e um apontador para uma função, em que a função deve retornar -1 caso a data recebida pela mesma sega menor a primeira que a segunda, 0 caso sejam iguais, ou um numero diferente de -1 ou 0 caso seja maior. E coloca a lista ordenadam consoante a função recebida.
Argumentos:
		Argumento						  Tipo						I/O     Descrição
		lista							Apontador para lista_t	     I		Um apontador para lista_t
		ptr_Comparar_Menor_Igual_Maior	Apontador para uma funcão	 I		Um apontador para uma função que tem dois parâmetros de entrada e retorna um inteiro.
										que tem dois parâmetros de
										entrada
Retorna:
		Retorna um inteiro.

*/


int Ordenar_Lista(lista_t *lista, int(*ptr_Comparar_Menor_Igual_Maior)(void* data1, void *data2)) {

	node_t *node = lista->head, *Node_Anterior = lista->head,*Guardar_Node_Seguinte=NULL;
	int alterou = -1;

	
	while (node) {
		
		if (node->next == NULL)break;

		if (ptr_Comparar_Menor_Igual_Maior(node->data, node->next->data) > 0) {
			
			if (node == lista->head) { //caso seja na cabeça
				Guardar_Node_Seguinte = node->next;  //guarda o apontador para node->next
				node->next = node->next->next;	//coloca o node->next a apontar par ao node->next-><next
				Guardar_Node_Seguinte->next = lista->head;		//coloca o apontado pelo node->next->next pelo node atual
				lista->head = Guardar_Node_Seguinte;   //coloca a head a apontar para o node seguinte

				node = lista->head;
				Node_Anterior = lista->head;
				alterou = 1;
				
			}
			
			else {
				Guardar_Node_Seguinte = node->next;  //no meio
				node->next = node->next->next;
				Node_Anterior->next = Guardar_Node_Seguinte;
				Guardar_Node_Seguinte->next = node;

				node = lista->head;
				Node_Anterior = lista->head;
				alterou = 1;
			}
		}

		if (node != lista->head)
			Node_Anterior = Node_Anterior->next;
		if (alterou == -1)
			node = node->next;
		else alterou = -1;

	}

	if (node != lista->head)   //Quer dizer que organizou pelo menos 1
		return 1;
	return 0;
}

/*******************************************************************************************************************************************************************/


