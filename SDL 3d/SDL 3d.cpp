// SDL 3d.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include<math.h>
#include <vector>
using namespace std;
//Struct for line, it just makes it easier to organize the lines
struct line3d {

    float a;
    float b; 
    float c;

    float X1;
    float Y1;
    float Z1;

    float X2;
    float Y2;
    float Z2;

    float x1;
    float y1;
    

    float x2;
    float y2;
    float two_pi = 6.28319;
    //constructor which assigns values, a, b, and c are just rotation
    line3d ( float x_1, float y_1, float z_1, float x_2, float y_2, float z_2 , float a_1, float b_1, float c_1 ) {

        a = a_1;
        b = b_1;
        c = c_1;

        X1 = x_1;
        Y1 = y_1;
        Z1 = z_1;

        //Z1 = -X1 * sin(b) + Y1 * sin(a)*cos(b) + Z1 * cos(a) * cos(b);



        X2 = x_2;
        Y2 = y_2;
        Z2 = z_2;


        //Z2 = -X2 * sin(b) + Y2 * sin(a) * cos(b) + Z2 * cos(a) * cos(b);


    }
    void vect(SDL_Renderer *r) {
        if (a > two_pi) {
            a = 0;
            b = 0;
        }
        //Keep in mind this is a matrix transformation to rotate the cube which I found on the internet
        x1 = X1 * cos(b) * cos(c) + Y1 * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c)) + Z1 * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
        y1 = X1 * cos(b) * sin(c) + Y1 * (sin(a) * sin(b) * sin(c) + cos(a) * cos(c)) + Z1 * (cos(a) * sin(b) * sin(c) - sin(a) * cos(c));

        x2 = X2 * cos(b) * cos(c) + Y2 * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c)) + Z2 * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
        y2 = X2 * cos(b) * sin(c) + Y2 * (sin(a) * sin(b) * sin(c) + cos(a) * cos(c)) + Z2 * (cos(a) * sin(b) * sin(c) - sin(a) * cos(c));

        //picks a random color to represent the edges
        SDL_SetRenderDrawColor(r, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255);
        // draws a line by only projecting he 2d coordinates, giving an orthogonal shadow like view, for a cube this is alright, for other things a more advanced transformation is needed
        SDL_RenderDrawLine(r, x1 + 640 / 2, y1 + 480 / 2, x2 + 640 / 2,y2 + 480 / 2);

    }
};

void drawcube(SDL_Renderer* r) {

    

}

int main(int argc, char* args[])
{


    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(640, 480,0, &window, &renderer);
    int i = 0;


    float θ = 0;
    float φ = 0;
    float Ψ = 0;
    float size = 100;
    double aspeed = 0.05;
    double bspeed = 0.05;
    std::vector<line3d> cube = {  };
    cube.push_back(line3d(size, size, size, size, -size,  size, θ, φ, Ψ));
    cube.push_back(line3d(size, size, size, -size, size,  size, θ, φ, Ψ));
    cube.push_back(line3d(size, size, size, size, size, -size, θ, φ, Ψ));

    cube.push_back(line3d(size, size, -size, size, -size, -size, θ, φ, Ψ));
    cube.push_back(line3d(size, size, -size, -size, size, -size, θ, φ, Ψ));

    cube.push_back(line3d(-size, size, -size, -size, size,  size, θ, φ, Ψ));
    cube.push_back(line3d(-size, size, -size, -size, -size, -size, θ, φ, Ψ));

    cube.push_back(line3d(size, -size, -size, -size, -size, -size, θ, φ, Ψ));
    cube.push_back(line3d(size, -size, -size, size, -size, size, θ, φ, Ψ));

    cube.push_back(line3d(-size, size, size, -size, -size, size, θ, φ, Ψ));
    cube.push_back(line3d(size, -size, size, -size, -size, size, θ, φ, Ψ));
    cube.push_back(line3d(-size, -size,  -size, -size, -size, size, θ, φ, Ψ));
    
    bool running = true;
    SDL_Event event;
    while (true) {

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        for (i = 0; i < cube.size(); i++) {
            cube[i].vect(renderer);

            cube[i].a += aspeed;


            cube[i].b += aspeed;
            
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);


    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


