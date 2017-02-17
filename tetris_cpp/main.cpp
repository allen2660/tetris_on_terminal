


/*
 * Author: allen2660
 * 
 *
 * File: main.cpp
 * Create Date: 2012-12-27 22:30:01
 *
 */
#include <stdlib.h>
#include <iostream>
#include "Container.h"
#include <pthread.h>
#include "ShapeFactory.h"
#include "KBListener.h"

using std::cout;
using std::endl;
using namespace tetris;

pthread_mutex_t mutex; 
control_t key_input=KEY_COUNT;
void *listen(void *ptr){
    while(true){
        KBListener listener;
        control_t input=listener.listen();
        //此处需要加锁
        pthread_mutex_lock (&mutex);
        key_input=input;
        //释放锁
        pthread_mutex_unlock(&mutex);
    }
}
void tetris_main(){
     Container container;
    ShapeFactory factory;
    IShape *s;
    IShape *next_s=factory.gen_random_shape();
    while(true){
        //开始新加入一个形状
        s=next_s;
        next_s=factory.gen_random_shape();
        container.set_next_shape(next_s);
        container.add_shape(s);
        do{
            //每0.1秒检查一次是否有输入
            //没检查五次，当前的Shape往下走一次
            for(int i=0;i<5;i++){
                system("clear");
                container.draw();
                //接受方向键输入，改变形状,重新绘图
                //此处需要加锁
                pthread_mutex_lock (&mutex);
                if(key_input == UP){
                    if(container.up(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==DOWN){
                    //用户输入了down
                    if(container.down(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==LEFT){
                    //用户输入了向左
                    if(container.left(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==RIGHT){
                    //用户输入了向右
                    if(container.right(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==SPACE){
                    if(container.down_to_end(s)){
                        system("clear");
                        container.draw();
                    }
                }

                //释放锁
                key_input=KEY_COUNT;
                pthread_mutex_unlock(&mutex);
                usleep(100000);
            }//for
        }while(container.down(s));
        //不能这个形状不能再下降了
        if(container.check_and_erase()){
            //需要删除某些行
            system("clear");
            container.draw();
        }

        delete s;
    }//while(true)

}

int main()
{
    //清屏
    system("clear");
    cout<<"-------------------------------Tetris------------------------------"<<endl;
    pthread_t reader;
    pthread_mutex_init (&mutex,NULL);
    pthread_create(&reader, NULL, &listen, NULL);
    tetris_main();
    return 0;
}



/* vim: set ts=4 sw=4: */

