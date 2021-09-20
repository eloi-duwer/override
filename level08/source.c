#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *backup_folder = "./backups/";

void	log_wrapper(
	FILE *file, // -0x118(%rbp)
	char *msg, // -0x120(%rbp)
	char *complement // -0x128(%rbp)
)
{
	char	buff[255]; // -0x110(%rbp)

	strcpy(buff, msg);
	snprintf(buff + strlen(buff), 254 - strlen(buff), complement);
	buff[strcspn(buff, "\n")] = '\0';
	fprintf(file, "LOG: %s\n", buff);
}

int		main(int argc, char **argv)
{
	char	**av = argv;	// -0xa0(%rbp)
	int		ac = argc;		// -0x94(%rbp)
	FILE	*backup_log;	// -0x88(%rbp)
	FILE	*backup_file;	// -0x80(%rbp)
	int		fd;				// -0x78(%rbp)
	char	c;				// -0x71(%rbp)
	char	path[100];		// -0x70(%rbp)

	if (argc == 2)
		printf("Usage: %s filename\n", argv[0]);
	backup_log = fopen("./backups/.log", "w");
	if (backup_log == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(backup_log, "Starting back up: ", argv[1]);
	backup_file = fopen(argv[1], "r");
	if (backup_file == NULL)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	strcpy(path, backup_folder);
	strncat(path, argv[1], 99 - strlen(backup_folder));
	fd = open(path, O_EXCL | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); // Read/write for user and group
	if (fd == 0)
	{
		printf("ERROR: Failed to open %s%s\n", backup_folder, argv[1]);
		exit(1);
	}
	while ((c = fgetc(backup_file)) != 0xFF)
	{
		write(fd, &c, 1);
	}
	log_wrapper(backup_log, "Finished back up ", argv[1]);
	fclose(backup_file);
	close(fd);
	return (0);
}
