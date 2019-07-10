#ifndef __vertex_h__
#define __vertex_h__

#include <iostream>
#include <cmath>

template <class t> struct ver2
{
    union
    {
        struct{t x, y;};
        t raw[2];
    };
    ver2(): x(0), y(0){}
    ver2(t _x, t _y): x(_x), y(_y){}
    ver2<t> operator+(const ver2<t>& sec) {return ver2<t>(x + sec.x, y + sec.y);}
    ver2<t> operator-(const ver2<t>& sec) {return ver2<t>(x - sec.x, y - sec.y);}
    ver2<t> operator*(float f) {return ver2<t>(x * f, y * f);}
    template <class> friend std::ostream& operator<<(std::ostream& stream, const ver2<t> &ver)
    {
        stream << "(" << ver.x << ", " << ver.y << ")\n";
        return stream;
    }
};

template <class t> struct ver3
{
    union
    {
        struct{t x, y, z;};
        t raw[3];
    };
    ver3(): x(0), y(0), z(0){}
    ver3(t _x, t _y, t _z): x(_x), y(_y), z(_z){}

    ver3<t> operator+(const ver3<t>& sec) const {return ver3<t>(x + sec.x, y + sec.y, z + sec.z);}
    ver3<t> operator-(const ver3<t>& sec) const {return ver3<t>(x - sec.x, y - sec.y, z - sec.z);}
    t       operator*(const ver3<t>& sec) const {return x * sec.x + y * sec.y + z * sec.z;}
    ver3<t> operator*(float f)            const {return ver3<t>(x * f, y * f, z * f);}
    ver3<t> operator^(const ver3<t>& sec) const {return ver3<t>(y*sec.z - z*sec.y,
                                                          z*sec.x - x*sec.z,
                                                          x*sec.y - y*sec.x);}

    float norm() const {return std::sqrt(x*x + y*y + z*z);}

    ver3<t>& normalize(t l = 1) {*this = (*this)*(l/norm()); return *this;}

    template <class> friend std::ostream& operator<<(std::ostream& stream, const ver3<t> &ver)
    {
        stream << "(" << ver.x << ", " << ver.y << ", " << ver.z << ")\n";
        return stream;
    }
};

typedef ver2<int> ver2i;
typedef ver2<float> ver2f;
typedef ver3<int> ver3i;
typedef ver3<float> ver3f;

#endif