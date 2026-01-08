#pragma once
#include "Globals.h"
namespace YIN
{
class App
{
private:
	RenderWindow* window;
	VideoMode videomode;

	RectangleShape baseshape;
	RectangleShape yinculator;
	RectangleShape display;
	RectangleShape buttonarea;
	RectangleShape buttons[BUTTON_AMOUNT];

	Texture basetexture;
	Texture yinculatortexture;
	Texture buttontexture[BUTTON_AMOUNT];

	Font font;
	std::optional<Text>displaytext;

	bool mousepressed;
	bool buttonpressed;
	size_t buttonnumber;

	std::string input;
	double outputnumber;
	std::stringstream strstream;

	std::vector<double>numbers;
	std::vector<std::string>inputs;
	std::vector<std::string>ops;

	mode_t displaymode;
	pemdas_mode_t pemmode;

public:
	App();
	~App();

	const Vector2f Get_Window_Size();
	const Vector2f Get_Mouse_Pos();

	void App_Init(void);
	bool App_Runnig(void);


	void Set_Display(std::string str);
	void Reset_Values(void);
	void Calculate(size_t buttonnumber);
	void Handle_Number(int number);
	void Handle_Operator(std::string op);
	void Handle_Output(void);
	void Handle_Comma(void);
	void Handle_Backspace(void);

	void Update_Display(void);
	void App_Pollevent(void);
	void App_Update(void);
	void App_Render(void);
};


} // Namspace YIN

/*
 cooltext images
 textsize : 50
 #0374FF
 #012F70
 centered
 70 * 70
 #1F1F1F
 */