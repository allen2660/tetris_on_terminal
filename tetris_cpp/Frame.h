/*
 * Author: allen2660
 * 
 *
 * File: Frame.h
 * Create Date: 2012-12-28 13:36:00
 *
 */
#ifndef TETRIS_FRAME_H
#define TETRIS_FRAME_H
#include <vector>

using std::vector;

namespace tetris {
    enum shape_status_t{
        STATUS_1,
        STATUS_2,
        STATUS_3,
        STATUS_4,
        STATUS_COUNT
    };

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

    class IShape{
    public:
        IShape(){}
        virtual ~IShape(){}
        //一个Shape的翻转
        virtual void rotate()=0;
        //一个Shape往下走
        virtual void down()=0;
        //ToDo:加速往下走
 
        virtual void left()=0;
        virtual void right()=0;
        
        Point _base_point;
        vector<Point> points;
    protected:
        shape_status_t _status;

    };

    class TShape:public IShape{
    public:
        TShape(){
            _status=STATUS_1;
            _base_point=Point(0,0);
            status_1();

        }
        ~TShape(){}

        void rotate();
        void down();
        void left();
        void right();
    private:

        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };

/*
    class Frame{
    public:
        Frame();
        virtual ~Frame();
        virtual paint();
        virtual refresh();
    private:
    };
*/
    class IDisplay{
    public:
        virtual ~IDisplay(){}
        virtual void draw()=0;
        //virtual void refresh()=0;
        virtual void addOneShape(IShape *)=0;
    };

    class TerminalDisplay :public IDisplay{
    public:
        
        TerminalDisplay(){
            init_table();
        //    _table[3][4]=1;
        }
        void draw();
        void addOneShape(IShape *);
    private:
        void init_table(){
            for (int i=0;i<_ROWS;i++){
                for (int j=0;j<_COLS;j++){
                    _table[i][j]=0;
                }
            }
        }
        const static int _COLS=10;
        const static int _ROWS=20;
        int  _table[_ROWS][_COLS];
        vector<IShape *> shapes;
        //int _table[][];
        //const static int _COLS;
        //const static int _ROWS;
    };

}//namespace



#endif
