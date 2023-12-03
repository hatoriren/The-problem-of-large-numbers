
#include <iostream>
#include <string>

using namespace std;

string addition(string a, string b)
{
    // wyznaczamy pozycję ostatniej cyfry w obu łańcuchach

    int pozycja_a = a.length() - 1;
    int pozycja_b = b.length() - 1;

    string wynik = "";

    int przeniesienie = 0;

    // dodajemy kolejne cyfry a i b

    while (pozycja_a >= 0 or pozycja_b >= 0)
    {
        // wyliczamy wartości cyfr w łańcuchach a i b

        int ca, cb, w;

        if (pozycja_a >= 0) ca = a[pozycja_a] - 48; else ca = 0;
        if (pozycja_b >= 0) cb = b[pozycja_b] - 48; else cb = 0;

        w = ca + cb + przeniesienie;

        // do łańcucha wynikowego wstawiamy ostatnią cyfrę w

        wynik = "0" + wynik;
        wynik[0] = 48 + w % 10;

        // obliczamy przeniesienie do następnej kolumny

        przeniesienie = w / 10;

        pozycja_a--; pozycja_b--;
    }

    // jeśli przeniesienie wynosi 1, dopisujemy cyfrę 1 do wyniku

    if (przeniesienie) wynik = "1" + wynik;

    return wynik;
}

string subtraction(string a, string b) {
    int pozycja_a = a.length() - 1;
    int pozycja_b = b.length() - 1;

    string wynik = "";

    int pozyczka = 0;

    // false = liczba dodatnia, true = liczba ujemna

    bool negative = false;

    if (a >= b) {
        while (pozycja_a >= 0 or pozycja_b >= 0) {
            int ca, cb, w;

            if (pozycja_a >= 0) ca = a[pozycja_a] - '0'; else ca = 0;
            if (pozycja_b >= 0) cb = b[pozycja_b] - '0'; else cb = 0;

            w = ca - cb - pozyczka; // Od a odejmujemy b

            // Przekazujemy pożyczkę, jeśli jest taka potrzeba

            if (w < 0) {
                w += 10;
                pozyczka = 1;
            }
            else {
                pozyczka = 0;
            }

            wynik = char(w + '0') + wynik;

            pozycja_a--; pozycja_b--;
        }

        // Usuwa zera wiodące

        while (wynik.length() > 1 && wynik[0] == '0') {
            wynik.erase(0, 1);
        }

        return wynik;
    }
    else {
        while (pozycja_a >= 0 or pozycja_b >= 0) {
            int ca, cb, w;

            if (pozycja_a >= 0) ca = a[pozycja_a] - '0'; else ca = 0;
            if (pozycja_b >= 0) cb = b[pozycja_b] - '0'; else cb = 0;

            w = cb - ca - pozyczka; // Od b pdejmujemy a

            if (w < 0) {
                w += 10;
                pozyczka = 1;
            }
            else {
                pozyczka = 0;
            }

            wynik = char(w + '0') + wynik;

            pozycja_a--; pozycja_b--;
        }

        while (wynik.length() > 1 && wynik[0] == '0') {
            wynik.erase(0, 1);
        }

        if (a < b) {
            negative = true; // Jeśli a jest mniejsze niż b, wynik będzie ujemny
        }

        if (negative) {
            wynik = "-" + wynik; 
        }

        return wynik;
    }
}

int main()
{
    string a, b;

    do {
        cout << "Write your numbers" << endl;
        getline(cin, a);
        getline(cin, b);
    } while (a.empty() || b.empty());


    cout << a << " + " << b << " = " << addition(a, b) << endl;

    cout << a << " - " << b << " = " << subtraction(a, b) << endl;



    return 0;
    

  
   
}