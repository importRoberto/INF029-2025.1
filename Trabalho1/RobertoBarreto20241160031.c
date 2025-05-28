// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----

//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:      Roberto Silva Barreto
//  E-mail:    robertoboficial@gmail.com
//  Matrícula: 20241160031
//  Semestre:  2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
//  Última atualização: 07/05/2021 - 19/08/2016

// #################################################


#include <stdio.h>
#include "RobertoBarreto20241160031.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

//Função para verificar se o ano é bissexto
int bissexto(int ano){
    //Checa se o aaaa tem 2 caracteres e insere +2000 anos, como sugerido
    if (ano < 100){
        ano += 2000;
    }
    
	if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0){
		return 1;
	}

	return 0;
}

//Usada na Q1 e Q2, cria um array para dizer quais os dias em cada mês
int diasNoMes(int mes, int ano) {
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // if fevereiro, checa bissexto
    if (mes == 2) {
        if (bissexto(ano)) {
             // Fevereiro = 29 no bissexto
            return 29;
        }
    }
    return diasPorMes[mes - 1];
}

//Função usada na Q3 para converter maiúsculos para minúsculos
int minuscular(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

int calcularTamanho(char palavra[]) {
    int tamanho = 0;
    while (palavra[tamanho] != '\0') {
        tamanho++;
    }
    return tamanho;
}

int buscarEmDirecao(char matriz[8][10], int linha, int coluna, char palavra[], int dx, int dy) {
    int tamanho = calcularTamanho(palavra);

    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + i * dx;
        int novaColuna = coluna + i * dy;

        // Verifica limites da matriz
        if (novaLinha < 0 || novaLinha >= 8 || novaColuna < 0 || novaColuna >= 10)
            return 0;

        // Verifica caractere da matriz com a letra da palavra
        if (matriz[novaLinha][novaColuna] != palavra[i])
            return 0;
    }

    return 1; // Palavra encontrada nessa direção
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    Uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa = ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */


int q1(char data[])
{
    DataQuebrada dq = quebraData(data);

	//Checa se o tamanho é compatível
	if (strlen(data)>10 || strlen(data)<6){
		return 0;
	}

    // Verifica se a data foi quebrada corretamente
    if (dq.valido == 0) {
        return 0; // Data inválida se a quebra falhou
    }

    // Verificar se o mês está no intervalo de 1 a 12
    if (dq.iMes < 1 || dq.iMes > 12) {
        return 0; // Mês inválido
    }

    // Verificar se o dia está dentro do intervalo válido para o mês
    int dias = diasNoMes(dq.iMes, dq.iAno);

    if (dq.iDia < 1 || dq.iDia > dias) {
        return 0; // Dia inválido para o mês
    }

    // Se passar por todas as validações
    return 1; // Data válida
}




/*
 Q2 = diferença entre duas datas
    @objetivo
        Calcular a diferença em anos, meses e dias entre duas datas
    @entrada
        uma string datainicial, uma string datafinal. 
    @saida
        Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
        1 -> cálculo de diferença realizado com sucesso
        2 -> datainicial inválida
        3 -> datafinal inválida
        4 -> datainicial > datafinal
        Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
*/

DiasMesesAnos q2(char datainicial[], char datafinal[]) {

    // Estrutura para armazenar os dados calculados
    DiasMesesAnos dma;

    // Inicialização dos campos da estrutura DiasMesesAnos com zero
    dma.qtdAnos = 0;
    dma.qtdMeses = 0;
    dma.qtdDias = 0;

    // Verifica se as datas são válidas
    if (q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;

    } else if (q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;

    } else {
        // Variáveis para armazenar os valores separados das datas
        DataQuebrada fim, inicio;
        inicio = quebraData(datainicial); // Quebra a data inicial em dia, mês e ano
        fim = quebraData(datafinal); // Quebra a data final em dia, mês e ano
        
        // Verifica se a data final não é menor que a data inicial
        if (fim.iAno < inicio.iAno || 
            (fim.iAno == inicio.iAno && fim.iMes < inicio.iMes) || 
            (fim.iAno == inicio.iAno && fim.iMes == inicio.iMes && fim.iDia < inicio.iDia)) {
            dma.retorno = 4;
            return dma;

        } else {
            // Calcula a diferença entre as datas
            dma.retorno = 1;
            
            // Calcula a diferença de anos
            dma.qtdAnos = fim.iAno - inicio.iAno;

            // Calcula a diferença de meses
            dma.qtdMeses = fim.iMes - inicio.iMes;

            if (dma.qtdMeses < 0) { // Casos em que a diferença resulta em menos de um ano
                dma.qtdMeses += 12;
                dma.qtdAnos--;
            }

            // Calcula a quantidade de dias
            dma.qtdDias = fim.iDia - inicio.iDia;
            if (dma.qtdDias < 0) {
                dma.qtdDias += diasNoMes(inicio.iMes, inicio.iAno);
                if (bissexto(inicio.iAno) && inicio.iMes == 2) {
                    dma.qtdDias--; // Verifica ano bissexto
                }

                dma.qtdMeses--;
            }

            // Ajusta a quantidade de dias para anos bissextos
            if (((bissexto(inicio.iAno) && inicio.iMes == 1) || 
                (bissexto(inicio.iAno) && inicio.iMes == 2 && inicio.iDia == 29)) &&
                ((inicio.iAno == fim.iAno && fim.iMes != 2) ||
                (inicio.iAno < fim.iAno && fim.iMes < 2))) {
                dma.qtdDias++;
            }           
            
            return dma;
        }
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
*/

int q3(char *texto, char c, int isCaseSensitive)
{
    // Inicializa a contagem de ocorrências
    int qtdOcorrencias = 0;

    // Percorre cada caractere da string
    for (int i = 0; texto[i] != '\0'; i++) {
        // Se a pesquisa não for case sensitive, converte ambos os caracteres para minúsculas
        if (!isCaseSensitive) {
            if (minuscular(texto[i]) == minuscular(c)) {
                qtdOcorrencias++;
            }
        } else {
            // Se a pesquisa for case sensitive, compara diretamente
            if (texto[i] == c) {
                qtdOcorrencias++;
            }
        }
    }

    return qtdOcorrencias; // Retorna a contagem de ocorrências
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;
*/

int q4(char *strTexto, char *strBusca, int posicoes[30]) {   

    // Inicializações
    int qtdOcorrencias = 0, posicoesBusca = 0;

    // Evita aviso de incompatibilidade de int com strlen, e deixa mais bunitin
    int tamTexto = strlen(strTexto), tamBusca = strlen(strBusca);

    // Percorre o texto até a posição onde ainda é possível encontrar a string de busca
    for(int i = 0; i < tamTexto - tamBusca; i++) {
        
        // Variáveis auxiliares
        int aux = 0;
        int k = i;

        // Percorre a string de busca
        for(int j = 0; j < tamBusca; j++) {
            // Ignora caracteres especiais (no caso, -61)
            if(strTexto[k] == -61 || strBusca[j] == -61) {
            continue;

            // Se os caracteres correspondem, incrementa o contador auxiliar e avança no texto
            } else if(strTexto[k] == strBusca[j]) {
                aux++;
                k++;

            } else {
                break;
            }
        }

        // Se todos os caracteres da string de busca foram encontrados
        if(aux == tamBusca){
            // Armazena a posição inicial e final
            posicoes[posicoesBusca] = i + 1;
            posicoesBusca++;
            
            posicoes[posicoesBusca] = k;
            posicoesBusca++;
            // Avança no texto para evitar sobreposição de buscas
            i += tamBusca - 1;

            qtdOcorrencias++;
        }

    }

    return qtdOcorrencias;
}

/*
Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
*/


int q5(int num){

    int invert = 0;

    while (num != 0){
        invert = invert * 10 + num % 10;
        num /= 10;
    }

    num = invert;

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base

*/

int q6(int numerobase, int numerobusca) {
    
    int qtdOcorrencias = 0;
    int casa = 1; // Potência de 10 do numerobusca
    int tempBusca = numerobusca; // Temporário para contar dígitos

    // Calcula a potência de 10 do numerobusca
    while (tempBusca > 0) {
        casa *= 10;
        tempBusca /= 10;
    }

    // Verifica se numerobusca está em numerobase
    while (numerobase > 0) {
        if (numerobase % casa == numerobusca) { 
            numerobase -= numerobusca; // Remove numerobusca de numerobase
            qtdOcorrencias++;
        }
        numerobase /= 10; // Remove último dígito
    }
 
    return qtdOcorrencias;
}


/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[]) {
    // Todas as 8 direções possíveis (linha, coluna)
    int direcoes[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    for (int i = 0; i < 8; i++) {         // linhas
        for (int j = 0; j < 10; j++) {    // colunas
            for (int d = 0; d < 8; d++) { // direções
                if (buscarEmDirecao(matriz, i, j, palavra, direcoes[d][0], direcoes[d][1])) {
                    return 1; 
                }
            }
        }
    }

    return 0; 
}



//Função para quebrar a data da Q1 e Q2
DataQuebrada quebraData(char data[]){
	DataQuebrada dq;
  	char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];
	}
	if (i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	} else {
		dq.valido = 0;
    return dq;
	}  
	

	int j = i + 1; //anda 1 casa para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if (i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	} else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for (; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if (i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	} else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
