/*
Wejście:
Na wejściu znajduje się liczba naturalna n – rozmiar miasta (1 ≤ n ≤ 500).  
Następnie w kolejnych n wierszach podane są po n liczb 0 lub 1, gdzie 1 oznacza obecność artefaktu w danym sektorze, a 0 – brak artefaktu.

Opis zadania:
Miasto jest ułożone w siatkę n×n. Eksplorację rozpoczynamy w lewym górnym rogu (0,0), najpierw przemieszczając się wyłącznie w prawo lub w dół, aż do prawego dolnego rogu (n−1,n−1).  
Następnie wracamy do (0,0), poruszając się wyłącznie w górę lub w lewo. Trasę powrotu możemy częściowo lub całkowicie pokryć z trasą w jedną stronę, ale każdy artefakt (komórka z wartością 1) można zebrać tylko raz.  
Znajdź maksymalną liczbę artefaktów, które da się zebrać, stosując dwukierunkową trasę zgodnie z opisem.  

Ograniczenia:
- 1 ≤ n ≤ 500  
- wartości w siatce to 0 lub 1  

Wyjście:
Jedna liczba – maksymalna liczba artefaktów, które można zebrać.

Przykład:
Wejście:
4
1 0 1 0
1 1 0 0
0 0 0 1
1 0 0 1

Wyjście:
6
*/

#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;

    int num_of_artifacts = 0;
    int arr[n][n];
    int values[n][n] = {0};

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }

    values[0][0] = (arr[0][0] == 1 ? 1 : 0);
    for (int j = 1; j < n; j++){
        values[0][j] = arr[0][j] + values[0][j-1]; 
    }
    for (int i = 1; i < n; i++){
        values[i][0] = arr[i][0] + values[i-1][0]; 
    }
    
    for (int i = 1; i < n; i++){
        for (int j = 1; j < n; j++){
            values[i][j] = max(values[i-1][j], values[i][j-1]) + arr[i][j];
        }
    }
    num_of_artifacts += values[n-1][n-1];

    int i = n-1;
    int j = n-1;

    while (i > 0 || j >0) {
        int val = arr[i][j];
        arr[i][j] = 0;

        if (values[i][j] == values[i-1][j] + val){
            i--;
        } else {
            j--;
        }
    }
    arr[0][0] = 0;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            values[i][j] = 0;
        }
    }

    values[0][0] = arr[0][0];
    for (int j = 1; j < n; j++){
        values[0][j] = arr[0][j] + values[0][j-1]; 
    }
    for (int i = 1; i < n; i++){
        values[i][0] = arr[i][0] + values[i-1][0]; 
    }
    
    for (int i = 1; i < n; i++){
        for (int j = 1; j < n; j++){
            values[i][j] = max(values[i-1][j], values[i][j-1]) + arr[i][j];
        }
    }
    num_of_artifacts += values[n-1][n-1];

    cout << num_of_artifacts;
}