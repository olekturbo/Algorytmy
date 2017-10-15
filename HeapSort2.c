/* Aleksander Szewczak
 * Informatyka, II ROK
 * Grupa 5 */
 


#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b){
  int zm=*a;
  *a=*b;
  *b=zm;
}

void Heapify(int *A, int i, int heapSize){
  int k, j;
  k=A[i-1];
  while (i<=heapSize/2){
    j=2*i;
    if (j<heapSize && A[j-1]<A[j]) j++;
    if (k>=A[j-1]) break;
    else{
      A[i-1]=A[j-1];
      i=j;
    }
  }
  A[i-1]=k;
}

void BuildHeap(int *A, int rozmiar){
  int i;
  for (i=rozmiar/2; i>0; i--) Heapify(A, i, rozmiar);
}

void HeapSort(int *A, int rozmiar){
  int i;
  BuildHeap(A, rozmiar);
  for (i=rozmiar; i>1; i--){
    swap(&A[i-1], &A[0]);
    rozmiar--;
    Heapify(A, 1, rozmiar);
  }
}
	
int licznik(char *nazwa) {
	 FILE *plik = fopen(nazwa, "r");

	int licz = 0;
	char ch;

	do {
      ch = fgetc(plik);                                       
  		if(ch == '\n')                                        
  			licz++;                                        
	} while (ch != EOF);

	fclose(plik);
return licz;
}	

int main(int argc, char *argv[]) {
   
   FILE *plik = fopen(argv[1], "r");
	if (plik == NULL) {
		printf("Nie mozna otworzyc pliku");
		exit(0);
}
  int ile = licznik(argv[1]);
   int *A=(int*)malloc(ile*sizeof(*A));

  
  int i;
  
  printf("Tablica przed sortowaniem:\n");
  
  for(i = 0; i < ile; i++) {
	fscanf(plik, "%d", &A[i]);
	printf("%d\t",A[i]);
}
fclose(plik);

    FILE *wyjscie = fopen("wyjscie","w");
  printf("\nTablica po sortowaniu:\n");
HeapSort(A,ile);

  for(i = 0; i < ile; i++) {
	  printf("%d\t",A[i]);
	  fprintf(wyjscie,"%d\n",A[i]);
  }
  
  
  printf("\n");
  for(i = 0; i < 77; i++) 
	  printf("-");
  
  printf("\nPosortowana tablica zostala zapisana do nowego pliku.\n\n");
  
fclose(wyjscie);
}

