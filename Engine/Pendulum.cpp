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
#include "Pendulum.h"
#include <cassert>

Pendulum::Pendulum()
	:
	attachment_point(Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 - Graphics::ScreenHeight / 4)
{}
void Pendulum::Draw(Graphics& gfx) const
{
	assert( 0.0f < attachment_point.y );
	assert( attachment_point.y < 600.0f );
	int x = attachment_point.x;
	int y = attachment_point.y;
	constexpr int width = 21;
	constexpr int height = 9;


	for (auto & elem : balls)
	{
		elem.Draw(gfx);
    }
	gfx.DrawRectByCenter( x, y, width, height, Colors::White);
}

void Pendulum::UpdateBools(const float& dt)
{
	if (!stop)
	{
		for (Ball& ball : balls)
		{
			float force = (gravitation) * dt * std::sin(ball.angle);

			// Calculate angular acceleration
			float angularAcceleration = -force / (ball.rope);

			// Update angular velocity and angle
			ball.angleV += angularAcceleration;
			ball.angle += ball.angleV;

			// Apply friction
			ball.angleV *= friction;

			// Update position
			ball.pos = Vec2(
				ball.rope * std::sin(ball.angle) + attachment_point.x,
				ball.rope * std::cos(ball.angle) + attachment_point.y
			);
		}
	}
}

void Pendulum::AddBall()
{
	if (balls.size() < 5)
	{
		balls.emplace_back( Ball( 400 + balls.size() * 70, 50 + balls.size() * 30, colors[balls.size() % 5], attachment_point));
	}
	else
	{
		balls.emplace_back(Ball(500, 300, colors[balls.size() % 5], attachment_point));
	}
}
void Pendulum::DelBall()
{
	if (!balls.empty())
	{
		balls.pop_back();
	}
}

bool Pendulum::IsDraggingBall(const Mouse& mouse) const
{
	Vei2 posMouse = mouse.GetPos();
	for (int i = 0; i < balls.size(); i++)
	{
		const auto& elem = balls[i];
		Vei2 pos = Vei2(elem.pos);
		int radius = elem.radius;
		RectI field = RectI(pos.x - radius, pos.x + radius, pos.y - radius, pos.y + radius);
		if (field.Contains(posMouse))
		{
			return true;
		}
	}
	return false;
}
void Pendulum::DragBall(const Mouse& mouse)
{
	Vei2 posMouse = mouse.GetPos();
	Vei2 posBall = { 0,0 };
	int iBall = -1;
	for (int i = 0; i < balls.size(); i++)
	{
		const auto& elem = balls[i];
		if (posMouse == Vei2(elem.pos) )
		{
			break;
		}
		Vei2 pos = Vei2(elem.pos);
		int radius = elem.radius;
		RectI field = RectI(pos.x - radius, pos.x + radius, pos.y - radius, pos.y + radius);
		if (field.Contains(posMouse))
		{
			posBall = posMouse;
			iBall = i;
			break;
		}
	}
	if (iBall != -1)
	{
		if (30 < Vei2(mouse.GetPos() - attachment_point).GetLength() && Vei2(mouse.GetPos() - attachment_point).GetLength() < 370)
		{
			balls[iBall].pos = Vec2(mouse.GetPos());
			balls[iBall].rope = (balls[iBall].pos - Vec2(attachment_point)).GetLength();
		}

		// Oblicz ró¿nicê miêdzy nowym po³o¿eniem a punktem przyczepienia
		Vec2 delta = balls[iBall].pos - Vec2(attachment_point);

		// Oblicz now¹ wartoœæ angle przy u¿yciu atan2
		balls[iBall].angle = std::atan2(delta.x, delta.y);

		// Upewnij siê, ¿e wartoœæ angle jest w odpowiednim zakresie
		if (balls[iBall].angle < 0) {
			balls[iBall].angle += 2 * 3.141592653589793236; // Zakres [0, 2*pi]
		}

		balls[iBall].angleV = 0;
		balls[iBall].angleA = 0;

	}
	
}

float Pendulum::GetG() const
{
	return gravitation;
}
void Pendulum::NormalG()
{
	gravitation = phy::G;
}
void Pendulum::ZeroG()
{
	gravitation = 0.0f;
}
void Pendulum::PlusG()
{
	gravitation += 0.1f;
}
void Pendulum::MinusG()
{
	gravitation = std::max(gravitation - 0.1f, 0.0f);
}

float Pendulum::GetF() const
{
	return friction;
}
void Pendulum::ZeroF()
{
	friction = phy::F;
}
void Pendulum::PlusF()
{
	friction = std::min(friction + 0.001f, 1.0f);
}
void Pendulum::MinusF()
{
	friction = std::max(friction - 0.001f, 0.0f);
}

void Pendulum::PlusMass(int i)
{
	balls[i].PlusMass();
}
void Pendulum::PlusRope(int i)
{
	balls[i].PlusRope();
}
void Pendulum::MinusMass(int i)
{
	balls[i].MinusMass();
}
void Pendulum::MinusRope(int i)
{
	balls[i].MinusRope();
}

Color Pendulum::GetColor(int i) const
{
	return colors[i];
}
int Pendulum::GetCountBalls() const
{
	return balls.size();
}
float Pendulum::GetMass(int i) const
{
	return balls[i].mass;
}
float Pendulum::GetRope(int i) const
{
	return balls[i].rope;
}

void Pendulum::Ball::Draw(Graphics& gfx) const
{
	gfx.DrawCircle(int( pos.x ), int( pos.y ), radius, c);
	gfx.DrawLine(pos, Vec2( attachment_point ), c, rope, 2);
}
void Pendulum::Ball::PlusMass()
{
	if (mass < 1000.0f)
	{
		mass = std::min(mass + 10.0f, 1000.0f);
		radius = std::min(std::max(int(mass / 45), 8), 22);
	}
}
void Pendulum::Ball::PlusRope()
{
	if (370.0f > rope)
	{
		rope = std::min(370.0f, rope + 10.0f);
		Vec2 dir = pos - Vec2(attachment_point.x, attachment_point.y);
		dir = dir.Normalize();
		pos += (dir * 10);
	}
}
void Pendulum::Ball::MinusMass()
{
	if (300 < mass)
	{
		mass = std::max(mass - 10.0f, 300.0f);
		radius = std::min(std::max(int(mass / 45), 8), 22);
	}
}
void Pendulum::Ball::MinusRope()
{
	if (30.0f < rope)
	{
		rope = std::max(30.0f, rope - 10.0f);
		Vec2 dir = pos - Vec2(attachment_point.x, attachment_point.y);
		dir = dir.Normalize();
		pos -= (dir * 10);
	}
}

Pendulum::Ball::Side Pendulum::Ball::WhichSideIm() const
{
	if (pos.x <= Graphics::ScreenWidth / 2 - 1)
	{
		return Ball::Side::Left;
	}
	else
	{
		return Ball::Side::Right;
	}
}
