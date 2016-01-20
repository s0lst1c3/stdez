#include <stdio.h>
#include <stdlib.h>

#include "file.h"

#define FILENAME "test.txt"

int main(int argc, char **argv, char **envp) {

	ez_file *fd = open_file(FILENAME, 'r');
	
	print_file(fd);

	close_file(fd);

	return 0;
}
