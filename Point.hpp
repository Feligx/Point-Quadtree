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
    //función que imprime las coordenadas de un punto
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
public:
    int x, y, w, h;
    //constructor pide una cordenada x,y y además la altura y ancho del rectángulo
    Rectangle(int x_cor, int y_cor, int width, int height);
    ~Rectangle();
    bool contain(Point point);
};


Rectangle::Rectangle(int x_cor=0, int y_cor=0, int width=0, int height=0)
{
    x=x_cor; //coordenada x del rectangulo
    y=y_cor; //coordenada y del rectangulo
    w=width; //ancho del rectangulo
    h=height; //alto del rectangulo
}

Rectangle::~Rectangle()
{
}

bool Rectangle::contain(Point point){
    bool ans = ((point.x > x - w && point.x < x+y) && (point.y > y-h && point.y < y+h));
    return ans;
}

//FINAL DE LA CLASE Y MÉTODOS RECTANGLE


//INICIO DE LA CLASE QUADTREE
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
    bool divided = false;  //Es true si está dividido, es false si no está dividido
    QuadTree(){Perimetro.x = 0; Perimetro.y=0; Perimetro.h=0; Perimetro.w=0; capacity = 0;};
    QuadTree(Rectangle p, int c);
    ~QuadTree();
    // Método que inserta un punto en el quadtree
    bool insert(Point point);
    // Método que divide el árbol si este excede su capacidad
    void split();
    
};

QuadTree::QuadTree(Rectangle p, int c)
{
    Perimetro.x = p.x; //coordenada x del rectangulo perimetro
    Perimetro.y=p.y; //coordenada y del retangulo perimetro
    Perimetro.h=p.h; //altura del rectangulo
    Perimetro.w=p.w; //ancho del rectangulo
    capacity = c; //capacidad del tree
}

QuadTree::~QuadTree()
{
}

void QuadTree::split(){
    //HACER FUNCION PARA RETORNAR LOS VALORES DEL RECTANGLE 
    int x = Perimetro.x; //coordenada x del rectangulo perimetro
    int y = Perimetro.y; //coordenada y del retangulo perimetro
    int w = Perimetro.w; //ancho del retangulo perimetro
    int h = Perimetro.h; //alto del rectangulo perimetro

    Rectangle ne ((x + w)/2, (y-h)/2, w/2 , h/2); //rectangulo de la seccion noreste
    Rectangle nw ((x - w)/2, (y-h)/2, w/2 , h/2); //rectangulo de la seccion noroeste
    Rectangle se ((x + w)/2, (y+h)/2, w/2 , h/2); //rectangulo de la seccion sureste
    Rectangle sw ((x - w)/2, (y+h)/2, w/2 , h/2); //rectangulo de la seccion suroeste
    QuadTree NW (nw, 4); //Quadtree correspondiente al hijo noroeste
    QuadTree NE (ne, 4); //Quadtree correspondiente al hijo noreste
    QuadTree SW (sw, 4); //Quadtree correspondiente al hijo suroeste
    QuadTree SE (se, 4); //Quadtree correspondiente al hijo sureste
    divided = true;
}

bool QuadTree::insert(Point point){
    vector<Point> points = points_vec;
    int size = points.size();
    bool ans = true;

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
    return false;
}

#endif

