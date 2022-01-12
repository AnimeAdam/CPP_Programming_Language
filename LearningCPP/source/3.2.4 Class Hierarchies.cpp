#include <iostream>
#include <vector>
#include <memory> //For the unique_ptr template
using namespace std; // make std members visible

// doubles stand for Point identifier ()
class Shape {
public:
	virtual double center() const = 0; // pure virtual
	virtual void move(double to) = 0;

	virtual void draw() const = 0; // draw on current "Canvas"
	virtual void rotate(int angle) = 0;

	virtual ~Shape() {} // destructor
						// ...
};
// Naturally, this interface is an abstract class: as far as representation is concerned, nothing (except
// the location of the pointer to the vtbl) is common for every Shape

class Circle : public Shape {
public:
	Circle(double p, int rr); // constructor

	double center() const { return x; }
	void move(double to) { x = to; }

	void draw() const;
	void rotate(int) {} // nice simple algorithm
private:
	double x; // center
	int r; // radius
};

class Smiley : public Circle { // use the circle as the base for a face
public:
	Smiley(double p, int r) : Circle{ p,r }, mouth{ nullptr } { }
	~Smiley() // Shape’s destructor is virtual and Smiley’s destructor overrides it.
// This destructor then implicitly invokes the destructors of its base classes and members
	{
		delete mouth;
		for (auto p : eyes) delete p;
	}

	void move(double to);

	void draw() const;
	void rotate(int);

	void add_eye(Shape* s) { eyes.push_back(s); }
// The push_back() member function adds its argument to the vector (here, eyes), increasing that
// vector’s size by one
	void set_mouth(Shape* s);
	virtual void wink(int i); // wink eye number i
							  // ...
private:
	vector<Shape*> eyes; //usually two eyes
// Smiley keeps its eyes in a standard-library vector and deletes them in its destructor
	Shape* mouth;
};

void Smiley::draw() const
{
	Circle::draw();
	for (auto p : eyes)
		p->draw();
	mouth->draw();
}

enum class Kind { circle, triangle, smiley };

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

// The definition of Shape, we can write general functions manipulating vectors of pointers to shapes
void rotate_all(vector<Shape*>& v, int angle) // rotate v’s elements by angle degrees
{
	for (auto p : v)
		p->rotate(angle);
}

// A user might fail to delete the pointer returned by read_shape().
/*Shape* read_shape(istream& is) // read shape descriptions from input stream is
{
// ... read shape header from is and find its Kind k ...
switch (k)
{
case Kind::circle:
// read circle data {Point,int} into p and r
return new Circle{ p,r };
case Kind::triangle:
// read triangle data {Point,Point,Point} into p1, p2, and p3
return new Triangle{ p1,p2,p3 };
case Kind::smiley:
// read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1 ,e2, and m
Smiley* ps = new Smiley{ p,r };
ps->add_eye(e1);
ps->add_eye(e2);
ps->set_mouth(m);
return ps;
}
}*/


/*void user()
{
	std::vector<Shape*> v;
	while (cin)
		v.push_back(read_shape(cin));
	draw_all(v); //call draw() for each element
	rotate_all(v, 45); //call rotate(45) for each element
	for (auto p : v) delete p; // remember to delete elements
	// The owner of a container of Shape pointers might not delete the objects pointed to.
}*/
// it vividly illustrates that user() has absolutely no idea of which kinds of shapes it manipulates.
// The user() code can be compiled once and later used for new Shapes added to the program.
// There are no pointers to the shapes outside user(), so user() is responsible for deallocating them.
// This is done with the delete operator and relies critically on Shape’s virtual destructor.
// Because that destructor is virtual, delete invokes the destructor for the most derived class.

// This is crucial because a derived class may have acquired all kinds of resources
// (such as file handles, locks, and output streams) that need to be released.
// In this case, a Smiley deletes its eyes and mouth objects.




//The following is change the functions to return a standard-library unique_ptr (§5.2.1) rather than a
//‘‘naked pointer’’ and store unique_ptrs in the container

unique_ptr<Shape> read_shape(istream& is) // read shape descriptions from input stream is
{
	// read shape header from is and find its Kind k
	switch (k)
	{
	case Kind::circle:
		// read circle data {Point,int} into p and r
		return unique_ptr<Shape>{new Circle{ p,r }}; // §5.2.1
													 // ...
	}
}

void user()
{
	vector<unique_ptr<Shape>> v;
	while (cin)
	v.push_back(read_shape(cin));		
	draw_all(v); // call draw() for each element
	rotate_all(v, 45); //call rotate(45) for each element
} // all Shapes implicitly destroyed

// Now the object is owned by the unique_ptr which will delete the object when it is no longer needed,
// that is, when its unique_ptr goes out of scope.

// For the unique_ptr version of user() to work, we need versions of draw_all() and rotate_all() that
// accept vector<unique_ptr<Shape>>s.