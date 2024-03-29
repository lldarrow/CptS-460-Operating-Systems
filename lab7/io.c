/*******************************************
Luke Darrow 11349190
CptS 460
Printf and helper functions
basically contains printf and stuff
*******************************************/

char *tab="0123456789ABCDEF";
int BASE = 10;
u16 ALIGN = 0;

//recursively print unsigned
int rpu(u16 x)
{
	char c;
	if (x)
	{
		c = tab[x % BASE];
		rpu(x / BASE);
		putc(c);
	}
}

//print unsigned
int printu(u16 x)
{
	(x) ? rpu(x) : putc('0');
	putc(' ');
}

//print decimal
int printd(int x)
{
	if (x < 0)
	{
		putc('-');
		x = -x;
	}
	printu(x);

}

//print hex
int printx(u16 x)
{
	BASE = 16;
	printu(x);
	BASE = 10;
}

//recursively print long
int rpl(u32 x)
{
	char c;
	if (x == 0)
		return;
	c = tab[x % BASE];
	rpl(x / BASE);
	putc(c);
}

//align digits
int align(u32 x)
{
	int digits, count, i;
	digits = 0;
	while(x)
	{
		digits++;
		x = x / 10;
	}
	count = 10 - digits;
	while(count > 0)
	{
		putc(' ');
		count--;
	}
}

//print long
int printl(u32 x)
{
	if (ALIGN)
		align(x);
	if (x == 0)
	{
		putc('0');
		putc(' ');
		return;
	}
	rpl(x);
	putc(' ');
}

//print string
int prints(char *s)
{
	while(*s)
	{
		putc(*s);
		s++;
	}
}

//printf function
int printf(char *fmt, ...)
{
	char *cp;
	u16 *ip;
	u32 *up;

	cp = fmt;
	ip = (int *)&fmt + 1;

	//while vars to print
	while(*cp)
	{
		if (*cp != '%')
		{
			putc(*cp);
			if(*cp == '\n')
				putc('\r');
			cp++;
			continue;
		}
		cp++;
		switch(*cp)
		{
			case 'c'://char
				putc(*ip);
				break;
			case 's'://string
				prints(*ip);
				break;
			case 'u'://unsigned
				printu(*ip);
				break;
			case 'd'://decimal
				printd(*ip);
				break;
			case 'x'://hex
				printx(*ip);
				break;
			case 'l'://long
				printl(*(u32 *)ip++);
				break;
		}
		cp++;
		ip++;
	}
}


//get input functions
#define LEN 64//max len is 64

//get string
int gets(char *s)
{ 
	char c, *b;
	int n = 0;

	b = s;

	while ( (c=getc()) != '\r' && n < LEN)
	{
		if (c=='\b')
		{
			if (s==b)
				continue;
			s--;
			putc('\b');
			putc(' ');
			putc('\b');
			continue;
		}   
		*s = c;   
		putc(*s); s++; n++;
	}
	*s = 0;
	prints("\n\r");
}


#define OSSEG 0x1000

//get word function
int get_word(u16 segment, u16 offset)
{
	u16 word;
	setds(segment);
	word = *(u16 *)offset;
	setds(OSSEG);
	return word;
}

//put word function
int put_word(u16 word, u16 segment, u16 offset)
{
	setds(segment);
	*(u16 *)offset = word;
	setds(OSSEG);
}

//get byte function
u8 get_byte(u16 segment, u16 offset)
{
	u8 byte;
	setds(segment);
	byte = *(u8 *)offset;
	setds(OSSEG);
	return byte;
}

//put byte function
int put_byte(u8 byte, u16 segment, u16 offset)
{
	setds(segment);
	*(u8 *)offset = byte;
	setds(OSSEG);
	return byte;
}
