#include <iostream>
#include <string>
#include <sstream>
#include "julia.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define ITERATIONS 512
const int PALETTE[] ={40,90,30};
//HELP FUNCTIONS
int main(int argc, char* argv[])
{
    unsigned int width, height;
    if(argc>2){
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }else{
        width = 400;
        height = 400;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATING THE MAIN WINDOW
    sf::RenderWindow window(sf::VideoMode(width, height,32), "Julia sets",sf::Style::Default);
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Uint8 *pixels = new unsigned char[width * height * 4];
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    double real_part = 0;
    double imaginary_part = 0;
    double * current = &real_part;
    double mouse_position_x = width/2;
    double mouse_position_y = height/2;
    double x_offset = 0;
    double y_offset = 0;
    double zoom =1.0;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

        for(int x = 0 ; x < width; x++){
            for(int y = 0; y < height; y++){
                pixels[(y*width + x)*4] =      100;
                pixels[(y*width + x)*4 + 1 ] = 100;
                pixels[(y*width + x)*4 + 2 ] = 200;
                pixels[(y*width + x)*4 + 3 ] = 255;
            }
        }

    while (window.isOpen())
    {   
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed){
                std::cout<<"Bye :)"<<std::endl;
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled){
                /*if(event.mouseWheelScroll.delta>0){
                    zoom *=1.01;
                }else{
                    zoom/=1.01;
                }*/ 
                mouse_position_x = event.mouseWheelScroll.x;
                mouse_position_y = event.mouseWheelScroll.y;
                x_offset += mouse_position_x/width;
                y_offset += mouse_position_y/height;

                std::cout<<"\n\n***********************************************************************************"<<std::endl;
                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << mouse_position_x << std::endl;
                std::cout << "mouse y: " << mouse_position_y << std::endl;
                std::cout << "Offset of x : " << x_offset << std::endl;
                std::cout << "Offset of y : " << y_offset << std::endl;
                std::cout<<"***********************************************************************************"<<std::endl;
            }
            if (event.type == sf::Event::KeyPressed){
                std::cout<<"\n\n***********************************************************************************"<<std::endl;
                std::cout<<"Current value of imaginary part: "<<imaginary_part<<std::endl;
                std::cout<<"Current value of real part: "<<real_part<<std::endl;
                std::cout<<"For help press 'H'"<<std::endl;
                std::cout<<"***********************************************************************************"<<std::endl;

                    if(event.key.code == sf::Keyboard::H){

                        std::cout<<"\n\n\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"To switch between imaginary and real part ----> Arrow Right/Left"<<std::endl;
                        std::cout<<"To increase the value of chosen part -----> Arrow Up"<<std::endl;
                        std::cout<<"To decrease the value of chosen part -----> Arrow Down"<<std::endl;
                        std::cout<<"To zoom in/out the picture ----> Scroll with mouse"<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;

                    }else if(event.key.code == sf::Keyboard::Right){

                        std::cout<<"\n\nChanging value of imaginary part."<<std::endl;
                        current = &imaginary_part;

                    }else if(event.key.code == sf::Keyboard::Left){

                        std::cout<<"\n\nChanging value of real part"<<std::endl;
                        current = &real_part;

                    }else if(event.key.code == sf::Keyboard::Up){

                        *current+=0.01;
                    
                    }else if(event.key.code == sf::Keyboard::Down){
                    
                        *current-=0.01;
                    
                    }
            }
        }
        for(int y =0; y<height; y++){
            for (int x = 0; x<width; x++){
                double new_Re =1.0*x/ (zoom * width) + x_offset;
                double new_Im =1.0*y/ (zoom * height) + y_offset;
                int iterations;
                for (iterations = 0; iterations< ITERATIONS; iterations++){
                    double old_Re = new_Re;
                    double old_Im = new_Im;
                    new_Re = old_Re*old_Re - old_Im*old_Im +real_part;
                    new_Im = 2*old_Re*old_Im +imaginary_part;
                    //CHECKING IF WE REACHED 2
                    if((new_Re*new_Re +new_Im*new_Im>4)){
                        break;
                    }
                }
                sf::Uint8 red = iterations * PALETTE[0] % 256;
				sf::Uint8 green = iterations * PALETTE[1] % 256;
				sf::Uint8 blue = iterations * PALETTE[2] % 256;
                //COLOURING
                pixels[(y*width + x)*4] =      red;
                pixels[(y*width + x)*4 + 1 ] = blue;
                pixels[(y*width + x)*4 + 2 ] = green;
                pixels[(y*width + x)*4 + 3 ] = 255;
            }
        }
        //CREATING THE OUTPUT FROM THE ARRAY OF PIXELS
        image.create(width,height,pixels);
        texture.create(width,height);
        texture.update(image);
        sprite.setTexture(texture);
        //CLEARS THE SCREEN
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Update the window
        window.display();
    }
    delete [] pixels;
    return 0;
}