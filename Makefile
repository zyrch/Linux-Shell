default: 
	gcc shell.c -o shell
	gcc cat.c -o cat
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc date.c -o date
	
shell : 
	gcc shell.c -o shell
	
cat :
	gcc cat.c -o cat
	
ls : 
	gcc ls.c -o ls

mkdir : 
	gcc mkdir.c -o mkdir
	
rm : 
	gcc rm.c -o rm

date : 
	gcc date.c -o date
	
