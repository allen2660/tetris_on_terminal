/*
 * Author: liwei12 <liwei12@baidu.com>
 * 
 *
 * File: kb_util.h
 * Create Date: 2012-12-29 21:49:19
 *
 */

// 在linux下需要修改terminal的属性
#include "kb_util.h"
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#undef TERMIOSECHO
#define TERMIOSFLUSH

/*
 * kbhit() — a keyboard lookahead monitor
 *
 * returns the number of characters available to read
 */
int kbhit ( void )
{
    struct timeval tv;
    struct termios old_termios, new_termios;
    int            error;
    int            count = 0;
    tcgetattr( 0, &old_termios );
    new_termios              = old_termios;
    /*
     * raw mode
     */
    new_termios.c_lflag     &= ~ICANON;
    /*
     * disable echoing the char as it is typed
     */
    new_termios.c_lflag     &= ~ECHO;
    /*
     * minimum chars to wait for
     */
    new_termios.c_cc[VMIN]   = 1;
    /*
     * minimum wait time, 1 * 0.10s
     */
    new_termios.c_cc[VTIME]  = 1;
    error                    = tcsetattr( 0, TCSANOW, &new_termios );
    tv.tv_sec                = 0;
    tv.tv_usec               = 100;
    /*
     * insert a minimal delay
     */
    select( 1, NULL, NULL, NULL, &tv );
    error                   += ioctl( 0, FIONREAD, &count );
    error                   += tcsetattr( 0, TCSANOW, &old_termios );
    return( error == 0 ? count : -1 );
}  /* end of kbhit */
/*————————————————*/
int getch( void )
{
    int c = 0;
    struct termios org_opts, new_opts;
    int res = 0;
    //—–  store old settings ———–
    res = tcgetattr( STDIN_FILENO, &org_opts );
    assert( res == 0 );
    //—- set new terminal parms ——–
    memcpy( &new_opts, &org_opts, sizeof(new_opts) );
    new_opts.c_lflag &= ~( ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL );
    tcsetattr( STDIN_FILENO, TCSANOW, &new_opts );
    c = getchar();
    //——  restore old settings ———
    res = tcsetattr( STDIN_FILENO, TCSANOW, &org_opts );
    assert( res == 0 );
    return( c );
}

/*
int main(){
    char c;
    int i;
    while(1){
        while(i=kbhit()){
            printf("You entered %d chars:",i);
            for(int ii=0;ii<i;ii++){
               c=getch();
               printf("\t%x",c);
            }
            printf("\n");
        }
    }


}*/
