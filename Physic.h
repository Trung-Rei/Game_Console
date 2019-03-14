#pragma once

namespace Physic
{
	struct PhysicObject
	{
		double v;
		double a;
		double t;
		double Height;
		double Side;
		int HeightInt;
		int SideInt;
		int CurrentX;
		int CurrentY;
		bool Moved;
	};
	void SetOriginPosi(PhysicObject &Ball, int CurrentX, int CurrentY);
	void Init(PhysicObject &Ball, double v, double a);
	void ResetTime(PhysicObject &Ball);
	void MoveObject_Height(PhysicObject &Ball, double Delta_t);
}