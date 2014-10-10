#pragma once
#pragma pack(push,1)
class Price
{
public:
	explicit Price(double dblVal)
	{
		double d = dblVal;
		d += 2048.0 + 1e-10;
		d *= (1 << 16);
		i = int(d);
		dec22.floor -= 2048;
		dec22.frac &= 0xFFF0;
	}
	~Price()
	{
	}

public:
	Price operator+(const Price & p2)
	{
		Price pr(*this);
		pr.i += p2.i;
		return pr;
	}
	Price operator-(const Price & p2)
	{
		Price pr(*this);
		pr.i -= p2.i;
		return pr;
	}
	Price operator*(const int & n)
	{
		Price pr(*this);
		pr.i *= n;
		return pr;
	}

	short floor() { return dec22.floor; }
	unsigned short keyFrac2() { return dec22.frac; }
	unsigned short keyFrac1() { return dec211.frac1; }
	int key() { return i; }
	int key1() { return (i + (1 << 15)) >> 16; }

private:
	union {
		int i;
		struct {
			unsigned short frac;
			short floor;
		} dec22;
		struct {
			unsigned char frac2;
			unsigned char frac1;
			short floor;
		} dec211;
	};

};

#pragma pack(pop)