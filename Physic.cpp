#include "Physic.h"

namespace Physic
{
	void SetOriginPosi(PhysicObject &Ball, int CurrentX, int CurrentY)
	{
		Ball.CurrentX = CurrentX; Ball.CurrentY = CurrentY;
	}
	void Init(PhysicObject &Ball, double v, double a)
	{
		Ball.v = v; Ball.a = a;
		Ball.t = 0;
		Ball.Height = 0; Ball.HeightInt = 0;
		Ball.Side = 0; Ball.SideInt = 0;
		Ball.Moved = false;
	}
	void ResetTime(PhysicObject &Ball)
	{
		Ball.CurrentX += Ball.SideInt; Ball.CurrentY -= Ball.HeightInt;
		Ball.t = 0;
	}
	void MoveObject_Height(PhysicObject &Ball, double Delta_t)
	{
		Ball.t += Delta_t;
		Ball.Height = Ball.v * Ball.t + 0.5 * Ball.a * Ball.t * Ball.t;
		if ((int)Ball.Height == Ball.HeightInt)
			Ball.Moved = false;
		else
			Ball.Moved = true;
		Ball.HeightInt = (int)Ball.Height;
	}
}