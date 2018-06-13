/*
 * Generate random floating point numbers for a specified operation
 * PDP-8 FP test case generator
 *
 */
#include "define_op.h"

#define MAX 200

//============== Assembly Program Strings =================
char *symboldef = "FPCLAC= 6550\n"
                  "FPLOAD= 6551\n"
                  "FPSTOR= 6552\n"
                  "FPADD= 6553\n"
                  "FPMULT= 6554\n\n";

char * LoopHalf1 ="*200\nMain, FPCLAC\n"
                  "\tcla\n\ttad count\n"
                  "loop, dca count\n"
                  "\tFPLOAD\naptr, a\n";

char *fpmult =   "\tFPMULT\nbptr, b\n";
char *fpadd  =   "\tFPADD\nbptr, b\n";

char *LoopHalf2 = "\tFPSTOR\ncptr, c\n"
                  "\ttad aptr\n\ttad d\n\tdca aptr\n"
                  "\ttad bptr\n\ttad d\n\tdca bptr\n"
                  "\ttad cptr\n\ttad d\n\tdca cptr\n"
                  "\ttad count\n\ttad j\n\tsma\n\tjmp loop\n"
                  "\thlt\n\n*250\nd,11\nj, -1\n";

char * constants_mult ="a, 0\n0\n0\n" // 0
                  "b, 200\n0\n0\n"    // 2
                  "c, 0\n0\n0\n"      // expect 0
                  "000\n000\n0111\n"
                  "201\n300\n1123\n"
                  "0\n4000\n0\n"
                  "377\n0111\n1111\n"
                  "201\n5000\n223\n"
                  "0\n4000\n0\n"
                  "201\n5000\n223\n"
                  "0\n0\n0\n"
                  "0\n0\n0\n";

char * constants_add ="a, 0\n0\n0\n" // 0
                  "b, 200\n0\n0\n"    // 2
                  "c, 200\n0\n0\n"    // expect 2
                  "000\n000\n0111\n"
                  "201\n300\n1123\n"
                  "0\n4000\n0\n"
                  "377\n0111\n1111\n"
                  "201\n5000\n223\n"
                  "0\n4000\n0\n"
                  "201\n5000\n223\n"
                  "0\n0\n0\n"
                  "0\n0\n0\n";
//===============================
void print_file(FILE *fp, char *format, unsigned int n);

int main(int argc, char **argv )
{
    FILE *fp;
    float range = 5;
    srand((unsigned int)time(NULL));
    int flag = 0;

    if(argc <= 2)
    {
        fprintf(stdout, "Not enough arguments. \nUsage:\t./rfg <op> <filename>"
                "\n\top --> FPADD or FPMULT\n\tfilename --> newly"
                "generated assembly code file\n\n");
        exit(1);
    }
    
    if(!strncmp("FPMULT",argv[1],6))
        flag = 1;
    else if(!strncmp("FPADD",argv[1],6))
        flag = 2;
    else
    {
        fprintf(stderr,"%s is not a valid operation. Use FPADD or FPMULT\n",argv[1]);
        exit(1);
    }
    
    // Print into specified file name
    fp = fopen(argv[2],"w");
    fprintf(fp,"%s%s",symboldef,LoopHalf1);
    if(flag == 1) // FPMULT
        fprintf(fp,"%s",fpmult);
    else
        fprintf(fp,"%s",fpadd);
    fprintf(fp,"%s",LoopHalf2);
    
    fprintf(fp,"count, %o\n",MAX+4);
    
    if(flag == 1)
        fprintf(fp,"%s",constants_mult);
    else
        fprintf(fp,"%s",constants_add);

    format = octalformat;
    

    for(int i = 0; i<MAX; i++)
    {
        Op1.f = rfg(range);
        Op2.f = rfg(range);
        if(flag == 1) // FPMULT
            result.f = Op1.f * Op2.f;
        else          // FPADD
            result.f = Op1.f + Op2.f;
        print(format, Op1.n);
        print(format, Op2.n);
        print(format, result.n);
        
        if(flag == 1)
            fprintf(stdout,"%f * %f = %f",Op1.f, Op2.f, result.f);
        else
            fprintf(stdout,"%f + %f = %f",Op1.f, Op2.f, result.f);
        print_file(fp, octalformat, Op1.n);
        print_file(fp, octalformat, Op2.n);
        print_file(fp, octalformat, result.n);
        range = range * 1.5;
    }
    fprintf(fp,"$Main");
    fclose(fp);
    return 0;
}


void print_file(FILE *fp, char *format, unsigned int n) 
{
    unsigned int exponent;
    unsigned int upperbits;
    unsigned int lowerbits;

    exponent = (n >> 23) & 0xFF;
    upperbits = ((n >> 12) & 0x7FF) | ((n >> 31) << 11);
    lowerbits = n & 0xFFF;

    fprintf(fp,format,exponent);
    fprintf(fp,format,upperbits);
    fprintf(fp,format,lowerbits);
}
