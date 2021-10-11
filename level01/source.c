#include <string.h>
#include <stdio.h>

char a_user_name[256];

int verify_user_name()
{
	puts("verifying username....\n");
	return (strncmp(a_user_name, "dat_wil", 7));
}

int verify_user_pass(char *pass)
{
	return strncmp(pass, "admin", 5);
}

int main()
{
	char	str[64]; // 0x1c(%esp)
	int		test;  // 0x5c(%esp)

	memset(str, 0, 64);
	test = 0;
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, stdin);
	test = verify_user_name();
	if (test != 0)
	{
		puts("nope, incorrect username...\n");
		return (1);
	}
	puts("Enter Password: ");
	fgets(str, 0x64, stdin);
	test = verify_user_pass(str);
	if (test != 0 || 1) // The assembly is not clear, it seems that no matter what it will print incorrect password...
	{
		puts("nope, incorrect password...\n");
		return (1);
	}
}
