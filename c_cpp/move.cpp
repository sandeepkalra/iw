#include <iostream>
#include <cassert>
#include <string>
using namespace std;
// This class does not have "Copy Constructor, or Static Elements, and no Move Ctor, so Compiler
// must generate a "IMPLICIT " Move Ctor
// Lets Seee
class CMoveTest1 {
public:
	CMoveTest1() {};
	~CMoveTest1() {};
}; 


// this class has a COPY, so, MOVE is not constructed.
// but operator=() will be generated
class CMoveTest2 {
	static int i;
public:
	CMoveTest2(CMoveTest2& cpy) { i = cpy.i; };
	CMoveTest2() {}
	~CMoveTest2() {}
};
int CMoveTest2::i=0;


// This Test 3 is same as Test 2 but we force compiler to generate one default _ MOVE!
// But this would not generate operator=() for you.
class CMoveTest3 {
	static int i;
public:
	CMoveTest3(CMoveTest3& cpy) { i = cpy.i; };
	CMoveTest3(CMoveTest3&& mv)=default;// want explicit generation from compiler.
	CMoveTest3() {}
	~CMoveTest3() {}
};
int CMoveTest3::i=0;


// want compiler to generate move() and operator=
class CMoveTest4 {
	static int i;
public:
	CMoveTest4(CMoveTest4& cpy) { i = cpy.i; };
	CMoveTest4(CMoveTest4&& mv)=default;// want explicit generation from compiler.
	CMoveTest4& operator=(CMoveTest4&& mv)=default;// want explicit generation from compiler.
	CMoveTest4() {}
	~CMoveTest4() {}
};
int CMoveTest4::i=0;



int main()
{
	//  Test1 
	// CTor (class&&)
	static_assert(std::is_copy_constructible<CMoveTest1>::value==true, "assert failed for copy Ctor in CMoveTest1");
	static_assert(std::is_nothrow_move_constructible<CMoveTest1>::value==true, "assert failed for copy Ctor in CMoveTest1");
	// operator=()
	static_assert(std::is_copy_assignable<CMoveTest1>::value==true, "assert failed for copy Ctor in CMoveTest1");
	static_assert(std::is_nothrow_move_assignable<CMoveTest1>::value==true, "assert failed for copy Ctor in CMoveTest1");
	

	//  Test2 
	// class &&
	static_assert(std::is_copy_constructible<CMoveTest2>::value==true, "assert failed for copy Ctor in CMoveTest2");
/*-->>*/static_assert(std::is_nothrow_move_constructible<CMoveTest2>::value==false, "assert failed for copy Ctor in CMoveTest2");
	// operator ==
	static_assert(std::is_copy_assignable<CMoveTest2>::value==true, "assert failed for copy Ctor in CMoveTest2");
	static_assert(std::is_nothrow_move_assignable<CMoveTest2>::value==true, "assert failed for copy Ctor in CMoveTest2");

	//  Test3 
	// class &&
	static_assert(std::is_copy_constructible<CMoveTest3>::value==true, "assert failed for copy Ctor in CMoveTest3");
/*-->>*/static_assert(std::is_nothrow_move_constructible<CMoveTest3>::value==true, "compiler didn't generate what i asked it for !");
	// operator ==
/*-->>*/static_assert(std::is_copy_assignable<CMoveTest3>::value==false, "assert failed for copy Ctor in CMoveTest3");
/*-->>*/static_assert(std::is_nothrow_move_assignable<CMoveTest3>::value==false, "assert failed for copy Ctor in CMoveTest3");

	//  Test4 
	// class &&
	static_assert(std::is_copy_constructible<CMoveTest4>::value==true, "assert failed for copy Ctor in CMoveTest4");
/*-->>*/static_assert(std::is_nothrow_move_constructible<CMoveTest4>::value==true, "compiler didn't generate what i asked it for !");
	// operator ==
/*-->>*/static_assert(std::is_copy_assignable<CMoveTest4>::value==false, "assert failed for copy Ctor in CMoveTest4");
/*-->>*/static_assert(std::is_nothrow_move_assignable<CMoveTest4>::value==true, "assert failed for copy Ctor in CMoveTest4");
}
