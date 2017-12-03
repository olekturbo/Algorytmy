#include <stdio.h>
#include <stdlib.h>

typedef struct Lista {
	char *slowo;
	struct Lista *nastepny;

} lista;

lista *L1 = NULL;
lista *L2 = NULL;
lista *L3 = NULL;

void wstaw(char *s, lista **L) {
	lista* nowy = (lista*)malloc(sizeof(lista));
	nowy->slowo = s;
	nowy->nastepny = *L;
	*L = nowy;
}

void drukuj(lista *wezel) {
	while(wezel != NULL) {
		printf("%s ",wezel->slowo);
		wezel = wezel->nastepny;
	}
	printf("\n");
}

void drukuj_szukaj(lista *wezel) {
	if(wezel != NULL)
		printf("Znalazlem %s ",wezel->slowo);
	else{
		printf("Nie znalazlem!");
	}
	printf("\n");
  }


lista *szukaj(char *s, lista *wezel) {
	while (wezel != NULL) {
    if (wezel->slowo == s) {
      return wezel;
    }
    wezel = wezel->nastepny;
  }
  return NULL;
}

void usun(char *s, lista **L) {

	while(*L != NULL)
   {
      if((*L)->slowo == s)
      {
         lista *help = *L;
         *L = (*L)->nastepny;
         free(help);
      }
      else
      {
         L = &((*L)->nastepny);
      }
   }
}

void kasuj(lista** L) {
  lista* tmp;

  while (*L != NULL) {
    tmp = *L;
    *L = (*L)->nastepny;
    if (tmp->slowo)
      free(tmp);
  }
}

void bezpowtorzen(lista* L) {
  lista *wezel1, *wezel2, *tmp;
  wezel1 = L;
  while (wezel1 != NULL && wezel1->nastepny != NULL) {
    wezel2 = wezel1;
    while (wezel2->nastepny != NULL) {
      if (wezel1->slowo == wezel2->nastepny->slowo) {
        tmp = wezel2->nastepny;
        wezel2->nastepny = wezel2->nastepny->nastepny;
        free(tmp);
      } else {
      wezel2 = wezel2->nastepny;
      }
    }
    wezel1 = wezel1->nastepny;
  }
}

void scal(lista** lista1, lista** lista2) {
  lista* tmp = (lista*)malloc(sizeof(lista));
  tmp = *lista2;
  while(tmp != NULL) {
    wstaw(tmp->slowo, &L3);
    tmp = tmp->nastepny;
  }
  tmp = *lista1;
  while (tmp != NULL) {
    wstaw(tmp->slowo, &L3);
    tmp = tmp->nastepny;
  }
  *lista1 = NULL;
  *lista2 = NULL;
}

int main() {
	// wstawianie
	wstaw("sowa",&L1);
	wstaw("sowa", &L1);
	wstaw("niedzwiedz",&L1);
	wstaw("lew",&L1);
	wstaw("pies",&L1);
	wstaw("kruk",&L1);

	wstaw("komputer",&L2);
	wstaw("drukarka", &L2);
	wstaw("mikrofon", &L2);
	wstaw("sluchawki", &L2);
	wstaw("monitor", &L2);

	//drukowanie
	printf("L1: "); drukuj(L1);
	printf("L2: "); drukuj(L2);

	//szukanie
	lista* znajdz;
	znajdz = szukaj("lew",L1);
	printf("Szukam lwa w L1: "); drukuj_szukaj(znajdz);
	znajdz = szukaj("monitor",L2);
	printf("Szukam monitora w L2: "); drukuj_szukaj(znajdz);
	znajdz = szukaj("gazeta",L2);
	printf("Szukam gazety w L2: "); drukuj_szukaj(znajdz);

	//usuwanie
	printf("Usuwam kruka z L1\n"); usun("kruk", &L1);
	printf("Usuwam monitor z L2\n"); usun("monitor", &L2);

	//drukowanie
	printf("L1: "); drukuj(L1);
	printf("L2: "); drukuj(L2);

	//kasowanie
	printf("Kasuje cala liste L2\n"); kasuj(&L2);

	//drukowanie
	printf("L1: "); drukuj(L1);
	printf("L2: "); drukuj(L2);

	//bez powtorzen
	printf("Lista L1 bez powtorzen: "); bezpowtorzen(L1); drukuj(L1);

	//wstawianie do listy 2
	printf("Wstawiam ponownie do listy 2!\n");
	wstaw("komputer",&L2);
	wstaw("drukarka", &L2);
	wstaw("mikrofon", &L2);
	wstaw("sluchawki", &L2);
	wstaw("monitor", &L2);

	//drukowanie
	printf("Drukowanie obecnych list:\n");
	printf("L1: "); drukuj(L1);
	printf("L2: "); drukuj(L2);

	//scalanie
	printf("Scalam L1 i L2 do L3...\n");
	scal(&L1,&L2);

	//drukowanie
	printf("L3: "); drukuj(L3);





}
