#pragma once

namespace Chapter2
{
    struct Vector {
    private:
        int sz; // number of elements
        double *elem; // pointer to elements
    public:
        Vector(int s) :elem{new double[s]}, sz{s} { } // construct a Vector

        ~Vector() { delete[] elem; } // destructor: release resources

        int size() const { return sz; }

        double& operator[](int i) {
            if (i<0 || size()<=i) throw std::out_of_range{"Vector::operator[]"}; // detect an attempted out-of-range access and throw an out_of_range exception
            return elem[i]; } // element access: subscripting

        void vector_init(Vector &v, int s) {
            v.elem = new double[s]; // allocate an array of s doubles
            //The new operator allocates memory from an area called the free store (also known as dynamic memory and heap)
            v.sz = s;
        }

//        double read_and_sum(int s)
//        // read s integers from cin and return their sum; s is assumed to be positive
//        {
//            Vector v;
//            vector_init(v,s); //allocate s elements for v
//            for (int i=0; i!=s; ++i)
//                std::cin >> v.elem[i]; // read into elements
//            double sum = 0;
//            for (int i=0; i!=s; ++i)
//                sum+=v.elem[i]; // take the sum of the elements
//            return sum;
//        }

        double read_and_sum(int s)
        {
            Vector v(s); // make a vector of s elements
            for (int i=0; i!=v.size(); ++i)
            std::cin >> v[i]; //read into elements
            double sum = 0;
            for (int i=0; i!=v.size(); ++i)
            sum+=v[i]; //take the sum of the elements
            return sum;
        }
    };

    double sqrt_sum(Vector& v)
    {
        double sum = 0;
        for (int i=0; i!=v.size(); ++i)
        sum+=sqrt(v[i]); // sum of square roots
        return sum;
    }

    void f(Vector& v)
    {
// ...
        try { // exceptions here are handled by the handler defined below
            v[v.size()] = 7; // tr y to access beyond the end of v
        }
        catch (std::out_of_range) { // oops: out_of_range error
// ... handle range error ...
        }
// ...
    }

    void test()
    {
        try {
            Vector v(-27);
        }
        catch (std::length_error) {
// handle negative size
        }
        catch (std::bad_alloc) {
// handle memory exhaustion
        }
    }

    void fct(int n)
    {
        Vector v(n);
// ... use v ...
        {
            Vector v2(2*n);
// ... use v and v2 ...
        } // v2 is destroyed here
// ... use v ..
    } // v is destroyed here
}