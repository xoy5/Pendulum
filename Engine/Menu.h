#pragma once
#include "Graphics.h"
#include "Colors.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
/// Kacper Wojtkowski 2023 october
/// pls dont copy my code because my bw in 2025 will be 225 pounds  
/// with 5% body fat for real I dont scam ( if I get some tren or my mom will still cook for me)
/// Files:
/// Pendulum.h 
/// Pendulum.cpp 
/// Menu.h 
/// Menu.cpp 
/// Physics.h 
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "Vec2.h"
#include "Rect.h"
#include "Font.h"
#include "Pendulum.h"

class Menu
{
public:
	enum class State
	{
		minimized,
		open
	};
	enum class Modify
	{
		State,
		GravityNormal,
		GravityUp,
		GravityDown,
		MassUp,
		MassDown,
		RopeUp,
		RopeDown
	};
public:
	Menu() = default;
	void Draw(Pendulum & pen, Graphics& gfx) const;
	void OnClick(const Vei2 & pos, Pendulum & pen) ;
private:
	int width = 140;
	int height = 160;
	Vei2 pos = Vei2{800 - width, 0};
	Color c = Color(140, 140, 140);
	RectI SizeButton{ 770, 785, 10, 16 };
	RectI PlayButton{ 750, 766, 0, 19 };
		  // char size 16x28
	const RectI AddButton	  { 670, 718, 20, 45 };
	const RectI DelButton	  { 734, 782, 20, 45 };

	const RectI NormalButton  { 670, 686, 46, 65 };
	const RectI ZeroButton    { 702, 718, 46, 70 };
	const RectI PlusButton    { 734, 750, 46, 70 };
	const RectI MinusButton   { 766, 782, 46, 70 };	

	const RectI ZeroButton2   { 702, 718, 95, 120 };
	const RectI PlusButton2   { 734, 750, 95, 120 };
	const RectI MinusButton2  { 766, 782, 95, 120 };

		  //1
	const RectI PlusMassButton1	 {670, 686, 145, 170};
	const RectI MinusMassButton1 {702, 718, 145, 170};
	const RectI PlusRopeButton1  {734, 750, 145, 170};
	const RectI MinusRopeButton1 {766, 782, 145, 170};
		  //2
	const RectI PlusMassButton2  {670, 686, 220, 245};
	const RectI MinusMassButton2 {702, 718, 220, 245};
	const RectI PlusRopeButton2  {734, 750, 220, 245 };
	const RectI MinusRopeButton2 {766, 782, 220, 245 };
		  //3
	const RectI PlusMassButton3  { 670, 686, 295, 320 };
	const RectI MinusMassButton3 { 702, 718, 295, 320 };
	const RectI PlusRopeButton3  { 734, 750, 295, 320 };
	const RectI MinusRopeButton3 { 766, 782, 295, 320 };
		  //4
	const RectI PlusMassButton4  { 670, 686, 370, 395 };
	const RectI MinusMassButton4 { 702, 718, 370, 395 };
	const RectI PlusRopeButton4  { 734, 750, 370, 395 };
	const RectI MinusRopeButton4 { 766, 782, 370, 395 };
	const // 5
	const RectI PlusMassButton5  { 670, 686, 445, 470 };
	const RectI MinusMassButton5 { 702, 718, 445, 470 };
	const RectI PlusRopeButton5  { 734, 750, 445, 470 };
	const RectI MinusRopeButton5 { 766, 782, 445, 470 };


	State state = Menu::State::minimized;
	Font text = Font("images/Fixedsys16x28.bmp");
};