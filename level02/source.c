#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE	*fd;			// -0x8(%rbp)
	size_t	ret_read;		// -0xc(%rbp)
	char	username[100];	// -0x70(%rbp)
	char	pass_file[41];	// -0xa0(%rbp)
	char	pass[100];		// -0x110(%rbp)

	memset(username, 0, 100);
	memset(pass_file, 0, 41);
	memset(pass, 0, 100);
	fd = 0;
	ret_read = 0;
	fd = fopen("/home/users/level03/.pass", "r");
	if (fd == 0)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	ret_read = fread(pass_file, 1, 41, fd);
	pass_file[strcspn(pass_file, "\n")] = '\0';
	if (ret_read != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr); // The assembly seems to call it two times? idk why
		exit(1);
	}
	fclose(fd);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(username, 100, stdin);
	username[strcspn(username, "\n")] = '\0';
	printf("--[ Password: ");
	fgets(pass, 100, stdin);
	pass[strcspn(pass, "\n")] = '\0';
	puts("*****************************************");
	if (strncmp(pass, pass_file, 41) != 0)
	{
		printf(username);
		puts(" does not have access!");
		exit(1);
	}
	printf("Greetings, %s!\n", username);
	system("/bin/sh");
	return (0);
}