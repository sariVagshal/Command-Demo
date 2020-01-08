#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 100 /* length of string allowed */


void type_prompt()
{
	printf("\nstart@ubuntu$ ");
}

void read_command(char* str, char * params[])
{
	int i=0;

	scanf("%[^\n]s",str);
	getchar();

	params[i] = strtok(str, " ");
	while( params[i] != NULL )
	{
		i++;
		params[i] = strtok(NULL, " ");
	}
	params[++i] = NULL;
}

void run()
{
	int status;
	char str[512];
	char * params[64] = {0};
		
	while(1)
	{
		type_prompt();
		read_command(str, params);
		
		if (strcmp(params[0],"exit") == 0)
		{
			execvp(params[0], params);
			return;
		}
		if(fork() != 0)
		{
			/* parent code */
			waitpid(-1, &status, 0);
		}
		else
		{
			/* child code */
			execvp(params[0], params);
			return;
		}
		
	}
}


int main()
{
	run();
	return 0;
}

