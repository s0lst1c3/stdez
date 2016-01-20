void error_handler(const char *msg) {

	fprintf(stderr, "[!] %s", msg);
	exit(1);
}
