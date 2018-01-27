#define _GNU_SOURCE

#include "../kernel/main.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	char name[100];
	int fd;

	snprintf(name, sizeof(name), "/dev/%s", MODULE_NAME);

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("unable to open dev");
		return 0;
	}

	if (ioctl(fd, STOP_DIVBYZERO, NULL) != 0)
	{
		perror("ioctl COUNT_DIVBYZERO error");
		abort();
	}

	close(fd);
	return 0;
}
