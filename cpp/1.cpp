#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int NOD (int a, int b){ // наибольший общий делитель 
    if (b == 0) return a; 
    return NOD(b, a % b); // ищем рекурсивно 
} // if b != 0             {NOD(b, a) == NOD(b, a % b)}

int modPow (int basis, int power, int modP) { // basis^power mod p
    if (power == 0) {
        return 1;
    }
    int z = modPow(basis % modP, power / 2, modP) % modP;
    if (power % 2 == 0) {
        return (z * z) % modP;
    }
    else {
        return ((basis % modP) * ((z * z) % modP)) % modP;
    }
}

bool isPrime (int a){ // проверка на простоту 
    if (a == 2) return true;
    if (a % 2 == 0) return false;
    for (int i = 3; i <= sqrt(a) + 1 ; i += 2){
        if (a % i == 0)  return false;
    }
    return true;
}

int eiler (int p) {
    int result = p;
    for (int i = 2; i * i <= p; i++) { //проходимся до корня из числа
        if (p % i == 0) { //если число разделилось на i, то мы уменьшаем р на i так как все числа,
            while (p % i == 0) { // которые делятся на i не являются взаимно простыми с p
                p /= i;
            }
            result -= result / i; // из результата вычитаем количество чисел result/i
        }
    }
    if (p > 1) { // если п - простое число, которое не разделилось, то оно простое и результатом
        result -= result / p; // функции будет р-1
    }

    return result;
}

pair<int, int> remainder(int& a, int& x, int& p) {
    pair<int, int> ost = {1, 1};

    // Вычисляем a^x mod p
    ost.first = modPow(a, x, p);

    // Переводим степень x в двоичную систему
    int logByNumber = log2(x);
    vector<int> binary;
    int x2 = x;
    while (x2 > 0) {
        binary.push_back(x2 % 2);
        x2 /= 2;
    }

    // Вычисляем произведение a^(2^i) mod p для каждого бита в двоичной записи x
    int resultForPrime = 1;
    for (int i = 0; i <= logByNumber; i++) {
        if (binary[i] == 1) {
            int oneDegree = pow(2, i);
            resultForPrime *= modPow(a, oneDegree, p);
        }
    }
    // Остаток от произведения по модулю p
    ost.second = resultForPrime % p;

    return ost;  // Возвращаем пару значений: остаток от a^x mod p и остаток от разложения степени
}

int main () {
    system("chcp 65001");
    int osnov, stepen,  module;
    cout << "enter the base, degree and modulus" << endl;
    cin >> osnov >> stepen >> module;
    bool zahod = false;
    if (osnov < module && stepen == (module - 1) && (isPrime(module) == true)) { // Проверяем условия для применения теоремы Ферма: osnov^stepen mod module = 1
    cout << "Согласно теореме Ферма получим: " << osnov << "^" << stepen << " mod " << module << " = 1" << endl;
    // Вычисляем остатки через функцию remainder
    pair<int, int> ost = remainder(osnov, stepen, module);
    cout << "Проверим, используя логарифм: " << ost.second << endl;
    zahod = true; // Устанавливаем флаг, что условие выполнилось
}

if (NOD(osnov, module) == 1 && stepen == eiler(module)) {
    // Проверяем условия для применения теоремы Эйлера: osnov и module взаимно просты, и stepen = φ(module)
    zahod = true;
    cout << "Согласно теореме Эйлера получим: " << osnov << "^" << stepen << " mod " << module << " = 1" << endl;
    // Вычисляем остатки через функцию remainder
    pair<int, int> ost = remainder(osnov, stepen, module);
    cout << "Проверим, используя логарифм: " << ost.second << endl;
}

if (zahod == false) {
    // Если ни одно из условий не выполнилось, вычисляем степень по функции Эйлера и используем modPow
    stepen = eiler(module);
    int result = modPow(osnov, stepen, module);
    // Вычисляем остатки через функцию remainder
    pair<int, int> ost = remainder(osnov, stepen, module);
    cout << "Результат, используя свойства сравнений = " << ost.first << " и результат, используя логарифм = " << ost.second << endl;
}

// Ввод второго числа для сравнения
int osnov2 = 0, stepen2 = 0;
cout << "Введите основание второго числа, которое будете сравнивать по модулю: ";
cin >> osnov2;
cout << "Введите степень числа второго числа, которое будете сравнивать по модулю: ";
cin >> stepen2;

// Сравнение результатов по модулю
if (modPow(osnov, stepen, module) > modPow(osnov2, stepen2, module)) {
    cout << osnov << "^" << stepen << " mod " << module << " > " << osnov2 << "^" << stepen2 << " mod " << module << endl;
} else if (modPow(osnov, stepen, module) < modPow(osnov2, stepen2, module)) {
    cout << osnov << "^" << stepen << " mod " << module << " < " << osnov2 << "^" << stepen2 << " mod " << module << endl;
} else {
    cout << osnov << "^" << stepen << " mod " << module << " = " << osnov2 << "^" << stepen2 << " mod " << module << endl;
}

return 0;

}