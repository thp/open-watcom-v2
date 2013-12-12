.func jstrerror
.synop begin
#include <jstring.h>
unsigned char *jstrerror( int errnum );
.ixfunc2 '&Jstring' &func
.ixfunc2 '&Errs' &func
.synop end
.desc begin
The
.id &func.
function maps the error number contained in
.arg errnum
to a Kanji error message.
.desc end
.return begin
The
.id &func.
function returns a pointer to the Kanji error message.
The array containing the error string should not be modified by the
program.
This array may be overwritten by a subsequent call to the &func
function.
.return end
.see begin
.seelist jstrerror jperror strerror perror
.see end
.exmp begin
#include <stdio.h>
#include <jstring.h>
#include <errno.h>

void main()
  {
    FILE *fp;
.exmp break
    fp = fopen( "file.nam", "r" );
    if( fp == NULL ) {
        printf( "Unable to open file: %s\n",
                 jstrerror( errno ) );
    }
  }
.exmp end
.class WATCOM
.system
