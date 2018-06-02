/*
 * Prompt for floating point numbers to use as operands
 * and perform the specified operation on them.
 *
 * Print out operands and result of operation.
 * Print out PDP8 format equivalents as well.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

int main(int argc, char **argv)
{
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
    char *format = octalformat;
    char *op;
    int i, flag = 0;

    if(argc > 3) // Too many arguments
    {
        usage();
        exit(1);
    }

    // determine format
    for(i = 1; i < argc; i++)
    {
       if(!strncmp("-h",argv[i],2))
          format = hexformat;
       else 
           format = octalformat;
    }

    while(!feof(stdin))
    {
        fprintf(stdout,"Specify floating point operation you want:\n");
        fprintf(stdout,"\tm for multiply\n\ta for addition\n\tq to exit\n");
        
        scanf("%c",op);
        getchar();
        if(!strncmp("q",op,1))
            exit(1);
        else if(!strncmp("m",op,1))
            flag = 1;
        else if(!strncmp("a",op,1))
            flag = 2;
        else 
        {
            fprintf(stderr,"Not a valid option.\n");
            flag = 0;
        }
        
        while(flag != 0 && !feof(stdin))
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
    exit(1);
}
