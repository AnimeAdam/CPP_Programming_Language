#pragma once

namespace Chapter3 {

    class complex {
        double re, im; // representation: two doubles
    public:
        complex(double r, double i) : re{r}, im{i} {} // construct complex from two scalars
        complex(double r) : re{r}, im{0} {} // construct complex from one scalar
        complex() : re{0}, im{0} {} // default complex: {0,0}
        double real() const { return re; }

        void real(double d) { re = d; }

        double imag() const { return im; }

        void imag(double d) { im = d; }

        complex &operator+=(complex z) {
            re += z.re, im += z.im;
            return *this;
        } // add to re and im
// and return the result
        complex &operator-=(complex z) {
            re -= z.re, im -= z.im;
            return *this;
        }

        complex &operator*=(complex); // defined out-of-class somewhere
        complex &operator/=(complex); // defined out-of-class somewhere
    };

    bool operator==(complex a, complex b) // equal
    {
        return a.real() == b.real() && a.imag() == b.imag();
    }

    bool operator!=(complex a, complex b) // not equal
    {
        return !(a == b);
    }

    complex operator+(complex a, complex b) { return a += b; }

    complex operator-(complex a, complex b) { return a -= b; }

    complex operator-(complex a) { return {-a.real(), -a.imag()}; } // unary minus
//    complex operator*(complex a, complex b) { return a *= b; }
//    complex operator/(complex a, complex b) { return a /= b; }

//    void f(complex z)
//    {
//        complex a {2.3}; // construct {2.3,0.0} from 2.3
//        complex b {1/a};
//        complex c {a+z*complex{1,2.3}};
//// ...
//        if (c != b)
//            c = -(b/a)+2*b;
//        //The compiler converts operators involving complex numbers into appropriate function calls. For
//        //example, c!=b means operator!=(c,b) and 1/a means operator/(complex{1},a).
//    }
}