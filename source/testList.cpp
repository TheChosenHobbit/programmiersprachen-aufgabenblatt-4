#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"

TEST_CASE ("List Empty Test","[List]"){
	List<int> l1;

	REQUIRE(l1.empty() == true);
	REQUIRE(l1.size() == 0);
}

TEST_CASE ("List Push Front und Back Test","[List]"){
	List<int> l1;
	l1.push_front(42);
	REQUIRE(42 == l1.front());
	REQUIRE(l1.empty() == false);
	REQUIRE(l1.size() == 1);

	l1.push_front(32);
	REQUIRE(32 == l1.front());
	REQUIRE(42 == l1.back());

	l1.push_back(55);
	REQUIRE(55 == l1.back());

	l1.pop_front();
	REQUIRE(42 == l1.front());

	l1.pop_back();
	REQUIRE(42 ==l1.back());
	l1.pop_back();
	REQUIRE(l1.empty() == true);
}

TEST_CASE ("List Clear","[List]"){
	List<int> l1;
	l1.push_front(1);
	l1.push_front(2);
	l1.push_front(3);
	l1.push_front(4);
	l1.clear();
	REQUIRE(l1.empty() == true);
}



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}