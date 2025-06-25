#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/System.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Test");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Cyan);
        window.display();
    }

    return 0;
}
