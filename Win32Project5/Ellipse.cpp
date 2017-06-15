#include "stdafx.h"
#include "Ellipse.h"

namespace Forms
{
	void Ellipse::Draw(Graphics &graphics, HDC hdc)
	{
	
		if (filled)
		{
			SolidBrush brush(color);
			graphics.FillEllipse(&brush, x, y, w, h);
		}		
		else
		{
			Pen pen(color);
			graphics.DrawEllipse(&pen, x, y, w, h);
		}
		
	}

	double Ellipse::GetArea()
	{
		return M_PI * (w/2.0) * (h/2.0);
	}

	bool Ellipse::IsInside(int Cx, int Cy)
	{
		double t1 = (Cx - x - w / 2.0);
		t1 *= t1;
		double t2 = w / 2.0;
		t2 *= t2;
		double t3 = (Cy - y - h / 2.0);
		t3 *= t3;
		double t4 = h / 2.0;
		t4 *= t4;
		return (((t1 / t2) + (t3 / t4)) <= 1.0);
	}
}

