/*
 * Author: allen2660
 * 
 *
 * File: Container.h
 * Create Date: 2012-12-29 14:30:38
 *
 */

#ifndef TETRIS_CONTAINER_H
#define TETRIS_CONTAINER_H
#include "Point.h"
#include "Shape.h"

namespace tetris {
    class Container{
    public:
        Container():_score(0){
            for(int i=0;i<20;i++){
                for(int j=0;j<10;j++){
                    _table[i][j]=0;
                }
            }
        }
        //加入一个Shape，check这个Shape是否越界？
        bool add_shape(IShape *);
        //消除一个Shape
        void erase_shape(IShape *);
        //其中的Shape往下走一格，碰到地下判断是否可以消除，然后新加入一个Shape
        bool down(IShape *);
        //执行一个动作，上下左右
        bool left(IShape *);
        bool right(IShape *);
        bool up(IShape *);
        bool down_to_end(IShape *);
        void draw();
        bool check_and_erase();
        void set_next_shape(IShape * n){
            _next_shape=n;
        }
    private:
        bool valid_shape(IShape *);
        IShape *current_shape;
        IShape *_next_shape;
        int _table[20][10];
        int _score; 
    
    };
}//namespace tetris
#endif
