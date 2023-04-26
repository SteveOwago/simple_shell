#include "main.h"

/**
 * get_signalint - Handle the crtl + c call in prompt
 * @signal: signalnal handler
 */
void get_signalint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
