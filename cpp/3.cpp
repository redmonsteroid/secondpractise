#include <iostream>
using namespace std;
// Функция для вычисления НОД и коэффициентов x, y
int extendedEuclidean(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedEuclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Функция для вычисления взаимнообратного числа s^-1 mod m
int modInverse(int s, int m) {
    int x, y;
    int gcd = extendedEuclidean(s, m, x, y);

    if (gcd != 1) {
        // Обратное число не существует, если s и m не взаимно просты
        return -1; // или другое значение, указывающее на ошибку
    } else {
        // Найдем положительное значение x, соответствующее s^-1 mod m
        x = (x % m + m) % m;
        return x;
    }
}

int main() {
    system("chcp 65001");
    int c, m;
    cout << "Введите число c: ";
    cin >> c;
    cout << "Введите модуль m: ";
    cin >> m;
    int result = modInverse(c, m);

    if (result == -1) {
        cout << "Обратного числа для " << c << " mod " << m << " не существует (числа не взаимно просты)\n";
    } else {
       cout << "Обратное число для " << c << " mod " << m << " равно " << result << "\n";
    }

    return 0;
}
