#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void print_hexa_upper(int d, int hexa) {
    if (d > 0) {
        print_hexa_upper(d / hexa, hexa);
        char hexDigit = (d % hexa < 10) ? (d % hexa + '0') : (d % hexa - 10 + 'A');
        putchar(hexDigit);
    }
}

void print_hexa_lower(int d, int hexa) {
    if (d > 0) {
        print_hexa_lower(d / hexa, hexa);
        char hexDigit = (d % hexa < 10) ? (d % hexa + '0') : (d % hexa - 10 + 'a');
        putchar(hexDigit);
    }
}

void print_string(char* s) {
    while (*s) {
        putchar(*s);
        s++;
    }
}

void print_int_base(int d, unsigned base) {
    if (d > 0) {
        print_int_base(d / base, base);
        putchar(d % base + '0');
    }
}

void print_padded_int(int d, int pd) {
    int numDigits = 0;
    int temp = d;
    while (temp != 0) {
        numDigits++;
        temp /= 10;
    }

    if (d < 0) {
        numDigits++; // Account for the negative sign
    }

    // Print padding spaces
    for (int i = 0; i < pd - numDigits; i++) {
        putchar(' ');
    }

    // Print the integer
    print_int_base(d, 10);
}

void print_padded0_int(int d, int p0d) {
    int numDigits = 0;
    int temp = d;
    while (temp != 0) {
        numDigits++;
        temp /= 10;
    }

    if (d < 0) {
        numDigits++; // Account for the negative sign
    }

    // Print leading zeros
    for (int i = 0; i < p0d - numDigits; i++) {
        putchar('0');
    }

    // Print the integer
    print_int_base(d, 10);
}

void print_padded_hexa_upper(int d, int pX) {
    int numDigits = 0;
    int temp = d;
    while (temp != 0) {
        numDigits++;
        temp /= 16;
    }

    if (d < 0) {
        numDigits++; // Account for the negative sign
    }

    // Print leading spaces
    for (int i = 0; i < pX - numDigits; i++) {
        putchar(' ');
    }

    // Print the hexa
    print_hexa_upper(d, 16);
}

void print_padded_hexa_lower(int d, int px) {
    int numDigits = 0;
    int temp = d;
    while (temp != 0) {
        numDigits++;
        temp /= 16;
    }

    if (d < 0) {
        numDigits++; // Account for the negative sign
    }

    // Print leading spaces
    for (int i = 0; i < px - numDigits; i++) {
        putchar(' ');
    }

    // Print the hexa
    print_hexa_lower(d, 16);
}

void print_padded0_hexa_upper(int d, int p0X) {
    int numDigits = 0;
    int temp = d;
    while (temp != 0) {
        numDigits++;
        temp /= 16;
    }

    if (d < 0) {
        numDigits++; // Account for the negative sign
    }

    // Print leading zeros
    for (int i = 0; i < p0X - numDigits; i++) {
        putchar('0');
    }

    // Print the hexa
    print_hexa_upper(d, 16);
}

void print_padded0_hexa_lower(int d, int p0x) {
    int numDigits = 0;
    int temp = d;
    while (temp != 0) {
        numDigits++;
        temp /= 16;
    }

    if (d < 0) {
        numDigits++; // Account for the negative sign
    }

    // Print leading zeros
    for (int i = 0; i < p0x - numDigits; i++) {
        putchar('0');
    }

    // Print the hexa
    print_hexa_lower(d, 16);
}

