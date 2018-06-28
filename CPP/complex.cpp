#ifndef __COMPLEX_CPP__
#define __COMPLEX_CPP__

class complex
{
public:
    complex(double r = 0, double i = 0)
        : re(r), im(i)
    {}

    complex& operator+= (const complex& x);
    double real() const { return re; }
    double imag() const { return im; }

private:
    double re, im;

    friend complex& __doapl(complex* ths, const complex& x);
};

complex& complex::operator+=(const complex& x)
{
    return __doapl(this, x);
}

complex& __doapl(complex* ths, const complex& x)
{
    ths->re += x.re;
    ths->im += x.im;
    return *ths;
}

#endif