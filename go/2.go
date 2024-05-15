package main

import "fmt"

// extendedEuclidean implements the extended Euclidean algorithm
func extendedEuclidean(a, b int) (int, int, int) {
	if b == 0 {
		return a, 1, 0
	}

	gcd, s1, d1 := extendedEuclidean(b, a%b)

	// Update c and d based on the results of the recursive call
	c := d1
	d := s1 - (a/b)*d1

	return gcd, c, d
}

// modInverse calculates c such that c*d ≡ 1 (mod m)
func modInverse(d, m int) int {
	gcd, c, _ := extendedEuclidean(d, m)

	if gcd != 1 {
		// Inverse element does not exist if gcd(d, m) != 1
		return -1 // or choose another approach to handle the error
	} else {
		// The found c will be the inverse of d modulo m
		return (c%m + m) % m
	}
}

func main() {
	var d, m int
	fmt.Print("Enter the number d: ")
	fmt.Scanln(&d)
	fmt.Print("Enter the modulus m: ")
	fmt.Scanln(&m)

	inverse := modInverse(d, m)

	if inverse == -1 {
		fmt.Printf("Inverse element for %d modulo %d does not exist.\n", d, m)
	} else {
		fmt.Printf("Inverse element for %d modulo %d is %d\n", d, m, inverse)
	}
}
