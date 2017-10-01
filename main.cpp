#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "fstream"
#include "string.h"
#include "iostream"
#include <iomanip>
#include<limits.h>
using namespace std;
void ordenar(int *V, int TAM);
void calcular(int *vec, int n, int k);
int recursiva(int *vec, int k, int cont, int i, int n);
int verificar(int *vec, int k, int i);
int main()
{
	int N, K, valor, *vec;
	char *aux;
	char linea[40];
	char cant[40];
	ifstream ob("input.txt");
	if(ob.is_open()){
		ob.getline(cant,90);
		for(int i=0;i<atoi(cant);i++){
			ob.getline(linea,90);
			aux=strtok(linea," ");
			N=atoi(aux);
			aux=strtok(NULL," ");
			K=atoi(aux);
			vec=new int[K];
			for(int j=0;j<K;j++){
				aux=strtok(NULL," ");
				vec[j]=atoi(aux);
			}
			ordenar(vec,K);
			calcular(vec,N,K);
		}
		ob.close();
	}
	getch();
}
void ordenar(int *V, int TAM){
	int temp;
	for(int i=0; i<TAM; i++){
	    for(int j=0 ; j<TAM - 1; j++){
	      if (V[j] < V[j+1]){
	        temp = V[j];
	        V[j] = V[j+1];
	        V[j+1] = temp;
	      }
	    }//j
   }//i
}
void calcular(int *vec, int n, int k){
	int cont, min=0,ver,contador;
	float final=0;
	for(int i=1;i<=n;i++){
		cont=0;
		contador=0;
		ver=0;
		ver=verificar(vec,k,i);
		cont=recursiva(vec,k,cont,i,n);
		if(cont<ver){
			contador=cont;
		}
		else{
			contador=ver;
		}
		if(contador>min){
			min=contador;
		}
		final=final+contador;
	}
	final=final/n;
	std::cout <<std::setprecision(3) <<final<<"  "<<min<<endl;
}
int verificar(int *vec, int k, int i){
	int count=0,min=INT_MAX;
	for(int j=0;j<k;j++){
		count=0;
		if(vec[j]<=i){
			if(i%vec[j]==0){
				count=i/vec[j];
				if((int)count<min){
					min=(int)count;
				}
			}	
			
		}
	}
	return min;
}

int recursiva(int *vec, int k, int cont, int i, int n){
	int r=0,r2=n;
	bool bandera=false, bandera2=false;
	for(int j=0;j<k;j++){
		if(i!=0){
			if(vec[j]==i){
				cont++;	
				i=i-vec[j];
				break;
			}
			else{
				if(vec[j]<i){
					r=i-vec[j];
					if(j>0){
						r2=vec[j-1]-i;
					}
					for(int t=0;t<k;t++) {
						if(vec[t]==r){
							bandera=true;
						}
						if(vec[t]==r2){
							bandera2=true;
						}
					}
					if(bandera){
						bandera=false;
					}
					else{
						if(bandera2){
							r=r2;
							bandera2=false;
						}
							
					}
					if(r<r2){            				
						cont++;
						i=i-vec[j];
						cont=recursiva(vec,k,cont,i,n);
						break;
						
					}
					else{
						cont++;
						i=vec[j-1]-i;
						cont=recursiva(vec,k,cont,i,n);
						break;
						
					}
				}
			}
		}
	}
	return cont;
}
