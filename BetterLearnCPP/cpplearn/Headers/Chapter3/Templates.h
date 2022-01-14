//
// Created by aszlamp on 23/12/2019.
//

#pragma once

namespace Chapter3_5
{

    //Class Templates

    template<typename T>
    class Vector {
    private:
        T* elem; // elem points to an array of sz elements of type T
        int sz;
    public:
        Vector(int s); // constructor: establish invariant, acquire resources
        ~Vector() { delete[] elem; } // destructor: release resources

        Vector(const Vector& a); // copy constructor
        Vector& operator=(const Vector& a); // copy assignment
        Vector(Vector&& a); // move constructor
        Vector& operator=(Vector&& a); // move assignment

        T* begin(Vector<T>& x); //begin function
        T* end(Vector<T>& x); //end function

        T& operator[](int i);
        const T& operator[](int i) const;
        int size() const { return sz; }
    };

    template<typename T>
    Vector<T>::Vector(int s)
    {
        if (s<0) throw std::length_error{""};
        elem = new T[s];
        sz = s;
    }
    template<typename T>
    const T& Vector<T>::operator[](int i) const
    {
        if (i<0 || size()<=i)
            throw std::out_of_range{"Vector::operator[]"};
        return elem[i];
    }

    void write(const Vector<std::string>& vs) // Vector of some strings
    {
        for (int i = 0; i!=vs.size(); ++i)
            std::cout << vs[i] << '\n';
    }

    template<typename T>
    T* Vector<T>::begin(Vector<T>& x)
    {
        return &x[0]; // pointer to first element
    }
    template<typename T>
    T* Vector<T>::end(Vector<T>& x)
    {
        return x.begin()+x.size(); // pointer to one-past-last element
    }

    Vector<char> vc(200); // vector of 200 characters
    Vector<std::string> vs(17); // vector of 17 strings
    Vector<std::list<int>> vli(45); // vector of 45 lists of integers

    //Function Objects

    template<typename T>
    class Less_than {
        const T val; // value to compare against
    public:
        Less_than(const T& v) :val(v) { }
        bool operator()(const T& x) const { return x<val; } // call operator
        void begin() const;
    };
    //The function called operator() implements the ‘‘function call,’’ ‘‘call,’’ or ‘‘application’’ operator ().

    Less_than<int> lti {42}; // okay lti contain 42 AND LATER when invoking lti(i) 42 will be compared to i
    Less_than<std::string> lts {"Backus"}; //  okay lts contains "Backus" AND LATER when invoking lts(s) "Backus" will be compared to s

    void fct(int i, const std::string & s)
    {
        bool b1 = lti(i); // true if n<42
        bool b2 = lts(s); // true if s<"Backus"
// ...
    }

    template<typename C, typename P>
    int count(const C& c, P pred)
    {
        int cnt = 0;
        for (const auto& x : c)
            if (pred(x))
                ++cnt;
        return cnt;
    }

    void f(const std::vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s)
    {
        std::cout << "number of values less than " << x
             << ": " << count(vec,Less_than<int>{x})
             << '\n';
        std::cout << "number of values less than " << s
             << ": " << count(lst,Less_than<std::string>{s})
             << '\n';
    }

//    Here, Less_than<int>{x} constructs an object for which the call operator compares to the int called x;
//    Less_than<string>{s} constructs an object that compares to the string called s. The beauty of these
//    function objects is that they carry the value to be compared against with them. We don’t hav e to
//    write a separate function for each value (and each type), and we don’t hav e to introduce nasty
//    global variables to hold values. Also, for a simple function object like Less_than inlining is simple,
//    so that a call of Less_than is far more efficient than an indirect function call. The ability to carry
//    data plus their efficiency make function objects particularly useful as arguments to algorithms.


    void h(const std::vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s)
    {
        std::cout << "number of values less than " << x
             << ": " << count(vec,[&](int a){ return a<x; })
             << '\n';
        std::cout << "number of values less than " << s
             << ": " << count(lst,[&](const std::string& a){ return a<s; })
             << '\n';
    }
//    The notation [&](int a){ return a<x; } is called a lambda expression (§11.4). It generates a function
//    object exactly like Less_than<int>{x}. The [&] is a capture list specifying that local names used
//    (such as x) will be passed by reference. Had we wanted to ‘‘capture’’ only x, we could have said so: [&x].

//    A function that applies an operation to each object pointed to by the elements of a container of pointers
    template<class C, class Oper>
    void for_all(C& c, Oper op) // assume that C is a container of pointers
    {
        for (auto& x : c)
            op(*x); //pass op() a reference to each element pointed to
    }

    void user()
    {
        std::vector<Chapter3::Shape*> v; //std::unique_ptr didn't work for some reason
        while (std::cin)
            v.push_back(Chapter3::read_shape(std::cin));
        for_all(v,[](Chapter3::Shape& s){ s.draw(); }); // draw_all()
        for_all(v,[](Chapter3::Shape& s){ s.rotate(45); }); // rotate_all(45)
    }

//    I pass a reference to Shape to a lambda so that the lambda doesn’t hav e to care exactly how the
//    objects are stored in the container. In particular, those for_all() calls would still work if I changed v
//    to a vector<Shape∗>.

    //Function Templates

    template<typename Container, typename Value>
    Value sum(const Container& c, Value v)
    {
        for (auto x : c)
            v+=x;
        return v;
    }

//    The Value template argument and the function argument v are there to allow the caller to specify the
//    type and initial value of the accumulator (the variable in which to accumulate the sum):

    void user(std::vector<int>& vi, std::list<double>& ld, std::vector<std::complex<double>>& vc)
    {
        int x = sum(vi,0); // the sum of a vector of ints (add ints)
        double d = sum(vi,0.0); // the sum of a vector of ints (add doubles)
        double dd = sum(ld,0.0); // the sum of a list of doubles
        auto z = sum(vc, std::complex<double>{}); // the sum of a vector of complex<double>
        // the initial value is {0.0,0.0}
    }

    //Variadic Templates

    template<typename T>
    void g(T x)
    {
        std::cout << x << " ";
    }

    void f() { } // do nothing

    template<typename T, typename ... Tail>
    void f(T head, Tail... tail)
    {
        g(head); // do something to head
        f(tail...); // try again with tail
    }

    int j()
    {
        std::cout << "first: ";
        f(1,2.2,"hello");
        std::cout << "\nsecond: ";
        f(0.2,'c',"yuck!",0,1,2);
        std::cout << "\n";
        return 1;
    }
    //This would call f(1,2.2,"hello"), which will call f(2.2,"hello"), which will call f("hello"), which will call f().

    //Aliases

    using size_t = unsigned int; //an alias

    template<typename T>
    class VecTemp {
    public:
        using value_type = T;
// ...
    };
    //It is very common for a parameterized type to provide an alias for types related to their template arguments.

//    every standard-library container provides value_type as the name of its value type (§31.3.1).
//    This allows us to write code that will work for every container that follows this convention.
    template<typename C>
    using Element_type = typename C::value_type;
    template<typename Container>
    void algo(Container& c)
    {
        VecTemp<Element_type<Container>> vec; // keep results here
// ...
    }

//    The aliasing mechanism can be used to define a new template by binding some or all template arguments.
    template<typename Key, typename Value>
    class Map {
// ...
    };

    template<typename Value>
    using String_map = Map<std::string,Value>;
    String_map<int> m; // m is a Map<string,int>

}