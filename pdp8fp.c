/*
 *
 *   Read floating number on command line and output three word PDP-8 floating point
 *   representation.   Most significant 12-bit word is biased exponent.  Next
 *   word is sign bit and 11 most significant bits of significand.   Third word is remaining
 *   12 bits of significand.  Word are printed in most to least significant order.
 *
 *	Accept either -h or -o on command line to indicate radix (hex or octal).
 *  If omitted, radix is octal.   If floating point number doesn't appear on command line
 *	stdin is read until EOF with each converted value going to stdout.
 *
 */


// #define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void print(char *format, unsigned int n) {

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
fprintf(stderr,"pdp8fp [-o | -h] [real]\n");
}


int main (int argc, char **argv) {

union {
	float f;
	unsigned int n;
	} fp;

char *octalformat = "%04o\n";
char *hexformat = "%03x\n";
char *format = octalformat;
int i;
int switchseen = 0;

if (argc >3) {
  usage();
  exit(1);
  }

for (i = 1; i < argc; i++) {
  if (!strncmp("-h", argv[i],2)) {
      if (switchseen) {
        usage();
        exit(1);
        }
      else {
       format = hexformat;
       switchseen = 1;
       }
      }
  else if (!strncmp("-o", argv[i],2)) {
      if (switchseen) {
        usage();
        exit(1);
        }
      else {
       format = octalformat;
       switchseen = 1;
       }
    }
  else {
    fp.f = strtof(argv[i], NULL);
    print(format,fp.n);
    exit(0);
    }
  }


/* number not specified on command line.   read them from stdin until EOF */

while (!feof(stdin)) {
  scanf("%g",&fp.f);
  print(format,fp.n);
  }
}
