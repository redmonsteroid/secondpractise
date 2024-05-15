#include <iostream>

using namespace std;

// Функция, реализующая расширенный алгоритм Евклида
int extendedEuclidean(int a, int b, int &c, int &d) {
    if (b == 0) {
        c = 1;
        d = 0;
        return a;
    }

    int s1, d1;
    int gcd = extendedEuclidean(b, a % b, s1, d1);

    // Обновляем c и d на основе результатов рекурсивного вызова
    c = d1;
    d = s1 - (a / b) * d1;

    return gcd;
}

// Функция для вычисления c такого, что c * d ≡ 1 (mod m)
int modInverse(int d, int m) {
    int c, temp;
    int gcd = extendedEuclidean(d, m, c, temp);

    if (gcd != 1) {
        // Обратный элемент не существует, если НОД(d, m) != 1
        return -1; // или выберите другой подход к обработке ошибки
    } else {
        // Найденное c будет обратным к d по модулю m
        return (c % m + m) % m;
    }
}

int main() {
    int d, m;
    cout << "Введите число d: ";
    cin >> d;
    cout << "Введите модуль m: ";
    cin >> m;

    int inverse = modInverse(d, m);

    if (inverse == -1) {
        cout << "Обратный элемент для " << d << " по модулю " << m << " не существует." << endl;
    } else {
        cout << "Обратный элемент для " << d << " по модулю " << m << " равен " << inverse << endl;
    }

    return 0;
}
