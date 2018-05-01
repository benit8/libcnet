#include "cnet/socket.h"

int main(void)
{
	socket_t *socket = socket_bare(TCP);

	socket_destroy(socket);
	return (0);
}