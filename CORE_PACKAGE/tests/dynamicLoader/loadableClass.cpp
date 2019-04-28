#include <iostream>
#include <loadableClass.hpp>

extern "C" LoadableClass *createObject () {
	return new LoadableClass ();
}


LoadableClass::LoadableClass () {
	i	= 0;
}

LoadableClass::~LoadableClass () {
	// Do nothing
}

void LoadableClass::doSomething () {
	std::cout << "(" << i << ")  Doing nothing..\n";
}

int LoadableClass::doSum (int a, int b) {
	return a+b;
}