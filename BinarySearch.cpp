/*
Wejście:
Na wejściu program otrzymuje liczbę naturalną T – liczbę testów. 
Dla każdego testu dostępne są dwie funkcje:
    int time_jump(unsigned int t);
    // skacze o t zdarzeń w przód (cyklicznie) i zwraca znacznik czasowy nowego wydarzenia
    void next_test();
    // ładuje kolejny zestaw danych (po ostatnim – zaczyna od pierwszego)

Opis zadania:
Ukryty jest cykl N zdarzeń e₁ < e₂ < … < e_N (N i pozycja startowa są nieznane).  
Funkcja time_jump(t) pozwala przemieścić się o t kroków w przód po tym cyklu (z zapętleniem).  
Twoim zadaniem jest dla każdego testu wyznaczyć długość cyklu N.

Ograniczenia:
1 ≤ T ≤ 100 000  
1 ≤ N ≤ 10^9  
–10^9 ≤ e_i ≤ 10^9  

Wyjście:
Wypisz T liczb – długości kolejnych cykli – oddzielone pojedynczymi spacjami.

Przykład:
Wejście:
2

Ukryte cykle:
cykl 1: {-1300, -893, -86, 4, 6, 79, 102, 745, 1945, 2345}
cykl 2: {-101, -100, 17, 1900, 2400}

Wyjście:
10 5
*/

#include <iostream>
#include <vector>

using namespace std;

int position = 0;

 vector<int> cycle = {1, 2, 3, 4, 5, 6, 7};

 int time_jump(int x) {
     position += x;
     if (position > (cycle.size()-1)) {
         return cycle[position % (cycle.size())];
     } 
     return cycle[position]; // Simulate cyclic behavior
}
//this time_jump was manually written for testing




int main() {

    int t;
    cin >> t;
    
    
    int jump_size;
    int mid;
    int left;
    int right;

    int size_of_cycle;

    int B;
    int X;
    int Y;

    bool overcycle;

    for (int i = 0; i < t; i++){
        jump_size = 1;
        size_of_cycle = 0;
        overcycle = false;

        left = 0;
        right = 0;
        mid = 0;

        B = time_jump(0);
        Y = time_jump(0);
        X = time_jump(jump_size);
        if (X == Y){
            size_of_cycle = 1;
        } else { 
            while (!overcycle){
                if (X == Y){
                    size_of_cycle = jump_size;
                    break;
                }
                jump_size *= 2;

                if (B == X){
                    size_of_cycle = jump_size - 1;
                    break;
                }

                if ((Y < B && B < X) || (B < X && X < Y) || (X < Y && Y < B)) {
                    overcycle = true;
                    B = X;
                    Y = X;
                    left = (jump_size/2);
                    right = (jump_size);
                    mid = (left+right) / 2;
                    X = time_jump(mid);

                } else {
                    Y = X;
                    X = time_jump(jump_size);
                }
            }
            while (overcycle){
                if (X == Y){
                    size_of_cycle = mid;
                    break;
                }

                if ((Y < B && B < X) || (B < X && X < Y) || (X < Y && Y < B) || (B == X && X < Y)) {
                    B = X;
                    Y = X;
                    left = mid;
                    right = (jump_size);
                    mid = (left+right) / 2;
                    X = time_jump(mid);
                } else {
                    right = mid;
                    mid = (left+right)/2;
                    Y = X;
                    X = time_jump(mid);
                }
            }
        }
        cout << size_of_cycle << ' ';
       // next_test();  
    }
}