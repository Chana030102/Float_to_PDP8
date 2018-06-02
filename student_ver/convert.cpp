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
 * With no arguments, converter will continuously accept user
 * input of float numbers and output as octal.
 *
 * If a float number is used as an argument, converter will only
 * convert that and end. 
 *
 * Commandline Flags:
 *    -b    outputs bits in binary
 *    -h    outputs bits in hex 
 *    -o    outputs bits in octal
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <math.h>
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

void out_binary(float_cast x, unsigned int a, unsigned int b);

int main(int argc, char *argv[])
{
    float_cast to_operate;
    unsigned int a, b;
    int format = 0;
    
    if(argc > 1)
    {
        // Determine output format or convert given float number
        if(strcmp(argv[1],"-h")==0)
            format = 1;
        else if(strcmp(argv[1],"-b")==0)
            format = 2;
        else if(strcmp(argv[1],"-o")==0)
            format = 0;
        else
        {
            to_operate.f = atof(argv[1]);
            if(isinf(to_operate.f))
            {
                to_operate.parts.sig = 0;
                to_operate.parts.exponent = 255;
            }
            else if(isnan(to_operate.f))
                to_operate.parts.exponent = 255;

            a = (to_operate.parts.sign << 11) | (to_operate.parts.sig >> 12);
            b = (1 << 12) & to_operate.parts.sig;
            printf("%o\n%o\n%o\n\n",to_operate.parts.exponent,a,b); 
            return 0;
        }

        if(argc == 3) // convert provided float number with desired format
        {
            to_operate.f = atof(argv[2]);
            
            if(isinf(to_operate.f))
            {
                to_operate.parts.sig = 0;
                to_operate.parts.exponent = 255;
            }
            else if(isnan(to_operate.f))
                to_operate.parts.exponent = 255;
            
            a = (to_operate.parts.sign << 11) | (to_operate.parts.sig >> 12);
            b = (1 << 12) & to_operate.parts.sig;
            
            if(format == 1) // output as hex
                printf("%x\n%x\n%x\n\n",to_operate.parts.exponent,a,b);
            else if(format == 2) // output as binary
                out_binary(to_operate,a,b);
            else // default output as octal 
                printf("%o\n%o\n%o\n\n",to_operate.parts.exponent,a,b); 
            
            return 0;
        }
        
    }
    
    while(!cin.eof()) // get user input until Ctrl+D
    {
        cin >> to_operate.f;
        
        if(isinf(to_operate.f))
        {
            to_operate.parts.sig = 0;
            to_operate.parts.exponent = 255;
        }
        else if(isnan(to_operate.f))
            to_operate.parts.exponent = 255;
        
        a = (to_operate.parts.sign << 11) | (to_operate.parts.sig >> 12);
        b = (1 << 12) & to_operate.parts.sig;

        if(format == 1) // output as hex
            printf("%x\n%x\n%x\n\n",to_operate.parts.exponent,a,b);
        else if(format == 2) // output as binary
            out_binary(to_operate,a,b);
        else // default output as octal 
            printf("%o\n%o\n%o\n\n",to_operate.parts.exponent,a,b); 
    }
    return 0;

}

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

