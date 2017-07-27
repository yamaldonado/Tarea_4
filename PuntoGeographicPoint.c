#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void aleatorio_inicial(int filas, int columnas, int *x_x, int *y_y, int **matriz);
int bordes(int a, int num);
void radio_r(int **matriz, int x, int y, int filas, int columnas, int *rad);
void caminata(int *x, int *y, int **matriz, int filas, int columnas);
void liberar_punteros(int **matriz, int filas);

int main(){
  
  int filas=500;
  int columnas= 744;
  int i, j;
  int x;
  int y;
  int radio=0;

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

  
  aleatorio_inicial(filas, columnas, &x, &y, matriz);
  //printf("%d %d\n", x, y);
  radio_r(matriz, x, y, filas, columnas, &radio);
  //printf("%d\n", radio);
  caminata(&x, &y, matriz, filas,columnas);
  printf("%d %d\n", x, y);
  liberar_punteros(matriz, filas);

  return 0;
}




void aleatorio_inicial(int filas, int columnas, int *x_x, int *y_y, int **matriz){
  int xx=*x_x;
  int yy=*y_y;
  int min=0;
  srand(time(NULL));
   yy = rand() % (columnas-min) + min;
   xx = rand() % (filas-min) + min;

  while(matriz[xx][yy] == 1){
    yy = rand() % (columnas-min) + min;
    xx = rand() % (filas-min) + min;
  }
  *x_x=xx;
  *y_y=yy;
}

int bordes(int a, int num){
  if (a >= num){
    a = a - num;
  }
  if (a < 0){
    a = a + num;
  }
  return a;
}  
void radio_r(int **matriz, int x, int y, int filas, int columnas, int *rad){
  int parar=0;
  int r= *rad;
  for (int i=0; i<filas ; i++){
    for(int m=x-i; m<x+i ; m++){
      for(int n=y-i; n<y+i; n++){
	if((pow((pow(m-x, 2.0) + pow(n-y, 2.0)),0.5)<=i)){
	  
	  if(matriz[bordes(m,columnas)][bordes(n,filas)]==1){
	    r=i;
	    parar=1;
	    	    
	  }
	}
	if(parar!=0){
	  break;
	}
      }
      if(parar!=0){
	break;
      }
    }
    if(parar!=0){
      break;
    }
  }
  *rad=r;
  
}


void caminata(int *x, int *y, int **matriz, int filas, int columnas){
  
  int a = *x;
  int b = *y;
  int rango=50;
  srand(time(NULL));
  a = rand() % (columnas-rango) + rango;
  b = rand() % (filas-rango) + rango;

   while(matriz[bordes(a,filas)][bordes(b,columnas)]==1){
     a = rand() % (columnas-rango) + rango;
     b = rand() % (filas-rango) + rango;
   }

   *x=a;
   *y=b;
}


void liberar_punteros(int **matriz, int filas){  
  for(int i=0; i<filas; i++){
    free(matriz[i]);
  }  
  free(matriz);
}
