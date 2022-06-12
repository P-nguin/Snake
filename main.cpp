#include<iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(640, 480), "Yes", Style::Default);
    window.setFramerateLimit(60);

    Sprite penguin;
    Texture penguinTexture;
    if (!penguinTexture.loadFromFile("Textures/penguin.jpg")) cout << "no" << endl;

    penguin.setTexture(penguinTexture);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
        }

        window.clear(Color::White);

        window.draw(penguin);

        window.display();
    }

    return 0;
}