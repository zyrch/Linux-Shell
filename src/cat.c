#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

// options
// -c - display $ at end of each line
// -n - number all output lines

char* itoa(int val, int base){
    static char buf[32] = {0};
    int i = 30;
    char *x = "0123456789abcdef";
    for(; val && i ; --i, val /= base)
	    buf[i] = x[val % base];
    return &buf[i+1];
}

void cat(char *filename, int _x, int _n) {
    int fd = open(filename,O_RDONLY);
        
    if(fd < 0) { 
	perror("Error"); 
	return;
    } 
    char ch;
    char dollor = '$';
    char prev;
    char space = ' ';
    int first = 1;
    int lineNo = 0;
    while(read(fd,&ch,1))  { 
	if (_n && (prev == '\n' || first)) {
	    first = 0;
	    for (int i = 0; i < 3; ++i) 
		write(STDOUT_FILENO, &space, 1);
	    char *te;
	    te = itoa(++lineNo, 10);
	    write(STDOUT_FILENO, te, strlen(te));
	    write(STDOUT_FILENO, &space, 1);
	}
	if (_x && ch == '\n') {
	    write(STDOUT_FILENO, &dollor, 1);
	}
	prev = ch;
	write(STDOUT_FILENO,&ch,1);
	
    }
    
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
	cat(argv[1], 0, 0);
    }else if (argc > 2) {
	int _x = 0, _n = 0;
	for (int i = 2; i < argc; ++i) {
	    if (argv[i][0] != '-') {
		puts("Incorrect options used");
		exit(EXIT_FAILURE);
	    }else {
		if (argv[i][1] == 'x' && strlen(argv[i]) == 2) {
		    _x = 1;
		}else if (strlen(argv[i]) == 2 && argv[i][1] == 'n') {
		    _n = 1;
		}else {
		    puts("Incorrect options used");
		    exit(EXIT_FAILURE);
		}
	    }
	}
	cat(argv[1], _x, _n);
    }else {
	puts("Incorrect options used");
	exit(EXIT_FAILURE);
    }
}
