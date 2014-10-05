#pragma once
class Price
{
public:
	Price(double dblVal)
	{
		double d = dblVal;
		d += 2048.0 + 1e-10;
		d *= 65536.0;
		i = int(d);
		decomp.floor -= 2048;
	}
	~Price()
	{
	}

public:


public:
	union {
		int i;
		struct {
			unsigned short frac;
			short floor;
		} decomp;
	};

};

