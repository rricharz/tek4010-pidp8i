//  tektoOS8 - convert Tektronix 4010 plot file
//  to OS/8 compatible format
//  rricharz 2020

//  convert all control characters to ^letter
//  (including CR and LF)
//  add a CRLF every 40 characters
//  convert ^ to ^#
//  convert ASCII(127) to `!

#include <stdio.h>
#include <stdlib.h>

#define MAX 40

FILE *finput;
FILE *foutput;

/*****************/
void closeAndExit()
/*****************/
{
    if (finput != NULL)
        fclose(finput);
    if (foutput != NULL)
        fclose(foutput);
    printf("%5d: tektoOS8 exit with error\n");
    exit (-1);
}

/******************************/
int main(int argc, char *argv[])
/******************************/
{
    int c, count;

    printf("tektoOS8 version 0.1\n");

    if (argc != 3) {
        printf("Usage: tektoOS8 input_filename output_filename\n");
        closeAndExit();
    }

    finput = fopen(argv[1], "r");         // open input file for read
    if (finput == NULL) {
        printf("Cannot open %s\n",argv[1]);
        closeAndExit();
    }
    
    foutput = fopen(argv[2], "w");      // open output file for read/write
    if (foutput == NULL) {
        printf("Cannot open %s\n",argv[2]);
        closeAndExit();
    }

    count = 0;
    
    while ((c = (fgetc(finput) & 0x7F)) != EOF) {
        count++;
        if (c == 0) printf("NULL\n");
        
        if (c < 32) { // convert control characters
            fputc('^', foutput);
            fputc(c + '@', foutput);
        }
        else if (c == '^') { // convert ^
            fputc('^', foutput);
            fputc('#', foutput);
        }
        else if (c == 127) { // convert ASCII(127)
            fputc('^', foutput);
            fputc('!', foutput);
        }
        else
            fputc(c, foutput);
        if (count>MAX) {
            fputc(13, foutput);
            fputc(10, foutput);
            count = 0;
        }
    }
    
    fclose(finput);
    fclose(foutput);
    exit(0);
}
