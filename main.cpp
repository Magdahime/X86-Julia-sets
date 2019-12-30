#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout<<"***********************************************************************************"<<std::endl;
    std::cout<<"For help press 'H'"<<std::endl;
    std::cout<<"***********************************************************************************"<<std::endl;

        for(int x = 0 ; x < width; x++){
            for(int y = 0; y < height; y++){
                pixels[(y*width + x)*4] =      y;
                pixels[(y*width + x)*4 + 1 ] = x;
                pixels[(y*width + x)*4 + 2 ] = 0;
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
                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
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