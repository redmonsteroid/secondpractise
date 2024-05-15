#include <iostream>
#include <cmath>
#include <string>
using namespace std;

bool isPrime (int a){ // проверка на простоту 
    if (a == 2) return true;
    if (a % 2 == 0) return false;
    for (int i = 3; i <= sqrt(a) + 1 ; i += 2){
        if (a % i == 0)  return false;
    }
    return true;
}

int modPow (int a, int b, int m){
    int res = 1;
    while (b > 0){
        if (b % 2 == 1) res = (res * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return res;
}

string encrypt_message(const string& message, int key) {
    string encrypted_message = "";
    for (char c : message) {
        encrypted_message += static_cast<char>(c + key);
    }
    return encrypted_message;
}

string decrypt_message(const string& encrypted_message, int key) {
    string decrypted_message = "";
    for (char c : encrypted_message) {
        decrypted_message += static_cast<char>(c - key);
    }
    return decrypted_message;
}

int main () {
    system("chcp 65001");
    int secretAlice, secretBob, osnov, module;
    cout << "Введите секретный ключ Алисы: "; cin >> secretAlice;
    cout << "Введите секретный ключ Боба: "; cin >> secretBob;
    cout << "Введите основание: "; cin >> osnov;
    cout << "Введите модуль для формулы (простое число): "; cin >> module;
    if (!isPrime(module)){
        cout << "Модуль должен быть простым" << endl;
        return -1;
    }
    int publicAlice = modPow( osnov, secretAlice, module); // генерация публичного ключа (общее основание) ^ (секрет каждого) mod (общее простое число)
    int publicBob = modPow( osnov, secretBob, module);
    int keyAlice = modPow( publicBob, secretAlice, module); // итоговый общий ключ
    int keyBob = modPow( publicAlice, secretBob, module);// (полученный публичный ключ)^(секрет каждого ) mod (общее простое число)
    int key = 0;
    if (keyAlice == keyBob){
        key = keyAlice;
    }
    string message;
    cin.ignore(); // Очистка буфера ввода
    cout << "Введите сообщение для шифрования: ";
    getline(cin, message);


    string encrypted = encrypt_message(message, key);
    cout << "Зашифрованное сообщение: " << encrypted << endl;

    string decrypted = decrypt_message(encrypted, key);
    cout << "Расшифрованное сообщение: " << decrypted << endl;

    return 0;

}