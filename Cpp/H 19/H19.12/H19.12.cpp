/* Definire una funzione che prende in input un array di stringhe, un
array di caratteri, ed uno short w. La funzione restituisce il numero
di stringhe del primo array che contengono almeno w dei caratteri
presenti nel secondo array.

NB: Si assuma che i caratteri presenti nel secondo array siano
distinti. */

#include <iostream>
#include <string>

using namespace std;

int func (string *str, char *fan, short int w, int n, int m){
	int count=0, countstr=0;
	
	
	for(int j=0; j<n; j++){
		cout<<"Inserisci una stringa : "<<endl;
		cin>>str[j];
	}
	
	for(int i=0; i<m; i++){
	cout<<"Inserisci un carattere : "<<endl;
	cin>>fan[i];
	}
	
		for(int j=0; j<n; j++){  //scorro le STRINGHE
            for(int k=0; k<str[j].length(); k++){
            	for(int i=0; i<m; i++){
				
//            	cout<<"str[j] [k]"<<str[j] [k]<<endl;

            	if(str[k] [j] == fan[i]){
            	count++;  //numero di caratteri presenti in una stringa
//            	cout<<"count : "<<count<<endl;
            	
            	if(count >= w){  //se il numero di caratteri è almeno w
				   count=0;  
                   countstr ++;
//                 cout<<"countstr : "<<countstr<<endl;
                return countstr; 
			       }
            
				}
			}
			
		}
		 
	}	
}

int main(){
	
	int n,m;
	short int w;
	
	cout<<"Numero di stringhe : "<<endl;
	cin>>n;
	cout<<"Numero di caratteri : "<<endl;
	cin>>m;
	cout<<"Inserisci w : "<<endl;
	cin>>w;
	
	string str[n];
	char fan[m];
	
	int ris=func(str, fan, w, n, m);
	cout<<"Il numero di stringhe che contengono "<<w<<" caratteri e' : "<<ris<<endl;
	return 0;
}