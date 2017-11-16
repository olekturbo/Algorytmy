/*Zadanie AL4.6 (5 pkt.) W oparciu o wykład napisz program sortujący napisy (ciągi liter/cyfr) różnej długości 
 * (i zajmujące różne ilości pamięci), stosując sortowanie pozycyjne (od ostatniego znaku do pierwszego),
 *  gdzie sortowanie według kolejnych znaków (nie rozróżniając dużych i małych liter) ma być wykonane sortowaniem przez zliczanie.

Uwagi: Nie jest dobrą praktyką wyliczać długość napisu przy każdej próbie sięgnięcia do niego.
*  Lepiej utworzyć osobną tablicę zawierającą długości napisów. W pliku napisy10b.c jest przykład, który może być pomocny. 
* 
* ALEKSANDER SZEWCZAK 16.11.17
* */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>                       

#define MAX_DL_SL 50                 
#define MAX_A 127 
#define POM 1000    

char **A;                                     
char **B;                                         
char **TMP;

//liczenie wierszy
int Licznik() {
	FILE *plik = fopen("nazwiska", "r");
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

void CountingSort (char **A, char **B, int ilosc, int pozycja) {
  int i, j;
  int C[POM];                                    

  for (i = 0; i <= MAX_A; i++)                  
    C[i] = 0;                                      
  for (j = 1; j <= ilosc; j++)                    
    C[(int)A[j][pozycja]] += 1;                       
  for (i = 1; i <= MAX_A; i++)       
    C[i] = C[i] + C[i-1];                        
  for (j = ilosc; j > 0; j--) {              
    B[C[(int)A[j][pozycja]]] = A[j];                   
    C[(int)A[j][pozycja]] --; //przy kompilowaniu z -Wall dostawalem komunikat array subscript has type ‘char’ i dodalem przekonwertowanie do integer
    }
}

void RadixSort (char **A, char **B, int maxDlugoscNapisu, int ile) {
  int i;

  for (i = maxDlugoscNapisu - 1; i >= 0; i--) {         
    CountingSort (A, B, ile, i);             
    TMP = A;
    A = B;
    B = TMP;                                     
  }
}

void Czytaj (char **A, int ilosc) {  
  FILE *fp  = fopen("nazwiska", "r");             
  if (fp == NULL) {
    printf("Brak pliku nazwiska! \n");
    exit(1);
  }

  char slowo [MAX_DL_SL];                       
  int i, j;                                         

  for (i = 1; i <= ilosc; i++) {                                         
    fscanf(fp, "%s", slowo);     
    
    for (j = 0; j < strlen(slowo); j++)         
	slowo[j] = tolower(slowo[j]);    
	              
    A[i] = (char*) malloc(sizeof(char) * MAX_DL_SL);  
    strcpy(A[i], slowo);                     
  }
  fclose(fp);                                     
}

void Drukuj (char **A, int ilosc) {
  FILE *fp = fopen("nazwiska_sorted", "w");

  int i;

  for (i = 1; i <= ilosc; i++)                      
    fprintf(fp, "%s \n", A[i]);              

  fclose(fp);
}

int MaxDlugoscNapisu (char **A, int ilosc) {
  int i, max = 0;

  for (i = 1; i <= ilosc; i++) {                    
    if (strlen(A[i]) > max)                   
      max = strlen(A[i]);                     
  }
  return max;                                       
}

int main () {
	
  int ile = Licznik();
  
  A = (char**) malloc(ile * sizeof(char*));  
  B = (char**) malloc(ile * sizeof(char*));  
  TMP = (char**) malloc(ile * sizeof(char*));

  int maxDlugoscNapisu = 0;

  Czytaj (A, ile);                   

  maxDlugoscNapisu = MaxDlugoscNapisu (A, ile);

  RadixSort (A, B, maxDlugoscNapisu , ile);

  Drukuj (B, ile);
  
  printf("Nazwiska zostaly posortowane. Wynik zapisano w pliku nazwiska_sorted.\n");
}
