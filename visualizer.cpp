#include <iostream>
#include <SDL2/SDL.h>
#include "Quadtree.hpp"
#include <stdlib.h>
#include <time.h>

#define WIDTH 800 //ancho de la ventana y del quadtree
#define HEIGHT 800 //alto de la ventana y del quadtree
#define TITLE "Colision Test" // título de la ventana

using namespace std;

bool running = false; //booleano que representa el estado de la ventana
SDL_Window *window; //objeto de tipo ventana, de la libreria SDL2
SDL_Renderer *renderer; //objeto de tipo renderer de la libreria SDL2
Quadtree *tree; //objeto de tipo Quadtree


void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius) //método que dibuja un círculo usando puntos de la librería SDL2 basado en las coordenadas del centro del punto y su radio
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Se renderiza un círculo basado en 8 puntos
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}


void handleEvents(){ //método que inserta un punto cada vez que se hace un clic en pantalla
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type){
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            tree->root->insert(Point {event.button.x, event.button.y});
            break;
        default:
            break;
        }
    }
}

void renderQuadNode(QuadNode *node){ //método que dibuja el árbol y los puntos del mismo
    SDL_Rect rect{node->bounds->x,node->bounds->y,node->bounds->w,node->bounds->h};
    SDL_SetRenderDrawColor(renderer, 5, 99, 213, 255);
    SDL_RenderDrawRect(renderer,&rect);

    if(!node->isLeaf()){
        renderQuadNode(node->NW);
        renderQuadNode(node->NE);
        renderQuadNode(node->SW);
        renderQuadNode(node->SE);
    }
    else
    {
        for (int i = 0; i < CAP; i++) {
            if (node->data[i].highlighted==true) {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                DrawCircle(renderer, node->data[i].x, node->data[i].y, node->data[i].radius);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 241, 148, 23, 255);
                DrawCircle(renderer, node->data[i].x, node->data[i].y, node->data[i].radius);
            }
        }
    }
}

void Point_gen(){ //método que genera n puntos de forma aleatoria dentro del área del quadtree y los inserta, n es determinado por el usuario con un cin
    int quantity;
    cout << "Insert Quantity: ";
    cin >> quantity;
    cout << endl;

    srand(time(NULL));
    while (quantity != 0) {
        int new_x_cor = rand() % 800;
        int new_y_cor = rand() % 800;
        tree->root->insert(Point{ new_x_cor, new_y_cor});
        quantity--;
    }
}


void render(){ //wraper de todos los métodos que se necesitan para el funcionamiento del visuaizador
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderQuadNode(tree->root);
    SDL_RenderPresent(renderer);
}


int main(int argc, char **argv){ //main que recibe los argumentos necesarios para funcionar con la libreria SDL2
    //Se inicializa la visuaización
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "SDL initialized succesfully." << endl;
        window = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
        if(!window){
            cerr << "Error creating window."<<endl;
            return 1;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(!renderer){
            cerr<<"Error creating renderer." << endl;
            return 2;
        }
        //se crea un árbol para iniciar el proceso
        tree = new Quadtree(0,0,WIDTH,HEIGHT);
        running=true;
    }
    
    Point_gen(); //se generan puntos de forma aleatoria
    tree->query(); // se hace la consulta de que puntos están en colisión
    while (running)
    {
        //tree->query(); //solo se debe usar si se planea usar la modalidad de inserción por clic
        //handleEvents(); //solo se debe usar si se planea usar la modalidad de inserción por clic
        render(); // se hace el render de los puntos y el árbol
    }
    return 0;
}
