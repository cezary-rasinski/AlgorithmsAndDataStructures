/*Zadaniem programu będzie kierowanie klientów do najmniej obleganych kas. 
Program ma symulować pracę sklepu przez określony czas liczony w sekundach oraz wyświetlać stan każdej kasy 
(ilość osób w kolejce oraz szacowany czas oczekiwania w kolejce) po upływie tego czasu.

Te same kasy mogą w trakcie trwania symulacji być otwierane i zamykane kilkukrotnie. W przypadku otwarcia kasy czas oczekiwania i ilość osób w kolejce wynosi 0. 
Kasy, w których czas oczekiwania w kolejce (nie liczba osób - ponieważ może być tak, 
że jedna osoba zrobiła zakupy na cały rok i czas obsłużenia takiej osoby jest wyższy niż 10 standardowych klientów) jest najkrótszy powinny być przez system wychwytywane, 
a nowe osoby powinny być do takich kas kierowane. Nie rozpatrujemy sytuacji znanych z supermarketów, gdzie informacja o kasie, która będzie otwarta niebawem, podawana jest przez megafon i klienci mogą tworzyć kolejki do jeszcze nie otwartej kasy. 

Dodatkowo zakładamy, iż sekwencyjne zamykanie i otwieranie tej samej kasy w sklepie nie występuje. 
W naszym programie, gdy kasa ma zostać zamknięta kasjer obsługuje tylko pierwszą osobę z kolejki (dla uproszczenia przyjmujemy, że taka osoba zostaje obsłużona natychmiastowo). 
Pozostałe osoby, zaczynając od drugiej osoby, należy pokierować do pozostałych kas w ten sam sposób jak opisano to dla nowych klientów.

Zakładamy, że w sklepie musi w każdym momencie istnieć co najmniej jedna otwarta kasa. 
W przypadku, gdy dwie kasy mają jednakowy czas oczekiwania - system wybiera kasę o mniejszym numerze (id).

Wejście
W pierwszej linii wejścia znajdują się cztery liczby naturalne: t - czas pracy sklepu podlegający symulacji liczony w sekundach; 
l - ilość kas w sklepie; 
s - sprawność kas, czyli liczba sekund potrzebna na zeskanowanie produktu przez kasjera; 
z - czas, jaki potrzebuje klient na dokonanie płatności. 

W kolejnych liniach pojawiać będą się liczby/symbole opisujące zdarzenia, których wyróżniamy 3 rodzaje: 
o - otwarcie kasy, 
z - zamknięcie kasy, 
k - pojawienie się nowego klienta oczekującego na obsługę. 

Każda linia zaczyna się od jednoznakowej flagi: f - oznaczającej rodzaj zdarzenia (o,z,k - jak opisano wcześniej).
W przypadku, gdy f == 'k' kolejne dwa parametry to: 
p - względny czas w sekundach liczony od rozpoczęcia symulacji w przypadku pierwszego klienta, a dla pozostałych klientów- czas od pojawienia się poprzedniego klienta 
(jest gwarancja, że suma wszystkich względnych czasów w danych wejściowych pi będzie większa lub równa t) ; 
r - liczba produktów w koszyku klienta. 
Gdy f == 'o' lub f == 'z' kolejnym parametrem znajdującym się za flagą jest a - numer kasy.

Wyjście
Na wyjściu powinniśmy otrzymać stan każdej kasy po upływie czasu t zapisany w postaci:
K[numer_kasy]: [ilosc_osob_w_kolejce]o, [dlugosc_kolejki_w_sekundach]s - jeżeli kasa jest otwarta lub
K[numer_kasy]: z - gdy kasa jest zamknięta.

Informacje o kasach powinny być wyświetlone w jednej linii i powinny być oddzielone przecinkami.

UWAGA! W zadaniu nie można używać bibliotek STL. Należy wykorzystać samodzielnie napisaną implementację kolejki.
Przykład:

Wejście:
30 5 5 5			
o 2				
o 1				
k 0 8			
k 1 7			
k 1 10		
k 0 5			
k 0 4			
o 4				
k 10 8		
k 0 5			
k 10 6		
z 1				
k 7 7			
k 0 5	
k 8 4
	

Wyjście:
K0: z, K1: z, K2: 4o 136s, K3: z, K4: 5o 147s
*/

#include <iostream>

using namespace std;

struct Client {
    long nums;
    Client* next;
    Client* prev;

    Client(long num) {
        nums = num;
        next = prev = nullptr;
    }
};

struct Register {
    int id;
    long total_pending;
    long first_client_time;
    long total_clients;

    Client* head;
    Client* tail;

    Register() : id(31), total_pending(100000000), first_client_time(0), total_clients(0), head(nullptr), tail(nullptr) {}

