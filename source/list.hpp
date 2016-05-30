#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>

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
	reference operator*() const {}
	pointer operator->() const {}
	Self& operator++() {}
	Self operator++(int) {}
	bool operator==(const Self& x) const {}
	bool operator!=(const Self& x) const {}
	Self next() const
	{
		if(m_node)
			return ListIterator(m_node ->m_next);
		else
			return ListIterator(nullptr);
	}
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

private:
	std::size_t m_size = 0;
	ListNode<T>* m_first = nullptr;
	ListNode<T>* m_last = nullptr;
};

#endif // #define BUW_LIST_HPP