package main

import "fmt"

// Функция для вычисления НОД и коэффициентов x, y
func extendedEuclidean(a, b int) (int, int, int) {
	if b == 0 {
		return a, 1, 0
	}

	gcd, x1, y1 := extendedEuclidean(b, a%b)
	x := y1
	y := x1 - (a/b)*y1
	return gcd, x, y
}

// Функция для вычисления взаимнообратного числа s^-1 mod m
func modInverse(s, m int) int {
	gcd, x, _ := extendedEuclidean(s, m)

	if gcd != 1 {
		// Обратное число не существует, если s и m не взаимно просты
		return -1 // или другое значение, указывающее на ошибку
	} else {
		// Найдем положительное значение x, соответствующее s^-1 mod m
		return (x%m + m) % m
	}
}

func main() {
	var c, m int
	fmt.Print("Введите число c: ")
	fmt.Scanln(&c)
	fmt.Print("Введите модуль m: ")
	fmt.Scanln(&m)
	result := modInverse(c, m)

	if result == -1 {
		fmt.Printf("Обратного числа для %d mod %d не существует (числа не взаимно просты)\n", c, m)
	} else {
		fmt.Printf("Обратное число для %d mod %d равно %d\n", c, m, result)
	}
}
