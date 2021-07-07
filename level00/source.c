#include <stdio.h>

int main()
{
	int	i; // 0x1c(%esp)

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &i);
	if (i == 5276)
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
		return (0);
	}
	else
	{
		puts("\nInvalid Password!");
		return (1);
	}
}