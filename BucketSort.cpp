/*
Wejście:
Pierwsza linia: liczba naturalna n (2 ≤ n ≤ 2 000 000) – liczba słupków ogrodzenia.  
Druga linia: n liczb rzeczywistych p_i (–10^9 ≤ p_i ≤ 10^9) – pozycje słupków w losowej kolejności.

Opis zadania:
Mamy n punktów (pozycji słupków) na prostej. Przęsło ogrodzenia to odcinek między dwoma sąsiednimi słupkami po posortowaniu pozycji rosnąco.  
Należy obliczyć maksymalną odległość między dwiema kolejnymi pozycjami (najdłuższe przęsło).  
Ponieważ n może sięgać 2 000 000, sortowanie musi odbyć się w czasie liniowym bez użycia bibliotek STL.

Wyjście:
Jedna liczba rzeczywista – długość najdłuższego przęsła, zaokrąglona do 4 miejsc po przecinku.

Przykład:
Wejście:
8
7.6 -2.0 12.0 0.3 9.3 2.0 4.5 5.1

Wyjście:
2.7000
*/
#include <iostream>
#include <climits>
#include <iomanip>
#include <cmath>

using namespace std;

double Min = INT_MAX;
double Max = INT_MIN;

void ins_sort(double* arr, int size) {
    for (int i = 1; i < size; i++) {
        double key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void min_max (double* arr, int size){
    Min = arr[0];
    Max = arr[0];
    for (int i = 0; i < size; i++){
        if (Min > arr[i]) { Min = arr[i];}
        if (Max < arr[i]) { Max = arr[i];}
    }
    
}
int main(){
    int n;
    scanf("%d", &n);\
    double arr[n];

    for (int i = 0; i < n; i++){
        scanf("%lf", &arr[i]);
        if (arr[i] > Max){
            Max = arr[i];
        }
        if (arr[i] < Min){
            Min = arr[i];
        }
    }
    
    if (Min < 0){
        for (int i = 0; i < n; i++){
            arr[i] += (-1 * Min);
        }
        Max += (-1 * Min);
    }

    
    double range = double((Max)) / double(n/10.0);

    int num_of_buckets = (n/10)+1;
    double edgeValues[num_of_buckets][2];
    int bucketCount[num_of_buckets] = {0};
    int nonEmptyBuckets = 0;
    int singleBucketid;

    for (int i = 0; i < n; i++) {
        int index = arr[i] / range;
        bucketCount[index]++;
    }

    double* buckets[num_of_buckets];
    for (int i = 0; i < num_of_buckets; i++) {
        if (bucketCount[i] != 0){
            nonEmptyBuckets++;
            singleBucketid = i;
            buckets[i] = new double[bucketCount[i]];
            bucketCount[i] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int index = arr[i] / range;
        buckets[index][bucketCount[index]] = arr[i];
        bucketCount[index]++;
    }
    for (int i = 0; i < num_of_buckets; i++){
        if (bucketCount[i] > 0) {
            min_max(buckets[i], bucketCount[i]);
            edgeValues[i][0] = Min;
            edgeValues[i][1] = Max;
        }
    }

    double gap, max_gap, prev_max;
    max_gap = 0;
    if (nonEmptyBuckets == 1) {
        ins_sort(buckets[singleBucketid], bucketCount[singleBucketid]);
        max_gap = buckets[singleBucketid][1] - buckets[singleBucketid][0];
        for (int i = 2; i < bucketCount[singleBucketid]; i++){
            if (buckets[singleBucketid][i] - buckets[singleBucketid][i-1] > gap){
                max_gap = buckets[singleBucketid][i] - buckets[singleBucketid][i-1];
            }
        }
    } else {
        for (int i = 0; i < num_of_buckets; i++){
            if (bucketCount[i] != 0){
                prev_max = edgeValues[i][1];
                break;
            }

        }
        for (int i = 1; i < num_of_buckets; i++){
            if (bucketCount[i] != 0){
                gap = edgeValues[i][0] - prev_max;
                if (gap > max_gap)
                    max_gap = gap;
                
                prev_max = edgeValues[i][1];
            }
        }
    }
    cout << fixed << setprecision(4) << max_gap;
}