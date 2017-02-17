


/*
 * Author: allen2660
 * 
 *
 * File: Container.cpp
 * Create Date: 2012-12-29 14:45:54
 *
 */
#include <iostream>
#include <math.h>
#include "Container.h"
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

bool tetris::Container::add_shape(IShape *shape){
    if (valid_shape(shape)){
        Point base_point=shape->_base_point;

        for(int i=0;i<shape->points().size();i++){ 
            Point p=shape->points()[i];
            _table[p.get_x()+base_point.get_x()][p.get_y()+base_point.get_y()]=1;
        } 

        return true;
    }
    return false;
}

bool tetris::Container::valid_shape(IShape *shape){
    //切克下是否合法
    bool is_valid=true;

    Point base_point=shape->base_point();
    int base_x=base_point.get_x();
    int base_y=base_point.get_y();
    //首先check下这些点是否越界
    //check下这些点是否和已有点重合
    for(int i=0;i<shape->points().size();i++){
        Point p=shape->points()[i];
        if(base_x+p.get_x() >19 ||base_x+p.get_x()<0){
            is_valid=false;
            break;
        }
        if(base_y+p.get_y() >9 ||base_y+p.get_y()<0){
            is_valid=false;
            break;
        }

        if(_table[p.get_x()+base_x][p.get_y()+base_y] ==0 ){
            continue;
        }else{
            is_valid=false;
            break;
        } 
    }
    return is_valid;

}

void tetris::Container::erase_shape(IShape *shape){
    Point base_point=shape->_base_point;

    for(int i=0;i<shape->points().size();i++){ 
        Point p=shape->points()[i];
        _table[p.get_x()+base_point.get_x()][p.get_y()+base_point.get_y()]=0;
    } 



}
bool tetris::Container::down(IShape *shape){
    erase_shape(shape);
    shape->down();
    if(add_shape(shape)){
        return true;
    }
    shape->up();
    add_shape(shape);

    return false;

}
bool tetris::Container::left(IShape *shape){
    erase_shape(shape);
    shape->left();
    if(add_shape(shape)){
        return true;
    }
    shape->right();
    add_shape(shape);

    return false;

}
bool tetris::Container::right(IShape *shape){
    erase_shape(shape);
    shape->right();
    if(add_shape(shape)){
        return true;
    }
    shape->left();
    add_shape(shape);

    return false;

}
bool tetris::Container::up(IShape *shape){
    erase_shape(shape);
    shape->rotate();
    if(add_shape(shape)){
        return true;
    }else{
        shape->rotate();
        shape->rotate();
        shape->rotate();
    }
    return false;

}
//一路滑到底
bool tetris::Container::down_to_end(IShape *shape){
    while(down(shape)){
        //dothing
    }

}
void tetris::Container::draw(){
    //下面需要输出下一个图形_next_shape
    vector<string> shape_lines;
    char shape_table[4][4]={0};

    Point base=_next_shape->base_point();
    vector<Point> pts = _next_shape->points();
    for(int i=0;i< pts.size();i++){
        shape_table[pts[i].get_x()][pts[i].get_y()]=1;
        //cout<<pts[i].get_x()<<" "<<pts[i].get_x()<<endl;
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            string tmp;
            shape_lines.push_back(tmp);
            if(shape_table[i][j]==1){
                shape_lines[i]+="[]";

            }else{
                shape_lines[i]+="  ";
            }

        }
      //  cout<<shape_lines[i]<<endl;
    }

    for(int i=0;i < 20 ;i++){
        cout<<"|";
        for (int j=0;j < 10 ; j++){
            if (1==_table[i][j]){
                cout<<"[]";
            }else {
                cout<<"  ";
            }
        }
        cout<<"|";
        if(i==4){
            cout<<"  Next Shape:";
        }

        if(i==5){
            cout<<"   "<<shape_lines[0];        
        }
        //输出下一个的第二行
        if(i==6){
            cout<<"   "<<shape_lines[1];        
        }
        //输出下一个的第三行
        if(i==7){

            cout<<"   "<<shape_lines[2];        
        }
        //输出下一个的第四行
        if(i==8){

            cout<<"   "<<shape_lines[3];        
        }
        if(i==15){
            cout<<"  Your score: "<<_score;
        }else if(i==17){
            cout<<"  Space: down";
        }
        cout<<endl;
    }
    cout<<"----------------------"<<endl;


}
bool tetris::Container::check_and_erase(){
    int lines_to_drop=0;
    for (int i=19;i>=0;i--){
        bool one_line_full=true;
        for (int j=0;j<10;j++){
            if(_table[i][j]==0){
                one_line_full=false;
                break;
            }
        }
        if(one_line_full){
            //本行会被消除
            ++lines_to_drop;
        }else{
            //本行需要往下坠one_line_full行
            for(int k=0;k<10;k++){
                _table[i + lines_to_drop][k]=_table[i][k];
            }
        }


    }
    if(lines_to_drop==0){
        return false;
    }else{
        //有某些行满了，且已经下坠
        //每次消掉n行，加分为n的平方
        _score+=lines_to_drop*lines_to_drop;
        return true;
    }
}
/* vim: set ts=4 sw=4: */

