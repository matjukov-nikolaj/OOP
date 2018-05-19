// FindMaxEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSportsman.h"
#include "FindMaxEx.h"


int main()
{
	std::vector<CSportsman> sportsmans= {
		CSportsman("Vasya", 60, 170),
		CSportsman("Petya", 63, 173),
		CSportsman("Igor", 65, 175),
	};

	std::cout << "Sportsman with max height: " << std::endl;
	CSportsman withMaxHeight;
	FindMax(sportsmans, withMaxHeight, [](const auto& man1, const auto& man2) {
		return man1.GetHeight() < man2.GetHeight();
	});

	withMaxHeight.PrintSportsmanInfo(withMaxHeight);

	std::cout << "Sportsman with max weight: " << std::endl;
	CSportsman withMaxWeight;
	FindMax(sportsmans, withMaxWeight, [](const auto& man1, const auto& man2) {
		return man1.GetWeight() < man2.GetWeight();
	});

	withMaxWeight.PrintSportsmanInfo(withMaxWeight);
	
	return 0;
}

