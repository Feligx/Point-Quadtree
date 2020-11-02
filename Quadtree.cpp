#include "Quadtree.hpp"
#include <iostream>
//#include <SDL2/SDL.h>

using namespace std;

template <typename T>
QuadNode<T>::QuadNode(int x, int y, int w, int h , int c){
    bounds.set_x(x);
    bounds.set_y(y);
    bounds.set_height(h);
    bounds.set_width(w);
    capacity = c;

    parent = nullptr;
    NW = nullptr;
    NE = nullptr;
    SW = nullptr;
    SE = nullptr;
}

template <typename T>
Quadtree<T>::Quadtree(int x, int y, int w, int h , int c){
    root= new QuadNode<T>(x,y,w,h,c);
    capacity = c;
}

template <typename T>
bool QuadNode<T>::isLeaf(){return NW==nullptr;}

template <typename T>
bool QuadNode<T>::insert(Point<T> point){
    if(!this->bounds->contains(point)){
        return false;
    }

    if(isLeaf()){
        if (count < capacity){
            this->data[count] = point;
            count++;
            return true;
        }
        split();
    }
    if(NW->insert(point)){
        return true;
    }
    
    if(NE->insert(point)){
        return true;
    }
    
    if(SW->insert(point)){
        return true;
    }
    
    if(SE->insert(point)){
        return true;
    }
    
    cout << "maybe the point is duplicated..." << endl;

    return false;
}

template <typename T>
void QuadNode<T>::split(){
    int x= bounds->x;
    int y= bounds->y;
    int w= bounds->w;
    int h= bounds->h;

    //creacion de los 4 nodos hijos segun el limite de su respectivo cuadrante
    NW= new QuadNode<T>( x , y , w/2 , h/2 );
    NE= new QuadNode<T>( x + w/2 ,y ,w/2 ,h/2 );
    SW= new QuadNode<T>( x , y + h ,w/2,h/2);
    SE= new QuadNode<T>( x + w/2 , y + h/2 , w/2 , h/2 );

    //encuentra un hijo en el cual incluir cada punto de los que estan en data[]
    for(int i = 0; i < count; i++){
        if(NW->insert(data[i])){
            continue;
        }
        if(NE->insert(data[i])){
            continue;
        }
        if(SW->insert(data[i])){
            continue;
        }
        if(SE->insert(data[i])){
            continue;
        }
        cout << "failed to place existing point after subdivide()" << endl;  
    }
}


int main(){
    return 0;
}