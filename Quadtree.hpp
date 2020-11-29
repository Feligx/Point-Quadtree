#ifndef _QUADTREE_HPP
#define _QUADTREE_HPP

#include <iostream>
#include <stdexcept>

#define CAP 4 //Capacidad de nodos y arbol

using namespace std;


//INICIO DE LA ESTRUCTURA POINT


struct Point{
    int x; //coordenada x
    int y; //coordenada
    int radius=4; //radio para todos los puntos
    bool highlighted=false; //es true si el punto colisiona con otro
    Point() { x = 0; y = 0; }
    Point(int x_, int y_){
        x=x_;
        y=y_;
    }
    float distance(Point p);

    bool intersected(Point p);
};


//FIN DE LA ESTRUCTURA RECTANGLE





//INICIO DE LA ESTRUCTURA RECTANGLE
struct Rectangle{
    int x, y, w, h; // coordenadas x,y en el plano / ancho y alto del plano

    Rectangle(){};
    Rectangle(int x_, int y_, int w_, int h_){
        x=x_;
        y=y_;
        w=w_;
        h=h_;
    }

    // Métodos
    bool contain_point(Point p) {
        //retorna true si las coordenadas del punto estan dentro del rango del rectangulo
        return (p.x >= x && p.x < (x + w)) && (p.y >= y && p.y < (y + h));
    }
};

// FINAL DE LA ESTRUCTURA Y MÉTODOS RECTANGLE






// CREACIÓN DE LOS NODOS DE UN QUADTREE
struct QuadNode{
    static const int capacity = CAP;
    private:
        void split();
    public:
    //ATRIBUTOS DE LA CLASE
    QuadNode *NW; //nodo hijo noroeste
    QuadNode *NE; //nodo hijo noreste
    QuadNode *SW; //nodo hijo suroeste
    QuadNode *SE; //nodo hijo sureste

    Rectangle *bounds; //rectuangulo del perimetro del qt
    Point data[capacity]; //arreglo con los puntos almacenados en el QuadTree
    int count=0;
    
    QuadNode(int x_, int y_, int w_, int h_);

    bool insert(Point point); // Método que inserta un punto en el quadtree
    bool isLeaf();

    void query_colision();

};

class Quadtree
{
public:

    QuadNode* root;
    Quadtree(int x, int y, int w, int h){
        this->root = new QuadNode(x, y, w, h);
    }
    ~Quadtree() {}

    void query();



private:
    static const int capacity = CAP; //Capacidad de todo el tree
};

#endif
