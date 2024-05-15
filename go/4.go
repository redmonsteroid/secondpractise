package main

import (
	"fmt"
	"math"
)

func isPrime(a int) bool {
	if a == 2 {
		return true
	}
	if a%2 == 0 {
		return false
	}
	for i := 3; i <= int(math.Sqrt(float64(a)))+1; i += 2 {
		if a%i == 0 {
			return false
		}
	}
	return true
}

func modPow(a, b, m int) int {
	res := 1
	for b > 0 {
		if b%2 == 1 {
			res = (res * a) % m
		}
		a = (a * a) % m
		b /= 2
	}
	return res
}

func encryptMessage(message string, key int) string {
	encrypted := ""
	for _, c := range message {
		encrypted += string(c + rune(key))
	}
	return encrypted
}

func decryptMessage(encryptedMessage string, key int) string {
	decrypted := ""
	for _, c := range encryptedMessage {
		decrypted += string(c - rune(key))
	}
	return decrypted
}

func main() {
	var secretAlice, secretBob, osnov, module int
	fmt.Print("Введите секретный ключ Алисы: ")
	fmt.Scan(&secretAlice)
	fmt.Print("Введите секретный ключ Боба: ")
	fmt.Scan(&secretBob)
	fmt.Print("Введите основание: ")
	fmt.Scan(&osnov)
	fmt.Print("Введите модуль для формулы (простое число): ")
	fmt.Scan(&module)

	if !isPrime(module) {
		fmt.Println("Модуль должен быть простым")
		return
	}

	publicAlice := modPow(osnov, secretAlice, module)
	publicBob := modPow(osnov, secretBob, module)
	keyAlice := modPow(publicBob, secretAlice, module)
	keyBob := modPow(publicAlice, secretBob, module)

	if keyAlice != keyBob {
		fmt.Println("Ошибка: ключи не совпадают")
		return
	}

	key := keyAlice

	var message string
	fmt.Print("Введите сообщение для шифрования: ")
	fmt.Scanln(&message)

	encrypted := encryptMessage(message, key)
	fmt.Println("Зашифрованное сообщение:", encrypted)

	decrypted := decryptMessage(encrypted, key)
	fmt.Println("Расшифрованное сообщение:", decrypted)
}
