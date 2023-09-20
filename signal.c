#include "simple_shell_lib.h"

/**
 * handle_signal - Handle the SIGINT (Ctrl-C) signal.
 * @signum: The signal number (SIGINT).
 *
 * This function is called when the SIGINT signal (Ctrl-C) is received.
 * It prints a message indicating that Ctrl-C was received and provides
 * guidance on how to quit the shell.
 */
void handle_signal(int signum)
{
	printf("\nCtrl-C (SIGINT) received. Use 'exit' to quit the shell.\n");
}
