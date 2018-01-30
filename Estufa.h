
/*

Nome:Estufa

Proposito:
		Este módulo como objetivo apresentar ferramentas para manusear uma estufa.
		


/*******************************************************************************************************************************************************************
--->Data Structs:*/

//Estrutura "estufa"
typedef struct estufa estufa_t;


/*******************************************************************************************************************************************************************
/*******************************************************************************************************************************************************************
--->Cabeçalhos das funções:*/

estufa_t*  Criar_Estufa();   //Reserva espaço de memória dinâmica do tamanho da struct estufa num apontador para estufa_t e retorna o apontador do tipo estufa_t.
void Destruir_Estufa(estufa_t *estufa);  //Recebe uma estufa por referencia e liberta o espaço de memoria dinamico da mesma.
estufa_t*  Preencher_Estufa(estufa_t* estufa,char nome[], float temperaturaint, float temperaturaext, int humidade, int areasuperficial, float k, int tipodefruta); //Reserva espaço de memória dinâmica do tamanho da struct estufa num apontador para estufa_t , preenche a struct estufa com os parâmetros recebidos e retorna o apontador do tipo estufa_t.
// void Alterar_Estufa(estufa_t *Estufa_Alt, char nome[], float temperaturaint, float temperaturaext, int humidade, int areasuperficial, float k, int tipodefruta, int v[]); //Recebe um apontador estufa_t, parâmetros que se pode mudar, e no vetor de tamanho 7, recebe os parâmetros que se deseja alterar, a posição a 1 altera, a 0 não altera, v[0]=nome, v[1]=Temperatura Interior, v[2]=Temperatura Exterior,v[3]=Humidade,v[4]=Area Superficial das Paredes,v[5]=K,v[6]= Tipo de Fruta.
int Verificar_Humidade(estufa_t *estufa); //Recebe a estufa que se pretende Verificar a Humidade e retorna um inteiro, 1 se a humidade for menor que a mínima, 2 se a humidade for maior que a máxima, -1 se a humidade for a recomendada para o Tipo de Fruta. 
int Verificar_Temperatura(estufa_t *estufa); //Recebe a estufa que se pretende Verificar a Temperatura Interior e retorna um inteiro, 1 se a Temperatura Interior for menor que a mínima, 2 se a Temperatura Interior for maior que a máxima, -1 se a Temperatura Interior for a recomendada, 3 se a Temperatura Interior esteja a baixo da temperatura critica para o Tipo de Fruta. 
float Aquecimento(estufa_t *estufa); //Recebe a estufa que se pretende Verificar a potencia necessária para subir 1 grau, pela equação : P=K*AreaSuperficialdasParedes*(Temperatura Interior-Temperatura Exterior) e retorna-a o resultado em float.




int Comparar_Nome_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2);  //Recebe duas estufas como parâmetro e retorna o resultado strcmp(nome da estufa1,nomeestufa2)
int Encontrar_Estufa_Nome(estufa_t *estufa, void* Data);  //Compara o nome da estufa recebida com o nome recebido e caso seja igual retorna -1 e caso não retorna 0.
int Comparar_Tipo_de_Fruta_Menor_Igual_Maior(estufa_t *estufa1,estufa_t *estufa2); //Recebe duas estufas, e retorna 1 caso o tipo de fruta da estufa 1 seja maior que o da estufa 2, -1 caso o tipo de fruta da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais 
int Comparar_Temperatura_Exterior_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2);//Recebe duas estufas como parãmetro, retorna 1 caso a temperatura exterior da estufa 1 seja maior que o da estufa 2, -1 caso a temperatura exterior da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais
int Comparar_Temperatura_Interior_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2);//Recebe duas estufas como parãmetro, retorna 1 caso a temperatura interior da estufa 1 seja maior que o da estufa 2, -1 caso a temperatura interior da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais
int Comparar_Humidade_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2);//Recebe duas estufas como parâmetro, retorna 1 caso a humidade da estufa 1 seja maior que o da estufa 2,-1 caso a humidade da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais
int Comparar_K_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2);//Recebe duas estufas como parámetro, retorna 1 caso o k da estufa 1 seja maior que o da estufa 2, -1 caso o k da estufa 1 seja menor que o da estufa 2, 0 caso sejam iguais 
int Comparar_Area_Superficial_Paredes_Menor_Igual_Maior(estufa_t *estufa1, estufa_t *estufa2);//Recebe duas estufas como parãmetro, retorna 1 caso a area superficial das paredes da estufa 1 seja maior que o da estufa 2, -1 caso a area superfias 


//Gets
char *Obter_Nome_Estufa(estufa_t *estufa); //Recebe a estufa e retorna o nome da mesma.
float Obter_Temperatura_Exterior(estufa_t *estufa); //Recebe a estufa e retorna a temperatura exterior da mesma.
float Obter_Temperatura_Interior(estufa_t *estufa); //Recebe a estufa e retorna a temperatura interior da mesma.
int Obter_Humidade(estufa_t *estufa); //Recebe a estufa e retorna a humidade da mesma.
float Obter_K(estufa_t *estufa); //Recebe a estufa e retorna o k da mesma.
int Obter_Area_Superficial_Paredes(estufa_t *estufa); //Recebe a estufa e retorna a Area Superfical das Paredes da mesma.
int Obter_Tipo_de_Fruta(estufa_t *estufa); //Recebe a estufa e retorna o tipo de fruta da mesma.
int Obter_Tamanho_da_Estrutura_Estufa(void); //Retorna o tamanho da estrutura estufa.

//Sets
void Alterar_Nome_Estufa(estufa_t *estufa, void* data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um fchar e altera o nome da estufa apontada
void Alterar_Temperatura_Exterior(estufa_t *estufa,void* Data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um float e altera a temperatura exterior da estufa apontada
void Alterar_Temperatura_Interior(estufa_t *estufa, void* Data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um float e altera a temperatura interior da estufa apontada
void Alterar_Humidade(estufa_t *estufa, void* Data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um int e altera a humidade da estufa apontada
void Alterar_K(estufa_t *estufa, void* Data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um float e altera o k da estufa apontada
void Alterar_Area_Superficial_Paredes(estufa_t *estufa, void* Data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um int e altera a area superficial das paredes da estufa apontada
void Alterar_Tipo_de_Fruta(estufa_t *estufa, void* Data); //Recebe um apontador para uma estufa_t e um apontador generico que aponta para um int e altera o tipo de fruta da estufa apontada


/*******************************************************************************************************************************************************************
*******************************************************************************************************************************************************************/

//23-01-2017 Joao Luis, Joao Borgues , Joao Gil , Miguel Silva