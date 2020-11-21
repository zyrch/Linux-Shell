#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

// options
// -i : prompt before performing removal
// -v : explain what is been done
void _rm(char *filename, int _i, int _v) {
    
    if (opendir(filename) != NULL) {
	printf("Cannot remove '%s' : Is a directory\n", filename);
	return;
    }else {
	if (_i) {
	    printf("Remove '%s' Enter y for Yes : ", filename);
	    char out;
	    scanf("%c", &out);
	    if (out != 'y') {
		return;
	    }
	}
	
	int va = remove(filename);
	if (va == -1) {
	    perror("Error");
	}else if (_v) {
	    printf("File '%s' successfully removed\n", filename);
	}
    }
}

int main(int argc, char *argv[]) {

    if (argc == 2) {
	_rm(argv[1], 0, 0);
    }else if (argc > 2) {
	int _i = 0, _v = 0;
	for (int i = 2; i < argc; ++i) {
	    if (argv[i][0] != '-') {
		puts("Incorrect options used");
		exit(EXIT_FAILURE);
	    }else {
		if (argv[i][1] == 'i' && strlen(argv[i]) == 2) {
		    _i = 1;
		}else if (strlen(argv[i]) == 2 && argv[i][1] == 'v') {
		    _v = 1;
		}else {
		    puts("Incorrect options used");
		    exit(EXIT_FAILURE);
		}
	    }
	}
	_rm(argv[1], _i, _v);
    }else {
	puts("Incorrect options used");
	exit(EXIT_FAILURE);
    }

}
