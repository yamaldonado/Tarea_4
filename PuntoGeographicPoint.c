#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int filas;
int columnas;
void aleatorio_inicial(int *x_x, int *y_y, int **matriz);
int bordes(int a, int num);
void obtener_radio(int **matriz, int x, int y, float *rad);
void caminata(int *x_p, int *y_p, int **matriz);
void liberar_punteros(int **matriz);

int main(){
  
  filas=500;
  columnas= 744;
  int i, j;
  int x_new;
  int y_new;
  int x_old;
  int y_old;
  int radio=0;
  float radio_old;
  float radio_new;
  float alpha;
  float beta;
  int n_iteraciones=1000;
  int rango= 50;

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

  //empieza el metodo de montecarlo

  FILE *mejor_dato;
  mejor_dato= fopen("mejor.txt", "w+");
   
   aleatorio_inicial(&x_old, &y_old, matriz);
   obtener_radio(matriz, x_old, y_old, &radio_old);
   
   srand(time(NULL));
   
   for(i=0; i<n_iteraciones; i++){
         
     x_new = rand() % (filas-rango) + rango;
     y_new = rand() % (columnas-rango) + rango;
     
     while(matriz[bordes(x_new,filas)][bordes(y_new,columnas)]==1){
       x_new = rand() % (filas-rango) + rango;
       y_new = rand() % (columnas-rango) + rango;  
     }

     obtener_radio(matriz, x_new, y_new, &radio_new);
     alpha = radio_new/radio_old;
     if(alpha>=1.0){
       radio = radio_new;
      }
     else{
       beta = (rand()/(double)(RAND_MAX))*abs(0-1)+0;
       if (beta <= alpha){
	 radio = radio_new;
       }
       else{
	 radio= radio_old;
       }
     }
     x_old=x_new;
     y_old=y_new;
     radio_old = radio_new;
     //printf("%d %d %d\n", radio, x_new, y_new); 
   }  
  fprintf(mejor_dato, "%d %d %d\n", radio, x_new, y_new);   
  liberar_punteros(matriz);

  return 0;
}




void aleatorio_inicial(int *x_x, int *y_y, int **matriz){
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
void obtener_radio(int **matriz, int x, int y, float *rad){
  int parar=0;
  int r= *rad;
  for (int i=0; i<filas ; i++){
    for(int m=x-i; m<x+i ; m++){
      for(int n=y-i; n<y+i; n++){
	if((pow((pow(m-x, 2.0) + pow(n-y, 2.0)),0.5)<=i)){
	  
	  if(matriz[bordes(m,filas)][bordes(n,columnas)]==1){
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


void caminata(int *x_p, int *y_p, int **matriz){
  
  int a = *x_p;
  int b = *y_p;
  int rango=50;
  srand(time(NULL));
  a = rand() % (columnas-rango) + rango;
  b = rand() % (filas-rango) + rango;

   while(matriz[bordes(a,filas)][bordes(b,columnas)]==1){
     a = rand() % (columnas-rango) + rango;
     b = rand() % (filas-rango) + rango;
   }

   *x_p=a;
   *y_p=b;
      
}


void liberar_punteros(int **matriz){  
  for(int i=0; i<filas; i++){
    free(matriz[i]);
  }  
  free(matriz);
}
