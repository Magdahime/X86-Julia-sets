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
    sf::RenderWindow window(sf::VideoMode(width, height,32), "Julia Explorer",sf::Style::Default);
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Uint8 *pixels = new unsigned char[width * height * 4];
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    double real_part = 0;
    double imaginary_part = 0;
    double * current = &real_part;
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
            if (event.type == sf::Event::MouseButtonPressed){
                std::cout<<"\n\n***********************************************************************************"<<std::endl;
                std::cout << "mouse x: " << event.mouseButton.x<< std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                std::cout << "button: " << event.mouseButton.button << std::endl;
                std::cout<<"***********************************************************************************"<<std::endl;
                if(event.mouseButton.button == sf::Mouse::Button::Right){
                    std::cout<<"\n\n***********************************************************************************"<<std::endl;
                    std::cout<<"You are now changing imaginary part."<<std::endl;
                    std::cout<<"***********************************************************************************"<<std::endl;
                    current=&imaginary_part;
                }else if(event.mouseButton.button == sf::Mouse::Button::Left){
                    std::cout<<"\n\n***********************************************************************************"<<std::endl;
                    std::cout<<"You are now changing real part."<<std::endl;
                    std::cout<<"***********************************************************************************"<<std::endl;
                    current=&real_part;
                }
            }
            if(event.type == sf::Event::MouseWheelScrolled){
                if(event.mouseWheelScroll.delta>0){
                    *current+=0.01;
                }else{
                    *current-=0.01;
                }
                std::cout<<"\n\n***********************************************************************************"<<std::endl;
                std::cout<<"Current value of imaginary part: "<<imaginary_part<<std::endl;
                std::cout<<"Current value of real part: "<<real_part<<std::endl;
                std::cout<<"For help press 'H'"<<std::endl;
                std::cout<<"***********************************************************************************"<<std::endl;
            }
            if (event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::H){
                        std::cout<<"\n\n\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"To move picture around ----> Arrow Right/Left/Up/Down"<<std::endl;
                        std::cout<<"To increase/decrease the value of chosen part -----> Scroll with mouse"<<std::endl;
                        std::cout<<"To change the part -----> Press left or right button of the mouse"<<std::endl;
                        std::cout<<"To zoom in/out the picture ----> Press Z/X"<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;

                    }else if(event.key.code == sf::Keyboard::Right){
                        x_offset+=0.01;

                    }else if(event.key.code == sf::Keyboard::Left){
                        x_offset-=0.01;

                    }else if(event.key.code == sf::Keyboard::Up){
                        y_offset-=0.01;
                    
                    }else if(event.key.code == sf::Keyboard::Down){
                        y_offset+=0.01;
                    
                    }else if(event.key.code == sf::Keyboard::Z){
                        zoom *= 1.1;

                    }else if(event.key.code == sf::Keyboard::X){
                        zoom /= 1.1;
                    }
            }
            if (event.type == sf::Event::KeyReleased){

                    if(event.key.code == sf::Keyboard::Right){
                        std::cout<<"\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"Moving picture to the right."<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;
                    }else if(event.key.code == sf::Keyboard::Left){
                        std::cout<<"\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"Moving picture to the left."<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;
                    }else if(event.key.code == sf::Keyboard::Up){
                        std::cout<<"\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"Lifting picture up."<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;                   
                    }else if(event.key.code == sf::Keyboard::Down){
                        std::cout<<"\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"Lowering picture down."<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;
                    }else if(event.key.code == sf::Keyboard::Z){  
                        std::cout<<"\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"Zooming in the picture."<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;
                    }else if(event.key.code == sf::Keyboard::X){
                        std::cout<<"\n\n***********************************************************************************"<<std::endl;
                        std::cout<<"Zooming out the picture."<<std::endl;
                        std::cout<<"***********************************************************************************"<<std::endl;
                    }
            }
        }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //JULIA
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        for(int y =0; y<height; y++){
            for (int x = 0; x<width; x++){
                double new_Re =x/ (zoom * width) + x_offset/zoom;
                double new_Im =y/ (zoom * height) + y_offset/zoom;
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //CREATING OUTPUT FROM THE ARRAY OF PIXELS
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