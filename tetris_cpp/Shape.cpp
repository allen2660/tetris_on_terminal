


/*
 * Author: allen2660
 * 
 *
 * File: Shape.cpp
 * Create Date: 2012-12-29 14:23:19
 *
 */

#include "Shape.h"
void tetris::IShape::down(){

    _base_point.add_x(1);

} 
void tetris::IShape::up(){

    _base_point.add_x(-1);

} 
void tetris::IShape::left(){
    _base_point.add_y(-1);
}

void tetris::IShape::right(){
    _base_point.add_y(1);
}


void tetris::IShape::rotate(){
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
//TShape 的初始状态为一个土
//   #
//  ###
void tetris::TShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(1,2));

}
//    #
//   ##
//    #
void tetris::TShape::status_2(){
    _points.clear();
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(2,1));
}

void tetris::TShape::status_3(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(0,2));
    _points.push_back(Point(1,1));

}

void tetris::TShape::status_4(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(2,0));

}


//LShape 的初始状态为一个L
//   #
//   #
//   ##
void tetris::LShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(1,0));
    _points.push_back(Point(2,0));
    _points.push_back(Point(2,1));

}

//     #
//   ###
void tetris::LShape::status_2(){
    _points.clear();
    _points.push_back(Point(0,2));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(1,2));
}
//  ##
//   #
//   #
void tetris::LShape::status_3(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,1));
    _points.push_back(Point(2,1));

}
// ###
// #
void tetris::LShape::status_4(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(0,2));
    _points.push_back(Point(1,0));

}
//JShape 的初始状态为一个
//  #
//  #
// ##
void tetris::JShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,1));
    _points.push_back(Point(2,1));
    _points.push_back(Point(2,2));

}
//  ###
//    #
void tetris::JShape::status_2(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(0,2));
    _points.push_back(Point(1,2));
}
//  ##
//  #
//  #
void tetris::JShape::status_3(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,0));
    _points.push_back(Point(2,0));

}
//  #
//  ###
void tetris::JShape::status_4(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(1,2));

}

//HLShape 的初始状态为一个
//#
//##
// #
void tetris::HLShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(2,1));

}
// ##
//##
void tetris::HLShape::status_2(){
    _points.clear();
    _points.push_back(Point(0,1));
    _points.push_back(Point(0,2));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
}
// #
// ##
//  #
void tetris::HLShape::status_3(){
    status_1();
}

void tetris::HLShape::status_4(){
    status_2();
}

//HJShape 的初始状态为一个
// @
//@@
//@
void tetris::HJShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));
    _points.push_back(Point(2,0));

}
// @@
//  @@
void tetris::HJShape::status_2(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,1));
    _points.push_back(Point(1,2));
}

void tetris::HJShape::status_3(){
    status_1();
}

void tetris::HJShape::status_4(){
    status_2();
}

//LineShape 的初始状态为一个
//   #
//   #
//   #
//   #
void tetris::LineShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(1,0));
    _points.push_back(Point(2,0));
    _points.push_back(Point(3,0));

}
//####
void tetris::LineShape::status_2(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(0,2));
    _points.push_back(Point(0,3));
}
//#
//#
//#
//#
void tetris::LineShape::status_3(){
    status_1();
}
//####
void tetris::LineShape::status_4(){
    status_2();
}
//OShape 的初始状态为一个
//   ##
//   ##
void tetris::OShape::status_1(){
    _points.clear();
    _points.push_back(Point(0,0));
    _points.push_back(Point(0,1));
    _points.push_back(Point(1,0));
    _points.push_back(Point(1,1));

}

void tetris::OShape::status_2(){
    status_1();
}

void tetris::OShape::status_3(){
    status_1();
}

void tetris::OShape::status_4(){
    status_1();
}





//

/* vim: set ts=4 sw=4: */

