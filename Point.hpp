#ifndef _POINT_HPP
#define _POINT_HPP

#include <iostream>
#include <vector>

using namespace std;

class Point{
private:
public:
    int x;
    int y;
    //constructor sin argumentos, coloca un valor por definición de 0 para ambas coordenadas
    Point(){x=0; y=0;}
    //constructor que pide como argumentos las coordenadas x e y y las asigna a los valores correspondientes
    Point(int x_cor, int y_cor){x=x_cor; y= y_cor;}
    ~Point(){delete this;};
    void print_point(Point point);
};

void Point::print_point(Point point){
    cout << "x: " <<x << endl;
    cout << "y: " <<y << endl;
}


// FINAL DE LA CLASE Y MÉTODOS POINT


class Rectangle
{
private:
    /* data */
public:
    int x, y, w, h;
    //constructor pide una cordenada x,y y además la altura y ancho del rectángulo
    Rectangle(int x_cor, int y_cor, int width, int height);
    ~Rectangle();
    bool contain(Point point);
};


Rectangle::Rectangle(int x_cor=0, int y_cor=0, int width=0, int height=0)
{
    x=x_cor;
    y=y_cor;
    w=width;
    h=height;
}

Rectangle::~Rectangle()
{
}

bool Rectangle::contain(Point point){
    //bool ans = (point.x > x - w && point.x < x+y && point.y > y-h && point.y < y+h);
    return true;
}

//FINAL DE LA CLASE Y MÉTODOS RECTANGLE

class QuadTree
{
private:
    int capacity; //capacidad máxima de puntos por nodo del quadtree
    vector<Point> points_vec;//vector donde se almacenan los puntos del nodo
    //QuadTree NW;
    //QuadTree NE;
    //QuadTree SW;
    //QuadTree SE;

public:
    Rectangle Perimetro;     //Medidas del quadtree
    bool divided = false;
    QuadTree(){Perimetro.x = 0; Perimetro.y=0; Perimetro.h=0; Perimetro.w=0; capacity = 0;};
    QuadTree(Rectangle p, int c);
    ~QuadTree();
    bool insert(Point point);
    void split();
    
};

QuadTree::QuadTree(Rectangle p, int c)
{
    //Rectangle Perimetro (p.x,p.y,p.w,p.h);
    Perimetro.x = p.x;
    Perimetro.y=p.y;
    Perimetro.h=p.h;
    Perimetro.w=p.w;
    capacity = c;
}

QuadTree::~QuadTree()
{
}

void QuadTree::split(){
    int x = Perimetro.x; //HACER FUNCION PARA RETORNAR LOS VALORES DEL RECTANGLE
    int y = Perimetro.y;
    int w = Perimetro.w;
    int h = Perimetro.h;

    Rectangle ne ((x + w)/2, (y-h)/2, w/2 , h/2);
    Rectangle nw ((x - w)/2, (y-h)/2, w/2 , h/2);
    Rectangle se ((x + w)/2, (y+h)/2, w/2 , h/2);
    Rectangle sw ((x - w)/2, (y+h)/2, w/2 , h/2);
    QuadTree NW (nw, 4);
    QuadTree NE (ne, 4);
    QuadTree SW (sw, 4);
    QuadTree SE (se, 4);
    divided = true;
}

bool QuadTree::insert(Point point){
    vector<Point> points = points_vec;
    int size = points.size();
    bool ans = true;

    cout << "contains? " << ans <<endl;

    if(ans){
        //cout << "else!" << endl;
        if (size < capacity){
            cout<<"pushing back!"<<endl;
            points.push_back(point);
            for(int i=0; i < points.size(); i++){
                Point p = points[i];
                cout << "printing " << i <<" point: " <<endl;
                p.print_point(points[i]);
            }
        
            return true;
        }
    
        else{
            cout<<"else" << endl;
            if(!divided){
                cout<<"spliting!" << endl;
                this->split();
            }
            //if (NE.insert(point)) return true;
            //if (NW.insert(point)) return true;
            //if (SW.insert(point)) return true;
            //if (SE.insert(point)) return true;
        }

    }
    else{
        cout<<"void"<<endl;
        return false;
    }
    cout << "hola" << endl;
    cout << "printing" << endl;

    for(int i=0; i < 4; i++){
        Point p = points[i];
        //cout << "aqui" << endl;
        p.print_point(points[i]);
    }
    return false;
}

#endif

int main(){
    int a=200;
    Rectangle perim (a,a,a,a);
    QuadTree qt (perim, 4);
    Point p (1, 12);
    cout << qt.insert(p);

    return 0;
}