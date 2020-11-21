#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>


#define nax 200
#define nax2 1000

char command[nax];
char *commands[nax];
char cwd[nax];
char history[nax2][nax];
int historySize = 0;

void parse_command();

int numberOfCommands;

void parse_command();
int isBuiltInCommand();
void execInternalCommand();
void execExternalCommand();
void addHistory();

// Internal Commands
void exitCommand();
void cdCommand();
void pwdCommand();
void echoCommand();
void historyCommand();


int main(int argc, char * argv[]) {

    system("clear");
    
    
    while(1) {
	
	printf("$");
	fflush(stdout);
	
	scanf("%[^\n]%*c", command);
	strcpy(history[historySize++], command);
	numberOfCommands = 0;
	parse_command();
	
	if (isBuiltInCommand()) {
	    execInternalCommand();
	}else {
	    // if not buildin command then use fork and run execv for child process while
	    // parent waits for child to finish
	    if (fork() == 0) {
		execExternalCommand();
	    }else {
		wait(NULL);
	    }
	}
	
    }

}

void execExternalCommand() {
    commands[numberOfCommands] = NULL;
    if (strcmp(commands[0], "ls") == 0) {
	commands[0] = "/home/zyrch/Desktop/OS/shell/./ls";
	execv(commands[0], commands);
    }else if (strcmp(commands[0], "cat") == 0) {
	commands[0] = "/home/zyrch/Desktop/OS/shell/./cat";
	execv(commands[0], commands);
    }else if (strcmp(commands[0], "mkdir") == 0) {
	commands[0] = "/home/zyrch/Desktop/OS/shell/./mkdir";
	execv(commands[0], commands);
    }else if (strcmp(commands[0], "rm") == 0) {
	commands[0] = "/home/zyrch/Desktop/OS/shell/./rm";
	execv(commands[0], commands);
    }else if (strcmp(commands[0], "date") == 0) {
	commands[0] = "/home/zyrch/Desktop/OS/shell/./date";
	execv(commands[0], commands);
    }else {
	puts("Command Not Found");
	exit(EXIT_FAILURE);
    }
}

int isBuiltInCommand() {
    return strcmp(commands[0], "cd") == 0 || strcmp(commands[0], "echo") == 0 || strcmp(commands[0], "history") == 0 
    || strcmp(commands[0], "pwd") == 0 || strcmp(commands[0], "exit") == 0;
}

void parse_command() {
    
    char *pch = strtok(command, " ");
	
    while(pch != NULL) {
	
	// TODO - Handle overflow
	commands[numberOfCommands] = pch;
	numberOfCommands++;
	
	pch = strtok (NULL, " ");
    }
}

void execInternalCommand() {
    if (strcmp(commands[0], "exit") == 0) {
	exitCommand();
    }else if (strcmp(commands[0], "cd") == 0) {
	cdCommand();
    }else if (strcmp(commands[0], "pwd") == 0) {
	pwdCommand();
    }else if (strcmp(commands[0], "echo") == 0) {
	echoCommand();
    }else if (strcmp(commands[0], "history") == 0) {
	historyCommand();
    }
}

void exitCommand() {
    exit(0);
}

// options 
// --help - print info about the command and what it does and it's usage
void cdCommand() {
    if (numberOfCommands > 2) {
	printf("Invalid Options");
    }else if (numberOfCommands == 2) {
	if (strcmp(commands[1], "--help") == 0) {
	    puts("cd : [dir]");
	    puts("Change the shell working directory to dir");
	}else if (chdir(commands[1]) != 0)  {
	    perror("");
	}
    }else if (numberOfCommands == 1) {
	printf("Invalid Options");
    }
}

// options 
// --help - print info about the command and it's usage and what it does
void pwdCommand() {
    if (numberOfCommands > 2) {
	printf("Invalid Options");
    }else if (numberOfCommands == 2) {
	if (strcmp(commands[1], "--help") == 0) {
	    puts("pwd");
	    puts("print the current working directory");
	}else {
	    printf("Invalid Options");
	}
    }else {
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
    }
    
}

// options
// --help - print info about the command and it's usage and what it does
// -n - do not print trailing new line
void echoCommand() {
    int _n = 0;
    if (strcmp(commands[1], "--help") == 0) {
	puts("echo");
	puts("prints given input to console");
	puts("options :");
	puts("   -n : do not print trailing new line");
	return;
    }else if (strcmp(commands[1], "-n") == 0) {
	_n = 1;
    }
    for (int i = 1 + _n; i < numberOfCommands; ++i) {
	printf("%s", commands[i]);
	if (i != numberOfCommands - 1) {
	    printf(" ");
	}
    }
    if (!_n)
	puts("");
}


//options
// -c : clear history
// -d offset : clear history with entry equal to offset
void historyCommand() {
    
    int _c = 0, _d = 0;
    int index;
    
    for (int i = 1; i < numberOfCommands; ++i) {
	if (commands[i][0] != '-') {
	    puts("Incorrect options used");
	    return;
	}else {
	    if (commands[i][1] == 'c' && strlen(commands[i]) == 2) {
		_c = 1;
	    }else if (strlen(commands[i]) == 2 && commands[i][1] == 'd') {
		_d = 1;
		if (i == numberOfCommands - 1) {
		    puts("Incorrect options used");
		    return;
		}else {
		    int val = 0;
		    for (int j = 0; j < strlen(commands[i + 1]); ++j) {
			if (commands[i + 1][j] < '0' || commands[i + 1][j] > '9') {
			    puts("Incorrect options used");
			    return;
			}
			val += commands[i + 1][j] - '0';
			val *= 10;
		    }
		    val /= 10;
		    if (val > historySize || val < 1) {
			printf("Error : History Position Out of Range");
			return;
		    }
		    index = val;
		    ++i;
		}
	    }else {
		puts("Incorrect options used");
		return;
	    }
	}
    }

    if (_c) {
	historySize = 0;
    }else if (_d) {
	for (int i = index - 1; i < historySize - 1; ++i) {
	    strcpy(history[i], history[i + 1]);
	}
	historySize--;
    }else {
	for (int i = 0; i < historySize; ++i) {
	    printf("%d : %s\n", i + 1, history[i]);
	}
    }
}
