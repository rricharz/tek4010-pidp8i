//  tektoOS8 - convert Tektronix 4010 plot file
//  to OS/8 compatible format
//  rricharz 2020

//  convert all control characters to ^letter
//  (including CR and LF)
//  add a CRLF every 40 characters
//  convert ^ to ^#
//  convert ASCII(127) to ^!

//  https://github.com/rricharz/tek4010-pidp8i

//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//  MA 02110-1301, USA.

//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//  MA 02110-1301, USA.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("tektoOS8 exit with error\n");
    exit (-1);
}

/******************************/
int main(int argc, char *argv[])
/******************************/
{
#define SLENGTH 127

    int c, count;
    char s[SLENGTH];

    printf("tektoOS8 version 0.2\n");

    if (argc != 2) {
        printf("Usage: tektoOS8 filename (without extension)\n");
        closeAndExit();
    }
    
    if (strlen(argv[1]) > (SLENGTH - 5)) {
        printf("File name %s is too long\n", argv[1]);
        closeAndExit();
    }
    
    strcpy(s, argv[1]);
    strcat(s,".plt");

    finput = fopen(s, "r");         // open input file for read
    if (finput == NULL) {
        printf("Cannot open %s\n",s);
        closeAndExit();
    }
    
    strcpy(s, argv[1]);
    strcat(s,".p8");
    
    foutput = fopen(s, "w");      // open output file for read/write
    if (foutput == NULL) {
        printf("Cannot open %s\n",s);
        closeAndExit();
    }

    count = 0;
    
    while ((c = fgetc(finput)) != EOF) {
        count++;
        c = c & 0x7F;
        
        if (c == 95) c = 94;
        
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
        else if (c == 95) { // convert ASCII(95)
            fputc('^', foutput);
            fputc('+', foutput);
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