    void initialize(int num) {
        id = num;
        total_pending = 0;
        first_client_time = 0;
        total_clients = 0;
        head = tail = nullptr;
    }

    void reset() {
        id = 31;
        total_pending = 100000000;
        first_client_time = 0;
        total_clients = 0;
        head = tail = nullptr;
    }

    void add(Client* c){
        if (head == nullptr){
            head = tail = c;
        } else {
            c->next = tail;
            c->prev = nullptr;
            tail->prev = c; 
            tail = c;
        }
        total_clients++;
    }

    void pop(){
        Client * temp = head;
        if (temp == nullptr)
            return;

        if (head->prev != nullptr){
            head = head->prev;
            head->next = nullptr;
        } else {
            head = tail = nullptr;
            first_client_time = 0;
            total_clients = 0;
            return;
        }

        if (temp != nullptr){
            delete temp;
            total_clients--;
        }
    }
};

Register new_reg(Register registers[], long num_of_reg) {
    Register top_priority;
    for (int i = 0; i < num_of_reg; i++) {
        if (registers[i].id == (31) )
             continue;
        
        if (registers[i].total_pending < top_priority.total_pending) {
            top_priority = registers[i];
        } else if (registers[i].total_pending == top_priority.total_pending){
            if (registers[i].id < top_priority.id){
                top_priority = registers[i];
            }
        }
    }
    return top_priority;
}

int main() {
    long worktime, num_of_reg, reg_eff, pay_time;
    cin >> worktime >> num_of_reg >> reg_eff >> pay_time;

    bool stop = 0;

    Register registers[num_of_reg];

    for (int i = 0; i < worktime;) {
        char flag;

        cin >> flag;

        if (flag == 'o') {
            long reg_num;
            cin >> reg_num;
            registers[reg_num].initialize(reg_num);
        } else if (flag == 'z') {
            long reg_num;
            cin >> reg_num;
            Client* que = registers[reg_num].head;
            registers[reg_num].reset();

            if (que != nullptr) {
                    que = que->prev;
            }
            while (que != nullptr) {
                Register low_reg = new_reg(registers, num_of_reg); 
                int regg = low_reg.id;
                Client* c = new Client(que->nums);
                low_reg.add(c);

                low_reg.total_pending += c->nums * reg_eff + pay_time;
                registers[regg] = low_reg;
                
                que = que->prev;
            }
        } else if (flag == 'k') {
            long p, r;
            cin >> p >> r;

            if (i + p > worktime) {
                p = worktime - i;
                stop = true;
            }

            long original_p = p;
            if (p>0) {
                for (int j = 0; j < num_of_reg; j++) {
                    p = original_p;
                    if (registers[j].id != 31 && registers[j].head != nullptr) {
                        if (registers[j].first_client_time - p > 0) {
                            registers[j].total_pending -= p;
                            registers[j].first_client_time -= p;
                        } else if (registers[j].first_client_time - p == 0) {
                           registers[j].total_pending -= p;
                           registers[j].pop();
                            if (registers[j].head != nullptr) {
                           registers[j].first_client_time =registers[j].head->nums * reg_eff + pay_time; 
                            }
                        } else if(registers[j].first_client_time - p < 0){
                            if (registers[j].total_pending - p <= 0){
                                registers[j].total_pending = 0;
                            } else {
                                registers[j].total_pending -= p;
                            }

                            while (registers[j].first_client_time - p < 0 && p > 0){
                                p = p - registers[j].first_client_time;
                                
                                registers[j].pop();
                                if (registers[j].head != nullptr) {
                                    registers[j].first_client_time = (registers[j].head->nums * reg_eff + pay_time); 
                                } else {
                                    break;
                                }
                            }

                            if (registers[j].first_client_time - p > 0){
                                registers[j].first_client_time -= p;
                            } else if (registers[j].first_client_time - p == 0) {
                                registers[j].pop();
                                if (registers[j].head != nullptr) {
                                registers[j].first_client_time = registers[j].head->nums * reg_eff + pay_time; 
                                }
                            }
                        }   
                    }
                }
            }

            if (stop == true){
                break;
            }

            Register low_reg = new_reg(registers, num_of_reg);
            int regg = low_reg.id;
            Client* c = new Client(r);
            low_reg.add(c);
            low_reg.total_pending += c->nums * reg_eff + pay_time;
            if (low_reg.head == c) {
                low_reg.first_client_time = low_reg.head->nums * reg_eff + pay_time;
            }
            registers[regg] = low_reg;
            i += original_p;
        } else{
            continue;
        }
    }

    for (int i = 0; i < num_of_reg; i++) {
        if (i != 0) cout << ", ";
        if (registers[i].id != 31) {
            cout << 'K' << i << ": " << registers[i].total_clients << "o " << registers[i].total_pending << 's';
        } else {
            cout << 'K' << i << ": z";
        }
    }

    return 0;
}