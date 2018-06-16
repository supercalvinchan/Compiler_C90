int addition (int a, int b) {
	return a + b;
}

int subtraction(int a, int b) {
	return addition(b, a);
}

int f() {

	return subtraction(20, 10);
}
