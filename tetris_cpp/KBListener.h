/*
 * Author: allen2660
 * 
 *
 * File: KBListener.h
 * Create Date: 2012-12-29 22:11:57
 *
 */
#include "kb_util.h"
#include <stdio.h>
#include <string.h>
namespace tetris{
    enum control_t{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        KEY_COUNT
    };
    class KBListener{
    public:
        control_t listen(){
            char up[3]={'\x1b','\x5b','\x41'};
            /*
            for (int j=0;j<3;j++){
                printf("%x\n",up[j]);
            }*/
            char down[3]={'\x1b','\x5b','\x42'};
            char left[3]={'\x1b','\x5b','\x44'};
            char right[3]={'\x1b','\x5b','\x43'};
            char space[1]={'\x20'};
            char buf[10]={0};
            char c;
            int i;
            while(0==(i=kbhit())){
            }

            for(int ii=0;ii<i;ii++){
                buf[ii]=getch();
               // printf("%x\n",buf[ii]);
            }
            if(0==strncmp(buf,up,3)){
                //用户输入了up
               // printf("用户输入了up\n");
                return UP;
            }else if(0==strncmp(buf,down,3)){
               // printf("用户输入了down\n");
                return DOWN;
            }else if(0==strncmp(buf,left,3)){
                //用户输入了left
               // printf("用户输入了left\n");
                return LEFT;
            }else if(0==strncmp(buf,right,3)){
                //用户输入了right
                //printf("用户输入了right\n");
                return RIGHT;
            }else if (0==strncmp(buf,space,1)){
                //printf("用户输入了空格\n");
                return SPACE;
            }else {
               printf("你输入了：\t");
               for(int ii=0;ii<i;ii++){
                   c=getch();
                   printf("0x%x",c);
               }
               printf("\n");
                return KEY_COUNT;
            }
        }
    };
}
