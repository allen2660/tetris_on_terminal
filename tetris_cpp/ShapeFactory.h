/*
 * Author: liwei12 <liwei12@baidu.com>
 * 
 *
 * File: ShapeFactory.h
 * Create Date: 2012-12-29 15:50:07
 *
 */
#ifndef TETRIS_SHAPE_FACTORY_H
#define TETRIS_SHAPE_FACTORY_H
#include "Shape.h"
#include <stdlib.h>
#include <ctime>
//此处采用简单工厂模式
namespace tetris{
    class ShapeFactory {
    public :
        IShape *gen_TShape(){
            return new TShape();
        }
        IShape *gen_LShape(){
            return new LShape();
        }
        IShape *gen_JShape(){
            return new JShape();
        }
        IShape *gen_HLShape(){
            return new HLShape();
        }
        IShape *gen_HJShape(){
            return new HJShape();
        }
        IShape *gen_LineShape(){
            return new LineShape();
        }
        IShape *gen_OShape(){
            return new OShape();
        }
        IShape *gen_shape(shape_t type){
            switch(type){
                case TSHAPE:
                    return new TShape();
                    break;
                case LSHAPE:
                    return new LShape();
                    break;
                case JSHAPE:
                    return new JShape();
                    break;
                case HLSHAPE:
                    return new HLShape();
                    break;
                case HJSHAPE:
                    return new HJShape();
                    break;
                case LINESHAPE:
                    return new LineShape();
                    break;
                case OSHAPE:
                    return new OShape();
                    break;
                default:
                    return NULL;
                    break;
            }
        }
        IShape *gen_random_shape(){
            srand((unsigned)time(0));
            int ran_num=rand()% SHAPE_COUNT;
            return gen_shape((shape_t)ran_num);
        }
    };
}
#endif