void my_printf(const char *format, ...) {
    va_list ap;
    char c;
    char* s;
    int d;

    va_start(ap, format);
    while (*format) {
        if (*format == '%') {
            char fident = *(format+1);
            switch (fident) {
                case 'c': 
                    c = (char)va_arg(ap, int);
                    putchar(c); 
                    break;
                case 's': 
                    s = va_arg(ap, char*);
                    print_string(s);
                    break;
                case 'd': 
                    d = va_arg(ap, int);
                    if (d == 0)
                        putchar('0');
                    else
                        print_int_base(d, 10);
                    break;
                case 'b':
                    d = va_arg(ap, int);
                    if (d == 0)
                        putchar('0');
                    else
                        print_int_base(d, 2);
                    break;
                case 'x':
                    d= va_arg(ap, int);
                    if (*(format+2) == 'x' || *(format+2) == 'X') {
                        putchar('0');
                        putchar(*(format+2));
                    }
                    if (d == 0)
                        putchar('0');
                    else
                        print_hexa_lower(d, 16);
                    if (*(format+2) == 'x' || *(format+2) == 'X')
                        format++;
                    break;
                case 'X':
                    d= va_arg(ap, int);
                    if (*(format+2) == 'x' || *(format+2) == 'X') {
                        putchar('0');
                        putchar(*(format+2));
                    }
                    if (d == 0)
                        putchar('0');
                    else
                        print_hexa_upper(d, 16);
                    if (*(format+2) == 'x' || *(format+2) == 'X')
                        format++;
                    break;
            }
            if (isdigit(*(format+1))) {
                char infident= *(format+2);
                switch (infident){
                    case 'd': 
                        d = va_arg(ap, int);
                        int pd = fident-'0';
                        if (d == 0)
                            putchar('0');
                        else
                            {print_padded_int(d,pd);
                            format++;}
                        break;
                    case 'x':
                        d=va_arg(ap,int);
                        int px= fident-'0';
                        int ok2=0;
                        if(*(format+3)=='x' || *(format+3)=='X')
                        {
                            putchar('0');
                            putchar(*(format+3));
                            ok2++;
                        }
                        if(d==0)
                            putchar('0');
                        else
                            {
                                format++;
                                print_padded_hexa_lower(d,px);
                            }
                        if(ok2==1)
                            format++;
                        if(ok2==2)
                            format++;
                        break;
                    case 'X':
                        d=va_arg(ap,int);
                        int pX= fident-'0';
                        int ok3=0;
                        if(*(format+3)=='x' || *(format+3)=='X')
                        {
                            putchar('0');
                            putchar(*(format+3));
                            ok3++;
                        }
                        if(d==0)
                            putchar('0');
                        else
                        {
                            format++;
                            print_padded_hexa_upper(d,pX);
                        }
                        if(ok3==1)
                            format++;
                        if(ok3==2)
                            format++;
                        break;
                }
            }
            if (*(format+1) == '0') {
                char inifident= *(format+3);
                switch (inifident){
                    case 'd': 
                        d = va_arg(ap, int);
                        int p0D = *(format+2)-'0';
                        if (d == 0)
                            putchar('0');
                        else
                            {
                                format+=2;
                                print_padded0_int(d,p0D);
                            }
                        break;
                    case 'x':
                        d=va_arg(ap,int);
                        int p0x= *(format+2)-'0';
                        int ok4=0;
                        if(*(format+4)=='x' || *(format+4)=='X')
                        {
                            putchar('0');
                            putchar(*(format+4));
                            ok4++;
                        }
                        if(d==0)
                            putchar('0');
                        else
                            {
                                format+=2;
                                print_padded0_hexa_lower(d,p0x);
                            }
                        if(ok4==1)
                            format++;
                        if(ok4==2)
                            format++;
                        break;
                    case 'X':
                        d=va_arg(ap,int);
                        int p0X= *(format+2)-'0';
                        int ok5=0;
                        if(*(format+4)=='x' || *(format+4)=='X'){
                            putchar('0');
                            putchar(*(format+4));
                            ok5++;
                        }
                        if(d==0)
                            putchar('0');\
                        else
                        {
                            format+=2;
                            print_padded0_hexa_upper(d,p0X);
                        }
                        if(ok5==1)
                            format++;
                        if(ok5==2)
                            format++;
                        break;
                }
            }
            format++;
        } else
            putchar(*format);
        format++;
    }
    va_end(ap);
}

int main() {
    my_printf("%s %c %b %d %x %X %5d %2x %2X %03d %03x %04X %xx %XX %3xx %3XX %03xx %03XX %xX %Xx %3xX %3Xx %03xX\n", 
     "string",'e',11,451,161,431,3456,12,11,11,11,12,353,201,123,10,20,21,10,31,10,10,10);
    return 0;
}