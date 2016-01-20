#include "file.h"
#include "aux.h"

size_t file_line_count(int fd) {
	
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

size_t file_length(int fd) {
	
	size_t bytes_read;
	size_t length;
	char next_char[1];

	
	length = 0;
	while((bytes_read = read(fd, &next_char, 1)) > 0) {

		length++;
	}

	lseek(fd, 0, SEEK_SET);

	return length;
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

int destroy_file_handle(char **handle) {

	if ( handle == 0x00 ) {

		return -1;
	}

	int i;
	for ( i = 0; handle[i] != 0x00; i++) {

		free(handle[i]);
	}

	free(handle);
	return 0;
}

int print_file(ez_file *handle) {

	if ( handle->lines == 0x00 ) {

		return -1;
	}
	
	
	int i;
	for( i = 0; handle->lines[i] != 0x00; i++) {

		printf("%s\n", handle->lines[i]);
	}

	return 0;
}

ez_file* open_file(char *filename, const char mode) {

	ez_file *handle;

	handle = (ez_file*)malloc(sizeof(ez_file));

	handle->name = filename;
	handle->mode = mode;

	switch(mode) {
	case 'r':
		handle->fd = open(filename, O_RDONLY);
		break;
	case 'w':
		break;
	default:
		error_handler("Invalid mode passed to open_file()");
	}
	if (handle->fd < 0) {
		free(handle);
		error_handler("Unable to open file.");
	}

	handle->line_count = file_line_count(handle->fd);
	handle->length = file_length(handle->fd);
	handle->lines = create_file_handle(handle->fd);

	return handle;
}

int close_file(ez_file *handle) {
	
	destroy_file_handle(handle->lines);
	free(handle);
}
