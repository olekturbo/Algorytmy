/* Aleksander Szewczak
 * Informatyka, II ROK
 * Grupa 5 */
 
/* Zadanie AL3.5 (5+2* pkt.)

    Zaimplementuj algorytm sortowania szybkiego omówiony na wykładzie. (4 pkt.)

    Następnie zmodyfikuj ten algorytm tak, aby dla tablic o rozmiarze mniejszym od pewnej stałej c ≥ 1 (tj. kiedy r−p+1 < c) nie była wykonywana procedura Partition i rekursywne wywołania,
    tylko stosowane było jakieś proste sortowanie, np. bąbelkowe czy przez wstawianie. Przetestuj czy zmodyfikowany algorytm poprawnie sortuje.(2 pkt.)
	Porównaj czasy działania algorytmu podstawowego oraz jego modyfikacji dla dwóch rodzajów danych: dane losowe oraz dane skrajnie niekorzystne (ciąg malejący). 
    Podobnie jak w zadaniu AL3.3, dla tego samego rodzaju danych należy zestawić czasy działania dwóch wersji algorytmów. (1 pkt) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double getUnixTime(void);
void swap(int *a, int *b);
void Quicksort(int *A, int p, int r, int c);
void Randomize(int *A, int rozmiar);
void badRandomize(int *A, int rozmiar);
void randomizeTime(double *czas, int c);
void badRandomizeTime(double *czas, int c);
void bubbleSort(int *A, int ile);
void QuicksortNormal(int *A, int p, int r);
void randomizeTimeNormal(double *czas);
void badRandomizeTimeNormal(double *czas);

double getUnixTime(void) { // pobor czasu
	struct timespec tv;
  if (clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;
return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
	
}

void swap(int *a, int *b){
  int zm=*a;
  *a=*b;
  *b=zm;
}

int Partition(int *A, int p, int r) {
	
	int x = A[r];
	int i = p-1;
	for(int j=p; j <= r; j++) {
		if(A[j]<=x) {
			i++;
			swap(&A[i],&A[j]);
		}
	}
	if(i<r) return i;
	else return i-1;
	
}

void Quicksort(int *A, int p, int r, int c) { //zmodyfikowany algorytm AL3.4
	int q;
	if(p<r && r-p+1>=c) {
		q = Partition(A,p,r);
		Quicksort(A,p,q,c);
		Quicksort(A,q+1,r,c);
	}
	if(p<r && r-p+1<c) bubbleSort(A,r-p+1);
}

void QuicksortNormal(int *A, int p, int r) { //normalny algorytm
	int q;
	if(p<r) {
		q = Partition(A,p,r);
		QuicksortNormal(A,p,q);
		QuicksortNormal(A,q+1,r);
	}
}

void Randomize(int *A, int rozmiar) { //losowanie liczby
	srand(time(NULL));
	for(int i = 0; i < rozmiar; i++) A[i] = rand()%9999;
}

void badRandomize(int *A, int rozmiar) { //ciag malejacy
	for(int i = rozmiar-1; i >0 ; i--) A[i] = i;
}

void randomizeTime(double *czas, int c) { //obliczanie czasu bubble+quick
	int tab100[100], tab500[500], tab1000[1000], tab2500[2500], tab5000[5000];
	double Tn_start, Tn_stop;
	
	Randomize(tab100,100);
	Tn_start = getUnixTime();
	Quicksort(tab100,0,100,c);
	Tn_stop = getUnixTime();
	czas[0] = Tn_stop - Tn_start;
	
	Randomize(tab500,500);
	Tn_start = getUnixTime();
	Quicksort(tab500,0,100,c);
	Tn_stop = getUnixTime();
	czas[1] = Tn_stop - Tn_start;
	
	Randomize(tab1000,1000);
	Tn_start = getUnixTime();
	Quicksort(tab1000,0,1000,c);
	Tn_stop = getUnixTime();
	czas[2] = Tn_stop - Tn_start;
	
	Randomize(tab2500,2500);
	Tn_start = getUnixTime();
	Quicksort(tab2500,0,2500,c);
	Tn_stop = getUnixTime();
	czas[3] = Tn_stop - Tn_start;
	
	Randomize(tab5000,5000);
	Tn_start = getUnixTime();
	Quicksort(tab5000,0,5000,c);
	Tn_stop = getUnixTime();
	czas[4] = Tn_stop - Tn_start;
	
}

void badRandomizeTime(double *czas, int c) { //obliczanie czasu niekorzystnego bubble+quick
	
	int tab100[100], tab500[500], tab1000[1000], tab2500[2500], tab5000[5000];
	double Tn_start, Tn_stop;
	
	badRandomize(tab100,100);
	Tn_start = getUnixTime();
	Quicksort(tab100,0,100,c);
	Tn_stop = getUnixTime();
	czas[0] = Tn_stop - Tn_start;
	
	badRandomize(tab500,500);
	Tn_start = getUnixTime();
	Quicksort(tab500,0,100,c);
	Tn_stop = getUnixTime();
	czas[1] = Tn_stop - Tn_start;
	
	badRandomize(tab1000,1000);
	Tn_start = getUnixTime();
	Quicksort(tab1000,0,1000,c);
	Tn_stop = getUnixTime();
	czas[2] = Tn_stop - Tn_start;
	
	badRandomize(tab2500,2500);
	Tn_start = getUnixTime();
	Quicksort(tab2500,0,2500,c);
	Tn_stop = getUnixTime();
	czas[3] = Tn_stop - Tn_start;
	
	badRandomize(tab5000,5000);
	Tn_start = getUnixTime();
	Quicksort(tab5000,0,5000,c);
	Tn_stop = getUnixTime();
	czas[4] = Tn_stop - Tn_start;
	
}

void randomizeTimeNormal(double *czas) { //obliczanie czasu quick
	int tab100[100], tab500[500], tab1000[1000], tab2500[2500], tab5000[5000];
	double Tn_start, Tn_stop;
	
	Randomize(tab100,100);
	Tn_start = getUnixTime();
	QuicksortNormal(tab100,0,100);
	Tn_stop = getUnixTime();
	czas[0] = Tn_stop - Tn_start;
	
	Randomize(tab500,500);
	Tn_start = getUnixTime();
	QuicksortNormal(tab500,0,100);
	Tn_stop = getUnixTime();
	czas[1] = Tn_stop - Tn_start;
	
	Randomize(tab1000,1000);
	Tn_start = getUnixTime();
	QuicksortNormal(tab1000,0,1000);
	Tn_stop = getUnixTime();
	czas[2] = Tn_stop - Tn_start;
	
	Randomize(tab2500,2500);
	Tn_start = getUnixTime();
	QuicksortNormal(tab2500,0,2500);
	Tn_stop = getUnixTime();
	czas[3] = Tn_stop - Tn_start;
	
	Randomize(tab5000,5000);
	Tn_start = getUnixTime();
	QuicksortNormal(tab5000,0,5000);
	Tn_stop = getUnixTime();
	czas[4] = Tn_stop - Tn_start;
	
}

void badRandomizeTimeNormal(double *czas) { //obliczanie czasu niekorzystnego quick
	int tab100[100], tab500[500], tab1000[1000], tab2500[2500], tab5000[5000];
	double Tn_start, Tn_stop;
	
	badRandomize(tab100,100);
	Tn_start = getUnixTime();
	QuicksortNormal(tab100,0,100);
	Tn_stop = getUnixTime();
	czas[0] = Tn_stop - Tn_start;
	
	badRandomize(tab500,500);
	Tn_start = getUnixTime();
	QuicksortNormal(tab500,0,100);
	Tn_stop = getUnixTime();
	czas[1] = Tn_stop - Tn_start;
	
	badRandomize(tab1000,1000);
	Tn_start = getUnixTime();
	QuicksortNormal(tab1000,0,1000);
	Tn_stop = getUnixTime();
	czas[2] = Tn_stop - Tn_start;
	
	badRandomize(tab2500,2500);
	Tn_start = getUnixTime();
	QuicksortNormal(tab2500,0,2500);
	Tn_stop = getUnixTime();
	czas[3] = Tn_stop - Tn_start;
	
	badRandomize(tab5000,5000);
	Tn_start = getUnixTime();
	QuicksortNormal(tab5000,0,5000);
	Tn_stop = getUnixTime();
	czas[4] = Tn_stop - Tn_start;
	
}

void bubbleSort(int *A, int ile) {
	
	for(int i = 0; i < ile; i++) {
		for(int j = 1; j < ile-i; j++) {
			if(A[j]<A[j-1]) swap(&A[j],&A[j-1]);
		}
		
	}
	
}


int main(int argc, char *argv[]) {
   
   double czas[5]; //tablica na przechowywanie roznicy czasu
   
   int c; //stala do zmodyfikowanego algorytmu
   printf("Podaj wartosc c >= 1\n");
   scanf("%d", &c);
   
//wydruki
   randomizeTime(czas, c);
   printf("\n\n\nQUICKSORT + BUBBLESORT\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
   printf("\nDane pseudolosowe:\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
   printf("    ROZMIAR TABLICY     |    CZAS             x\n");
   printf("          100           | %lf            x\n",czas[0]);
   printf("          500           | %lf            x\n",czas[1]);
   printf("          1000          | %lf            x\n",czas[2]);
   printf("          2500          | %lf            x\n",czas[3]);
   printf("          5000          | %lf            x\n",czas[4]);
   printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
   
   badRandomizeTime(czas, c);
   printf("\n\nDane niekorzystne(n,n-1,...,1,0):\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
   printf("    ROZMIAR TABLICY     |    CZAS             x\n");
   printf("          100           | %lf            x\n",czas[0]);
   printf("          500           | %lf            x\n",czas[1]);
   printf("          1000          | %lf            x\n",czas[2]);
   printf("          2500          | %lf            x\n",czas[3]);
   printf("          5000          | %lf            x\n",czas[4]);
   printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
   
   randomizeTimeNormal(czas);
   printf("QUICKSORT\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
   printf("\nDane pseudolosowe:\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
   printf("    ROZMIAR TABLICY     |    CZAS             x\n");
   printf("          100           | %lf            x\n",czas[0]);
   printf("          500           | %lf            x\n",czas[1]);
   printf("          1000          | %lf            x\n",czas[2]);
   printf("          2500          | %lf            x\n",czas[3]);
   printf("          5000          | %lf            x\n",czas[4]);
   printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
   
   badRandomizeTimeNormal(czas);
   printf("\n\nDane niekorzystne(n,n-1,...,1,0):\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
   printf("    ROZMIAR TABLICY     |    CZAS             x\n");
   printf("          100           | %lf            x\n",czas[0]);
   printf("          500           | %lf            x\n",czas[1]);
   printf("          1000          | %lf            x\n",czas[2]);
   printf("          2500          | %lf            x\n",czas[3]);
   printf("          5000          | %lf            x\n",czas[4]);
   printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
   

}
