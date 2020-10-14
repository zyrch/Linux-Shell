# Linux-Shell
OBJECTIVE: 
	Create a linux shell using standard C libraries and systems calls

METHOD:
	There are two type of commands to be processed internal and external commands, 
	to process external commands the original process is first forked and then 
	execv command is used to execute another file and wait is used to let the child 
	process finish and then continue to next input of shell

SOME ASSUMPTIONS:
	- The user can use the shell infinitely
	- A new execution of the shell is indepented of all the previous executions
	- shell's starting directory is the same as directory where the program is executed
	- path of the files rm.c mkdir.c ls.c date.c cat.c is in the same folder as shell and is
	  known beforehand

IMPORTANT METHODS:
	fork: 
		Spawning a child process in the beginning using the fork() 
		system call. Check the value of pid to assert a correct fork.
	open: 
		For pid == 0, we enter the child process and calculate the 
		average for students of Section A. We use the open system 
		call to open our target file. It returns an integer, positive is 
		file was successfully opened and  negative if not.
	read:
		When the target file is succesfully opened, we use the read system call to read the entire data in our
		target file to a buffer that is a char* array. It returns the the total number of bytes read. Following 
		this, we read the buffer byte by byte to get student parameters. Once we have the data for a student, 
		we check sections and print average accordingly.
		
	close: 
		We close the target file using the close system call after we have read the data into the buffer.	
		
	wait:
		When the returned process id is greater than 0, we have entered the parent process. 
		We use the wait() system call. After this, we calculate the average of the section B 
		students. The process is exactly the same as done in the child process.
		
	execv: 
		When an external command is entered execv is used to execute the respecitve binary file
	
	chdir: 
		Used to change the current working directory
		
	getcwd:
		Used to get the current working directory
	
	opendir:
		Opens a specific directory given as arguments and returns NULL
		if there is no such directory
	remove:
		removes a file with specific name passed in argument.
	mkdir:
		creates a directory at a specifies path
	readdir: 
		reads files from a directory, returns NULL is if last file is crossed

SOME CORNER CASES:
	
	cd:
	   -Check if the input is valid or not, if there are more than two statements
	    then the input is invalid
	    
	pwd:
	   -Check if the input is valid or not, if there are more than two statements
	    then the input is invalid
	   -Input is invalid if the second argument is non-empty is not equal to '--help'
	
	echo:
	   -options should always be added towards the start right after echo otherwise they are 
	    treated as part of the input data is outputed to the console
	
	   
	   -there cannot be more than one option at the same time, if two are given 
	    the second option is treated as part of the input data is outputed to
	    the console
	    
	history:
	   -check if the input is valid or not all the commands after 'history' should be a option
	   
	   -if two options are used then -c is given the priority
	   
	   -check if the value just after -d is a correct index or not
	   
	   -(-d) shoudn't be the last input of the command
	
	rm:
	   -check if the file is a directory or not as directories cannot be 
	    removed using rm command, this is done using the call opendir() which
	    return NULL if the file is not a directory
	    
	   -check if the file exits if it dosent' give error
	   
	   -check if the options used are valid
	
	mkdir:
	   -check if directory already exists before creating if it does
	    print error or do nothing depending upon the flag used, mkdir return 
	    -1 when there is an error and we can use errno to figure out what 
	    kind of error has occured (EEXIST is the directory already exits and 
	    ENOENT if the parent directory doesn't exist)
	    
	   -if parent directory dosen't exist and -p is used then instead of on 
	    error they are newly created
	    
	   -check if the options used are valid
	
	ls:
	   -check if the options used are valid 
	
	   -handle the case if it is unable to open the directory and report it
	    this can be done by using the return value of opendir()
	    
	date:
	   -check if the options used are valid 
	   
	   -check if both options -R and -I and not used at the same time
	   
	cat:
	   -check if the file is opened successfully to prevent bugs
	   
	   -check if the opetions used are valid, both the options can be used at the
	    same time
	    
COMMANDS TO TEST PROGRAM (some the test are designed to give error):
	cd: 
	    cd ..
	    cd --help
	
	pwd: 
	    pwd
	    pwd --help
	
	echo:
	    echo --help output this
	    echo --help -n output this
	    echo -n --help output this
	    echo -n output this
	    
	exit:
	    exit
	    
	history:
	    history 
	    history -c
	    history -c -d 1
	    history -d -1
	    history -d ab   
	    
	rm:
	    rm $(name of a directory)
	    rm $(file name that dosen't exits)
	    rm -i -v $(file name that exits)
	
	mkdir:
	    mkdir $(new directory)
	    mkdir $(already existing directory)
	    mkdir -p $(already existing directory)
	    mkdir -v -p $(new directory/new directory)
	
	ls:
	    ls
	    ls -a
	    ls -al
	    ls -a -al
	
	date:
	    date 
	    date -R
	    date -I
	    date -R -I
	
	cat:
	    cat $(file that dosen't exits)
	    cat $(file)
	    cat -c $(file)
	    cat -n $(file)
	    cat -n -c $(file)
