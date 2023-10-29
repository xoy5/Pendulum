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
#pragma once
#include <vector>
#include "Rect.h"
#include "Graphics.h"
#include "Colors.h"
#include "Physics.h"
#include <algorithm>
#include "Mouse.h"
#include <cmath>

class Pendulum
{
private:
	class Ball
	{
		public:
			enum class Side
			{
				Left, 
				Right
			};
		public:
			Ball(float mass, float rope, Color c, const Vei2& attachment_point)
				: 
				mass(mass),
				rope(rope),
				c(c),
				pos( float( attachment_point.x ), float( attachment_point.y + rope ) ),
				attachment_point(attachment_point),
				radius(std::min(std::max(int( mass / 45), 8), 22) ) // 300 - 1000
			{}	
			void Draw(Graphics& gfx) const;
			void PlusMass();
			void PlusRope();			
			void MinusMass();
			void MinusRope();
			Side WhichSideIm() const;
		public:
			float mass;   
			float rope;  
			Color c;
			Vec2 pos;
			float angleV = 0;
			float angleA = 0;
			float angle = 3.14159265358979f / 4.0f;
			const Vei2 & attachment_point;
			int radius;
	};
public:
	Pendulum();
	void Draw(Graphics& gfx) const; 
	void UpdateBools(const float & dt);
	void AddBall();
	void DelBall();
	bool IsDraggingBall(const Mouse & mouse) const;
	void DragBall(const Mouse & mouse);
// kms i dont know inheritance or friend yet lol
	float GetG() const;
	void NormalG();
	void ZeroG();
	void PlusG();
	void MinusG();	
	float GetF() const;
	void ZeroF();
	void PlusF();
	void MinusF();
	void PlusMass(int i);
	void PlusRope(int i);
	void MinusMass(int i);
	void MinusRope(int i);
	Color GetColor(int i) const; 
	int GetCountBalls() const;
	float GetMass(int i) const;
	float GetRope(int i) const;
////////////////////////////////////////////////
public:
	bool stop = false;
private: 
	float gravitation = phy::G;
	float friction = phy::F;
	std::vector<Ball> balls;
	Vei2 attachment_point;
	static constexpr Color colors[5] = { Color(200,200,200), 
										 Color(255, 102, 102), 
										 Color(153, 102, 255), 
										 Color(153, 255, 102), 
									     Color(153, 248, 255)};
};