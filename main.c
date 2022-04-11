#include "main.h"

/**
 * main - Main function where everything starts
 *
 * @argc: Count the number of things that I pass
 * on the command line when I run this program
 * @argv: Array that contains the string values
 * of things that were entered on the command line
 * when I run this program
 *
 * Return: Always 0.
 */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char **arguments = NULL;
	char *input_stdin = NULL;
	int status_return = 1;
	size_t size = 0;
	ssize_t n = 0;

	while (status_return)
	{
		size = 0;

		status_return = isatty(STDIN_FILENO);

		if (status_return)
			write(STDOUT_FILENO, "#Shell_CL$ ", 11);


		n = getline(&input_stdin, &size, stdin);

		if (n == -1)
		{
			free(input_stdin);
			break;
		}

		if (validate_spaces(input_stdin))
		{
			free(input_stdin);
			continue;
		}

		arguments = hsh_tokenizer(input_stdin);
		if (*arguments[0] == '\0')
			continue;
		status_return = hsh_execute_builtins(arguments, input_stdin, argv);

		free(input_stdin);
		free(arguments);
	}
	return (0);
}