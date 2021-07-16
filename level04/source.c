#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

int main()
{
	int		wstatus;// 0x1c(%esp)
	char	s[128]; // 0x20(%esp)
	int		n;      // 0xa8(%esp)
	pid_t	pid;    // 0xac(%esp)


	pid = fork();
	memset(s, 0, 128);
	n = 0;
	wstatus = 0;
	if (pid == 0)
	{
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(s);
	}
	else
	{
		loop:
			wait(&wstatus);
			if (WTERMSIG(wstatus))
			{
				if (WIFSIGNALED(wstatus))
				{
					n = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
					if (n != 0xb)
						goto loop;
					puts("no exec() for you");
					kill(pid, 9);
				}
			}
			else
			{
				puts("child is exiting...");
			}
	}
	return (0);
}