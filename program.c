//PROJETO DESENVOLVIDO POR:
//19188 - MATEUS STOLZE VAZQUEZ, 
//19194 - NOUANI GABRIEL SANCHES
//18172 - VICTOR BOTIN AVELINO
 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>


char* inverterVetor(char vetorinteiro[], int tamanhoVetor)
{
  char* vetorAux = (char*)malloc(sizeof(char)*tamanhoVetor);
  
  int i1, i2;
  for(i1 = 0, i2 = tamanhoVetor - 1; i1 < tamanhoVetor; i1++, i2--)
  {
    vetorAux[i1] = vetorinteiro[i2];
  }

  return vetorAux;
}

char* alterarVetor(char vetorOriginal [], int tamanhoAntigo, int novoTamanho)
{
  
  char* vetorAux = (char*)malloc(sizeof(char)*novoTamanho);

  if(tamanhoAntigo < novoTamanho)
  {
    for(int i = 0; i < tamanhoAntigo; i++)
    {
      vetorAux[i] = vetorOriginal[i];
    }
  }
  else
  {
    for(int i = 0; i < novoTamanho; i++)
    {
      vetorAux[i] = vetorOriginal[i];
    }
  }

  return vetorAux;
}

/*
Aqui recebemos os parametros do numero que é um double e a base que vamos passar ele
*/

