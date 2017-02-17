/*
 * Author: allen2660
 * 
 *
 * File: Point.h
 * Create Date: 2012-12-29 14:11:20
 *
 */
#ifndef TETRIS_POINT_H
#define TETRIS_POINT_H
namespace tetris {
    class Point{
    public:
        Point(){
            _x=0;
            _y=0;
        }
        Point(int x,int y)
            :_x(x),_y(y){};
        ~Point(){};
        void add_x(int x){
            _x+=x;
        }
        void add_y(int y){
            _y+=y;
        }
        int get_x(){
            return _x;
        }
        int get_y(){
            return _y;
        }
    private:
        int _x;
        int _y;
    };

}//namespace tetris
#endif
