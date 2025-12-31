#include "App.h"

App::App()
{
	App_Init();
}

App::~App()
{
	delete window;
}

const Vector2f App::Get_Window_Size()
{
	return static_cast<Vector2f>(window->getSize());
}

const Vector2f App::Get_Mouse_Pos()
{
	return window->mapPixelToCoords(Mouse::getPosition(*this->window));
}

void App::App_Init(void)
{
	// Variables
	mousepressed = false;
	input = "0";
	displaymode = INPUT;

	// Calculate the size of the calculator using the screen resolution.
	videomode = VideoMode::getDesktopMode();
	videomode.size.x = videomode.size.x / X_SIZE_DIVIDER;
	videomode.size.y = videomode.size.y / Y_SIZE_DIVIDER;

	// Create the window.
	window = new RenderWindow(videomode, "Yinculator");
	window->setVerticalSyncEnabled(true);

	// Colors
	Color color_outline(50, 50, 50);
	Color color_display(31, 31, 31);
	Color color_text(1, 55, 185);
	Color color_text_outline(10, 10, 10);

	// Textures
	static_cast<void>(basetexture.loadFromFile("Assets/Textures/background.png"));
	static_cast<void>(yinculatortexture.loadFromFile("Assets/Textures/yinculator.png"));
	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		std::string filepath = "Assets/Textures/button" + std::to_string(i) + ".png";
		static_cast<void>(buttontexture[i].loadFromFile(filepath));
	}
	
	// Have a space between everything and button outline.
	float spacing = Get_Window_Size().x / 20;
	float outlinethickness = Get_Window_Size().x / 100;

	// Base calculator background.
	baseshape.setSize(Get_Window_Size());
	baseshape.setPosition({ 0,0 });
	baseshape.setFillColor(Color::White);
	baseshape.setTexture(&basetexture);

	// Yinculator
	yinculator.setSize({ Get_Window_Size().x - (2*spacing ) - (2*outlinethickness),Get_Window_Size().y / 10});
	yinculator.setPosition({ spacing + outlinethickness,spacing + outlinethickness });
	yinculator.setFillColor(Color::White);
	yinculator.setOutlineThickness(2*outlinethickness);
	yinculator.setOutlineColor(color_outline);
	yinculator.setTexture(&yinculatortexture);

	// Display
	display.setSize({Get_Window_Size().x - (2*spacing) - (2*outlinethickness),Get_Window_Size().y / 8 - (2*outlinethickness)});
	display.setPosition({ spacing + outlinethickness, yinculator.getSize().y + (2*spacing) + (4*outlinethickness) });
	display.setFillColor(color_display);
	display.setOutlineThickness(2*outlinethickness);
	display.setOutlineColor(color_outline);

	// Button Area
	buttonarea.setSize({ (Get_Window_Size().x - (2*spacing)), (Get_Window_Size().y / 1.8f ) });
	buttonarea.setPosition({ spacing,Get_Window_Size().y - buttonarea.getSize().y - spacing });
	buttonarea.setFillColor(Color::White);
	buttonarea.setOutlineThickness(outlinethickness);
	buttonarea.setOutlineColor(color_outline);

	// Buttons
	float button_size_x = (buttonarea.getSize().x / 4);
	float button_size_y = (buttonarea.getSize().y / 6);

	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		buttons[i].setSize({ button_size_x- (2*outlinethickness), button_size_y - (2*outlinethickness) });
		buttons[i].setFillColor(Color::White);
		buttons[i].setOutlineThickness(outlinethickness);
		buttons[i].setOutlineColor(color_outline);
		buttons[i].setTexture(&buttontexture[i]);
	}

	int index = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			buttons[index].setPosition({ buttonarea.getPosition().x + (j * button_size_x) + outlinethickness, buttonarea.getPosition().y + (i * button_size_y) + outlinethickness });
			index++;
		}
	}

	// Display text
	static_cast<void>(font.openFromFile("Assets/Fonts/armalite_rifle.ttf"));
	displaytext.emplace(font);
	displaytext->setPosition({display.getPosition().x + (2*outlinethickness) , display.getPosition().y});
	displaytext->setCharacterSize(Get_Window_Size().x / 8);
	displaytext->setString("0");
	displaytext->setFillColor(color_text);
	displaytext->setOutlineColor(color_text_outline);
	displaytext->setOutlineThickness(outlinethickness);
}

bool App::App_Runnig(void)
{
	return this->window->isOpen();
}

void App::Set_Display(std::string str)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(3) << std::stod(str);
	std::string outputstr = oss.str();
	outputstr.erase(outputstr.find_last_not_of('0') + 1, std::string::npos);
	if (outputstr.back() == '.') outputstr.pop_back();
	displaytext->setString(outputstr);
}

void App::Reset_Values(void)
{
	ops.clear();
	numbers.clear();
	input = "0";
}

