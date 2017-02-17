


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
        //�˴���Ҫ����
        pthread_mutex_lock (&mutex);
        key_input=input;
        //�ͷ���
        pthread_mutex_unlock(&mutex);
    }
}
void tetris_main(){
     Container container;
    ShapeFactory factory;
    IShape *s;
    IShape *next_s=factory.gen_random_shape();
    while(true){
        //��ʼ�¼���һ����״
        s=next_s;
        next_s=factory.gen_random_shape();
        container.set_next_shape(next_s);
        container.add_shape(s);
        do{
            //ÿ0.1����һ���Ƿ�������
            //û�����Σ���ǰ��Shape������һ��
            for(int i=0;i<5;i++){
                system("clear");
                container.draw();
                //���ܷ�������룬�ı���״,���»�ͼ
                //�˴���Ҫ����
                pthread_mutex_lock (&mutex);
                if(key_input == UP){
                    if(container.up(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==DOWN){
                    //�û�������down
                    if(container.down(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==LEFT){
                    //�û�����������
                    if(container.left(s)){
                        system("clear");
                        container.draw();
                    }
                }else if(key_input==RIGHT){
                    //�û�����������
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

                //�ͷ���
                key_input=KEY_COUNT;
                pthread_mutex_unlock(&mutex);
                usleep(100000);
            }//for
        }while(container.down(s));
        //���������״�������½���
        if(container.check_and_erase()){
            //��Ҫɾ��ĳЩ��
            system("clear");
            container.draw();
        }

        delete s;
    }//while(true)

}

int main()
{
    //����
    system("clear");
    cout<<"-------------------------------Tetris------------------------------"<<endl;
    pthread_t reader;
    pthread_mutex_init (&mutex,NULL);
    pthread_create(&reader, NULL, &listen, NULL);
    tetris_main();
    return 0;
}



/* vim: set ts=4 sw=4: */

