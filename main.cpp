/*
 #include <iostream>
 #include <vector>
 #include <cmath>

 using namespace std;

 // Функция для проверки простоты числа
 bool isPrime(int n) {
     if (n <= 1) return false;
     if (n <= 3) return true;
     if (n % 2 == 0 || n % 3 == 0) return false;
     for (int i = 5; i * i <= n; i += 6) {
         if (n % i == 0 || n % (i + 2) == 0)
             return false;
     }
     return true;
 }

 // Функция для вычисления a^x mod p
 int modPow(int base, int exponent, int module) {
     // Проверка на случай отрицательного значения степени
     if (exponent < 0)
         return -1; // Признак ошибки
     int result = 1;
     base %= module; //  берем остаток от деления базы на модуль
     while (exponent > 0) {
         // Если степень нечетная, умножаем результат на базу по модулю
         if (exponent % 2 == 1)
             result = (result * base) % module;
         // Берем квадрат базы и обновляем степень
         base = (base * base) % module;
         exponent /= 2;
     }
     return result;
 }

 // Функция для вычисления a^x mod p через логарифмический метод
 int modPowLog(int base, int exponent, int module) {
     int t = log2(exponent); // Логарифм степени по основанию 2
     vector<int> a;
     int result = 1;
     for (int i = 1; i <= pow(2, t); i *= 2) {
         a.push_back(modPow(base, i, module)); // Ищем ряд а, заполняем вектор
     }
     // Преобразуем степень в двоичное представление
     int exp2 = exponent;
     vector<int> binaryExp;
     while (exp2 > 0) {
         binaryExp.push_back(exp2 % 2);
         exp2 /= 2;
     }
     // Умножаем результаты a по соответствующим битам двоичного представления степени
     for (int i = 0; i < a.size(); i++) {
         if (binaryExp[i] == 1)
             result = (result * a[i]) % module;
     }
     return result;
 }

 int main() {
     int a, x, b, y, p;

     cout << "Введите число a: ";
     cin >> a;

     cout << "Введите степень x: ";
     cin >> x;

     cout << "Введите число b: ";
     cin >> b;

     cout << "Введите степень y: ";
     cin >> y;

     cout << "Введите модуль p: ";
     cin >> p;

     // Проверка на простоту модуля p
     if (!isPrime(p)) {
         cout << "Модуль p должен быть простым числом." << endl;
         return 1;
     }

     // Проверка на теорему Ферма для a и p
     if (modPow(a, p - 1, p) != 1) {
         cout << "Теорема Ферма не выполняется для a и p." << endl;
         return 1;
     }

     // Проверка на теорему Ферма для b и p
     if (modPow(b, p - 1, p) != 1) {
         cout << "Теорема Ферма не выполняется для b и p." << endl;
         return 1;
     }

     // Вычисляем a^x mod p и b^y mod p
     int result1 = modPowLog(a, x, p);
     int result2 = modPowLog(b, y, p);

     // Выводим результаты и сравниваем их по модулю p
     cout << "Результат вычисления a^x mod p: " << result1 << endl;
     cout << "Результат вычисления b^y mod p: " << result2 << endl;
     if (result1 == result2)
         cout << "Оба результата совпадают по модулю p." << endl;
     else
         cout << "Результаты по модулю p не совпадают." << endl;

     return 0;
 }
*/

 


/*

//Задание 3
#include <iostream>

// Функция, вычисляющая НОД(a, b) и одновременно находящая коэффициенты x и y
int extendedEuclidean(int a, int b, int &x_coefficient, int &y_coefficient) {
    if (b == 0) {
        x_coefficient = 1;
        y_coefficient = 0;
        return a;
    }

    int previous_x_coefficient, previous_y_coefficient;
    int gcd = extendedEuclidean(b, a % b, previous_x_coefficient, previous_y_coefficient);

    x_coefficient = previous_y_coefficient;
    y_coefficient = previous_x_coefficient - (a / b) * previous_y_coefficient;

    return gcd;
}

// Функция для нахождения обратного элемента по модулю
int modInverse(int number, int modulo) {
    int x_coefficient, y_coefficient;
    int gcd = extendedEuclidean(number, modulo, x_coefficient, y_coefficient);

    if (gcd != 1) {
        std::cout << "inverse element does not exist!\n";
        return -1;
    } else {
        return (x_coefficient % modulo + modulo) % modulo;
    }
}

int main() {
    int number, modulo;
    std::cout << "Enter number and modulus: ";
    std::cin >> number >> modulo;

    int inverse = modInverse(number, modulo);
    if (inverse != -1)
        std::cout << "inverse element for " << number << " modulo " << modulo << " is: " << inverse << std::endl;

    return 0;
}

*/



