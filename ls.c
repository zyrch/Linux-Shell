#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// options 
// -a - do not ignore entries starting with .
// -al - use a long listing format and show hidden files
void ls(int _a, int _al) {
    
    struct dirent *myfile;
    struct stat mystat;
    DIR *dir = opendir(".");
    if (!dir) {
	perror("Unable to open directory");
	exit(EXIT_FAILURE);
    }
    char buf[512];
    while((myfile = readdir(dir)) != NULL){
	if (!(_a || _al) && myfile->d_name[0] == '.') {
	    continue;
	}
	if (_al) {
	    sprintf(buf, "%s/%s", ".", myfile->d_name);
	    stat(buf, &mystat);
	    printf("%zu",mystat.st_size);
	    printf(" %s\n", myfile->d_name);
	}else 
	    printf("%s ", myfile->d_name);
    }
    if (!_al)
	printf("\n");
    closedir(dir);
    
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
	ls(0, 0);
    }else {
	int _a = 0, _al = 0;
	for (int i = 1; i < argc; ++i) {
	    if (argv[i][0] != '-') {
		puts("Incorrect options used");
		exit(EXIT_FAILURE);
	    }else {
		if (argv[i][1] == 'a' && strlen(argv[i]) == 2) {
		    _a = 1;
		}else if (strlen(argv[i]) == 3 && argv[i][1] == 'a' && argv[i][2] == 'l') {
		    _al = 1;
		}else {
		    exit(EXIT_FAILURE);
		}
	    }
	}
	ls(_a, _al);
    }
}

