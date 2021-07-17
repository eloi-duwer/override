#include <stdio.h>


int main()
{
	char	str[100]; // 0x28(%esp)
	int		i;        // 0x8c(%esp)

	i = 0;
	fgets(str, 100, stdin);
	i = 0;
	while (i < strlen(str))
	{
		if (str[i] > 64)
		{
			if (str[i] <= 90)
			{
				str[i] ^= 32;
			}
		}
	}
	printf(str);
	exit(0);
}