
#include <sys/ioctl.h>
	ioctl(1, TIOCGWINSZ, &window);
	if (arg_len == window.ws_col)
		return (0);
	else if (arg_len > window.ws_col)
		return (arg_len);
	else
