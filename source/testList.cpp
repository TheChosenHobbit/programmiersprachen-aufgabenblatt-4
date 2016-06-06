#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"
#include <iostream>

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

TEST_CASE("Empty range after default constructor","[Iterator]"){
	List<int> list;
	auto b = list.begin();
	auto e = list.end();
	REQUIRE(b == e);
}

TEST_CASE("Acces to first Element with begin","[Iterator]"){
	List<int> list;
	list.push_front(42);
	REQUIRE(42 == *list.begin());
}

TEST_CASE("Acces to last Element with end","[Iterator]"){
	List<int> list;
	list.push_front(42);
	list.push_back(55);
	//REQUIRE(55 == *list.end());
	list.push_back(33);
	//REQUIRE(33 == *list.end());

}

TEST_CASE("Check if List are the same","[Operator]"){
	List<int> l1;
	l1.push_front(42);
	l1.push_front(99);
	l1.push_front(33);
	List<int> l2;
	l2.push_front(42);
	l2.push_front(99);
	l2.push_front(33);
	REQUIRE(l1 == l2);
}

TEST_CASE("Check if List are NOT the same","[Operator]"){
	List<int> l1;
	l1.push_front(42);
	l1.push_front(99);
	l1.push_front(33);
	List<int> l2;
	l2.push_front(42);
	l2.push_front(2);
	l2.push_front(33);
	REQUIRE(l1 != l2);
}

TEST_CASE("Copy constructor","[Constructor]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	List<int> list2{list};
	REQUIRE(list == list2);
}

TEST_CASE("Insert of an element","[Insert]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	auto it = list.begin();
	++it;
	list.insert(it, 4);
	list.pop_front();
	REQUIRE(4 == *list.begin());

}

TEST_CASE("Reverse a list intern","[Reverse]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.reverse();
	List<int> list2;
	list2.push_front(4);
	list2.push_front(3);
	list2.push_front(2);
	list2.push_front(1);

	REQUIRE(list == list2);
}

TEST_CASE("Reverse a list extern","[Reverse]"){
	List<int> list;
	//list.push_front(1);
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);

	List<int> list2 = reverse(list);

/*
	for(auto iter = list.begin(); iter != list.end(); ++iter){
		std::cout << *iter << std::endl;
	}
	
	for(auto iter = list2.begin(); iter != list2.end(); ++iter){
		std::cout << *iter << std::endl;
	}
*/

	REQUIRE(1 == *list2.begin());
	list2.pop_front();
	REQUIRE(2 == *list2.begin());
	list2.pop_front();
	REQUIRE(3 == *list2.begin());
	list2.pop_front();
	REQUIRE(4 == *list2.begin());
}

TEST_CASE("move constructor","[constructor]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	List<int> list2 (std::move(list));
	REQUIRE (0 == list.size());
	REQUIRE (list.empty());
	REQUIRE (4 == list2.size());
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}