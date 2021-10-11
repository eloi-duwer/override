#include <stdio.h>
#include <string.h>

typedef struct	s_msg {
	char		msg[140]; // 0x0(%rax), no offset
	char		username[40]; // 0x8c(%rax)
	size_t		msg_len; // 0xb4(%rax)
}				t_msg;

void secret_backdoor(void)
{
	char str[128]; // -0x80(%rbp)

	fgets(str, 128, stdin /* 0x20171d(%rip) ? */); 
	system(str);
}

void set_msg(t_msg *_m)
{
	t_msg	*msg = _m; // -0x408(%rbp)
	char	str[1024]; // -0x400(%rbp)

	memset(str, 0, 1024);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(str, 1024, stdin /* 0x201630(%rip) is stdin ? */);
	strncpy(msg->msg, str, msg->msg_len);
}

void set_username(t_msg *_m)
{
	int		n; // -0x4(%rbp) ?
	t_msg	*msg = _m; // -0x98(%rbp)
	char	str[128]; // -x090(%rbp)

	memset(str, 0, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(str, 128, stdin /* 0x201595(%rip) is stdin? */);
	n = 0;

	while (n <= 40 && str[n] != '\0')
	{
		msg->username[n] = str[n];
		n++;
	}
	printf(">: Welcome, %s", msg->username);
}

void handle_msg(void)
{
	t_msg msg;  // -0xc0(%rbp)
	msg.msg_len = 140; // -0xc(%rbp) ??? found @ handle_msg + 63

	memset(msg.username, 0, 40);

	set_username(&msg);
	set_msg(&msg);
	puts(">: Msg sent!");
}

int main()
{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
	handle_msg();
	return (0);
}
