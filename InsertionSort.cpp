/*Algorithm: Stable Insertion Sort

Goal of the algorithm: add items in the most efficent way
Rule for adding an item: the energy cost of adding an item is it's weight plues the weight of all previous items added

How it works: The code reads an integer t (number of test cases), and for each reads an integer n followed 
by n lines of items(name and weight), then uses a stable insertion sort to order artifacts by descending mass
(preserving original order on ties). Then initializes y=0 and total_cost=0 and for each sorted artifact
of mass x adds (x+y) to total_cost and does y+=x. 

Input: t test cases, each with n and n pairs (name, mass).
Output: for each test case, print the minimal total energy and on the next line, item names in the order
to insert. 

Example:
Input: 1 3 A 2 B 5 C 3
Output:
17
A C B*/



#include <iostream>

using namespace std;

struct Item{
    string name;
    long weight;
};

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        int n; 
        cin >> n;
        
        Item items[n];

        for (int j = 0; j < n; j++){
            cin >> items[j].name >> items[j].weight;
        }

        for (int i = 1; i < n; i++){
            int j = i-1;
            int key_val = items[i].weight;
            string name = items[i].name;

            while (j >= 0 && items[j].weight > key_val){
                items[j+1].weight = items[j].weight;
                items[j+1].name = items[j].name;
                j--;
            }
            items[j+1].weight = key_val;
            items[j+1].name = name;
        }

        long total_min_weight = 0;
        long y = 0;
        for (int i = 0; i < n; i++) {
            total_min_weight += y;
            total_min_weight += items[i].weight;
            y += items[i].weight;
        }
        cout << total_min_weight << "\n";
        for (int i = 0; i < n; i++) {
            cout << items[i].name << ' ';
        }
    }
}