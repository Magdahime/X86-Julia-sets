#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
std::string create_title(double imaginary_part, double real_part);
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
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Julia sets");
    sf::Texture texture;
    sf::Sprite sprite(texture);
    double real_part = 0;
    double imaginary_part = 0;
    double * current = &real_part;
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
                    std::cout<<"\n\n\n\n\n"<<std::endl;
                    std::cout<<"***********************************************************************************"<<std::endl;
                    std::cout<<"Current value of imaginary part:"<<imaginary_part<<std::endl;
                    std::cout<<"Current value of real part:"<<real_part<<std::endl;
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
                        std::cout<<"Changing value of imaginary part."<<std::endl;
                        current = &imaginary_part;
                    }else if(event.key.code == sf::Keyboard::Left){
                        std::cout<<"Changing value of real part"<<std::endl;
                        current = &real_part;
                    }else if(event.key.code == sf::Keyboard::Up){
                        *current+=0.01;
                    }else if(event.key.code == sf::Keyboard::Down){
                        *current-=0.01;
                    }
            }
        }
        // Clear screen
        const std::string new_title(create_title(imaginary_part,real_part));
        window.clear();
        window.setTitle(new_title);
        // Draw the sprite
        window.draw(sprite);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
std::string create_title(double imaginary_part, double real_part){
    std::string title="JULIA SETS: ";
    title+="IM: ";
    title+= std::to_string(imaginary_part);
    title+="RE: ";
    title+= std::to_string(real_part);
    return title;
}