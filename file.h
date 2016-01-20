#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct ez_file {

	char **lines;
	size_t line_count;
	size_t length;
	char mode;
	int fd;
	char *name;
};
typedef struct ez_file ez_file;

ez_file* open_file(char *filename, const char mode);
int close_file(ez_file *handle);

size_t file_line_count(int fd);
size_t file_length(int fd);

char **create_file_handle(int fd);
int destroy_file_handle(char **handle);

int print_file(ez_file *handle);

