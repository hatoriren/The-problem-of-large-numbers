#include <iostream>
#include <vector>
#include <string>

using namespace std;

string addition(const string& a, const string& b)
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

string subtraction(string a, string b)
{
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


string multiplication(string a, string b) {
    // Przetwarzanie znaków
    bool isNegative = (a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-');
    if (a[0] == '-') a.erase(0, 1);
    if (b[0] == '-') b.erase(0, 1);

    int n = a.length();
    int m = b.length();
    vector<int> result(n + m, 0);

    // Mnożenie liczb
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = result[i + j + 1] + mul;

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Konwertuj wynik na ciąg znaków
    string res;
    for (int num : result) {
        if (!(res.empty() && num == 0)) {
            res.push_back(num + '0');
        }
    }

    // Konwertuj wynik na ciąg znaków
        if (res.empty()) res = "0";
        
        // Dodaj znak, jeśli to konieczne
        if (isNegative && res != "0") {
            res = "-" + res;
        }

    return res;
}

string division(string dividend, string divisor)
{
    // Sprawdzanie dzielenia przez zero
    
    if (divisor == "0") {
        return "Division by zero is not allowed";
    }

    // Sprawdź, czy dzielnik jest większy od dywidendy

    if (dividend.length() < divisor.length() or (dividend.length() == divisor.length() and dividend < divisor)) {
        return "0";
    }

   
    string result = "";
    string part = "";

    int index = 0;

    while (index < dividend.length()) {
        part += dividend[index++];

        if (part.length() > 1 && part[0] == '0') {
            part.erase(0, 1); // Inicjalizacja zmiennych
        }

        if (part.length() < divisor.length() || (part.length() == divisor.length() && part < divisor)) {
            if (!result.empty() || index >= dividend.length()) {// Dodaj 0 tylko wtedy, gdy wynik zawiera już cyfry znaczące lub jest ostatnią iteracją
                result += "0";
            }
            continue;
        }

        // Znajdź, ile razy dzielnik mieści się w bieżącej części
        int count = 0;
        string tempDivisor = divisor;
        while ((part.length() > tempDivisor.length() || (part.length() == tempDivisor.length() && part >= tempDivisor))) {
            count++;
            tempDivisor = addition(divisor, tempDivisor);

        } 

        // Dodaj wynik
        result += to_string(count);

        // Oblicz różnicę
        part = subtraction(part, multiplication(to_string(count - 1), divisor)); // Używamy funkcji mnożenia i odejmowania
    }

    return result;
}

string handleSignAndOperation(string a, string b, char op)
{
    
    bool isANegative = a[0] == '-';
    bool isBNegative = b[0] == '-';

    if (isANegative) a = a.substr(1);
    if (isBNegative) b = b.substr(1);

    if (op == '+') {
        if (isANegative == isBNegative) {
            if (isANegative) {
                return "-" + addition(a, b);
            }
            else {
                return addition(a, b);
            }
        }
        else {
            if (isANegative) {
                return subtraction(b, a);
            }
            else {
                return subtraction(a, b);
            }
        }
    }
    else if (op == '-') {
        if (isANegative == isBNegative) {
            if (isANegative) {
                return subtraction(b, a);
            }
            else {
                return subtraction(a, b);
            }
        }
        else {
            if (isANegative) {
                return "-" + addition(a, b);
            }
            else {
                return addition(a, b);
            }
        }
    }
    return "Invalid Operation";
}



int main()
{
    int Z;
    cin >> Z;

    Z = min(Z, 200); 

    vector<string> tests(Z);
    vector<string> results(Z);

    for (int i = 0; i < Z; i++) {
        cin >> tests[i];
    }

    for (int i = 0; i < Z; i++) {
        size_t operatorPos = tests[i].find_first_of("+-*/");
        string a = tests[i].substr(0, operatorPos);
        string b = tests[i].substr(operatorPos + 1);
        char op = tests[i][operatorPos];
        switch (op) {
        case '+': results[i] = handleSignAndOperation(a, b, '+'); break;
        case '-': results[i] = handleSignAndOperation(a, b, '-'); break;
        case '*': results[i] = multiplication(a, b); break;
        case '/': results[i] = division(a, b); break;
        default: results[i] = "Invalid Operation";
        }
    }
    cout << endl;
    cout << "Result: " << endl;
    cout << endl;

    for (const auto& result : results) {
        cout << result << endl;
    }

    system("pause");
}