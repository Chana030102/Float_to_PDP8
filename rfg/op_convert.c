/*
 * Prompt for floating point numbers to use as operands
 * and perform the specified operation on them.
 *
 * Print out operands and result of operation.
 * Print out PDP8 format equivalents as well.
 *
 */

#include "define_op.h"
int main(int argc, char **argv)
{
    int i, flag;
    
    format = octalformat;
    srand((unsigned int)time(NULL));
    
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
        flag = op_prompt();
        if(flag == -1) // quit program
            exit(1);
        else if(flag == 1 || flag == 2)
            input_op(flag);
        else if(flag == 3 || flag == 4)
            rand_op(flag);
    }
    exit(1);
}
