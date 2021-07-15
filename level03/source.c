#include <time.h>
#include <stdlib.h>

int decrypt(int n)
{
	char str[] = "Q}|u`sfg~sf{}|a3"; // -0x1d(%ebp)
	size_t len; // -0x24(%ebp)
	size_t i; // -0x28(%ebp)

	len = strlen(str);
	i = 0;
	while (i < len)
	{
		str[i] = n ^ str[i];
		i++;
	}
	if (strncmp("Congratulations!", str, 17) == 0)
	{
		system("/bin/sh");
	}
	else
	{
		puts("\nInvalid Password");
	}
	return ;
}

int (*arr_decrypt[21]) (int n) = {decrypt};

int test(int a, int b)
{
	int	c; // -0xc(%ebp)
	int	tmp;

	c = b - a;
	if (c > 21)
	{
		return (decrypt(rand()));
	}
	// I'm not sure about that, the asm seems to use an array of pointers to functions (0x80489f0) and call a function stored in it but the array only contains references to decrypt?
	// The array seems to be kinda optimised away and what remains could not really be created in C afaik
	// It might be some obfuscation techniques, I think the levels comes from another project, the start of the main and get_unum / clear_stdin / prog_timeout funcs (in gdb info func)
	// seems to come from https://github.com/RPISEC/MBE/blob/master/include/utils.h
	arr_decrypt[c](c);
}

int main()
{
	int	n; // 0x1c(%esp)

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &n);
	return (test(n, 322424845));
}