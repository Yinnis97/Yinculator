#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream> 
#include <fstream>
#include "math.h"

using namespace sf;

#define BUTTON_AMOUNT		24
#define X_SIZE_DIVIDER		8
#define Y_SIZE_DIVIDER		3

#define DEBUG_Y
#define PEMDAS					// Order of Operations : Parentheses, Exponents, Multiplication/Division, Addition/Subtraction.

using mode_t = int;

enum MODE
{
	INPUT = 0,
	DIVIDEZERO,
	OUTPUT
};

