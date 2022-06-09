#include <iostream>
#include <math.h>

using namespace std;

#define N 25

// Esercizio 1
void removeOdds4(int n){ // iterativa
	for(int i=0; i<n; i++){
		if(i%2==0 && i%4!=0){
			cout << i << " ";
		}
	}
}

void removeOdds4ric(int n){ // ricorsiva
	if(n>1){
		if((n-1)%2==0 && (n-1)%4!=0){
			cout << n-1 << " ";
		}
		removeOdds4ric(n-1);
	}
}

// Esercizio 2
struct lista_di_studenti{
	char nome[N];
	char cognome[N];
	int matricola;
	lista_di_studenti *next;
};

typedef lista_di_studenti *lista;

// funzione ausiliaria per test
lista addElement(lista p, char n[N], char c[N], int nm){
	lista tmp = p;
	if(p==NULL){
		p = new lista_di_studenti;
		strcpy(p->nome,n);
		strcpy(p->cognome,c);
		p->matricola = nm;
		p->next = NULL;
	}
	else{
		while(tmp->next!=NULL){
			tmp = tmp->next;
		}
		tmp->next = new lista_di_studenti;
		tmp = tmp->next;
		strcpy(tmp->nome,n);
		strcpy(tmp->cognome,c);
		tmp->matricola = nm;
		tmp->next = NULL;
	}
	return p;
}

// funzione ausiliaria per test
void printList(lista p){
	while(p!=NULL){
		cout << p->nome << " " << p->cognome << " " << p->matricola << endl;
		p = p->next;
	}
}

lista removeOdds(lista p){ // versione iterativa
	lista aux = p, prec = NULL;
	while(aux!=NULL){
		if(aux->matricola%2!=0 || aux->matricola%4 == 0){
			if(prec == NULL){
				p = aux->next;
			}
			else{
				prec->next = aux->next;
			}
			lista aux2 = aux;
			aux = aux->next;
			delete(aux2);

		}
		else{
			prec = aux;
			aux = aux->next;

		}
	}
	return p;
}

lista removeOddsRec(lista p){ // versione ricorsiva
	if (p == NULL) return(p) ;
	else if (p->matricola%2!=0 || p->matricola%4==0) return(removeOddsRec(p->next)) ;
	else {
		p->next = removeOddsRec(p->next) ;
		return(p) ;
	}
}

// Esercizio 3
class segmento{
protected:
	float x1, y1, x2, y2;
public:
	segmento(float px1, float py1, float px2, float py2){
		if(px1>=0 && py1>=0 && px2>=0 && py2>=0){
			x1 = px1;
			x2 = px2;
			y1 = py1;
			y2 = py2;
		}
		else{
			x1 = 0;
			x2 = 0;
			y1 = 0;
			y2 = 0;
			cout << "Errore: le coordinate devono essere maggiori di zero" << endl;
		}
	}
	float lunghezza(){
		return  sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	}
};

class segmenti_adiacenti:public segmento{
protected:
	float x3, y3;
public:
	segmenti_adiacenti(float px1, float py1, float px2, float py2, float px3, float py3):segmento(px1,py1,px2,py2){
		if(px1>=0 && py1>=0 && px2>=0 && py2>=0 && px3>=0 && py3>=0){
			x3 = px3;
			y3 = py3;
		}
		else{
			x3 = 0;
			y3 = 0;
			cout << "Errore: le coordinate devono essere maggiori di zero" << endl;
		}
	}

	float lunghezza_primo(){
		return segmento::lunghezza();
	}

	float lunghezza_secondo(){
		return sqrt(pow(x2-x3,2)+pow(y2-y3,2));
	}

	float lunghezza(){
		return lunghezza_primo()+lunghezza_secondo();
	}
};



int main() {

	cout << "Esercizio 1:" << endl;
	removeOdds4(50);

	removeOdds4ric(50);
	cout << endl;
	cout << "########################" << endl;

	cout << "Esercizio 2:" << endl;
	lista p = NULL;
	p = addElement(p,"Antonio","Rossi",4);
	p = addElement(p,"Andrea","Ferrari",58);
	p = addElement(p,"Giulia","Bianchi",23);
	p = addElement(p,"Chiara","Ricci",15);
	p = addElement(p,"Lorenzo","Mancini",14);
	cout << "========Lista iniziale:========" << endl;
	printList(p);
	lista q = NULL;
	q = p;
	//printList(q);
	cout << "========Lista con elementi rimossi - versione ricorsiva :========" << endl;
	q = removeOddsRec(q);
	printList(q);
	cout << "========Lista con elementi rimossi - versione iterativa:========" << endl;
	p = removeOdds(p);
	printList(p);

	cout << "########################" << endl;

	cout << "Esercizio 3:" << endl;
	segmento s = segmento(1,3,6,9);
	cout << s.lunghezza() << endl;
	segmenti_adiacenti sa = segmenti_adiacenti(1,3,6,9,12,1);
	cout << sa.lunghezza() << endl;
	cout << sa.lunghezza_primo() << endl;
	cout << sa.lunghezza_secondo() << endl;
	return 0;
}
