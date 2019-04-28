#define CATCH_CONFIG_MAIN

#include <thirdParty/catch.hpp>
#include <core/dynamicLoader.hpp>
#include <loadableClass.hpp>
#include <iostream>

using namespace std;
using namespace microservicespp;
using namespace dynamicLoader;


TEST_CASE( "Loading an object" ) {
	LoadableClass *loaded	= nullptr;
	{
		DynamicLoader<LoadableClass> loader ("loadableClass.so");
		loaded	= loader.makeObject ();
	}

	loaded->doSomething ();

	REQUIRE (loaded != nullptr);

	REQUIRE (loaded->doSum (5, 5) == 10);

	delete (loaded);
}