
/*
 * Author: allen2660
 * 
 *
 * File: test_kb_util.cpp
 * Create Date: 2012-12-30 14:58:34
 *
 */
#include "kb_util.h"
#include <stdio.h>

int main(){
    char c;
    int i;
    while(1){
        while(i=kbhit()){
            printf("You entered %d chars:",i);
            for(int ii=0;ii<i;ii++){
                c=getch();
                //printf(" 0x%x(%c)",c,c);
                printf(" 0x%x",c);
            }
            printf("\n");
        }
    }


}



/* vim: set ts=4 sw=4: */

