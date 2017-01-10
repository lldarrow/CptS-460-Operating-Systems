/**********************************************
Luke Darrow 11349190
CptS 460
Final Project
more
***********************************************/

#include "ucode.c"

//print a page
void printpage(int fd)
{
	int i, j, n;
	char c;

	putc('\n');

	//height of console is about 24 lines of text
	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 80; j++)
		{
			n = read(fd, &c, 1);//read a byte
			putc(c);//output it
			if (n < 1)//no more bytes, kill it
				exit(0);
			if(c=='\n' || c=='\r')//end of line, go to next line
				break;
		}
	}
	return;
}

//print a line
void printline(int fd)
{
	int i, n;
	char c;

	//width of console is about 80 chars
	for (i = 0; i < 80; i++)
	{
		n = read(fd, &c, 1);//read byte
		putc(c);
		if (n < 1)//nothing left to print, kill it
			exit(0);
		if (c == '\n' || c=='\r')//end of line go to next line
			break;
	}
	return;
}

int main(int argc, char *argv[])
{
	char c, input;
	char *tty;
	int fd, read, i, j;

	if(argc == 1)//no file, stdin
	{
		fd = dup(0);//duplicate stdin file descriptor
		close(0);//close default stdin

		//go to terminal so getc works
		gettty(tty);//get proc.tty name, stores fd to terminal to redirect to terminal
		open(tty, O_RDONLY);
	}
	else//file, open file for reading
		fd = open(argv[1], O_RDONLY);

	if (fd < 0)
	{
		printf("ERROR: cannot open file %s\n", argv[1]);
		exit(0);
	}
	while(1)
	{
		//first print page
		printpage(fd);
		while (1)//keep getting input until nothing left to print
		{
			input = getc();//get input

			switch(input)
			{
				case ' '://space, page down
					printpage(fd);
					break;
				default://every other key, print a line
					printline(fd);
					break;
			}
		}
	}

	return 0;
}