//aqui fazemos a transicao de int para char de acordo com o resto
char getValorInt(int valor)
{
  char num [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  return num[valor];
}

char* dezParaOutra(double numero, int outraBase) 
{
  //declaramos um vetor que futuramente será expandido
  char* numeroInvertido = (char*)malloc(sizeof(char)*20);
  //isso sera usado no futuro para retornar um vetor com o preciso tamanho que sera usado
  int vez = 0;
  //faremos 3 etapas, uma com a parte inteira, a outra com a parte decimal e por fim as uniremos. 
  int parteInteira = (int)numero;
  double parteFrac = numero - parteInteira;

  
  //essa eh a etapa numero 1, etapa "(i)"
  //se a parte inteira nao e mais maior que 0
  while(parteInteira > 0)
  {
    
    numeroInvertido[vez] = getValorInt((parteInteira % outraBase));
    parteInteira = parteInteira / outraBase;
    vez += 1;

    //se ele preencheu todos os espacos do vetor, vamos alterar ele para um maior
    if(vez == strlen(numeroInvertido) -1)
      numeroInvertido = alterarVetor(numeroInvertido, strlen(numeroInvertido) , (strlen(numeroInvertido) + 5));
  }

  numeroInvertido = alterarVetor(numeroInvertido, strlen(numeroInvertido), vez);
  //a partir de agora, o vetor nao eh mais invertido
  numeroInvertido = inverterVetor(numeroInvertido, strlen(numeroInvertido));
  
  /*essa e a segunda etapa que so acontece se o numero tiver algo na parte decimal*/

  if(parteFrac > 0.0)
  {
    //se o numero tiver algo na parte decimal, vamos expandir o vetor em 10 casas e calcular as 10 primeiras casas decimais

    numeroInvertido = alterarVetor(numeroInvertido, vez, vez + 10);

    numeroInvertido[vez] = ',';
    vez++;
    int i;
    for(i = 0; i < 9 ; i++, vez++)
    {
      //se  a parte fracionaria se tornar 0
      if(parteFrac == 0.0)
      break;

      // a parte fracionaria eh multiplicada pela outra base
      parteFrac = parteFrac * outraBase;
      // armazenamos a parte inteira
      numeroInvertido[vez] = getValorInt(parteFrac);
      // removemos a parte inteira e agora ela eh fracionaria de novo
      parteFrac = parteFrac - (int)parteFrac;    
    }
  }

  return numeroInvertido;
}

int getVirgulaPosicao(char numero[], int tamanho) {
  int i = 0;
  for (; i < tamanho; i++){
    if (numero[i] == ',') {
      return i;
    }
  }
  return -1;
}

double getValorChar(char valor) {
  if (isdigit(valor)) {
    //o -48 e -55 envolve os digitos da tabela ascII
    return (double) valor - 48;
  } else {
    return (double) toupper(valor) - 55;
  }
}

double outraParaDez(char numero[], int tamanho, int baseAtual) {
  
  double resultado = 0;
  //
  int indexPotencia = 0, index = 0;

  /*
  usaremos a posicao da virgula para determinar 
  onde começa a parte inteira e a decimal, isso 
  vai determinar a partir de qual casa comecamos 
  a potencializacao
  */
  int posicaoVirgula = 0;
  posicaoVirgula = getVirgulaPosicao(numero, tamanho);

  /*
  Se nao houver nenhuma virgula, iremos determinar essa posicao
  como a "posicao invisivel" que existe em todos os numeros inteiros:
  a ultima posicao, por exemplo, 13 eh o mesmo que 13,0 que e o mesmo que 13,00 na matematica, entao colocamos a posicao da virgula como a ultima do vetor
  */
  if (posicaoVirgula == -1) 
      posicaoVirgula = tamanho - 1;

  /*
  
  Nessa parte eh realizada a potencializacao da parte inteira:
  ele comeca na unidade (index = posicaoVirgula - 1) e vai ate a ate a casa mais a esquerda (que seria quando index = 0), ao mesmo tempo,ele realiza as potencializacoes com indexPotencia, conforme as repeticoes sao feitas, ele diminui o index, indo para casas mais a esquerda e aumenta a potencia. 
  */
  for (index = posicaoVirgula - 1, indexPotencia = 0; index >= 0; index--, indexPotencia++) 
  {
    double valorChar = getValorChar(numero[index]);
    resultado = resultado + valorChar * pow(baseAtual, indexPotencia);
  }

  /*isso eh o contrario, ele faz potencializacao negativa e move-se para a direita, mas primeiro, ele verifica se ha casas descimais, a mecanica e a mesma*/
  if (posicaoVirgula != tamanho - 1) {
    for (index = posicaoVirgula + 1, indexPotencia = 1; index < tamanho - 1; index++, indexPotencia++) {
      double valorChar = getValorChar(numero[index]);
      resultado = resultado + valorChar * pow((double)1/baseAtual, (double)indexPotencia);
    }
  }

  return resultado;
}

char* removeSinal(char numero[], int tamanho) {
  char *numeroSemSinal = (char*)malloc(tamanho*sizeof(char));

  int i1, i2;

  for (i1 = 1, i2 = 0; i1 < tamanho; i1++) {
    numeroSemSinal[i2] = numero[i1];
    i2++;
  }

  return numeroSemSinal;
}

char* adicionaSinal(char numero[], int tamanho) {
  char *numeroComSinal = (char*)malloc(tamanho*sizeof(char));
  
  numeroComSinal[0] = '-';
  int i1, i2;
  for (i1 = 0, i2 = 1; i1 < tamanho; i1++, i2++) {
    numeroComSinal[i2] = numero[i1];
  }

  return numeroComSinal;
}

int main() {
  char numero[1000];
  int baseAtual = 0, baseFutura = 0;

  printf("Digite o número: ");
  fgets(numero, 1000, stdin);

  printf("\nDigite a base atual: ");
  scanf("%d", &baseAtual);

  printf("\nDigite a base futura: ");
  scanf("%d", &baseFutura);
  fflush(stdin);
  
  int ehNegativo = 0;
  if (numero[0] == '0') ehNegativo = 1;

  char *n = (char*)malloc(1000*sizeof(char));

  if (ehNegativo)
      n = removeSinal(numero, strlen(numero));
  else
      n = numero;

  char* novoNumero = dezParaOutra(outraParaDez(n, strlen(n), baseAtual), baseFutura);

  if (ehNegativo)
      novoNumero = adicionaSinal(novoNumero, strlen(novoNumero));

  printf("%s", novoNumero);
  
  return 0;
}
