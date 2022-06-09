#include <iostream>
#include <math.h>
#include <string.h>
#include <cstdlib>


using namespace std;

#define N 40

// Esercizio 1
void strcat2(char dest[], char src[]){
	int i=0,j=0;
	while(dest[i]!='\0')
		i++;
	while(src[j]!='\0'){
		dest[i]=src[j];
		j++;
		i++;
	}
}

// Esercizio 2
struct nodo{
	char corso[N];
	char docente[N];
	char corsoDiLaurea[N];
	int crediti;
};

struct lista{
	nodo *esame;
	lista *next;
};

typedef lista *ptr_lista;
typedef nodo *ptr_nodo;

ptr_lista addExam(ptr_lista p, ptr_nodo exam){
	ptr_lista tmp = p;
	if(p==NULL){
		p = new lista;
		p->esame = exam;
		p->next = NULL;
	}
	else{
		while(tmp->next!=NULL){
			tmp = tmp->next;
		}
		tmp->next = new lista;
		tmp = tmp->next;
		tmp->esame = exam;
		tmp->next = NULL;
	}
	delete(tmp);
	return p;
}

int totalCredits(ptr_lista p,char name[N]){
	int tot = 0;
	while(p!=NULL){
		if(strcmp(p->esame->docente,name)==0){
			tot+=p->esame->crediti;
		}
		p=p->next;
	}
	return tot;
}

void printList(ptr_lista p){
	while(p!=NULL){
		cout << p->esame->corso << " " << p->esame->docente << " " << p->esame->corsoDiLaurea << " " << p->esame->crediti << endl;
		p = p->next;
	}
}

// Esercizio 2 con struttura alternativa
struct listaEsami{
	char corso[40];
	char docente[40];
	char corsoDiLaurea[40];
	int crediti;
	listaEsami *next;
};

typedef listaEsami *ptr_listaEsami;

ptr_listaEsami addExam2(ptr_listaEsami p, char nomeCorso[], char nomeDocente[], char nomeCDL[], int cfu){
	ptr_listaEsami tmp = p;
	if(p==NULL){
		p = new listaEsami;
		strcpy(p->corso,nomeCorso);
		strcpy(p->docente,nomeDocente);
		strcpy(p->corsoDiLaurea,nomeCDL);
		p->crediti = cfu;
		p->next = NULL;
	}
	else{
		while(tmp->next!=NULL){
			tmp = tmp->next;
		}
		tmp->next = new listaEsami;
		tmp = tmp->next;
		strcpy(tmp->corso,nomeCorso);
		strcpy(tmp->docente,nomeDocente);
		strcpy(tmp->corsoDiLaurea,nomeCDL);
		tmp->crediti = cfu;
		tmp->next = NULL;
	}
	return p;
}

int totalCredits2(ptr_listaEsami p,char name[40]){
	int tot = 0;
	while(p!=NULL){
		if(strcmp(p->docente,name)==0){
			tot+=p->crediti;
		}
		p=p->next;
	}
	return tot;
}

void printList2(ptr_listaEsami p){
	while(p!=NULL){
		cout << p->corso << " " << p->docente << " " << p->corsoDiLaurea << " " << p->crediti << endl;
		p = p->next;
	}
}

// Esercizio 3
class rainMeter{
protected:
	int pioggiaTotale;
	int giorni;
public:
	rainMeter(){
		pioggiaTotale = 0;
		giorni = 0;
	}

	void reset(){
		pioggiaTotale = 0;
		giorni = 0;
	}

	void dayEnd(){
		giorni++;
	}

	void rain(int n){
		pioggiaTotale+=n;
	}

	double average(){
		if(giorni==0){
			return pioggiaTotale;
		}
		return double(pioggiaTotale)/giorni;
	}
};

int main(){
	cout << " ##### Esercizio 1 ####" << endl;
	char dest[40] = "Adele ", src[20] = "Veschetti";
	strcat2(dest,src);
	cout << dest << endl;

	cout << " ##### Esercizio 2 ####" << endl;
	ptr_lista p = new lista;
	p = NULL;
	ptr_nodo e1 = new nodo;
	strcpy(e1->corso,"Analisi Matematica");
	strcpy(e1->docente,"Mughetti");
	strcpy(e1->corsoDiLaurea,"Informatica");
	e1->crediti = 12;
	ptr_nodo e2 = new nodo;
	strcpy(e2->corso,"Programmazione");
	strcpy(e2->docente,"Laneve");
	strcpy(e2->corsoDiLaurea,"Informatica");
	e2->crediti = 12;
	ptr_nodo e3 = new nodo;
	strcpy(e3->corso,"Compilatori e Interpreti");
	strcpy(e3->docente,"Laneve");
	strcpy(e3->corsoDiLaurea,"Informatica Magistrale");
	e3->crediti = 6;
	p = addExam(p,e1);
	p = addExam(p,e2);
	p = addExam(p,e3);
	printList(p);
	cout << "Crediti totali: " << totalCredits(p,"Laneve") << endl;
	ptr_listaEsami q = new listaEsami;
	q = NULL;
	q = addExam2(q,"Analisi Matematica", "Mughetti", "Informatica",12);
	q = addExam2(q,"Programmazione", "Laneve", "Informatica",12);
	q = addExam2(q,"Compilatori e Interpreti", "Laneve", "Informatica Magistrale",6);
	printList2(q);
	cout << "Crediti totali: " << totalCredits2(q,"Laneve") << endl;

	cout << " ##### Esercizio 3 ####" << endl;
	rainMeter rm = rainMeter();
	cout << rm.average() << endl;
	for(int i = 0; i<30; i++){
		int tmp = rand()%60+1;
		rm.rain(tmp);
		cout << "Oggi ha piovuto " << tmp << " millimetri di pioggia." << endl;
		rm.dayEnd();
	}

	cout << rm.average() << endl;

	return 0;
}
