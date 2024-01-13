
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


string multiplication(string a, string b) {
    // Обробка знаків
    bool isNegative = (a[0] == '-' and b[0] != '-') or (a[0] != '-' and b[0] == '-');
    if (a[0] == '-') a.erase(0, 1);
    if (b[0] == '-') b.erase(0, 1);

    // Ініціалізація масиву для результату
    int* result = new int[a.length() + b.length()] {0};

    // Множення цифр
    for (int i = a.length() - 1; i >= 0; i--) {
        for (int j = b.length() - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = result[i + j + 1] + mul;

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Конвертування результату у рядок
    string res = "";
    for (int i = 0; i < a.length() + b.length(); i++) {
        if (!(res.empty() and result[i] == 0)) {
            res.push_back(result[i] + '0');
        }
    }

    // Перевірка на випадок, якщо результат дорівнює нулю
    if (res.empty()) res = "0";

    // Додавання знаку, якщо потрібно
    if (isNegative and res != "0") {
        res = "-" + res;
    }

    // Видалення масиву
    delete[] result;

    return res;
}


string division(string dividend, string divisor) {
    // Перевірка на ділення на нуль
    if (divisor == "0") {
        return "Division by zero is not allowed";
    }

    // Перевірка, чи дільник більший за ділене
    if (dividend.length() < divisor.length() or (dividend.length() == divisor.length() and dividend < divisor)) {
        return "0";
    }

    // Ініціалізація змінних
    string result = "";
    string part = "";

    int index = 0;

    while (index < dividend.length()) {
        part += dividend[index++];

        if (part.length() > 1 && part[0] == '0') {
            part.erase(0, 1); // Видаляємо ведучі нулі
        }

        if (part.length() < divisor.length() || (part.length() == divisor.length() && part < divisor)) {
            if (!result.empty() || index >= dividend.length()) { // Додаємо 0 тільки якщо у результаті вже є значущі цифри або це остання ітерація
                result += "0";
            }
            continue;
        }

        // Знаходимо, скільки разів дільник вміщується у поточній частині
        int count = 0;
        string tempDivisor = divisor;
        while ((part.length() > tempDivisor.length() || (part.length() == tempDivisor.length() && part >= tempDivisor))) {
            count++;
            tempDivisor = addition(divisor, tempDivisor); // Використовуємо вашу функцію addition для додавання
        }

        // Дописуємо результат
        result += to_string(count);

        // Вираховуємо різницю
        part = subtraction(part, multiplication(to_string(count - 1), divisor)); // Використовуємо ваші функції multiplication і subtraction
    }

    return result;
}

string handleSignAndOperation(string a, string b, char op) {
    // Визначення від'ємних чисел
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
    return "Invalid Operation"; // На випадок неправильного введення
}



int main()
{
    int Z;
    cin >> Z;

    string* tests = new string[Z]; // Динамічний масив для тестів
    string* results = new string[Z]; // Динамічний масив для результатів

    for (int i = 0; i < Z; i++) {
        cin >> tests[i];
    }

    for (int i = 0; i < Z; i++) {
        string test = tests[i];
        size_t operatorPos = test.find_first_of("+-*/");
        string a = test.substr(0, operatorPos);
        string b = test.substr(operatorPos + 1);
        char op = test[operatorPos];

        if (op == '+') {
            results[i] = handleSignAndOperation(a, b, '+');
        }
        else if (op == '-') {
            results[i] = handleSignAndOperation(a, b, '-');
        }
        else if (op == '*') {
            results[i] = multiplication(a, b);
        }
        else if (op == '/') {
            results[i] = division(a, b);
        }
    }

    for (int i = 0; i < Z; i++) {
        cout << results[i] << endl;
    }

    // Очищення виділеної пам'яті
    delete[] tests;
    delete[] results;

    system("pause");
}