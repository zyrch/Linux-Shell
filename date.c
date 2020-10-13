#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char* itoa(long val, int base){
    static char buf[32] = {0};
    int i = 30;
    char *x = "0123456789abcdef";
    for(; val && i ; --i, val /= base) {
	buf[i] = x[val % base];
    }
    return &buf[i+1];
}

// options
// -I - output date/time in ISO 8601 format
// -R - output date and time in RFC 5322 format
void _date(int _I, int _R) {
    
    if (_I && _R) {
	printf("date: multiple output formats specified\n");
	return;
    }
    time_t t = time(NULL);
    struct tm *dat = localtime(&t);
    
    if (_I) {
	struct tm tm = *localtime(&t);
	printf("%d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    }else if (!_R) {
	char *s = asctime(dat);
	
	for (int i = 0; i < 20; ++i) {
	    printf("%c", s[i]);
	}
	printf("%s ", dat->tm_zone);
	for (int i = 20; i < strlen(s); ++i) {
	    printf("%c", s[i]);
	}
    }else {
	char *s = asctime(dat);
	for (int i = 0; i < 3; ++i) {
	    printf("%c", s[i]);
	}
	printf(", %c%c ", s[8], s[9]);
	
	for (int i = 4; i < 7; ++i) {
	    printf("%c", s[i]);
	}
	printf(" ");
	for (int i = 20; i < strlen(s) - 1; ++i) {
	    printf("%c", s[i]);
	}
	for (int i = 10; i < 19; ++i) {
	    printf("%c", s[i]);
	}
	long var = dat->tm_gmtoff;
	if (var > 0) {
	    printf(" +");
	}else {
	    printf(" -");
	}
	long hrs = var/(60 * 60);
	long mins = (var/60)%60;
	char *hr = itoa(hrs, 10);
	if (strlen(hr) == 1) {
	    printf("0");
	}
	printf("%s", hr);
	char *min = itoa(mins, 10);
	if (strlen(min) == 1) {
	    printf("0");
	}
	printf("%s", min);
	puts("");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
	_date(0, 0);
    }else if (argc > 1) {
	int _I = 0, _R = 0;
	for (int i = 1; i < argc; ++i) {
	    if (argv[i][0] != '-') {
		puts("Incorrect options used");
		exit(EXIT_FAILURE);
	    }else {
		if (argv[i][1] == 'I' && strlen(argv[i]) == 2) {
		    _I = 1;
		}else if (strlen(argv[i]) == 2 && argv[i][1] == 'R') {
		    _R = 1;
		}else {
		    puts("Incorrect options used");
		    exit(EXIT_FAILURE);
		}
	    }
	}
	_date(_I, _R);
    }else {
	puts("Incorrect options used");
	exit(EXIT_FAILURE);
    }
    
    return 0;
}
