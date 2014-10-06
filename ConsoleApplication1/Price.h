#pragma once
class Price
{
public:
	Price()
	{
	}
	explicit Price(double dblVal)
	{
			double d = dblVal;
		d += 2048.0 + 1e-10;
		d *= 65536.0;
		i = int(d);
		decomp.floor -= 2048;
		//decomp.frac += 1;
		//decomp.frac &= 0xFFFE;
	}
	~Price()
	{
	}

public:
	Price operator-(const Price & p2)
	{
		Price pr;
		pr.i = i - p2.i;
//		decomp.frac &= 0xFFFE;
		return pr;
	}

public:
	union {
		int i;
		struct {
			unsigned short frac;
			short floor;
		} decomp;
	};

};

