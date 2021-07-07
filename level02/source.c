#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE	*fd;		// -0x8(%rbp)
	size_t	ret_read;	// -0xc(%rbp)
	char	str[100];	// -0x70(%rbp)
	char	pass[41];	// -0xa0(%rbp)
	char	str3[100];	// -0x110(%rbp)

	memset(str, 0, 100);
	memset(pass, 0, 41);
	memset(str3, 0, 100);
	fd = 0;
	ret_read = 0;
	fd = fopen("/home/users/level03/.pass", "r");
	if (fd == 0)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	ret_read = fread(pass, 1, 41, fd);
	pass[strcspn(pass, "\n")] = '\0';
	if (ret_read != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr); // The assembly seems to call it two times? idk why
		exit(1);
	}
	
}