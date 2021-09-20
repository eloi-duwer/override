#include <string.h>
#include <stdio.h>

// clear_argv, clear_stdin and get_unum are from https://github.com/RPISEC/MBE/blob/master/include/utils.h
// I heavily suspect parts of this project comes from there
/* clear argv to avoid shellcode */
#define clear_argv(_argv) \
    for (; *_argv; ++_argv) { \
        memset(*_argv, 0, strlen(*_argv)); \
    }
#define clear_envp(_envp) clear_argv(_envp)

/* clears stdin up until newline */
void clear_stdin(void)
{
    char x = 0;
    while(1)
    {
        x = getchar();
        if(x == '\n' || x == EOF)
            break;
    }
}

/* gets a number from stdin and cleans up after itself */
unsigned int get_unum(void)
{
    unsigned int res = 0;
    fflush(stdout);
    scanf("%u", &res);
    clear_stdin();
    return res;
}

int read_number(unsigned int *data) {
	unsigned int index = 0; // -0xc(%ebp)
	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, data[index]);
	return (0);
}

int store_number(unsigned int *data)
{
	unsigned int nb = 0; // -0x10(%ebp)
	unsigned int index = 0; // -0xc(%ebp)

	printf(" Number: ");
	nb = get_unum();
	printf(" Index: ");
	index = get_unum();
	if ((index / 3) * 3 != index || nb >> 24 == 183 ) /* equivalent to to nb % 3 == 0 || nb >= 3070230528 ? */
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	data[index] = nb;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char			*s = *argv; // 0x1c(%esp)
	char			*e = *envp; // 0x18(%esp)
	unsigned int	data[100]; // 0x24(%esp)
	int				ret = 0; // 0x1b4(%esp)
	char			input[20] = {0}; // 0x1b8(%esp)
	
	memset(data, 0, 100 * sizeof(unsigned int));
	clear_argv(argv);
	clear_argv(envp);
	puts("----------------------------------------------------\n\
  Welcome to wil's crappy number storage service!\n\
----------------------------------------------------\n\
 Commands:\n\
    store - store a number into the data storage\n\
    read  - read a number from the data storage\n\
    quit  - exit the program\n\
----------------------------------------------------\n\
   wil has reserved some storage :>\n\
----------------------------------------------------\n");
	while(1) {
		printf("Input command: ");
		ret = 1;
		fgets(input, 20, stdin);
		input[strlen(input)] = 0; // ??
		if (strncmp(input, "store", 5) == 0)
			ret = store_number(data);
		else if (strncmp(input, "read", 4) == 0)
			ret = read_number(data);
		else if (strncmp(input, "quit", 4) == 0)
			break;
		if (ret != 0)
		{
			printf(" Failed to do %s command\n", input);
		}
		else
		{
			printf(" Completed %s command successfully\n", input);
		}
		memset(input, 0, 20);
	}
	return (0);
}
