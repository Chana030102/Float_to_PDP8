/* 
 * ECE486 (Spring 2018)
 * Homework 4 - Float to PDP-8 Float converter
 *
 * Takes single precision floating point numbers and 
 * converts them to PDP-8 representation.
 *
 * PDP-8 is a 12-bit system, so an alternative way to store
 * floating point has been decided to be the following for
 * the project:
 *    Location 1 = |0000|Exponent|
 *    Location 2 = |Sign|sig Higher 11|
 *    Location 3 = |sig Lower 12   |
 * 
 * Converter can be either fed a number on the commandline upon startup,
 * fed a file with ONLY floating point numbers, or no arguments for
 * endless user entry (which can be ended with Ctrl+D).
 *
 * Commandline Flags:
 *    -o    outputs bits in octal
 *    -h    outputs bits in hex 
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define SYS_BITS 12

typedef union {
    float f;
    struct {
        unsigned int sig: 23;
        unsigned int exponent: 8;
        unsigned int sign: 1;
    }parts;
}float_cast;

// Output floating point in binary
void out_binary(float_cast x, unsigned int a, unsigned int b)
{
    int i; // for-loop condition
    for(i=0;i<12;i++) // Four zeros and exponent bits
        cout << (x.parts.exponent >> ((SYS_BITS-1-i)) & 1);
    cout << endl;

    for(i=0;i<12;i++) // sign bit and significand higher 11 bits
        cout << ((a >> (SYS_BITS-1-i)) & 1);
    cout << endl;
    
    for(i=0;i<12;i++) // significand lower 12 bits
        cout << ((b >> (SYS_BITS-1-i)) & 1);
    cout << endl << endl;
}

/*
printf("%o\n%o\n%o\n\n",x.parts.exponent,a,b);
*/
int main(int argc, char *argv[])
{
    float_cast to_operate;
    unsigned int a, b;
    if(argc == 1)
    {
        cout << "Input IEEE-754 floating point numbers to convert to PDP-8.\n";
        while(!cin.eof())
        {
            cin >> to_operate.f;
            a = (to_operate.parts.sign << 11) | (to_operate.parts.sig >> 12);
            b = (1 << 12) & to_operate.parts.sig;
            out_binary(to_operate,a,b);
        }
    }
    else if (argc == 2) 
    {
        if(strcmp(argv[1],"-h")==0)
        {
            while(!cin.eof())
            {
                cin >> to_operate.f;
                a = (to_operate.parts.sign << 11) | (to_operate.parts.sig >> 12);
                b = (1 << 12) & to_operate.parts.sig;
                printf("%x\n%x\n%x\n\n",to_operate.parts.exponent,a,b);
            }
        }
        else if(strcmp(argv[1],"-o")==0)
        {
            while(!cin.eof())
            {
                cin >> to_operate.f;
                a = (to_operate.parts.sign << 11) | (to_operate.parts.sig >> 12);
                b = (1 << 12) & to_operate.parts.sig;
                printf("%o\n%o\n%o\n\n",to_operate.parts.exponent,a,b);
            }
        }
    }

    return 0;

}
