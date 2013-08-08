/***************************************************************************
 *
 * Copyright (c) 2011 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/


/*
 * Author: liwei12 <liwei12@baidu.com>
 * 
 *
 * File: Frame.cpp
 * Create Date: 2012-12-28 12:26:59
 *
 */

#include <iostream>
#include "Frame.h"

using std::cout;
using std::endl;

//const  int tetris::TerminalDisplay::_COLS=10;
//const  int tetris::TerminalDisplay::_ROWS=20;

void tetris::TerminalDisplay::draw(){
    for(int i=0;i < _ROWS ;i++){
        for (int j=0;j < _COLS ; j++){
            if (1==_table[i][j]){
                cout<<"#";
            }else {
                cout<<" ";
            }
        }
        cout<<endl;
    }
    //system("clear");

}

void tetris::TerminalDisplay::addOneShape(IShape *shape){
    //Todo:切克下是否合法
    bool is_valid=true;
    Point &base_point=shape->_base_point;
    for(int i=0;i<shape->points.size();i++){
        Point &p=shape->points[i];
        if(_table[p.get_x()+base_point.get_x()][p.get_y()+base_point.get_y()] ==0 ){
            continue;
        }else{
            is_valid=false;
            break;
        } 
    }
    if (is_valid){
        for(int i=0;i<shape->points.size();i++){
            Point &p=shape->points[i];
            _table[p.get_x()+base_point.get_x()][p.get_y()+base_point.get_y()] =1;
        }

    }

    shapes.push_back(shape);


}
void tetris::TShape::rotate(){
    if(_status == STATUS_1){
        status_2();
        _status = STATUS_2;
    }else if(_status == STATUS_2){
        status_3();
        _status = STATUS_3;
    }else if (_status == STATUS_3){
        status_4();
        _status = STATUS_4;
    }else if (_status == STATUS_4){
        status_1();
        _status = STATUS_1;
    }else {
        //
    }


}

void tetris::TShape::status_1(){
    points.clear();
    points.push_back(Point(0,1));
    points.push_back(Point(1,0));
    points.push_back(Point(1,1));
    points.push_back(Point(1,2));

}

void tetris::TShape::status_2(){
    points.clear();
    points.push_back(Point(0,1));
    points.push_back(Point(1,0));
    points.push_back(Point(1,1));
    points.push_back(Point(2,1));
}

void tetris::TShape::status_3(){
    points.clear();
    points.push_back(Point(0,0));
    points.push_back(Point(0,1));
    points.push_back(Point(0,2));
    points.push_back(Point(1,1));

}

void tetris::TShape::status_4(){
    points.clear();
    points.push_back(Point(0,0));
    points.push_back(Point(1,0));
    points.push_back(Point(1,1));
    points.push_back(Point(2,0));

}
void tetris::TShape::down(){

    _base_point.add_x(1);

} 

void tetris::TShape::left(){
    _base_point.add_y(-1);
}

void tetris::TShape::right(){
    _base_point.add_y(1);
}



/* vim: set ts=4 sw=4: */

