/*
#################################
#                               #
#   By Risotto von Bissmarck    #
#                               #
#################################

Litle mandelbroot fractale calcul 
    program using SFML

#################################
            controls
zoom in: P
zoom out: M
move up: Z
move left: Q
move left: S
move right: D

(azerty configuration)

#################################
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <math.h>

int ind_div(float a, float b){
    /*
    calcule indice de divergence de la suite
    */
    
    float x = 0;
    float y = 0;

    float x_n = x;
    float y_n = y;

    for (int n = 0; n < 500;  n++){
        x_n = pow(x,2) - pow(y,2) + a;
        y_n = 2*x*y + b;

        x = x_n;
        y = y_n;

        if (pow(x,2)+pow(y,2) > 4){
            return n;
        }
    }

    return -1;
}

sf::Texture mdbroot(float x, float y, float l, float h, int W, int H){
    /*
    genère l'image
    */

    // tableau de pixel générant limage de mandelbroot    
    sf::Uint8 pixels[H*W*4];

    // textures contenat l'image de mandelbroot
    sf::Texture texture;
    texture.create(H,W);

    // couleurs de référence
    sf::Uint8 colors[16][3] = {
        {66, 30, 15},
        {25, 7, 26},
        {9, 1, 47},
        {4, 4, 73},
        {0, 7, 100},
        {12, 44, 138},
        {24, 82, 177},
        {57, 125, 209},
        {134, 181, 229},
        {211, 236, 248},
        {241, 233, 191},
        {248, 201, 95},
        {255, 170, 0},
        {204, 128, 0},
        {153, 87, 0},
        {106, 52, 3},
    };

    for (int i = 0; i < W; i++){
        for (int j = 0; j < H; j++){
            
            // calcul de l'indice de divergence
            int ind = ind_div(x + i*l/W, y + j*h/H);

            // afectation des couleurs aux pixels
            if (ind == -1){
                pixels[((j*H)+i)*4+0] = 0;
                pixels[((j*H)+i)*4+1] = 0;
                pixels[((j*H)+i)*4+2] = 0;
                pixels[((j*H)+i)*4+3] = 255;
            }
            else{
                pixels[((j*H)+i)*4+0] = colors[ind % 16][0];
                pixels[((j*H)+i)*4+1] = colors[ind % 16][1];
                pixels[((j*H)+i)*4+2] = colors[ind % 16][2];
                pixels[((j*H)+i)*4+3] = 255;
            }
        }
    }
    
    // charge la texture a partir du tableau de pixels
    texture.update(pixels);

    return texture;
}

int main(){
    
    // taille de la fenetre
    const int WIDTH = 500;
    const int HEIGHT = 500;

    // zoom dans la fractales
    float l = 2.5;
    float h = 2.5;

    // position de la fractale
    float x = -2;
    float y = -1.25;

    // vitesse de deplacement
    float speed = 0.5;

    // créations de la fenetre
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbroot");
    
    // créations de la texture contenant l'image de mandelbroot
    sf::Texture texture;
    if (!texture.create(HEIGHT, WIDTH)){
        std::cout << "Erreur" << std::endl;
    }

    // créations du sprite contenant l'image de mandelbroot 
    sf::Sprite sprite;
    sf::Texture text;

    // chargement de la fractale
    text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
    
    // actualisation de la texture
    sprite.setTexture(text);
 
    while (window.isOpen())
    {

        // gère l'evenement de fermeture de la fentre 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // zoom in
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            
            l *= 0.8;
            h *= 0.8;

            x += 0.5*speed;
            y += 0.5*speed;

            speed *= 0.8;

            text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
            sprite.setTexture(text);
        }

        // zoom out
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            
            l *= 1.25;
            h *= 1.25;
            
            speed *= 1.25;

            x -= 0.5*speed;
            y -= 0.5*speed;
            
            text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
            sprite.setTexture(text);
        }

        // move up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            y -= speed;
            text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
            sprite.setTexture(text);
        }

        // move down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            y += speed;
            text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
            sprite.setTexture(text);
        }

        // move right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            x += speed;
            text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
            sprite.setTexture(text);
        }

        // move left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            x -= speed;
            text = mdbroot(x,y, l,h, WIDTH,HEIGHT);
            sprite.setTexture(text);
        }

        // actualise la fenetre
        window.clear();
        window.draw(sprite);
        window.display();   
    }
    
    return 0;
}