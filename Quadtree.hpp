#ifndef _QUADTREE_HPP
#define _QUADTREE_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
struct Point{
    float x; //coordenada x
    float y; //coordenada 
    T userData;
    Point(){x=0;y=0;}
    Point(float a, float b){
        x=a;
        y=b;
    }
};


//INICIO DE LA CLASE RECTANGLE
template <typename T>
class Rectangle{
private:
    int x,y,w,h; // coordenadas x,y en el plano / ancho y alto del plano
public:
    Rectangle(){};
    Rectangle(int x_, int y_, int w_, int h_){
        x=x_;
        y=y_;
        w=w_;
        h=h_;
    }
    ~Rectangle(){};

    //Métodos getters
    int get_x();
    int get_y();
    int get_width();
    int get_height();

    //Setters

    void set_x(int x_cor);
    void set_y(int y_cor);
    void set_width(int width);
    void set_height(int height);

    //Otros métodos
    bool contains(Point<T> p);
};

//Getters
template <typename T>
int Rectangle<T>::get_x(){return x;}

template <typename T>
int Rectangle<T>::get_y(){return y;}

template <typename T>
int Rectangle<T>::get_height(){return h;}

template <typename T>
int Rectangle<T>::get_width(){return w;}

//Setters
template <typename T>
void Rectangle<T>::set_x(int x_cor){x= x_cor;}

template <typename T>
void Rectangle<T>::set_y(int y_cor){y= y_cor;}

template <typename T>
void Rectangle<T>::set_width(int width){w= width;}

template <typename T>
void Rectangle<T>::set_height(int height){h= height;}

// Función que evalua si un punto está dentro de la región del rectángulo
template <typename T>
bool Rectangle<T>::contains(Point<T> point){
    //consigue las coordenadas del rectangulo
    int x = this->get_x();
    int y= this->get_y();
    int w= this->get_width();
    int h= this->get_height();

    //retorna true si las coordenadas del punto estan dentro del rango del rectangulo
    return ((point.x >= x && point.x < (x+w)) && (point.y >= y && point.y < (y+h)));
}

// FINAL DE LA CLASE Y MÉTODOS RECTANGLE

// CREACIÓN DE LOS NODOS DE UN QUADTREE
template <typename T>
struct QuadNode{
    private:
        void split();
    public:
    //ATRIBUTOS DE LA CLASE
    QuadNode<T> *NW; //nodo hijo noroeste
    QuadNode<T> *NE; //nodo hijo noreste
    QuadNode<T> *SW; //nodo hijo suroeste
    QuadNode<T> *SE; //nodo hijo sureste
    QuadNode<T> *parent; //parent del QuadNode

    static const int capacity=2;
    Rectangle<T> *bounds; //rectuangulo del perimetro del qt
    int depth; //profundidad en la que se haya el nodo
    Point<T> data[capacity]; //arreglo con los puntos almacenados en el QuadTree
    int count=0;
    bool divided = false; //es true si está dividido, es false si no está dividido
    
    QuadNode<T>(int x, int y, int w, int h , int c);

    bool insert(Point<T> point); // Método que inserta un punto en el quadtree
    bool isLeaf();

};



// INICIO DE LA CLASE QUADTREE
template <typename T>
class Quadtree
{
private:
    QuadNode<T>* root; //nodo raiz del Quadtree
    int capacity=root->capacity; // Capacidad de puntos del arbol

public:
    Quadtree();
    Quadtree(int x, int y, int w, int h , int c);
    ~Quadtree();
    bool insert(Point<T> point){return root->insert(point);}

    // Método que divide el árbol si este excede su capacidad
};

template <typename T>
Quadtree<T>::Quadtree()
{
    root= new QuadNode<T>(0,0,0,0,2); //el constructor por default trae la capacity en 2
}


template <typename T>
Quadtree<T>::~Quadtree()
{
    delete[] root;
}


// Función para dividir el Qtree una vez llegue a su máx capacity

#endif