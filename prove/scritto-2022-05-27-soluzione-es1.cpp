// NOTA: LE REGION MARCATE DEBUG SONO PER 
// TESTARE IL CODICE NON SONO NECESSARIE NEL COMPITO
// REGION DEBUG 
#include <bits/stdc++.h>
using namespace std; 

struct nodo {
    int val;
    int next;
};

void swap(int *p, int *d) {
    int tmp = *p; 
    *p = *d; 
    *d = tmp; 
}
// ENDREGION DEBUG

// REGION ESERCIZIO 1

int i_revert(nodo arr[], int lun, bool *noswap, int j=0) {
  if(arr[j].next == -1) {
    swap(&arr[0].val, &arr[j].val);
    return arr[0].next;
  } else {
    int index = i_revert(arr, lun, noswap, arr[j].next);
    if(arr[j].next == index || index == j) *noswap = true;
    if(!(*noswap)) {
      swap(&arr[j].val, &arr[index].val);
      return arr[index].next;
    }
    return 0;
  }
}

// La funzione da chiamare è revert, che internamente chiama la funzione ricorsiva i_revert
void revert(nodo arr[], int lun) {
  bool swap = false;
  i_revert(arr, lun, &swap);
}

// REGION DEBUG 
ostream &operator <<(ostream &out, nodo n) {
    out << "(" << n.val << ", " << n.next << ") ";
    return out; 
}

int main() {
    nodo test_arr[] = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, -1}
    };
    for (auto &i : test_arr) cout << i;
    cout << endl; 

    revert(test_arr, 4);

    for (auto &i : test_arr) cout << i;
    cout << endl; 

    // TODO: se ti va fai altri test
}
// ENDREGION DEBUG 
