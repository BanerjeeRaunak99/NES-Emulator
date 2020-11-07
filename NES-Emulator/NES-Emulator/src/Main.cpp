#include <SFML/Graphics.hpp>

#include "NES/CPU.h"

#include "stdafx.h"

int main()
{
	std::string msg("This is the NES Emulator!!");
	std::cout << msg << '\n';

	sf::RenderWindow window(sf::VideoMode(640, 480), "NES Emulator | By ramizkhan99 & BanerjeeRaunak97");
	sf::RectangleShape shape(sf::Vector2f(100.f, 120.f));
	sf::err().rdbuf(NULL);
	shape.setFillColor(sf::Color::Green);

	while ( window.isOpen() )
	{
		sf::Event event;
		while ( window.pollEvent(event) )
		{
			if ( event.type == sf::Event::Closed )
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}