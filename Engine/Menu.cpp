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
#include "Menu.h"

void Menu::Draw(Pendulum & pen, Graphics& gfx) const
{
	if (state == Menu::State::open)
	{
		std::string gravitation = std::to_string(pen.GetG());
		std::string friction    = std::to_string( pen.GetF() );
		gfx.DrawRect(pos.x, pos.y, width, height, c);
		if ( pen.stop )
		{
			text.DrawText("o", Vei2(750, -2), Color(255, 80, 80), gfx);
		}
		else
		{
			text.DrawText("o", Vei2(750, -2), Color(102, 255, 102), gfx);
		}

		text.DrawText("Add", Vei2(670, 20), Color(102, 255, 102), gfx);
		text.DrawText("Del", Vei2(730, 20), Color(255, 80, 80), gfx);

		text.DrawText("N", Vei2(670, 45), Color(102, 204, 255), gfx);
		text.DrawText("0", Vei2(702, 45), Color(210, 210, 210), gfx);
		text.DrawText("+", Vei2(734, 45), Color(102, 255, 102), gfx);
		text.DrawText("-", Vei2(766, 45), Color(255, 80, 80), gfx);
		text.DrawText("G = " + gravitation, Vei2(670, 70), Colors::White, gfx);

		text.DrawText("0", Vei2(702, 95), Color(210, 210, 210), gfx);
		text.DrawText("+", Vei2(734, 95), Color(102, 255, 102), gfx);
		text.DrawText("-", Vei2(766, 95), Color(255, 80, 80), gfx);
		text.DrawText("F " + friction, Vei2(670, 120), Colors::White, gfx);

		int size = pen.GetCountBalls();
		if (1 <= size)
		{
			Color c = pen.GetColor(0);
			text.DrawText("+ - + -", Vei2(670, 145), c, gfx);
			text.DrawText("M = " + std::to_string( int(pen.GetMass(0))), Vei2(670, 170), c, gfx);
			text.DrawText("L = " + std::to_string( int(pen.GetRope(0))), Vei2(670, 195), c, gfx);
		}
		if (2 <= size) 
		{
			Color c = pen.GetColor(1);
			text.DrawText("+ - + -", Vei2(670, 220), c, gfx);
			text.DrawText("M = " + std::to_string(int(pen.GetMass(1))), Vei2(670, 245), c, gfx);
			text.DrawText("L = " + std::to_string(int(pen.GetRope(1))), Vei2(670, 270), c, gfx);
		}
		if (3 <= size) 
		{
			Color c = pen.GetColor(2);
			text.DrawText("+ - + -", Vei2(670, 295), c, gfx);
			text.DrawText("M = " + std::to_string(int(pen.GetMass(2))), Vei2(670, 320), c, gfx);
			text.DrawText("L = " + std::to_string(int(pen.GetRope(2))), Vei2(670, 345), c, gfx);
		}
		if (4 <= size) 
		{
			Color c = pen.GetColor(3);
			text.DrawText("+ - + -", Vei2(670, 370), c, gfx);
			text.DrawText("M = " + std::to_string(int(pen.GetMass(3))), Vei2(670, 395), c, gfx);
			text.DrawText("L = " + std::to_string(int(pen.GetRope(3))), Vei2(670, 420), c, gfx);
		}
		if (5 == size) 
		{
			Color c = pen.GetColor(4);
			text.DrawText("+ - + -", Vei2(670, 445), c, gfx);
			text.DrawText("M = " + std::to_string(int(pen.GetMass(4))), Vei2(670, 470), c, gfx);
			text.DrawText("L = " + std::to_string(int(pen.GetRope(4))), Vei2(670, 495), c, gfx);
		}

	}
	gfx.DrawRect(SizeButton, Color(190, 185, 185) );
}

void Menu::OnClick(const Vei2 & pos, Pendulum & pen) 
{
	if ( SizeButton.Contains(pos) )
	{
		if (state == Menu::State::open)
		{
			state = Menu::State::minimized;
		}
		else if (state == Menu::State::minimized)
		{
			state = Menu::State::open;
		}
	}
	else if (PlayButton.Contains(pos))
	{
		if (pen.stop)
		{
			pen.stop = false;
		}
		else
		{
			pen.stop = true;
		}
	}
	else if (AddButton.Contains(pos))
	{
		pen.AddBall();
		if (height != 535)
		{
			height += 75;
		}
	}
	else if (DelButton.Contains(pos))
	{
		pen.DelBall();
		if (height != 160)
		{
			height -= 75;
		}
	}
	else if (NormalButton.Contains(pos))
	{
		pen.NormalG();
	}	
	else if (ZeroButton.Contains(pos))
	{
		pen.ZeroG();
	}
	else if (PlusButton.Contains(pos))
	{
		pen.PlusG();
	}
	else if (MinusButton.Contains(pos))
	{
		pen.MinusG();
	}	
	else if (ZeroButton2.Contains(pos))
	{
		pen.ZeroF();
	}
	else if (PlusButton2.Contains(pos))
	{
		pen.PlusF();
	}
	else if (MinusButton2.Contains(pos))
	{
		pen.MinusF();
	}
	else if (PlusMassButton1.Contains(pos))
	{
		pen.PlusMass(0);
	}
	else if (MinusMassButton1.Contains(pos))
	{
		pen.MinusMass(0);
	}	
	else if (PlusRopeButton1.Contains(pos))
	{
		pen.PlusRope(0);
	}
	else if (MinusRopeButton1.Contains(pos))
	{
		pen.MinusRope(0);
	}
	else if (PlusMassButton2.Contains(pos))
	{
		pen.PlusMass(1);
	}
	else if (MinusMassButton2.Contains(pos))
	{
		pen.MinusMass(1);
	}
	else if (PlusRopeButton2.Contains(pos))
	{
		pen.PlusRope(1);
	}
	else if (MinusRopeButton2.Contains(pos))
	{
		pen.MinusRope(1);
	}
	else if (PlusMassButton3.Contains(pos))
	{
		pen.PlusMass(2);
	}
	else if (MinusMassButton3.Contains(pos))
	{
		pen.MinusMass(2);
	}
	else if (PlusRopeButton3.Contains(pos))
	{
		pen.PlusRope(2);
	}
	else if (MinusRopeButton3.Contains(pos))
	{
		pen.MinusRope(2);
	}
	else if (PlusMassButton4.Contains(pos))
	{
		pen.PlusMass(3);
	}
	else if (MinusMassButton4.Contains(pos))
	{
		pen.MinusMass(3);
	}
	else if (PlusRopeButton4.Contains(pos))
	{
		pen.PlusRope(3);
	}
	else if (MinusRopeButton4.Contains(pos))
	{
		pen.MinusRope(3);
	}
	else if (PlusMassButton5.Contains(pos))
	{
		pen.PlusMass(4);
	}
	else if (MinusMassButton5.Contains(pos))
	{
		pen.MinusMass(4);
	}
	else if (PlusRopeButton5.Contains(pos))
	{
		pen.PlusRope(4);
	}
	else if (MinusRopeButton5.Contains(pos))
	{
		pen.MinusRope(4);
	}
}
