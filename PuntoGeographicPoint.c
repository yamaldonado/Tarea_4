#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
  
  int filas=500;
  int columnas= 744;
  int i, j;

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

  for (int i=0; i<columnas; i++){
     printf("%d\n", matriz[499][i]);
     
  }

  fclose(mapa);
  
  return 0;
}


void liberar_punteros(int **matriz, int filas){  
  for(int i=0; i<filas; i++){
    free(matriz[i]);
  }  
  free(matriz);
}