void App::Calculate(size_t buttonnumber)
{
	switch (buttonnumber)
	{
		case 0:				// %
			break;
		case 1:				// CE
			break;
		case 2:				// C
			Reset_Values();
			break;
		case 3:				// <X	
			Handle_Backspace();
			break;
		case 4:				// 1/
			break;
		case 5:				// x²
			break;
		case 6:				// sqrroot
			break;
		case 7:				// /
			Handle_Operator("/");
			break;
		case 8:				// 7
			Handle_Number(7);
			break;
		case 9:				// 8
			Handle_Number(8);
			break;
		case 10:			// 9
			Handle_Number(9);
			break;
		case 11:			// *
			Handle_Operator("*");
			break;
		case 12:			// 4
			Handle_Number(4);
			break;
		case 13:			// 5
			Handle_Number(5);
			break;
		case 14:			// 6
			Handle_Number(6);
			break;
		case 15:			// -
			Handle_Operator("-");
			break;
		case 16:			// 1
			Handle_Number(1);
			break;
		case 17:			// 2
			Handle_Number(2);
			break;
		case 18:			// 3
			Handle_Number(3);
			break;
		case 19:			// +
			Handle_Operator("+");
			break;
		case 20:			// pi
			break;
		case 21:			// 0
			Handle_Number(0);
			break;
		case 22:			// ,
			Handle_Comma();
			break;
		case 23:			// =
			Handle_Output();
			break;
		default : 
			std::cout << "Error in switch case - function : " << __FUNCTION__;
	}
}

void App::Handle_Number(int number)
{
	displaymode = INPUT;
	input += std::to_string(number);
}

void App::Handle_Operator(std::string op)
{
	ops.push_back(op);
	numbers.push_back(std::stod(input));
	std::cout << "New number added : " << input << std::endl;
	input = "0";
}

void App::Handle_Output(void)
{
	double result;
	// Push last number.
	numbers.push_back(std::stod(input));

#ifdef DEBUG_Y
	std::cout << "New number added : " << input << std::endl;
#endif

#ifdef PEMDAS
	// Check the * and / operations and do them first.
	for (size_t i = 0; i < ops.size();)
	{
		if (ops[i] == "*")
		{
			numbers[i] = numbers[i] * numbers[i + 1];
			numbers.erase(numbers.begin() + i + 1);
			ops.erase(ops.begin() + i);
		}
		else if (ops[i] == "/")
		{
			if (numbers[i+1] != 0)
			{
				numbers[i] = numbers[i] / numbers[i + 1];
				numbers.erase(numbers.begin() + i + 1);
				ops.erase(ops.begin() + i);
			}
			else
			{
				std::cout << "Divide zero \n";
				displaymode = DIVIDEZERO;
				Reset_Values();
				return;
			}
		}
		else
		{
			i++;
		}
	}

	// First number in result
	result = numbers[0];

	// Loop over the rest of the + and - operations.
	for (size_t i = 0; i < ops.size(); i++)
	{
		if (ops[i] == "+")
		{
			result += numbers[i + 1];
		}
		else if (ops[i] == "-")
		{
			result -= numbers[i + 1];
		}
	}

	outputnumber = result;
	displaymode = OUTPUT;
#endif

#ifndef PEMDAS
	// First number in result.
	result = numbers[0];

	// Loop over all the operations
	for (int i = 0; i < ops.size(); i++)
	{
		if (ops[i] == "+")
		{
			result += numbers[i + 1];
		}
		else if (ops[i] == "-")
		{
			result -= numbers[i + 1];
		}
		else if (ops[i] == "*")
		{
			result *= numbers[i + 1];
		}
		else if (ops[i] == "/")
		{
			if (numbers[i + 1] != 0)
			{
				result /= numbers[i + 1];
			}
			else
			{
				displaymode = DIVIDEZERO;
				Reset_Values();
				return;
			}
		}
	}
	outputnumber = result;
	displaymode = OUTPUT;
#endif

#ifdef DEBUG_Y
	std::cout << "Formula : " << numbers[0] << " ";
	for (size_t i = 0; i < ops.size(); i++)
	{
		std::cout << ops[i] << " " << numbers[i + 1] << " ";
	}
	std::cout << " = " << outputnumber << std::endl;
#endif

	result = 0;
	Reset_Values();
}

void App::Handle_Comma(void)
{
	if (input.find(',') == std::string::npos)
	{
		input += ".";
	}
}

void App::Handle_Backspace(void)
{
	if (input.size() > 1)
	{
		input.pop_back();
	}
	else
	{
		input = "0";
	}
}

void App::Update_Display(void)
{
	switch (displaymode)
	{
	case INPUT:
		Set_Display(input);
		break;
	case DIVIDEZERO:
		displaytext->setString("NOPE");
		break;
	case OUTPUT:
		Set_Display(std::to_string(outputnumber));
		break;
	}

}

void App::App_Pollevent(void)
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window->close();
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case Keyboard::Scancode::Escape:
				window->close();
				break;
			}
		}
	}
}

void App::App_Update(void)
{
	App_Pollevent();
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (!mousepressed)
		{
			mousepressed = true;
			for (size_t index = 0; index < BUTTON_AMOUNT; index++)
			{
				if (buttons[index].getGlobalBounds().contains(Get_Mouse_Pos()))
				{
					buttons[index].setFillColor(Color::Blue);
					buttonpressed = true;
					buttonnumber = index;
				}
			}
		}
	}
	else
	{
		if (buttonpressed)
		{
			//std::cout << "Button Pressed" << "Button : " << buttonnumber << std::endl;
			Calculate(buttonnumber);
		}
		else
		{

			buttons[buttonnumber].setFillColor(Color::White);
		}
		buttonpressed = false;
		mousepressed = false;
	}

	Update_Display();
}

void App::App_Render(void)
{
	window->clear();
	window->draw(baseshape);
	window->draw(yinculator);
	window->draw(display);
	window->draw(*displaytext);
	window->draw(buttonarea);
	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		window->draw(buttons[i]);
	}
	window->display();
}
