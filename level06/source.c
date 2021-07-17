#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial)
{
	size_t			len;  // -0xc(%ebp)
	unsigned int	hash; // -0x10(%ebp)
	unsigned int	i;    // -0x14(%ebp)

	login[strcspn(login, "\n")] = '\0';
	len = strnlen(login, 32);
	if (len <= 5)
		return (1);
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
	{
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m'---------------------------'");
		return (1);
	}
	hash = login[3] ^ 0x1337 + 0x5eeded;
	i = 0;
	while (i < len)
	{
		if (login[i] <= 0x1f)
			return (1);
		hash += hash - ((((((login[i] ^ hash)
			* 2284010283)
			- 2284010283)
			<< 1)
			+ 2284010283)
			<< 10)
			* 1337;
		i++;
	}
	if (serial == hash)
		return (0);
	return (1);
}

int main()
{
	unsigned int	serial;    //    0x28(%esp)
	char			login[32]; // 0x2c(%esp)

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(login, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &serial);
	if (auth(login, serial) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return (0);
	}
	return (1);
}
