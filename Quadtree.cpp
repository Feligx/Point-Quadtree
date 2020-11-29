#include "Quadtree.hpp"
#include <iostream>
#include <math.h>


using namespace std;

QuadNode::QuadNode(int x_, int y_, int w_, int h_){
    this->bounds = new Rectangle{ x_,y_,w_,h_};
    this->NW = nullptr;
    this->NE = nullptr;
    this->SE = nullptr;
    this->SW = nullptr;
}

bool QuadNode::isLeaf(){return NW==nullptr;}


bool QuadNode::insert(Point point){//Método que inserta puntos en el árbol

    if(!this->bounds->contain_point(point)){
        return false;
    }

    if(isLeaf()){  //Si es una hoja el punto se inserta en este nodo
        if (count < capacity){
            this->data[count] = point;
            cout << "agregare el punto: " << this->data[count].x << "," << this->data[count].y << endl;
            count++;
            return true;
        }
        split(); //Si el nodo alcanza su capacidad máxima se divide
    }

    //Si no es una hoja o se divide, inserta el punto en el primer punto que le sea posible
    if(NW->insert(point)){
        cout << "Logre insertarlo en NW" << endl;
        return true;
    }
    
    if(NE->insert(point)){
        return true;
        cout << "Logre insertarlo en NW" << endl;
    }
    
    if(SW->insert(point)){
        return true;
        cout << "Logre insertarlo en NW" << endl;
    }
    
    if(SE->insert(point)){
        cout << "Logre insertarlo en NW" << endl;
        return true;
    }
    
    cout << "maybe the point is duplicated..." << endl;

    return false;
}

void QuadNode::split(){ //método que divide el nodo en 4 subnodos
    cout << "Spliting" << endl;
    int x= bounds->x;
    int y= bounds->y;
    int w= bounds->w;
    int h= bounds->h;

    //creacion de los 4 nodos hijos segun el limite de su respectivo cuadrante
    NW= new QuadNode( x , y , w/2 , h/2);
    NE= new QuadNode( x+w/2, y, w/2, h/2);
    SW= new QuadNode( x , y + h/2 ,w/2,h/2);
    SE= new QuadNode( x + w/2 , y + h/2 , w/2 , h/2);

    //encuentra un hijo en el cual incluir cada punto de los que estan en data[]
    for(int i = 0; i < count; i++){
        if(NW->insert(data[i])){
            cout << " Intentando NW! " << endl;
            continue;
        }
        if(NE->insert(data[i])){
            cout << " Intentando NE! " << endl;
            continue;
        }
        if(SW->insert(data[i])){
            cout << " Intentando SW! " << endl;
            continue;
        }
        if(SE->insert(data[i])){
            cout << " Intentando SE! " << endl;
            continue;
        }
        cerr << "failed to place existing point after subdivide()" << endl;  
    }
}

float Point::distance(Point p) {//calcula la distancia entre dos puntos
    int d = 0;
    int x1 = this->x;
    int y1 = this->y;
    int x2 = p.x;
    int y2 = p.y;

    d = ((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
    return d;
}


bool Point::intersected(Point p) { // método que evalúa si dos puntos colisionan 
    float distance= sqrt(this->distance(p)); //calcula la distancia entre los centros de los círculos
    int diameter = (this->radius)*2;
    cout << "distance: "<<distance << endl;
    cout << "diameter: " <<diameter << endl;
    return distance <= diameter;
}


void QuadNode::query_colision(){ //método que hace la consulta de los puntos que colisonan dentro de UN nodo dado
    if(!isLeaf()){
        this->NW->query_colision();
        this->NE->query_colision();
        this->SW->query_colision();
        this->SE->query_colision();
    }

    else
    {
        for (int i = 0; i < this->count; i++) {
            for (int j = 0; j < this->count; j++) {
                if (this->data[i].intersected(this->data[j]) && this->data[j].x != this->data[i].x && this->data[j].y != this->data[i].y) { //Se revisa si el punto es diferente para no incluirse a si mismo y si este intersecta con los demás
                    cout << "El punto: (" << this->data[i].x << "," << this->data[i].y << ") con radio:" << this->data[i].radius << "colisiona" << endl;
                    cout << "con el punto: (" << this->data[j].x << "," << this->data[j].y << ") con radio:" << this->data[j].radius << "colisiona" << endl;
                    this->data[j].highlighted = true;
                }
            }
        }
    }
}



void Quadtree::query() { // wrapper que ejecuta el método query_colision para revisar colisiones desde la raíz del árbol
    root->query_colision();
}
