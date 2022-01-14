#pragma once

namespace Chapter3 {

    //region Concrete Class

    class Vector {
    private:
        int sz; // number of elements
        double *elem; // pointer to elements

    public:

        int size() const { return sz; }

        Vector(std::initializer_list<double>) ; // initialize with a list
// ...
        void push_back(double); // add element at end increasing the size by one
// ...

        double& operator[](int i) {
            if (i<0 || size()<=i) throw std::out_of_range{"Vector::operator[]"}; // detect an attempted out-of-range access and throw an out_of_range exception
            return elem[i]; } // element access: subscripting

        Vector read(std::istream &is) {
            Vector v{1, 2, 3};
            for (double d; is >> d;) // read floating-point values into d
                v.push_back(d); // add d to v
            return v;
            //The input loop is terminated by an end-of-file or a formatting error.
        }
    };

    //Constructor
    Vector::Vector(std::initializer_list<double> lst) // initialize with a list
            : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
        std::copy(lst.begin(), lst.end(), elem); // copy from lst into elem
    }

    Vector v1 = {1,2,3,4,5}; // v1 has 5 elements
    Vector v2 = {1.23, 3.45, 6.7, 8}; // v2 has 4 elements

    //endregion

    //region Abstract Classes

    class Container {
    private:
        int sz; // number of elements
        double *elem; // pointer to elements

    public:
        int size1() { return sz; }

        virtual double &operator[](int) = 0; // pure virtual function
        virtual int size() const = 0; // const member function (§3.2.1.1)
        virtual ~Container() {} // destructor (§3.2.1.2)

    };

    void use(Container &c) {
        const int sz = c.size();
        for (int i = 0; i != sz; ++i)
            std::cout << c[i] << '\n';
    }

    class Vector_container : public Container //can be read as ‘‘is derived from’’ or ‘‘is a subtype of.’’
    { // Vector_container implements Container
        Vector v;
    public:
        Vector_container(std::initializer_list<double> s) : v(s) { } // Vector of s elements
        ~Vector_container() {} //Note that the member destructor (˜Vector()) is implicitly invoked by its class’s destructor(˜Vector_container()).
        double& operator[](int i) { return v[i]; }
        int size() const { return v.size(); }
    };

    void g()
    {
        Vector_container vc {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        use(vc);
    }
    //Since use() doesn’t know about Vector_containers but only knows the Container interface, it will
    //work just as well for a different implementation of a Container.

    class List_container : public Container { // List_container implements Container
        std::list<double> ld; // (standard-library) list of doubles (§4.4.2)
    public:
        List_container() { } // empty List
        List_container(std::initializer_list<double> il) : ld{il} { }
        ~List_container() {}
        double& operator[](int i);
        int size() const { return ld.size(); }
    };
    double& List_container::operator[](int i)
    {
        for (auto& x : ld) {
            if (i==0) return x;
            --i;
        }
        throw std::out_of_range("List container");
    }

    void h()
    {
        List_container lc = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        use(lc);
    }
    //The point is that use(Container&) has no idea if its argument is a Vector_container, a List_container,
    //or some other kind of container; it doesn’t need to know. It can use any kind of Container. It knows
    //only the interface defined by Container. Consequently, use(Container&) needn’t be recompiled if the
    //implementation of List_container changes or a brand-new class derived from Container is used.

    //endregion

    //region Class hierarchy

    struct Point{
        double x;
        double y;
        double z;

        Point(double x_, double y_, double z_) : x{x_}, y{y_}, z{z_} {}
    };

    class Shape {
    public:
        virtual Point center() const =0; // pure virtual
        virtual void move(Point to) =0;
        virtual void draw() const = 0; // draw on current "Canvas"
        virtual void rotate(int angle) = 0;
        virtual ~Shape() {} // destructor
// ...
    };

    void rotate_all(std::vector<Shape*>& v, int angle) // rotate v’s elements by angle degrees
    {
        for (auto p : v)
        p->rotate(angle);
    }

    class Circle : public Shape {
    public:
        Circle(Point p, int rr); // constructor
        Point center() const { return x; }
        void move(Point to) { x=to; }
        void draw() const;
        void rotate(int) {} // nice simple algorithm
    private:
        Point x; // center
        int r; // radius
    };

    class Smiley : public Circle { // use the circle as the base for a face
    public:
        Smiley(Point p, int r) : Circle{p,r}, mouth{nullptr} { }
        ~Smiley()
        {
            delete mouth;
            for (auto p : eyes) delete p;
        }
        void move(Point to);
        void draw() const;
        void rotate(int);
        void add_eye(Shape* s) { eyes.push_back(s); }
        void set_mouth(Shape* s);
        virtual void wink(int i); // wink eye number i
// ...
    private:
        std::vector<Shape*> eyes; //usually two eyes
        Shape* mouth;
    };

    void Smiley::draw() const
    {
//        Circle::draw();
        for (auto p : eyes)
            p->draw();
        mouth->draw();
    }

    enum class Kind { circle, triangle , smiley };
    Kind k;

    Shape* read_shape(std::istream& is) // read shape descriptions from input stream is
        {
        // ... read shape header from is and find its Kind k ...
        switch (k) {
            case Kind::circle:
            // read circle data {Point,int} into p and r
//            return new Circle{p,r};
                return NULL;
            case Kind::triangle:
            // read triangle data {Point,Point,Point} into p1, p2, and p3
//            return new Triangle{p1,p2,p3};
                return NULL;
            case Kind::smiley:
            // read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1 ,e2, and m
//            Smiley* ps = new Smiley{p,r};
//            ps->add_eye(e1);
//            ps->add_eye(e2);
//            ps->set_mouth(m);
//            return ps;
                return NULL;
            default:
                return NULL;
        }
        }

//    Experienced programmers will notice that I left open two obvious opportunities for mistakes:
//    • A user might fail to delete the pointer returned by read_shape().
//    • The owner of a container of Shape pointers might not delete the objects pointed to.
//    In that sense, functions returning a pointer to an object allocated on the free store are dangerous.
//    One solution to both problems is to return a standard-library unique_ptr (§5.2.1) rather than a
//    ‘‘naked pointer’’ and store unique_ptrs in the container:

    void user()
    {
        std::vector<Shape*> v;
        while (std::cin)
            v.push_back(read_shape(std::cin));
//        draw_all(v); //call draw() for each element
        rotate_all(v,45); //call rotate(45) for each element
        for (auto p : v) delete p; // remember to delete elements
    }
//    The user()
//    code can be compiled once and later used for new Shapes added to the program. Note that there are
//    no pointers to the shapes outside user(), so user() is responsible for deallocating them. This is done
//            with the delete operator and relies critically on Shape’s virtual destructor. Because that destructor is
//    virtual, delete invokes the destructor for the most derived class. This is crucial because a derived
//    class may have acquired all kinds of resources (such as file handles, locks, and output streams) that
//            need to be released. In this case, a Smiley deletes its eyes and mouth objects.


    std::unique_ptr<Shape> read_shapeUP(std::istream& is) // read shape descriptions from input stream is
    {
// read shape header from is and find its Kind k
        switch (k) {
            case Kind::circle:
// read circle data {Point,int} into p and r
//                return std::unique_ptr<Shape>{new Circle{p,r}}; // §5.2.1
// ...
                return NULL;
            default:
                return NULL;
        }
    }

    void userUP()
    {
        std::vector<std::unique_ptr<Shape>> v;
        while (std::cin)
//            v.push_back(read_shape(std::cin))
//        draw_all(v); // call draw() for each element
//        v.rotate_all(v,45); //call rotate(45) for each element
            break;
    } // all Shapes implicitly destroyed

    //endregion
}