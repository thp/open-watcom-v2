.func memcmp _fmemcmp wmemcmp
.synop begin
#include <string.h>
int memcmp( const void *s1,
            const void *s2,
            size_t length );
.ixfunc2 '&Compare' &func
.if &farfnc eq 1 .do begin
int _fmemcmp( const void __far *s1,
              const void __far *s2,
              size_t length );
.ixfunc2 '&Compare' &ffunc
.do end
.if &'length(&wfunc.) ne 0 .do begin
#include <wchar.h>
int wmemcmp( const wchar_t *s1,
             const wchar_t *s2,
	     size_t length );
.ixfunc2 '&Compare' &wfunc
.do end
.synop end
.desc begin
The
.id &func.
function compares the first
.arg length
characters of the object pointed to by
.arg s1
to the object pointed to by
.arg s2
.ct .li .
.im farparm
.if &'length(&wfunc.) ne 0 .do begin
.np
The
.id &wfunc.
wide-character function is identical to
.id &func.
except that it
operates on characters of
.kw wchar_t
type.
The argument
.arg length
is interpreted to mean the number of wide characters.
.do end
.desc end
.return begin
The
.id &func.
function returns an integer less than, equal to, or greater
than zero, indicating that the object pointed to by
.arg s1
is less than, equal to, or greater than the object pointed to by
.arg s2
.ct .li .
.return end
.see begin
.seelist &function. memchr memcmp memcpy memicmp memset
.see end
.exmp begin
#include <stdio.h>
#include <string.h>

void main( void )
{
    auto char buffer[80];
.exmp break
    strcpy( buffer, "world" );
    if( memcmp( buffer, "Hello ", 6 ) < 0 ) {
        printf( "Less than\n" );
    }
}
.exmp end
.class ANSI
.system
