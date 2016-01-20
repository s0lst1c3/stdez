#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_WORKERS 4
#define FILENAME "test.txt"

void attempt(char *password) {

	printf("%s", password);

	free(password);
}

void error_handler(const char *msg) {

	fprintf(stderr, "[!] %s", msg);
	exit(1);
}

size_t file_length(int fd) {
	
	size_t bytes_read;
	size_t line_count;
	char next_char[1];

	line_count = 0;
	while((bytes_read = read(fd, &next_char, 1)) > 0) {

		if (next_char[0] == '\n') {

			line_count++;
		}
	}

	lseek(fd, 0, SEEK_SET);

	return line_count;
}

char **create_file_handle(int fd) {

	size_t line_count, bytes_read, line_length, handle_index;
	char next_char[1];
	char *line;
	char **file_handle; 

	bytes_read = line_length = handle_index = 0;

	line_count = file_length(fd);
	file_handle = (char**)malloc(sizeof(char*) * line_count+1);

	while((bytes_read = read(fd, &next_char, 1)) > 0) {

		if (next_char[0] == '\n') {

			line_length;
			lseek(fd, -1 * line_length-1, SEEK_CUR);
		
			line = (char*)malloc(sizeof(char) * line_length + 1);
			read(fd, line, line_length + 1);
			line[line_length] = 0x00;

			file_handle[handle_index++] = line;
			
			line_length = 0;	
		}
		else {
				
			line_length++;
		}
	}

	return file_handle;
}

int main(int argc, char **argv, char **envp) {


	//pthread_t workers[MAX_WORKERS] = 0x00;

	// open input file
	int fd = open(FILENAME, O_RDONLY);
	if (fd < 0 ) {
		error_handler("Unable to open file.");
	}
		
	char **file_handle = create_file_handle(fd);

	int i;
	for( i = 0; file_handle[i] != 0x00; i++) {

		printf("%s\n", file_handle[i]);
	}
	/*
	int i;
	for(i = 0; i < MAX_WORKERS; i++) {

			
	}
	*/

	close(fd);

	return 0;
}
