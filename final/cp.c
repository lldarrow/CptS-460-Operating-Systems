/**********************************************
Luke Darrow 11349190
CptS 460
Final Project
copy file user mode function
***********************************************/

#include "ucode.c"

//cp function
int main(int argc, char *argv[])
{
	char buf[1024];
	int fd1, fd2;
	int n, bytes = 0;

	printf("RUNNING LUKE'S CP\n");

	//check if enough arguments
	if(argc < 3)
	{
		printf("ERROR: not enough arguments\n");
		printf("e.g. cp f1 f2\n");
		exit(0);
	}

	//open first file for reading
	fd1 = open(argv[1], O_RDONLY);

	//make sure it opened correctly
	if(fd1 < 0)
	{
		printf("ERROR: cannot open file %s\n", argv[1]);
		exit(0);
	}

	//open the second file for writing or create it if it doesn't exist
	fd2 = open(argv[2], O_WRONLY|O_CREAT);

	//check it opened correctly
	if(fd2 < 0)
	{
		printf("ERROR: cannot open file %s\n", argv[2]);
		exit(0);
	}

	//keep reading max of 1024 bytes into buffer (n is the number of bytes read)
	while(n = read(fd1, buf, 1024))
	{
		//write buffer to file descripter 2 (second file)
		write(fd2, buf, n);
		//add to bytes copied counter
		bytes += n;
	}

	//close files and print number of bytes copied
	close(fd1);
	close(fd2);
	printf("%d bytes copied\n", bytes);
	//kill process
	exit(0);
}
