/********************************
Luke Darrow 11349190
CptS 460 Lab 2

helper functions
********************************/

char *table = "0123456789ABCDEF";
char *cp;
int *FP, *ip;

int gets(char buf[])
{
    int i = 0;
    char c = getc();
    while (c != '\r')
    {
        buf[i] = c;
        putc(c);
        c = getc();
        i++;
    }
    buf[i] = 0;
}

void prints(char *s)
{
    int i;
    //writes each character until null character in string is reached
    for (i = 0;s[i] != '\0'; i++)
    {
        putc(s[i]);
    }
}

int rpu(u32 x, int base)
{
    char c;
    if (x){
        c = table[x % base];
        rpu(x / base, base);
        putc(c);
    }
    return 0;
}

//prints an unsigned int (u32)x, as written in the lab
int printu(u32 x, int base)
{
    if (x == 0)
        putc('0');
    else
        rpu(x, base);
    putc(' ');
}

//prints an integer (which may be negative)
int printd(int x)
{
    //if x is negative print the sign and convert to unsigned
    if(x < 0)
    {
        prints("-");
        x = x * -1;
    }
    printu(x, 10);
    return 0;
}

//print x in octal as 0.....
int printo(u32 x)
{
    prints("0");
    printu(x, 8);
    return 0;
}

//print x in hex. as 0x....
int printx(u32 x)
{
    prints("0x");
    printu(x, 16);
    return 0;
}

void myprintf(char *fmt, ...)
{
    //set ip to first item to be printed on stack, which is to the left of fmt
    ip = (int*)&fmt + 1;
    //point cp to the format string
    cp = fmt;
    
    //iterate through the format string
    while(*cp)
    {
        //if the symbol matches '%' it skips this and goes to the switch after incrementing cp
        if(*cp != '%')
        {
            putc(*cp);
            if(*cp == '\n')
                putc('\r');
            cp++;
            //go to next iteration of while loop
            continue;
        }
        cp++;
        switch(*cp)
        {
            case 'c':
                putc(*ip);
                break;
            case 's':
                prints(*ip);
                break;
            case 'u':
                printu(*ip, 10);
                break;
            case 'd':
                printd(*ip);
                break;
            case 'o':
                printo(*ip);
                break;
            case 'x':
                printx(*ip);
                break;
        }
        cp++;
        ip++;
    }
}
