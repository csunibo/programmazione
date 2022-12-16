#include <iostream>
#include <cstring>
#include <cstdlib>

struct vacanza
{
    int ngirni;
    float prezzo;
    char tipo[20];
    vacanza *next;
};

typedef vacanza *pvac;

pvac sortInsert(pvac h, pvac node){
    if(h == NULL){ //inserimento in testa
        h = new vacanza;
        h->next = NULL;
        h->ngirni = node->ngirni;
        h->prezzo = node->prezzo;
        strcpy(h->tipo, node->tipo);   
        return h;
    } else { // nodo qualsiasi
        pvac nnode = h->next;
        pvac prec = h;
        bool check = false;
        while (nnode != NULL && (!check))
        {
            if ((node->prezzo/node->ngirni) < (nnode->prezzo/nnode->ngirni))
            {
                prec->next = NULL;
                prec->next = new vacanza;
                prec = prec->next;
                prec->ngirni = node->ngirni;
                prec->prezzo = node->prezzo;
                strcpy(node->tipo ,prec->tipo);
                prec->next = nnode;
                check = true;
            }
            
            prec = nnode;
            nnode = nnode->next;
        }

        if(!check){ // inserimento in coda
                prec->next = NULL;
                prec->next = new vacanza;
                prec = prec->next;
                prec->ngirni = node->ngirni;
                prec->prezzo = node->prezzo;
                strcpy(prec->tipo, node->tipo);
                prec->next = nnode;
                check = true;
        }
        return h;
    }
}

pvac sortxTipo(pvac h, char tipo[]){
    pvac node = h;
    pvac newlist = NULL;
    while (node != NULL)
    {
        if(strcmp(node->tipo, tipo) == 0){
            newlist = sortInsert(newlist, node);
        }
        node = node->next;
    }
    return newlist;
}

void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

void sortDP(int a[], int len){
	int k = 0;
	while(k<len){
		if((a[k]%2 == 0 && k%2 == 1)||(a[k]%2 == 1 && k%2 == 0))
			swap(a[k], a[k+1]);
		else 
			k++;
	}
	for (int i = 0; i < len; i++)
	{
		if(i%2 == 0){
			for (int j = i; j < len; j+=2)
			{
				if(a[j]%2 == 0 && a[j] > a[i]){
					swap(a[j], a[i]);
				}
			}			
		} else {
			for (int j = i; j < len; j+=2)
			{
				if(a[j]%2 == 1 && a[j] < a[i]){
					swap(a[j], a[i]);
				}
			}
		}
	}
}

class Self
{
protected:
    char nome[20]; // "benzina", "disel"
    float litri_benz;
    float litri_disel;
    float litriMax;
public:
    Self(char *str = NULL, float lb = 0.0, float ld = 0.0, float lm = 0.0) {
        strcpy(nome, str);
        this->litri_benz = lb;
        this->litriMax = lm;
        this->litri_disel = ld;
    }

    bool aggiungi_litro(float l, char *str){
        if(strcmp(str, "benzina") == 0){
            if (l+litri_benz <= litriMax){
                litri_benz += l;   
                return true;
            } else {
                std::cout << "stai tentando di inserire troppi litri!\n";
                return false;
            }
            
        } else if(strcmp(str, "disel") == 0){
            if (l+litri_disel <= litriMax){
                litri_disel += l;   
                return true;
            } else{
                std::cout << "stai tentando di inserire troppi litri!\n";
                return false;
            }
        } else {
            return false;
        }
    }

    bool decrementa_litro(float l, char *str){
        if(strcmp(str, "benzina") == 0){
            if (litri_benz-l >= 0) {
                litri_benz -= l;
                return true;   
            } else {
                std::cout << "stai tentando di estrarre troppi litri!\n";
                return false;
            }
        } else if(strcmp(str, "disel") == 0){
            if (litri_disel-l >= 0) {
                litri_disel -= l;   
                return true;
            } else{
                std::cout << "stai tentando di estrarre troppi litri!\n";
                return false;
            }
        }else {
            return false;
        }
    }
};

class Servito: public Self
{
protected:
    float litri_met;
public:
    Servito(char* str, float lb = 0.0, float ld = 0.0, float lm = 0.0, float lmax = 0.0): Self(str, lb, ld, lmax) {
        litri_met = lm;
    }

    bool aggiungi_litri(float l, char *str){
        if(!Self::aggiungi_litro(l, str)){
            if (strcmp(str, "metano"))
            {
                if (litri_met + l <= litriMax)
                {   
                    litri_met += l;
                    return true;
                } else
                    return false;
                
            }else
                return false;
            
        }else
            return true;
    }

    bool decrementa_litri(float l, char *str){
        if(!Self::decrementa_litro(l, str)){
            if (strcmp(str, "metano"))
            {
                if (litri_met - l >= 0)
                {   
                    litri_met -= l;
                    return true;
                } else
                    return false;
                
            }else
                return false;
            
        }else
            return true;
    }
};

int main(){
    int n = 8;
	int a[] = {8,5,2,3,4,6,9,7};
	sortDP(a, n);
	for (int i = 0; i < n; i++)
	{
		std::cout << "a["<< i << "]:" << a[i] << "\n";
	}

    pvac h = NULL;
    vacanza newNode = (vacanza){5, 90.0, {"montagna"}, NULL};
    h = sortInsert(h, &newNode);
    newNode = (vacanza){3, 150.0, {"montagna"}, NULL};
    h = sortInsert(h, &newNode);
    newNode = (vacanza){7, 2000.0, {"montagna"}, NULL};
    h = sortInsert(h, &newNode);
    newNode = (vacanza){7, 90.0, {"mare"}, NULL};
    h = sortInsert(h, &newNode);
    newNode = (vacanza){9, 2000.0, {"citta"}, NULL};
    h = sortInsert(h, &newNode);

    pvac node = h;
    while (node != NULL)
    {
        std::cout << "node:{" << node->ngirni << "gg[" << node->prezzo << "€]-" << node->tipo << "\n";
        node = node->next;
    }
    delete(node);
    node = nullptr;

    pvac h2 = new vacanza;
    char tipo[] = {"montagna"};
    h2 = sortxTipo(h, tipo);
    node = h2;
    while (node != NULL)
    {
        std::cout << "node:{" << node->ngirni << "gg[" << node->prezzo << "€]-" << node->tipo << "\n";
        node = node->next;
    }

    Self Riempo("benzina", 50.0, 0, 80);
    std::cout << "Self- andato a buon fine?" << Riempo.aggiungi_litro(31.0, "benzina") << "\n";
    std::cout << "Self- andato a buon fine?" << Riempo.aggiungi_litro(30.0, "benzina") << "\n";

    
    return 0;
}