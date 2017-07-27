#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void aleatorio_inicial(int filas, int columnas, int x, int y, int **matriz);
void mascara(int **matriz, int x, int y, int filas);
void liberar_punteros(int **matriz, int filas);

int main(){
  
  int filas=500;
  int columnas= 744;
  int i, j;
  int x;
  int y;
  int radio;

  int **matriz = malloc(filas*sizeof(int *));
  
  for (i=0; i<filas; i++){
    matriz[i]= malloc(columnas*sizeof(int));
  }

  FILE *mapa;
  mapa = fopen("map_data.txt", "r");
  
  for (i=0; i<filas; i++){
    for(j=0; j<columnas; j++){       
      fscanf(mapa,"%d", &matriz[i][j]);       
     } 
  }

  
  fclose(mapa);

  
  int min=0;
  srand(time(NULL));

  while(matriz[x][y] != 1){
    y = rand() % (columnas - min +1) + min;
    x = rand() % (filas - min+1 ) + min;
  }
 
  

  aleatorio_inicial(filas, columnas, x, y, matriz);
  //mascara(matriz, 170, 100, filas);
  printf("%d", radio);
  liberar_punteros(matriz, filas);

  return 0;
}

void aleatorio_inicial(int filas, int columnas, int x, int y, int **matriz){
  
  int min=0;
  srand(time(NULL));

  while(matriz[x][y] == 1){
    y = rand() % (columnas-min+1) + min;
    x = rand() % (filas-min+1) + min;
  }
}


  
void mascara(int **matriz, int x, int y, int filas){
  int radio=0;
  for (int i=0; i<filas ; i++){
    for(int m=x-i; m<x+i ; m++){
      for(int n=y-i; n<y+i; n++){
	if(matriz[m][n]==1){
	  i=filas;
	  n=y+i;
	  m=x+i;
	}
      }
    }
    radio=i;
   }  
}


void liberar_punteros(int **matriz, int filas){  
  for(int i=0; i<filas; i++){
    free(matriz[i]);
  }  
  free(matriz);
}
