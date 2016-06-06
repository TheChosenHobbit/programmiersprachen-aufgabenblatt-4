#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>
#include <iostream>
//List.hpp

template <typename T>
struct List;

template <typename T>
struct ListNode
{
	ListNode() : m_value(), m_prev(nullptr), m_next(nullptr){}
	ListNode(T const& v, ListNode* prev, ListNode* next) : m_value(v), m_prev(prev), m_next(next) {}
	T m_value;
	ListNode* m_prev;
	ListNode* m_next;
};

template <typename T>
struct ListConstIterator
{
	friend class List<T>;
public:
	//TODO
private:
	ListNode<T>* m_node = nullptr;
};

//Aufgabe 4
template<typename T>
struct ListIterator
{
	typedef ListIterator<T> Self;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class List<T>;

	ListIterator() : m_node(nullptr) {}
	ListIterator(ListNode<T>* n) : m_node(n) {}
	reference operator*() const {
		return m_node->m_value;
	}
	pointer operator->() const {
		return *m_node;
	}
	Self& operator++() {
		*this = next();
		return *this;
	}
	Self operator++(int count) {
		while (count != 0)
		{
			*this = next();
			--count;
		}
		return *this;
	}
	bool operator==(const Self& x) const {
		return m_node == x.m_node;
	}
	bool operator!=(const Self& x) const {
		return m_node != x.m_node;
	}
	Self next() const
	{
		if(m_node)
			return ListIterator(m_node ->m_next);
		else
			return ListIterator(nullptr);
	}
	//für insert
	ListNode<T>* getNode() const { return m_node; };

private:
// The  Node  the  iterator  is  pointing  to
	ListNode<T>* m_node = nullptr;
};

template <typename T>
class List
{ 
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef ListIterator<T> iterator;
	typedef ListConstIterator<T> const_iterator;

	friend class ListIterator<T>;
	friend class ListConstIterator<T>;

//Aufgabe 1
	List() : m_size(0), m_first(nullptr), m_last(nullptr){}

	bool empty() const 
	{
		if(m_first == nullptr && m_last == nullptr)
		{
			return true;
		} else {
			return false;
		}
	}

	std::size_t size() const
	{
		return m_size;
	}

//Aufgabe 2
	void push_front(T const& value) 
	{
		if(empty())
		{
			m_first = new ListNode<T> (value, nullptr, nullptr);
			m_last = m_first;
		} else {
			m_first -> m_prev = new ListNode<T> (value, nullptr, m_first);
			m_first = m_first->m_prev;
		}
		++m_size;
	}

	void push_back(T const& value)
	{
		if (empty())
		{
			m_last = new ListNode<T> (value, nullptr, nullptr);
			m_first = m_last;
		} else {
			m_last -> m_next = new ListNode<T> (value, m_last, nullptr);
			m_last = m_last -> m_next;
		}
		++m_size;
	}

	void pop_front()
	{
		if(size()==1)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
		} else if(!empty()) {
			m_first = m_first -> m_next;
			delete m_first->m_prev;
			m_first -> m_prev =  nullptr;
		}
		--m_size;
	}

	void pop_back()
	{
		if(size()==1)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
		} else if(!empty()) {
			m_last = m_last -> m_prev;
			delete m_last -> m_next;
			m_last -> m_next = nullptr;
		}
		--m_size;
	}


	T& front () const{
		return m_first->m_value;
	}

	T& back () const{
		return m_last->m_value;
	}

//Aufgabe 3
	void clear()
	{
		while(!empty())
		{
			pop_front();
		}
	}

	~List(){
		clear();
	}

//Aufgabe 5
	iterator begin() const{
		return iterator(m_first);
	}

	iterator end() const{
		return iterator(m_last);
	}

//Aufgabe 7
	List(List const& copy) : m_size(0), m_first(nullptr), m_last(nullptr){
		for(ListIterator<T> ListIter = copy.begin(); ListIter != copy.end(); ++ListIter)
		{
			push_back(*ListIter);
		}
	}

//Aufgabe 8
	void insert(iterator const& iter, T const& value){
		//Neuen Node erstellt und Zeiger auf prev und "next"
		ListNode<T>* insertNode = new ListNode<T>(value, nullptr, nullptr);
		ListNode<T>* prevNode = iter.getNode()->m_prev;
		ListNode<T>* nextNode = iter.getNode();

		//Zeiger auf Nodes richtig zuweisen
		insertNode->m_prev = prevNode;
		prevNode->m_next = insertNode;
		insertNode->m_next = nextNode;
		nextNode->m_prev = insertNode;
	}

//Aufgabe 9
	void reverse(){
		if(empty())
			return;

		auto rememberNode = m_first;
		m_first = m_last;
		m_last = rememberNode;


		for (ListIterator<T> iter = begin(); iter != end(); ++iter)
		{
			auto node = iter.getNode();
			auto remember = node -> m_prev;
			node->m_prev  = node->m_next;
			node->m_next = remember;
		}
	}


//Aufgabe 12
	List<T> (List<T>&& rhs) : m_size(rhs.m_size), m_first(rhs.m_first), m_last(rhs.m_last) {
		rhs.m_size = 0;
		rhs.m_first = nullptr;
		rhs.m_last = nullptr;
	}

	List<T>& operator = (List<T>&& list){
		std::swap(m_size, list.m_size);
		std::swap(m_first, list.m_first);
		std::swap(m_last, list.m_last);

	return *this;
	}


private:
	std::size_t m_size = 0;
	ListNode<T>* m_first = nullptr;
	ListNode<T>* m_last = nullptr;
};

//Aufgabe 6
template<typename T>
bool operator==(List<T> const& xs, List<T> const& ys)
{
	ListIterator<T> yIter = ys.begin();
	bool check = true;
	for(ListIterator<T> xIter = xs.begin(); xIter != xs.end(); ++xIter)
	{
		if(*xIter != *yIter)
		{
			check = false;
			break;
		}
		++yIter;
	}
	return check;
}

template<typename T>
bool operator!=(List<T> const& xs, List<T> const& ys)
{
	ListIterator<T> yIter = ys.begin();
	bool check = false;
	for(ListIterator<T> xIter = xs.begin(); xIter != xs.end(); ++xIter)
	{
		if(*xIter == *yIter)
		{
			check = true;
		}
		++yIter;
	}
	return check;
}

//Aufgabe 9
template<typename T>
List<T> reverse(List<T> const& liste1){
	List<T> liste2;
	for(ListIterator<T> iter = liste1.begin(); iter != liste1.end(); ++iter)
	{
		liste2.push_front(*iter);
	}
	return liste2;
}

#endif // #define BUW_LIST_HPP