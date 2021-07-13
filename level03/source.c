#include <time.h>
#include <stdlib.h>


int decrypt(int n)
{

}

int (*arr_decrypt[21]) (int n) = {
	decrypt
};

int test(int a, int b)
{
	int c; // -0xc(%ebp)
	int tmp;

	c = a - b;
	if (c > 21)
	{
		return (decrypt(rand()));
	}
	// I'm not sure about that, the asm seems to use an array of pointers to functions (0x80489f0) and call a function stored in it but the array only contains references to decrypt?
	// The array seems to be kinda optimised away and what remains could not really be created in C afaik
	arr_decrypt[c](c);
}

int main()
{
	int n; // 0x1c(%esp)

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &n);
	return (test(n, 322424845));
}