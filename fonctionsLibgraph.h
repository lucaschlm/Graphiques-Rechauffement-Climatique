#pragma once
#include <vector>

const float pi = 3.14159265358979323846;

enum class displayType
{
	ClairFonce,
	Spirale,
	Raie,
	None
};

displayType displayClairFonce(const std::vector<float>& data, size_t colorNb = 8);

displayType displaySpirale(const std::vector<float>& sommeMoyStation);

displayType displayRaieDeCouleurs(const std::vector<float>& data);

void help();