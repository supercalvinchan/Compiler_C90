int f() {
	int i, sum = 0, e, f;
	int a[9] = {5,-2,3, 0, 6, 9, 12, 20, 7};
	for (i = 0; i < 9; i++) {
		sum = sum + a[i];
		if (a[i] > 0)
		{
		e += a[i];
	}
		if (a[i] < 0)
		{
			f += a[i];
		}
	}
	return sum;
}
