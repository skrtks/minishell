#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "libft/libft.h"

int main(void)
{
	int   	ret;
	int		retry;
	char	*buffer;

	// TODO: Turn off ctrl-c / ctrl-z / ctrl-d to prevent user exiting shell

	while (1)
	{
		write(1, "> $ ", 4);

		retry = 1;
		while (retry == 1)
		{
			retry = 0;
			ret = get_next_line(0, &buffer);
			if (ret <= 0 && errno == EINTR)
			{
				retry = 1; /* Try reading again */
				errno = 0;
			}
		}

		printf("+++ %s +++\n", buffer); // Remove

		// TODO: lexic analysis
		// TODO: Parse result of lexic analysis into "syntax tree/command table"
		// TODO: Execute "syntax tree/command table"
	}
	// TODO: Clean everything before returning
	return 0;
}
