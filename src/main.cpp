#include "util.h"

using namespace std;

class Base {
public:
	Base(void)               { puts("Base::Base\n"); }
	~Base(void)              { puts("Base::~Base\n"); }
	void test(void)          { puts("Hello from Base::test\n"); }
	virtual void vtest(void) { puts("Hello from virtual method Base::vtest\n"); }
};

class Child : public Base {
public:
	Child(void)              { puts("Child::Child\n"); }
	~Child(void)             { puts("Child::~Child\n"); }
	virtual void vtest(void) { puts("Hello from virtual method Child::vtest\n"); }
};

/* Statically allocated object */
Child static_child;

/* Program Entry */
int main(int argc, char const *argv[])
{
	puts("*** Creating instance of Base\n");
	Base ibase;
	puts("*** Calling method test() on instance of Base()\n");
	ibase.test();

	puts("*** Creating instance of Child\n");
	Child ichild;
	puts("*** Calling method test() on instance of Child()\n");
	ichild.test();

	Base *s;
	s = &ichild;
	puts("*** Calling virtual method vtest() on instance of Child via Base pointer\n");
	s->vtest();

	puts("*** Calling test() on statically allocated child\n");
	static_child.test();

	return 0;
}
