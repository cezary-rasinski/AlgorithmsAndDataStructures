/*
Wejście:
Pierwsza linia: liczba naturalna n – liczba przedsiębiorców (n ≥ 1).  
Następnie dla każdego przedsiębiorcy:
– liczba operacji o (o ≥ 0),  
– o kolejnych linii, każda w jednej z form:
    a p t   – dodaj nowy produkt o cenie p (w zł) i stawce podatku t%,
    p x     – zmień cenę najdroższego produktu o x (jeżeli nie ma produktów, operację pomiń).

Opis zadania:
Dla każdego przedsiębiorcy trzeba zebrać wszystkie jego produkty i – korzystając ze wszystkich dostępnych stawek podatkowych – przydzielić je do produktów tak, aby suma podatku była jak najmniejsza.  
- Jeśli jest M produktów, jest też M stawek (z operacji dodawania).  
- Przy obliczeniach wykorzystujemy dokładnie te M wartości cen i M wartości stawek, każdą dokładnie raz.  
- Na końcu obliczamy sumę (p_i × t_j / 100) po skojarzeniu cen p_i z stawkami t_j w najlepszy (minimalizujący podatek) sposób.

Oblicz i wypisz, dla każdego z n przedsiębiorców, minimalną możliwą wartość podatku (w groszach).

Uwaga: rozwiązanie musi używać własnej implementacji kopca do dynamicznego śledzenia najdroższego produktu.

Wyjście:
n linii – w każdej minimalna suma podatku dla danego przedsiębiorcy, wyrażona w groszach (całkowita liczba).

Przykład:
Wejście:
2
10
a 1000 20
a 1200 10
a 900 5
a 1500 30
p 100
a 3000 40
p -200
p -100
a 20 20
a 30 4
8
a 970 20
a 1800 10
a 1900 5
a 150 30
a 2000 40
p -200
a 50 10
a 9000 4

Wyjście:
70500
107400
*/
#include <iostream>
#include <vector>
using namespace std;

class heapStruct{
private:
    vector<int> price;
    vector<int> tax;

    void price_placement(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (price[index] > price[parent]) {
                swap(price[index], price[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }
    void tax_placement(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (tax[index] < tax[parent]) {
                swap(tax[index], tax[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }
public:
    void insert_price(int val){
        price.push_back(val);
        price_placement(price.size() -1);
    }
    void insert_tax(int val) {
        tax.push_back(val);
        tax_placement(tax.size() -1);
    }
    void change_max_price(int val) {
        if (price.empty() || price[0] + val < 0) {
            return;
        }
        price[0] += val;

        int lastIndex = price.size() - 1;
        swap(price[0], price[lastIndex]);

        int old_top = price.back();
        price.pop_back();

        int index = 0;
        int size = price.size();

        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && price[leftChild] > price[largest]) {
                largest = leftChild;
            }
            if (rightChild < size && price[rightChild] > price[largest]) {
                largest = rightChild;
            }
            if (largest == index) {
                break;
            }

            swap(price[index], price[largest]);
            index = largest;
        }
        insert_price(old_top);
    }   
    int getSize(){
        return price.size();
    }
    int getTax(int n){
        return tax[n];
    }
    int getPrice(int n){
        return price[n];
    }
    void pop_price(){
        if (!price.empty()){

            int lastIndex = price.size() - 1;
            swap(price[0], price[lastIndex]);
            price.pop_back();
            
            int index = 0;
            int size = price.size();

            while (true) {
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;
                int largest = index;

                if (leftChild < size && price[leftChild] > price[largest]) {
                    largest = leftChild;
                }
                if (rightChild < size && price[rightChild] > price[largest]) {
                    largest = rightChild;
                }
                if (largest == index) {
                    break;
                }

                swap(price[index], price[largest]);
                index = largest;
            }
        }
    }
    void pop_tax(){
        if (!price.empty()){
            int lastIndex = tax.size() - 1;
            swap(tax[0], tax[lastIndex]);
            tax.pop_back();
            
            int index = 0;
            int size = tax.size();

            while (true) {
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;
                int largest = index;

                if (leftChild < size && tax[leftChild] < tax[largest]) {
                    largest = leftChild;
                }
                if (rightChild < size && tax[rightChild] < tax[largest]) {
                    largest = rightChild;
                }
                if (largest == index) {
                    break;
                }

                swap(tax[index], tax[largest]);
                index = largest;
            }
        }

    }
};
int main(){
    int n, o;
    int p, t, x;
    int sum;
    char letter;
    cin >> n;

    for (int i = 0; i < n; i++){
        
        heapStruct heap;
        sum = 0;
        
        cin >> o;
        for (int j = 0; j < o; j++){
            cin >> letter;
            if (letter == 'a'){
                cin >> p;
                heap.insert_price(p);
                cin >> t;
                heap.insert_tax(t);

            }
            if (letter == 'p'){
                cin >> x;
                heap.change_max_price(x);
            }

        }
        int v = heap.getSize();


        for (int i = 0; i < v; i++){
            sum += heap.getPrice(0)* heap.getTax(0);
            heap.pop_tax();
            heap.pop_price();
            
        }
        cout << sum << endl;
    }
}