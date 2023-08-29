#include "test.h"

void test_add(int a, int b, int expect)
{
	int result = add(a, b);

	if (result == expect)
		printf("%s\n", GREEN"OK"RESET);
	else
		printf("%s value %d, expect %d\n", RED"KO"RESET, a + b, expect);
}

int main(void)
{
	test_add(2, 3, 5);
	test_add(2, 3, 6);
	test_add(2, 6, 8);
	// test_add(2, 3, 5);
	// test_add(2, 3, 5);
	return (0);
}
