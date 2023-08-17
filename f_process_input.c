#include "team_fa_lib.h"

/**
* free_tokens -This function help free tokens.
*
* @tokens: string parameter
* Return: Always void (success).
*/

void free_tokens(char **tokens)
{
int idx;
for (idx = 0; tokens[idx] != NULL; idx++)
{
free(tokens[idx]);
}
}

/**
* handle_exit_command -This function help handle exit.
*
* @input_tokens: string parameter
* Return: Always void (success).
*/
void handle_exit_command(char **input_tokens)
{
if (_strcmp(input_tokens[0], "exit") == 0)
{
process_exit_command();
}
}

/**
* execute_command -This function execute command.
*
* @input_tokens: string parameter
* Return: Always void (success).
*/
void execute_command(char **input_tokens)
{
pid_t processID = fork();

if (processID == -1)
{
perror("Fork error");
exit(EXIT_FAILURE);
}
else if (processID == 0)
{
/* child process */
run_executable(input_tokens);
}
else
{
/* parent process */
waitpid(processID, NULL, 0); /* wait for child to finish */
/* free memory allocated for tokens */
free_tokens(input_tokens);
}
}

/**
* process_user_input -This function process user input.
*
* @void: void parameter
* Return: Always void (success).
*/
void process_user_input(void)
{
char user_input[MAX_INPUT_LENGTH];
char *input_tokens[MAX_INPUT_LENGTH / 2 + 1];

while (1)
{
_printf("#team_fa$ ");

if (fgets(user_input, sizeof(user_input), stdin) == NULL)
{
/* EOF or error */
break;
}

user_input[strcspn(user_input, "\n")] = '\0';
tokenize_input(user_input, input_tokens);

if (input_tokens[0] == NULL)
{
/* Empty input, prompt again */
continue;
}

handle_exit_command(input_tokens);
execute_command(input_tokens);
}
}