#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//========= Global Variables ===========
union{
    float f;
    unsigned int n;
} Op1;

union{
    float f;
    unsigned int n;
} Op2;

union{
    float f;
    unsigned int n;
} result;

char *octalformat = "%04o\n";
char *hexformat = "%03x\n";
char *octalformat2 = "\t%04c\n";
char *format;
//========= Function Defs  ===========
// Print float in PDP-8 format
void print(char *format, unsigned int n) 
{
    unsigned int exponent;
    unsigned int upperbits;
    unsigned int lowerbits;

    exponent = (n >> 23) & 0xFF;
    upperbits = ((n >> 12) & 0x7FF) | ((n >> 31) << 11);
    lowerbits = n & 0xFFF;

    printf(format,exponent);
    printf(format,upperbits);
    printf(format,lowerbits);
}

void usage() {
    fprintf(stderr,"op_convert [-o | -h]\n");
}

// Generate floating point within provided range
float rfg(float range)
{
    if( (rand() % 100) < 50)
        return ((float)rand()/(float)RAND_MAX) * range * -1;
    else
        return ((float)rand()/(float)RAND_MAX) * range;
}

// Prompt user what operation they would like to perform
int op_prompt()
{   
    char op;
    while(!feof(stdin))
    {
        fprintf(stdout,"Specify floating point operation you want:\n");
        fprintf(stdout,"\tm for multiply\n\ta for addition\n\t"
                "t for multiply with random operands\n\t"
                "s for addition with random operands\n\t"
                "q to exit\n");
        
        scanf("%c",&op);
        getchar();
        if(!strncmp("q",&op,1))
            return -1;
        else if(!strncmp("m",&op,1))
            return 1;
        else if(!strncmp("a",&op,1))
            return 2;
        else if(!strncmp("t",&op,1))
            return 3;
        else if(!strncmp("s",&op,1))
            return 4;
        else 
            fprintf(stderr,"Not a valid option.\n");
    }
    return 0;
}

// Random operand floating point operations
void rand_op(int flag)
{
    char c = 'y';
    float range = rand();

    while(!feof(stdin) && !strncmp("y",&c,1))
    {
        Op1.f = rfg(range);
        Op2.f = rfg(range);
        if(flag == 3) // multiply
        {
            result.f = Op1.f * Op2.f;
            fprintf(stdout, "%g * %g = %g\n",Op1.f, Op2.f, result.f);
        }
        else // addition
        {
            result.f = Op1.f + Op2.f;
            fprintf(stdout, "%g + %g = %g\n",Op1.f, Op2.f, result.f);
        }
        print(format, Op1.n);
        print(format, Op2.n);
        print(format, result.n);
        
        fprintf(stdout,"Again? (y/n)");
        scanf("%c",&c);
        fprintf(stdout,"\n");
    }
}

// Floating point operations with user inputting operands
void input_op(int flag)
{
    while(!feof(stdin))
    {
        fprintf(stdout,"Operand 1: ");
        scanf("%g",&Op1.f);
        print(format, Op1.n);
                
        fprintf(stdout,"Operand 2: ");
        scanf("%g",&Op2.f);
        print(format, Op2.n);

        if(flag == 1)
            result.f = Op1.f * Op2.f;
        else
            result.f = Op1.f + Op2.f;

        fprintf(stdout,"Result   : %f\n", result.f);
        print(format, result.n);
        fprintf(stdout,"\n");
    }
}

