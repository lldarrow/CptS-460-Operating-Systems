/********************************
Luke Darrow 11349190
CptS 460 Lab 2

helper functions
********************************/

typedef unsigned int u16;
typedef unsigned long u32;

//hex values
char *ctable = "0123456789ABCDEF";

//base 10 values
u16 BASE = 10;


int rpu(u16 x)
{
	char c;
	if (c)
	{
		c = ctable[x % BASE];
		rpu(x /BASE);
		putc(c);
	}
}

//print unsigned 32 bit
int printu(u32 x)
{
	if (x == 0)
		putc('0');
	else
		rpu(x);
	putc(' ');
}

//print string
void prints(char *s)
{
	//keeps outputting the char until end of string
	while(*s)
	{
		putc(*s);
		s++;
	}
}

//print decimal
int printd(int x)
{
	char c;

	//if 0 print 0 character
	if(x == 0)
	{
		putc('0');
		return 0;
	}
	if (x < 0) //if negative print negative sign
	{
		x = x*-1;
		prints("-");
	}
	if (x) //if
	{
		c = ctable[x % BASE];
		rpu(x);
	}
}

//as shown in KC's book
int printf(char *fmt, ...) // some C compiler requires the three dots
{
	char *cp = fmt; // cp points to the fmt string
	u16 *ip = (u16 *)&fmt + 1; // ip points to first item
	u32 *up; // for accessing long parameters on stack

	while (*cp) // scan the format string
	{
		if (*cp != '%') // spit out ordinary chars
		{
			putc(*cp);
			if (*cp=='\n') // for each ‘\n’
				putc('\r'); // print a ‘\r’
			cp++;
			continue;
		}
		cp++; // print item by %FORMAT symbol
		switch(*cp)
		{
			case 'c': //print char
				putc(*ip);
				break;
			case 's': //print string
				prints(*ip);
				break;
			case 'u': //print unsigned
				printu(*ip);
				break;
			case 'd': //print decimal
				printd(*ip);
				break;
		}
		cp++;
		ip++; // advance pointers
	}
}