//Вариант 3 // 4 задние

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// Вспомогательная функция для возведения числа в степень по модулю
int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Функция для нахождения обратного элемента в кольце вычетов по модулю m
int mod_inverse(int a, int m) {
    int m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Функция для генерации ключей
vector<int> generate_keys(int p) {
    mt19937 rng(time(NULL));
    int g = 2; // Первообразный корень для больших простых чисел, можно использовать другие методы нахождения
    int x = rng() % (p - 1) + 1;
    int y = mod_pow(g, x, p);
    return vector<int>{g, p, y, x};
}

// Функция для шифрования
pair<int, vector<int>> encrypt(const string& plain_text, const vector<int>& public_key) {
    int g = public_key[0], p = public_key[1], y = public_key[2];
    mt19937 rng(time(NULL));
    int k = rng() % (p - 2) + 1; // Выбор случайного числа k
    int c1 = mod_pow(g, k, p);
    vector<int> c2;

    for (char ch : plain_text) {
        int m = static_cast<int>(ch); // не ASCII а UNICOD utf-8
        int c2_val = (m * mod_pow(y, k, p)) % p;
        c2.push_back(c2_val);
    }

    return make_pair(c1, c2);
}

// Функция для дешифрования
string decrypt(const pair<int, vector<int>>& ciphertext, const vector<int>& private_key) {
    int c1 = ciphertext.first;
    const vector<int>& c2 = ciphertext.second;
    int p = private_key[1], x = private_key[3];
    string decrypted_text;

    int s = mod_pow(c1, x, p);
    int s_inverse = mod_inverse(s, p);

    for (int enc_char : c2) {
        int m = (enc_char * s_inverse) % p;
        decrypted_text.push_back(static_cast<char>(m));
    }

    return decrypted_text;
}

int main() {
    int prime_p = 2087; // Большее простое число для демонстрации
    vector<int> alice_keys = generate_keys(prime_p);
    vector<int> bob_keys = generate_keys(prime_p);

    string alice_message = "Я к вам пишу — чего же боле? Что я могу еще сказать? Теперь, я знаю, в вашей воле Меня презреньем наказать. Но вы, к моей несчастной доле Хоть каплю жалости храня,Вы не оставите меня."; // Сообщение от Алисы к Бобу
    cout << "Исходное сообщение Алисы: " << alice_message << endl;

    auto encrypted_message = encrypt(alice_message, bob_keys); // Алиса шифрует сообщение для Боба
    cout << "Зашифрованное сообщение для Боба: ";
    for (int num : encrypted_message.second) {
        cout << num << " ";
    }
    cout << endl;

    string bob_decrypted_message = decrypt(encrypted_message, bob_keys); // Боб расшифровывает сообщение
    cout << "Боб расшифровал сообщение: " << bob_decrypted_message << endl;

    return 0;
}




/*Найти последнюю цифру «трехэтажного числа».*/
/*


//Задание 5

#include <iostream>
#include <cmath>

// Функция для быстрого возведения в степень по модулю
int modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // Если степень нечетная
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // Возводим основание в квадрат
        exp /= 2; // Делим степень на 2
    }
    return result;
}

int main() {
    int a = 1;
    int b = 1;
    int c = 1;
    

    std::cout << "enter values a, b, c: ";
    std::cin >> a >> b >> c;

    // Поскольку для нахождения последней цифры a^(b^c) достаточно найти b^c по модулю 4,
    // а затем a^(b^c mod 4) по модулю 10, сделаем это
    int exp_mod_4 = modExp(b, c, 4);
    int last_digit = modExp(a, exp_mod_4, 10);

    std::cout << "Last digit of the number " << a << "^(" << b << "^" << c << ") is " << last_digit << std::endl;

    return 0;
}

*/
