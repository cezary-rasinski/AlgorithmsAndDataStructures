/*
Wejście:
Pierwsza linia: liczba naturalna t – liczba zestawów danych.  
Dla każdego zestawu:
– liczba naturalna n – ilość obserwowanych wartości,  
– n liczb naturalnych a₁, a₂, …, aₙ (1 ≤ aᵢ ≤ 10⁶),  
– liczba naturalna k – pozycja szukanej wartości (0‑indeksowana).

Opis zadania:
Liczba aᵢ jest „korzystna”, jeśli ma parzystą liczbę unikalnych dzielników pierwszych.  
Spośród wszystkich korzystnych liczb należy wybrać k‑tą pod względem rosnącej wartości.  
Jeśli jest mniej niż k+1 takich liczb, wypisać „BRAK DANYCH”.  
Rozwiązanie trzeba oprzeć na algorytmie selekcji.

Wyjście:
Dla każdego zestawu danych w osobnej linii:
– k‑ta korzystna liczba (jeśli istnieje),  
– lub słowo BRAK DANYCH.

Przykład:
Wejście:
2
5
12 15 9 10 6
2
4
8 14 7 18
2

Wyjście:
12
BRAK DANYCH
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> count_unique_prime_factors(int max_n) {

    vector<int> unique_factors(max_n + 1, 0);
    vector<bool> is_prime(max_n + 1, true);
    unique_factors[0] = 1;

    for (int p = 2; p <= max_n; ++p) {

        if (is_prime[p]){
            for( int multiple = p; multiple <= max_n; multiple += p){
                unique_factors[multiple]++;
                is_prime[multiple] = false;
            }
            is_prime[p] = true; 
        }
    }
    return unique_factors;
}
int qs (vector<int> &arr, int k){

    int pivot = arr[0];

    vector<int> B;
    vector<int> C;
    vector<int> D;

    for (int i = 0; i < arr.size(); i++){
        if (arr[i] < pivot){
            B.push_back(arr[i]);
        } else if (arr[i] == pivot){
            C.push_back(arr[i]);
        } else if (arr[i] > pivot){
            D.push_back(arr[i]);
        }
    }
    
    if (k < B.size()){
        return qs(B, k);
    } else if (k < B.size() + C.size()){
        return pivot;
    } else {
        return qs(D, k - (B.size() + C.size()));
    }
}
int main(){

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t, n, a, k;
    cin >> t;

    vector<int> unique_factors = count_unique_prime_factors(1000000);

    for (int i = 0; i < t; i++){
        cin >> n;
        vector<int> numbers;
        for (int j = 0; j < n; j++){
            cin >> a;
            numbers.push_back(a);
        }
        cin >> k;

        vector<int> beneficial_numbers;
        for (int v = 0; v < numbers.size(); v++){
            int current_number = numbers[v];
            if (current_number >= 1 && current_number <= 1000000 && unique_factors[current_number] % 2 == 0){
            beneficial_numbers.push_back(current_number);
            }
        }

        if (k >= beneficial_numbers.size()){
            cout << "BRAK DANYCH\n";
        } else {
           int result_number = qs(beneficial_numbers, k);
           cout << result_number << '\n';
        }
    }
}