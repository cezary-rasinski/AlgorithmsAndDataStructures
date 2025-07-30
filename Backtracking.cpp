/*
Wejście:
Na wejściu znajduje się liczba naturalna n (1 ≤ n ≤ 35) – wymiar kwadratowej siatki.  
Następnie w kolejnych n wierszach podane są po n liczb naturalnych (każda ≤ 1000) – koszty zbioru przyprawy z danej grządki.

Opis zadania:
Mamy macierz kosztów rozmiaru n×n. Należy wybrać dokładnie jedną grządkę w każdym wierszu i każdej kolumnie tak, aby suma kosztów była minimalna.  
Ponieważ każda kolumna i każdy wiersz musi być użyty dokładnie raz, rozwiązanie można przedstawić jako permutację π, gdzie π[j] = i oznacza, że w kolumnie j wybieramy wiersz i.  
W przypadku wielu permutacji o takiej samej minimalnej sumie wybieramy tę, która jest najmniejsza leksykograficznie (najmniejsze możliwe π).  
Zadanie należy zaimplementować metodą przeszukiwania z nawrotami (backtracking) bez użycia bibliotek STL.

Wyjście:
Wypisz n liczb π[0] π[1] … π[n−1] – numer wiersza przypisany kolejno do każdej kolumny od 0 do n−1.

Przykład:
Wejście:
4
5 3 2 2
1 2 3 3
2 1 8 7
3 5 3 2

Wyjście:
1 2 0 3
*/

#include <iostream>
#include <climits>

using namespace std;

int n;
int min_sum = INT_MAX; 
int shortest_path[35];    
int arr[35][35];  

void backtrack(int col, int currentSum, bool visitedRows[], int path[]) {
    if (col == n) {
        if (currentSum < min_sum) {
            min_sum = currentSum;
            for (int i = 0; i < n; i++){
                shortest_path[i] = path[i];
            }
        }
        return;
    }
    if (currentSum >= min_sum){
        return;
    }

    for (int row = 0; row < n; row++) {
        if (!visitedRows[row]) { 
            visitedRows[row] = true;
            path[col] = row;

            backtrack(col+1, currentSum+arr[row][col], visitedRows, path);

            visitedRows[row] = false;
        }
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    bool visitedRows[n];
    int path[n];

    for (int i = 0; i < n; ++i) {
        visitedRows[i] = false;
    }

    backtrack(0, 0, visitedRows, path);
    for (int i = 0; i < n; i++){
        cout << shortest_path[i] << ' ';
    }
}
