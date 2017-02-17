
/*
 * Author: allen2660
 * 
 *
 * File: thread.cpp
 * Create Date: 2012-12-29 23:40:19
 *
 */

void reader_function ( void );
void writer_function ( void );

char buffer;
int buffer_has_item=0;
pthread_mutex_t mutex;
struct timespec delay;
void main ( void ){
    pthread_t reader;
    /* 定义延迟时间*/
    delay.tv_sec = 2;
    delay.tv_nec = 0;
    /* 用默认属性初始化一个互斥锁对象*/
    pthread_mutex_init (&mutex,NULL);
    pthread_create(&reader, pthread_attr_default, (void *)&reader_function), NULL);
    writer_function( );
}

void writer_function (void){
    while(1){
        /* 锁定互斥锁*/
        pthread_mutex_lock (&mutex);
        if (buffer_has_item==0){
            buffer=make_new_item( );
            buffer_has_item=1;
        }
        /* 打开互斥锁*/
        pthread_mutex_unlock(&mutex);
        pthread_delay_np(&delay);
    }
}

void reader_function(void){
    while(1){
        pthread_mutex_lock(&mutex);
        if(buffer_has_item==1){
            consume_item(buffer);
            buffer_has_item=0;
        }
        pthread_mutex_unlock(&mutex);
        pthread_delay_np(&delay);
    }
}



/* vim: set ts=4 sw=4: */

