#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

// options
// -p : prompt before performing removal
// -v : explain what is been done
void _mkdir(char *path, int _p, int _v) {
    
    int va = mkdir(path, 0777);
    
    if (va == -1) {
	if (errno == ENOENT && _p) {
	    char *tempath = (char *) calloc(512, sizeof(char));
	    int si = 0;
	    
	    for (int i = 0; i < strlen(path); ++i) {
		if (path[i] == '/') {
		    int va2 = mkdir(tempath, 0777);
		    //~ printf
		    if (va2 == -1) {
			if (errno != EEXIST || !_p) {
			    perror("Error Occured");
			}
		    }
		    
		    if (_v) {
			printf("mkdir : directory %s created\n", tempath);
		    }
		}
		tempath[si++] = path[i];
	    }
	}else if (errno != EEXIST || !_p) {
	    perror("Error Occured");
	}else if (errno == EEXIST && _p) {
	    goto x;
	}
    }else {
	x:
	printf("mkdir : directory %s created\n", path);
    }
}

int main(int argc, char *argv[]) { 
   
    if (argc == 2) {
	_mkdir(argv[1], 0, 0);
    }else if (argc > 2) {
	int _p = 0, _v = 0;
	for (int i = 2; i < argc; ++i) {
	    if (argv[i][0] != '-') {
		puts("Incorrect options used");
		exit(EXIT_FAILURE);
	    }else {
		if (argv[i][1] == 'p' && strlen(argv[i]) == 2) {
		    _p = 1;
		}else if (strlen(argv[i]) == 2 && argv[i][1] == 'v') {
		    _v = 1;
		}else {
		    puts("Incorrect options used");
		    exit(EXIT_FAILURE);
		}
	    }
	}
	_mkdir(argv[1], _p, _v);
    }else {
	puts("Incorrect options used");
	exit(EXIT_FAILURE);
    }
       
}
