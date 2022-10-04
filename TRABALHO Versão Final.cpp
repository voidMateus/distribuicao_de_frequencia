/*************************************************************************
Descrição do Algoritmo: 
Este algoritmo trata-se da solução para o trabalho da disciplina de Algoritmos II 2021/3.

O codigo tem como objetivo a analise de uma amostra de inteiros,
esta amostra foi pre-definida na orientação do trabalho, sendo valores representados como 
"CLASSIFICAÇÃO FINAL DO CAMPEONATO BRASILEIRO 2017 SÉRIE A"

Foi orientado que fosse usada para criação do histograma a biblioteca conion2.h
No entando, devido diversos problemas entre os compiladores/IDE e a biblioteca,não foi possivel usa-la.

Para elaboração do histograma foi usada sintaxes "comuns".
A biblioteca windows.h foi usada apenas para "colorir" a exibição no console.

Nome da Disciplina:  Algoritmos II
Nome Professor: Leonair Neves Sousa
Nome Aluno: Mateus Augusto Silva
Turma: Sistemas de Informação 2021/3
RGA: 202111316026
Data Entrega: 10/08/2022
*************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<math.h>
#include <windows.h>

// função para retornar a soma dos valores do vetor da amostra:
int somar (int vetor[20]){
	int soma = 0;
	for(int i = 0;i<20;++i){
		soma = soma + vetor[i];
	}
	return soma;
}

// procedimento para imprimir a matriz da distribuicao da frequencia:
void imprimirmatriz(float matriz[5][8]){
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("Tabela Distribuicao da Frequencia:\n\n");
	SetConsoleTextAttribute(color,6);
	printf("\tCI\tCS\tFI\tXI\tFR\tFCA\tFCI\tFCS\n");
	for(int i = 0;i<5;++i){
		for(int j = 0;j<8;++j){
			switch(j){
				case 0:
					printf("\t%2.0f|",matriz[i][j]);
					break;
				case 1:
					printf("\t%2.0f|",matriz[i][j]);
					break;
				case 2:
					printf("\t%2.0f|",matriz[i][j]);
					break;
				case 4:
					printf("\t%2.0f%%|",matriz[i][j]);
					break;	
				case 5:
					printf("\t%3.0f%|",matriz[i][j]);
					break;		
				default:
					printf("\t%2.1f|",matriz[i][j]);
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(color,7);
}
// procedimento para imprimir o histrograma:
void histogram(float matriz[5][8]){
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	
	int menor, maior = matriz[0][2];
	for(int i = 0; i < 5; i++){
		if(matriz[i][2] > maior){
			maior = matriz[i][2];
		}
		if(matriz[0][2] < menor){
			menor = matriz[i][2];
		}
	}
	
	
	printf("\n\n");
	printf("Histograma:\n\n");
	
	for (int c = maior; c > 0; --c){
        printf("%d|\t", c);
        for (int d = 0; d < 5; ++d){
			SetConsoleTextAttribute(color,2+d);
			if (matriz[d][2] >= c){
				
				printf("%c%c",178,178);
			}

            printf("\t");
            SetConsoleTextAttribute(color,7);
        }
        printf("\n");
    }
	
	
    printf("  ");
    for (int c = 0; c < 42; ++c)
        printf("-");
    
	printf("\n");

    for (int c = 0; c < 5; ++c)
        printf("\t%.0f-%.0f", matriz[c][0],matriz[c][1]);

    printf("\n");
    
}
	
//Procedimento para calculo da Moda da amostra:	
void moda(int *amostra, int n){
	// Declaração da matriz auxiliar e demais variaveis:
	int maux[2][n];
	int i,j,aux;
	
	//"Zerando" os valores da matriz auxiliar:
	for( i = 0;i<2;++i){
		for( j = 0;j<n;++j){
			maux[i][j] = 0;
		}
	}
	
	//atribuindo os elementos na matriz auxiliar, eliminando os duplicados
	aux = 0;
	for( i = 0; i < n; i++){
        for( j = 0; j < aux; j++ )
        {
            if( amostra[i] == maux[0][j] )
                break;
        }

        if( j == aux )
        {
            maux[0][aux] = amostra[i];
            aux++;
        }
    }

	//calculando a incidencia dos elementos (vezes repetidas):
	for( i = 0; i < n; i++){
        for( j = 0; j < n; j++ ){
            if( amostra[j] == maux[0][i] )
                maux[1][i]++;
        }
    }
    
    //identificando numero que mais se repete:
    int maior = 0;
	for(int i = 0; i < n; i++){
		if(maux[1][i] > maior){
			maior = maux[1][i];
		}
	}
	
	//imprimindo moda(s):
	printf("Moda: ");
	for(int i = 0;i<n;i++){
		if(maior==maux[1][i])
			printf("%i ",maux[0][i]);
	}
	printf("(%i Recorrencias)",maior);
	
}


int main(){
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//Declaração da quantidade de elementos da amostra:
	int n = 20;
	
	//Declaração e atribuição da amaostra:
	int amostra[n] = {43,43,43,39,36,47,45,72,63,50,50,53,51,54,54,57,56,56,62,63};
	
	//Declaração da matriz
	float matriz[5][8];
	
	// Demais declarações:
	int ci = 0;
	float k, at, atc, media, mediana;
	int menor, primeiro, cont, aux = 0;
	
	//Ordenando o vetor da amostra:
	while (cont<20){
		menor = primeiro;
		for(int i = primeiro + 1; i < 20; i++){
			if(amostra[menor] > amostra[i]){
				menor = i;
			}
		}
		aux = amostra[primeiro];
		amostra[primeiro] = amostra[menor];
		amostra[menor]=aux;
		primeiro = primeiro + 1;
		cont++;
	}

	//Calculo dos valores da amostra:
	k = ceil(pow(n,0.5));
	at = amostra[19] - amostra[0];
	atc = ceil(at/k);
	media = somar(amostra)/n;
	mediana = (amostra[9]+amostra[10])/2;
	
	// Calculo da tabela da distribuicao da frequencia:
	for(int lin = 0;lin<5;++lin){
		for(int col = 0;col<8;++col){
			switch(col){
				
				case 0:
					if(lin==0){
						matriz[lin][col] = amostra[0];
					}else{
						matriz[lin][col] = matriz[lin-1][col]+atc;
					}		
					break;
					
				case 1:
					matriz[lin][col] = (matriz[lin][0] + atc)-1;
					break;
				
				case 2:
					matriz[lin][col] = 0;
					for (int i2 = 0; i2<20;++i2){
						if((amostra[i2]>=matriz[lin][0])&&(amostra[i2]<=matriz[lin][1]))
							matriz[lin][col]=matriz[lin][col]+1;
					}		
					break;
				
				case 3:
					matriz[lin][col] = (matriz[lin][0]+matriz[lin][1])/2;
					break;
					
				case 4:
					matriz[lin][col] = (matriz[lin][2]*100)/n;
					break;	
					
				case 5:
					matriz[lin][col]=0;
					for(int x=lin;x>=0;--x) matriz[lin][col] = matriz[x][2]+matriz[lin][col];
					break;
				
				case 6:
					matriz[lin][col]=matriz[lin][0]-0.5;
					break;
				
				case 7:
					matriz[lin][col]=matriz[lin][1]+0.5;
					break;
				
				default:
					matriz[lin][col]=-99;	
			}
		}	
	}
	
	//Imprimir Vetor:
	printf("Amostra: ");
	SetConsoleTextAttribute(color,3);
	for(int i=0;i<n;++i) printf(" %i",amostra[i]);
	printf("\n\n");
	SetConsoleTextAttribute(color,7);
	
	//Imprimir dados calculados a partir da amostra:
	printf("Dados Identificados:\n");
	SetConsoleTextAttribute(color,2);
	printf(" K: %.1f\n",k);
	printf(" AT: %.0f\n",at);
	printf(" ATC: %.0f\n",atc);
	printf(" Media: %.1f\n",media);
	printf(" Mediana: %.0f\n",mediana);
	printf(" ");moda(amostra, n);
	printf("\n\n\n");
	SetConsoleTextAttribute(color,7);
	
	//Imprimir Grafico de histogrma:
	imprimirmatriz(matriz);
		
	
	//Imprimir Grafico de histogrma: 
	histogram(matriz);
		
	
	return 0;
}
