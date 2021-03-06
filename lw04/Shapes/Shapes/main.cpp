// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CShapeCreator.h"
#include "ICanvas.h"
#include "CCanvas.h"

void DrawShapes(std::vector<std::shared_ptr<IShape>> &shapes)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Canvas");
	CCanvas canvas(window);
	for (auto shape : shapes)
	{
		shape->Draw(canvas);
	}
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
}

void PrintShapesInfo(std::vector<std::shared_ptr<IShape>> & shapes)
{
	for (auto shape : shapes)
	{
		std::cout << shape->ToString() << "\n";
	}
}

void PrintShapeWithMinPerimeter(std::vector<std::shared_ptr<IShape>> & shapes)
{
	std::vector<std::shared_ptr<IShape>>::iterator it = 
		std::min_element(shapes.begin(), shapes.end(),
		[](const std::shared_ptr<IShape> &shapeOne, const std::shared_ptr<IShape> &shapeTwo)
	{
		return shapeOne->GetPerimeter() < shapeTwo->GetPerimeter();
	});
	if (it != shapes.end())
	{
		std::cout << (*it)->ToString() << "\n";
	}
}

void PrintShapeWithMaxArea(std::vector<std::shared_ptr<IShape>> & shapes)
{
	std::vector<std::shared_ptr<IShape>>::iterator it =
		std::max_element(shapes.begin(), shapes.end(),
			[](const std::shared_ptr<IShape> &shapeOne, const std::shared_ptr<IShape> &shapeTwo)
	{
		return shapeOne->GetArea() < shapeTwo->GetArea();
	});
	if (it != shapes.end())
	{
		std::cout << (*it)->ToString() << "\n";
	}
}

int _tmain()
{
	try
	{
		std::vector<std::shared_ptr<IShape>> shapes;
		CShapeCreator shapeCreator(std::cin);
		while (auto shape = shapeCreator.HandleCommand())
		{
			shapes.push_back(shape);
		}

		if (!shapes.empty())
		{
			PrintShapesInfo(shapes);

			std::cout << "Shape with min perimeter: " << "\n";
			PrintShapeWithMinPerimeter(shapes);

			std::cout << "Shape with max area: " << "\n";
			PrintShapeWithMaxArea(shapes);

			DrawShapes(shapes);
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << "\n";
	}
	return 0;
}

