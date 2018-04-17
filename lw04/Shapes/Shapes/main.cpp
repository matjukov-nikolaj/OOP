// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CTraingle.h"


int _tmain()
{
	try
	{
		//CTraingle traingle({ 0, 0 }, { 1, 1 }, {2, 0}, "lol", "kek");
		//double lol = traingle.GetArea(); // проверить формулу
		//std::cout << lol << "\n";
		////double lol = traingle.GetPerimeter();
			sf::RenderWindow window(sf::VideoMode(200, 200), "SFMLworks");
			sf::CircleShape shape(100.f);
			shape.setFillColor(sf::Color::Green);

			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				window.clear();
				window.draw(shape);
				window.display();
			}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

