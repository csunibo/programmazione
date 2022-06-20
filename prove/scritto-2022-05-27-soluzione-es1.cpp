// La funzione da chiamare è revert, che internamente chiama la funzione ricorsiva i_revert

void revert(nodo arr[], int lun) {
  bool swap = false;
  revert_i(arr, lun, &swap);
}

int i_revert(nodo arr[], int lun, bool * noswap, int j=0) {
  if(arr[j].next == -1) {
    swap(&arr[0].val, &arr[j].val);
    return arr[0].next;
  } else {
    int index = i_revert(arr, lun, noswap, arr[j].next);
    if(j == arr[index].next || index == j) *noswap = true;
    if(!(*noswap)) {
      swap(&arr[j].val, &arr[index].val);
      return arr[index].next;
    }
    return 0;
  }
}