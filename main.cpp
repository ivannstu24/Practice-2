/*Реализовать ax mod p Сравнения по модулю простого числа через теорему Ферма и свойства сравнений. Программа должна проверять условия выполнения теоремы Ферма и простоту вводимого пользователем модуля.*/


/*
//задание 1.1
#include <iostream>
#include <cmath>

// проверка числа на простоту
bool isPrime(int n) {
   if (n <= 1) return false;
   if (n <= 3) return true;
   if (n % 2 == 0 || n % 3 == 0) return false;
   for (int i = 5; i * i <= n; i += 6) {
       if (n % i == 0 || n % (i + 2) == 0) return false;
   }
   return true;
}



bool fermatTheorem(int a, int p) {
   if (a == 0) return true; // 0^p ≡ 0 (mod p)
   return (int)pow(a, p - 1) % p == 1;
}

int modPow(int base, int exponent, int modulus) {
   int result = 1;
   base = base % modulus;
   while (exponent > 0) {
       if (exponent % 2 == 1) {
           result = (result * base) % modulus;
           exponent--;
       }
       exponent = exponent / 2;
       base = (base * base) % modulus;
   }
   return result;
}

int modInverse(int a, int m) {
   return modPow(a, m - 2, m);
}

bool modComparison(int a, int b, int m) {
   return (a * modInverse(b, m)) % m == 1;
}

int main() {
   int p, a, b, exponent, exponent1;
   std::cout << "Введите модуль: ";
   std::cin >> p;

    // проверяем является ли число модуля простым числом
   if (!isPrime(p)) {
       std::cout << "Введенное число не является простым." << std::endl;
       return 0;
   }
    
    
   std::cout << "Введите первое число a: ";
   std::cin >> a;

   if (!fermatTheorem(a, p)) {
       std::cout << "Теорема Ферма не выполняется для числа a." << std::endl;
       return 0;
   }

   std::cout << "Введите степень для a: ";
   std::cin >> exponent;

   a = modPow(a, exponent, p);

   std::cout << "Введите второе число b: ";
   std::cin >> b;
   
   if (!fermatTheorem(b, p)) {
       std::cout << "Теорема Ферма не выполняется для числа b." << std::endl;
       return 0;
   }
   
   std::cout << "Введите степень для b: ";
   std::cin >> exponent1;
   
   b = modPow(b, exponent1, p);
   
   if (modComparison(a, b, p)) {
       std::cout << "Числа a и b равны по модулю p." << std::endl;
   } else {
       std::cout << "Числа a и b не равны по модулю p." << std::endl;
   }

   return 0;
}
*/



/*Реализовать алгоритм через разложение степени в двоичный вид (логарифм).*/

/*
//Задание 1.2
#include <iostream>

// Функция для вычисления a^b mod p
long long power_mod(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p; // Уменьшаем a до предела p

    while (b > 0) {
        // Если текущий бит в двоичном разложении степени b равен 1
        if (b & 1) {
            result = (result * a) % p;
        }

        // Умножаем a само на себя и уменьшаем b вдвое
        b = b >> 1;
        a = (a * a) % p;
    }

    return result;
}

// Функция для проверки теоремы Ферма
bool fermatTheorem(int a, int p) {
    if (a >= p) return false; // Теорема Ферма не применима, если a >= p
    return power_mod(a, p - 1, p) == 1;
}

// Функция для проверки, является ли число простым
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    long long a, x, p;
    std::cout << "Введи a, x, и p: ";
    std::cin >> a >> x >> p;

    // Вычисляем a^x mod p
    long long result = power_mod(a, x, p);
    std::cout << "Результат: " << result << std::endl;

    // Проверяем, является ли p простым числом и выполняется ли теорема Ферма
    if (is_prime(p)) {
        std::cout << "p является простым числом" << std::endl;
    }

    // Проверяем теорему Ферма
    if (fermatTheorem(a, p)) {
        std::cout << "Теорема Ферма выполняется" << std::endl;
    } else {
        std::cout << "Теорема Ферма не выполняется" << std::endl;
    }

    return 0;
}




*/


/*Реализовать обобщенный алгоритм Евклида для вычисления с*d mod m=1.*/

/*
//Задание 2 (Обобщенный алгоритм Евклида)

#include <iostream>

// Функция для расчета наибольшего общего делителя и коэффициентов Безу
int extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Функция для нахождения модульного обратного
int modInverse(int c, int m) {
    int x, y;
    int gcd = extendedGCD(c, m, x, y);
    if (gcd != 1) {
        std::cerr << "Обратный элемент не существует." << std::endl;
        return 0;
    } else {
        // Нормализация x чтобы получить положительный результат
        return (x % m + m) % m;
    }
}

int main() {
    int c, m;
    std::cout << "Введите c: ";
    std::cin >> c;
    std::cout << "Введите m: ";
    std::cin >> m;

    int inv = modInverse(c, m);
    if (inv != 0) {
        std::cout << "Мультипликативный обратный элемент " << c << " по модулю " << m << " равен: " << inv << std::endl;
    }
    return 0;
}
*/




/*Написать программу, использующую алгоритм шифрования данных
 для преобразования исходного текста*/

/*
// Задание 4 (Вариант 3: Эль-Гамаль)
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
        int m = static_cast<int>(ch); // ASCII
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
    vector<int> keys = generate_keys(prime_p);

    string message = "Hello World!";
    cout << "Original Message: " << message << endl;

    auto encrypted_message = encrypt(message, keys);
    cout << "Encrypted Message: ";
    for (int num : encrypted_message.second) {
        cout << num << " ";
    }
    cout << endl;

    string decrypted_message = decrypt(encrypted_message, keys);
    cout << "Decrypted Message: " << decrypted_message << endl;

    return 0;
}

*/

/*Найти последнюю цифру «трехэтажного числа».*/


/*
// Задание 5

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
    int a, b, c;

    // Ввод значений a, b и c
    std::cout << "Введите значения a, b, c: ";
    std::cin >> a >> b >> c;

    // Поскольку для нахождения последней цифры a^(b^c) достаточно найти b^c по модулю 4,
    // а затем a^(b^c mod 4) по модулю 10, сделаем это
    int exp_mod_4 = modExp(b, c, 4);
    int last_digit = modExp(a, exp_mod_4, 10);

    std::cout << "Последняя цифра числа " << a << "^(" << b << "^" << c << ") равна " << last_digit << std::endl;

    return 0;
}
*/

