/*
 * Author: allen2660
 * 
 *
 * File: Shape.h
 * Create Date: 2012-12-29 14:19:42
 *
 */

#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H
#include <vector>
#include "Point.h"
using std::vector;
namespace tetris{
    enum shape_status_t{
        STATUS_1,
        STATUS_2,
        STATUS_3,
        STATUS_4,
        STATUS_COUNT
    };

    enum shape_t{
        TSHAPE,
        LSHAPE,
        JSHAPE,
        HLSHAPE,
        HJSHAPE,
        LINESHAPE,
        OSHAPE,
        SHAPE_COUNT
    };
    class IShape{
    public:
        IShape(){}
        virtual ~IShape(){}
        //一个Shape的翻转,逆时针旋转，左上角的base_point不变
        virtual void rotate();
        //一个Shape往下走
        virtual void down();
        virtual void up();
        //ToDo:加速往下走

        virtual void left();
        virtual void right();
        const vector<Point> &points(){
            return _points;
        }
        const Point &base_point(){
            return _base_point;
        }
        Point _base_point;
        vector<Point> _points;
    protected:
        shape_status_t _status;
    private:
        virtual void status_1()=0;
        virtual void status_2()=0;
        virtual void status_3()=0;
        virtual void status_4()=0;


    };

    class TShape:public IShape{
    public:
        TShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();

        }
        ~TShape(){}
    private:

        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };
    class LShape:public IShape{
    public:
        LShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();

        }
        ~LShape(){}
    private:

        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };
    class JShape:public IShape{
    public:
        JShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();
        }
        ~JShape(){}
    private:

        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };
    class HLShape:public IShape{
    public:
        HLShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();

        }
        ~HLShape(){}
    private:
        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };
    class HJShape:public IShape{
    public:
        HJShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();

        }
        ~HJShape(){}
    private:
        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };
    class LineShape:public IShape{
    public:
        LineShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();

        }
        ~LineShape(){}
    private:
        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };

    class OShape:public IShape{
    public:
        OShape(){
            _status=STATUS_1;
            _base_point=Point(0,4);
            status_1();

        }
        ~OShape(){}
    private:
        void status_1();
        void status_2();
        void status_3();
        void status_4();
    };


}//namespace tetris
#endif
