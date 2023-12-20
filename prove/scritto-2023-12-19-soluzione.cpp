#include <iostream>
#include <cstring>

using namespace std;

// ~Raffo



// es. 1
// 1.a
struct nodo {
    int val;
    int left;
    int right;
};

// 1.b
int somma(nodo A[], int index = 0) {
    int tot = A[index].val;
    if ( A[index].left != -1 )
        tot += somma(A, A[index].left);
    if ( A[index].right != -1 )
        tot += somma(A, A[index].right);
    return tot;
}

// 1.c
void all_odd(nodo A[], int index = 0) {
    if ( A[index].val % 2 == 0 )
        A[index].val++;
    if ( A[index].left != -1 )
        all_odd(A, A[index].left);
    if ( A[index].right != -1 )
        all_odd(A, A[index].right);
}


// es. 2
#define MAX 20

struct esame {
    char nome[MAX];
    int cfu;
    int voto;
    esame* next;
};

// 2.a
esame* rifiuta_esame(esame* head, int cfu) {
    esame* now = head, * prev = NULL;
    while ( now != NULL ) {
        if ( now -> cfu == cfu ) {
            if ( prev == NULL ) {
                head = head -> next;
                delete now;
                now = head;
            } else {
                prev -> next = now -> next;
                delete now;
                now = prev -> next;
            }
        } else {
            prev = now;
            now = now -> next;
        }
    }
    return head;
}

// 2.b
// PRECONDIZIONE: lunghezza di dest[] = MAX;
void min_esame(esame* head, char dest[]) {
    esame* min = NULL, * now = head;
    if ( now != NULL ) {
        min = now;
        now = now -> next;
        while ( now != NULL ) {
            if ( now -> voto < min -> voto )
                min = now;
            now = now -> next;
        }
        strcpy(dest, min -> nome);
    } else {
        strcpy(dest, "NULL");
    }
}

// 2.c
float media(esame* head) {
    int cfut = 0, tot = 0;
    esame* now = head;
    while ( now != NULL ) {
        tot += now -> voto * now -> cfu;
        cfut += now -> cfu;
        now = now -> next;
    }
    if ( cfut != 0 ) {
        return tot / cfut;
    } else {
        return 0;
    }
}


// es. 3
// 3.a
#define N 20

struct camera {
    int id;
    int letti;
    bool disp; // true se la camera è disponibile
};

// 3.b
class Albergo {
protected:
    camera c[N];
public:
    Albergo(camera camere[]) {
        // Visto che la traccia parla di semplificazione, in cui un albergo ha N stanze, non ho fatto i controlli e ho
        // dato per scontato che l'array che viene passato (camere[]) inizializzi tutte le stanze e sia di lunghezza N.
        for ( int i = 0; i < N; i++ ) {
            c[i].id = camere[i].id;
            c[i].letti = camere[i].letti;
            c[i].disp = camere[i].disp;
        }
    }

    int prenota(int n_letti) { // return -1 se non è stata trovata
        bool found = false;
        int id_stanza;
        for ( int i = 0; i < N && !found; i++ ) {
            if ( c[i].disp && c[i].letti == n_letti ) {
                id_stanza = c[i].id;
                c[i].disp = false;
                found = true;
            }
        }
        if ( found )
            return id_stanza;
        else
            return -1;
    }
};

// 3.c
#define M 30

struct ombrellone {
    int id;
    bool disp; // true se l'ombrellone è disponibile
};

class AlbergoConSpiaggia: public Albergo {
protected:
    ombrellone o[M];
public:
    AlbergoConSpiaggia(camera camere[], ombrellone ombrelloni[]): Albergo(camere) {
        // Stessa semplificazione di Albergo qui, senza neanche i controlli per M > N, poiché previsto dalla traccia
        for ( int i = 0; i < M; i++ ) {
            o[i].id = ombrelloni[i].id;
            o[i].disp = ombrelloni[i].disp;
        }
    }

    int prenota(int n_letti) { // return -1 se non è stata trovata una stanza libera
       int id_stanza = Albergo::prenota(n_letti);
       if ( id_stanza != -1 ) {
           bool found = false;
           for ( int i = 0; i < M && !found; i++ ) {
               if ( o[i].disp ) {
                   o[i].disp = false;
                   found = true;
               }
           }
       }
       return id_stanza;
    }

    int prenota_ombrellone() { // return id dell'ombrellone, -1 se non è riuscito a prenotarlo
        int id_ombrellone;
        int c_libere = 0, o_liberi = 0;
        for ( int i = 0; i < N; i++ ) {
            if ( c[i].disp )
                c_libere++;
        }
        for ( int i = 0; i < N; i++ ) {
            if ( o[i].disp )
                o_liberi++;
        }
        if ( o_liberi > c_libere ) {
            bool found = false;
            for ( int i = 0; i < M && !found; i++ ) {
                if ( o[i].disp ) {
                    o[i].disp = false;
                    id_ombrellone = o[i].id;
                    found = true;
                }
            }
            return id_ombrellone;
        } else {
            return -1;
        }
    }
};



int main() {
    cout << "Ao!";
    return 0;
}
