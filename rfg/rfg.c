/*
 * Generate random floating point numbers
 *
 */
#include "define_op.h"

#define MAX 20
char * assembly = "FPCLAC= 6550\n"
                  "FPLOAD= 6551\n"
                  "FPSTOR= 6552\n"
                  "FPADD= 6553\n"
                  "FPMULT= 6554\n\n"
                  "*200\nMain, FPCLAC\n"
                   "\tcla\n\ttad k\n"
                   "loop, dca k\n"
                   "\tFPLOAD\naptr, a\n"
                   "\tFPMULT\nbptr, b\n"
                   "\tFPSTOR\ncptr, c\n"
                   "\ttad aptr\n\ttad d\n\tdca aptr\n"
                   "\ttad bptr\n\ttad d\n\tdca bptr\n"
                   "\ttad cptr\n\ttad d\n\tdca cptr\n"
                   "\ttad k\n\ttad j\n\tsma\n\tjmp loop\n"
                   "\thlt\n\n*250\nd,11\n"
                   "k, 27\nj, -1\n"
                   "a, 0\n0\n0\n"
                   "b, 0\n0\n0\n"
                   "c, 0\n0\n0\n"
                   "000\n000\n0111\n"
                   "201\n300\n1123\n"
                   "0\n4000\n0\n"
                   "377\n0111\n1111\n"
                   "201\n5000\n223\n"
                   "0\n4000\n0\n"
                   "201\n5000\n223\n"
                   "0\n0\n0\n"
                   "0\n0\n0\n";

/*
char * assembly = "FPCLAC = 6550\n"
                  "FPLOAD = 6551\n"
                  "FPSTOR = 6552\n"
                  "FPADD = 6553\n"
                  "FPMULT = 6554\n\n"
                  "*200\nMain, FPCLAC\n"
                  "FPLOAD\na\nFPMULT\n"
                  "b\nFPSTOR\nc\nhlt\n"
                  "*20\n";
*/
void print_file(FILE *fp, char *format, unsigned int n);

int main()
{
    FILE *fp;
    fp = fopen("fptest.as","w");

    float range = 10;
    srand((unsigned int)time(NULL));
    fprintf(fp,"%s",assembly);

    format = octalformat;
    for(int i = 0; i<MAX; i++)
    {
        Op1.f = rfg(range);
        Op2.f = rfg(range);
        result.f = Op1.f * Op2.f;
        fprintf(stdout,"%g * %g = %g\n",Op1.f, Op2.f, result.f);
        print(format, Op1.n);
        print(format, Op2.n);
        print(format, result.n);

        print_file(fp, octalformat, Op1.n);
        print_file(fp, octalformat, Op2.n);
        print_file(fp, octalformat, result.n);
        range = range + 2;
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
