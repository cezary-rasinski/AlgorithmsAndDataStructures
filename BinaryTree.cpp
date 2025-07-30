
/*Wejście
W pierwszej linii wejścia znajduje się liczba naturalna n - ilość podróży w czasie. Następnie ze standardowego wejścia pobrane zostanie n linii , 
składających się z trzech liczb naturalnych: y - rok, do którego przybyła załoga oraz f - zasłyszana częstotliwość w Hz oraz l - zmierzona długość fali w cm.
Gdy wszystkie zanotowane częstotliwośći będą oscylować w granicach (300 +/- 25)Hz silnik można uznać za dotarty.

1 ≤ n ≤ 300 000
1 ≤ y ≤ 10 000
1 ≤ f ≤ 100 000
1 ≤ l ≤ 5 000

Wyjście
Na wyjściu powinniśmy otrzymać tyle linii, ile unikatowych dat pojawiło się w danych wejściowych, 
dla których dokonano prawidłowych pomiarów. Daty te powinny zostać posortowane rosnąco. Każda linia powinna zawierać zasłyszane w danym roku częstotliwości i długości fal:
[rok]: (f1,l1), (f2,l2), (f3,l3)...
Posortuj pary (fi,li) w porządku rosnącej częstotliwości. Jeżeli znajdą się dwie pary o jednakowej częstotliwości, to jako pierwszą wyświetl tę parę, która ma mniejszą długość fali.
W ostatniej linii wyjścia umieść dodatkową informację o tym czy silnik został dotarty TAK/NIE.
Odrzuć wszystkie pomiary spoza zakresu 20 - 20 000 Hz oraz takie których nie da się otrzymać w temperaturze -30 - 30 stopni Celsjusza.

UWAGA! W zadaniu nie można używać bibliotek STL. Należy wykorzystać samodzielnie napisaną implementację drzewa binarnego.
Przykład:

Wejście:
16
5029 10 2789
7819 45043 23
1993 30 1080
2789 29 1090
2222 302 107
834 299 108
67 34 100
123 390 12888
728 300 108
1073 302 107
2222 302 107
834 109 300
1993 300 108
234 3000 11
2222 150 214
834 299 109
	
Wyjście:
234: (3000,11)
728: (300,108)
834: (109,300) (299,108) (299,109)
1073: (302,107)
1993: (30,1080) (300,108)
2222: (150,214) (302,107) (302,107)
2789: (29,1090)
NIE

*/

#include <iostream>

using namespace std;

struct Node {
    int year;
    int Hz;
    int cm;
    long dupes;

    Node* left;
    Node* right;

    Node (int y, int f, int l){
        year = y;
        Hz = f;
        cm = l;
        dupes = 0;
        left = right = nullptr;
    }
};

Node* insert(Node* node, int y, int Hz, int cm);
void order_out(Node* node, int& a, string& out);
void yes_or_no (bool t);

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int travels, year;
    bool dotarty = false;
    int count = 0;
    int Hz, cm;
    string out = "";
    cin >> travels;
    
    Node* root = nullptr;

    for (int i = 0; i < travels; i++){
        cin >> year >> Hz >> cm;
        if (Hz >= 20 && Hz <= 20000){
            if (Hz*cm < 31300 || Hz*cm > 35000){
                continue;
            } else {
                if (Hz >= 275 || Hz <= 325){
                    dotarty = true;
                } 
                if (Hz < 275 || Hz > 325){
                    count = 1;
                }
                root = insert(root, year, Hz, cm);
            }
        }
        continue;
    }
    int a;
    if (count == 1){
        dotarty = false;
    }
    order_out(root, a, out);
    cout << out;
    yes_or_no(dotarty);

}

Node* insert(Node* node, int y, int Hz, int cm) {

    if (node == nullptr){

        return new Node(y, Hz, cm);
    }

    if (node->year == y && node->Hz == Hz && node->cm > cm || node->year == y && node->Hz > Hz ||  node->year > y) {
         node->left = insert(node->left, y, Hz, cm);
    } else if (node->year == y && node->Hz == Hz && node->cm == cm){
         node->dupes += 1;
    } else {    
        node->right = insert(node->right, y, Hz, cm);
    }
    
    return node;
}

void order_out(Node* node, int& a, string& out) {
    if (node != nullptr) {

        order_out(node->left, a, out);
        if (a == node->year){
            out += ( " (" + to_string(node->Hz) + "," + to_string(node->cm) + ")" );
            if (node->dupes > 0) {
                for (long i = 0; i < node->dupes; i++){
                out += ( " (" + to_string(node->Hz) + "," + to_string(node->cm) + ")" );
                }  
            }
        } else {
            out += "\n";
            out += (to_string(node->year) + ": (" + to_string(node->Hz) + "," + to_string(node->cm) + ")");
            for (long i = 0; i < node->dupes; i++){
                out += ( " (" + to_string(node->Hz) + "," + to_string(node->cm) + ")" );
            }  
             
        }
        a = node->year;
        order_out(node->right, a, out);
    }
    return;
}

void yes_or_no (bool t){
    if (t){
        cout << "\n" << "TAK";
    } else {
        cout << "\n" << "NIE";
    }
}