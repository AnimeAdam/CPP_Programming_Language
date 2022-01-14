//
// Created by aszlamp on 23/12/2019.
//

#pragma once

namespace Chapter3_3
{

    void test(Chapter3::complex z1)
    {
        Chapter3::complex z2 {z1}; // copy initialization
        Chapter3::complex z3;
        z3 = z2; // copy assignment
// ...
    }

//    Copying of an object of a class is defined by two members: a copy constructor and a copy
//            assignment:
    class Vector {
    private:
        double* elem; // elem points to an array of sz doubles
        int sz;
    public:
        Vector(int s); // constructor: establish invariant, acquire resources
        ~Vector() { delete[] elem; } // destructor: release resources
        Vector(const Vector& a); // copy constructor
        Vector& operator=(const Vector& a); // copy assignment
        Vector(Vector&& a); // move constructor
        Vector& operator=(Vector&& a); // move assignment
        double& operator[](int i);
        const double& operator[](int i) const;
        int size() const;
    };

    Vector::Vector(const Vector& a) // copy constructor
            :elem{new double[sz]}, // allocate space for elements
             sz{a.sz}
    {
        for (int i=0; i!=sz; ++i) // copy elements
            elem[i] = a.elem[i];
    }

    Vector& Vector::operator=(const Vector& a) // copy assignment
    {
        double* p = new double[a.sz];
        for (int i=0; i!=a.sz; ++i)
            p[i] = a.elem[i];
        delete[] elem; // delete old elements
        elem = p;
        sz = a.sz;
        return *this;
    }

    Vector::Vector(Vector&& a)  // move constructor
            :elem{a.elem}, // "grab the elements" from a
             sz{a.sz}
    {
        a.elem = nullptr; // now a has no elements
        a.sz = 0;
    }


}

namespace Chapter3_4
{

    class Vector {
// ...
        Vector(const Vector& a); // copy constr uctor
        Vector& operator=(const Vector& a); // copy assignment

    };

}