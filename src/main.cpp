#include "util.h"

using namespace std;

class Base {
public:
	Base(void)               { puts("Base::Base"); }
	~Base(void)              { puts("Base::~Base"); }
	void test(void)          { puts("Hello from Base::test"); }
	virtual void vtest(void) { puts("Hello from virtual method Base::vtest"); }
};

class Child : public Base {
public:
	Child(void)              { puts("Child::Child"); }
	~Child(void)             { puts("Child::~Child"); }
	virtual void vtest(void) { puts("Hello from virtual method Child::vtest"); }
};

/* Statically allocated object */
Child static_child;

/* Program Entry */
int main(int argc, char const *argv[])
{
	puts("*** Creating instance of Base");
	Base ibase;
	puts("*** Calling method test() on instance of Base()");
	ibase.test();

	puts("*** Creating instance of Child");
	Child ichild;
	puts("*** Calling method test() on instance of Child()");
	ichild.test();

	Base *s;
	s = &ichild;
	puts("*** Calling virtual method vtest() on instance of Child via Base pointer");
	s->vtest();

	puts("*** Calling test() on statically allocated child");
	static_child.test();

	return 0;
}
