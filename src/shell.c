#include "shell.h"
#include "syscall.h"
#include "fb_cursor.h"
#include "string.h"
#include "malloc.h"
#include "shell_commands.h"
#include "config.h"
#include "hw.h"
#include "fb_cursor.h"

typedef void (command_t) (char**);


static void clean_command(char * cmd)
{
	int i = 0;
	while(cmd[i] != '\n')
	{
		i++;
	}
	cmd[i] = '\0';

}

static char** parse_command(char* cmd, int* argc)
{
	// TODO parse each argument into a different pointer. not all args in args[1]
	clean_command(cmd);
	char* space = strtok(cmd, ' ');
	space++;

	char** args = (char**) gmalloc(sizeof(char*) * 2);
	args[0] = cmd;
	args[1] = space;

	*argc = 2;

	return args;
}

static command_t* find_command(char* cmd_name)
{
	if (strcmp(cmd_name, "echo") == 0)
	{
		return do_echo;
	}
	else if (strcmp(cmd_name, "ps") == 0)
	{
		return do_ps;
	}
	else if (strcmp(cmd_name, "fork") == 0)
	{
		return do_fork;
	}
	else if (strcmp(cmd_name, "music") == 0)
	{
		return do_music;
	}

	return NULL;
}


int start_shell()
{
	//while (1)
	fb_prompt();

	// Read line
	//char* cmd_line = "fork\n";
	//char* cmd_line = "ps\n";
	char* cmd_line = "echo Hello world\n";
	fb_print_text(cmd_line);

	int argc;

	char** args = parse_command(cmd_line, &argc);

	command_t* command = find_command(args[0]);
	if (command == NULL)
	{
		fb_print_text("Command not found\n");
	}
	else
	{
		int pid = sys_fork();
		if (pid == 0)
		{
			command(args+1); // skip command name
			sys_exit(0);
		}
		else
		{
			int cmd_status;
			sys_waitpid(pid, &cmd_status);
			// TODO fill shell variable of last return code: $?
		}
	}

	return 0;
}

