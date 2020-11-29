#include <iostream>
#include <SDL2/SDL.h>
#include "Quadtree.hpp"
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Colision Test"

using namespace std;

bool running = false;
SDL_Window *window;
SDL_Renderer *renderer;
Quadtree *tree;


void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
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


void handleEvents(){
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

void renderQuadTreeNode(QuadNode *node){
    //cout<< "Voy a renderizar un nodo" <<endl;
    SDL_Rect rect{node->bounds->x,node->bounds->y,node->bounds->w,node->bounds->h};
    SDL_SetRenderDrawColor(renderer, 5, 99, 213, 255);
    SDL_RenderDrawRect(renderer,&rect);

    if(!node->isLeaf()){
        //cout << "renderizare los nodos hijos!" << endl;
        renderQuadTreeNode(node->NW);
        renderQuadTreeNode(node->NE);
        renderQuadTreeNode(node->SW);
        renderQuadTreeNode(node->SE);
    }
    else
    {
        for (int i = 0; i < CAP; i++) {
            //cout << "estoy en el for!" << i.x << "," << i.y << endl;
            if (node->data[i].highlighted==true) {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                //SDL_RenderDrawPoint(renderer, node->data[i].x, node->data[i].y);
                DrawCircle(renderer, node->data[i].x, node->data[i].y, node->data[i].radius);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 241, 148, 23, 255);
                //SDL_RenderDrawPoint(renderer, node->data[i].x, node->data[i].y);
                DrawCircle(renderer, node->data[i].x, node->data[i].y, node->data[i].radius);
            }
        }
    }
}

void Point_gen(){
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


void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderQuadTreeNode(tree->root);
    SDL_RenderPresent(renderer);
}


int main(int argc, char **argv){
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
        tree = new Quadtree(0,0,WIDTH,HEIGHT);
        running=true;
    }
    Point_gen();
    tree->query();
    while (running)
    {
        //tree->query();
        //handleEvents();
        render();
    }
    return 0;
}