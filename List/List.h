#pragma once
#include <assert.h>

//__ListNode成员变量Node* next和Node* _prev和T _data
template <typename T>
struct __ListNode
{
	__ListNode<T>* _next;
	__ListNode<T>* _prev;
	T _data;

	__ListNode(const T& e)
		:_next(NULL)
		, _prev(NULL)
		, _data(e)
	{}
};

//__ListIterator的成员变量Node* _node
template <typename T, typename Ref, typename Ptr>
struct __ListIterator
{
	typedef __ListNode<T> Node;
	typedef __ListIterator<T, Ref, Ptr> Self;

	Node* _node; 

	__ListIterator(){} //无参构造函数
	__ListIterator(Node* node)
		:_node(node)
	{}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(_node->_data);
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
};


//List成员变量Node* _head
template <typename T>
class List
{
	typedef __ListNode<T> Node;

public:
	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T, const T&, const T*> ConstIterator;

	Node* BuyNode(const T& e)
	{
		return new Node(e);
	}

	List()
		:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(const T& e)
	{
		/*
		//求尾结点、开辟新结点
		Node* tail = _head->_prev;
		Node* tmp = BuyNode(e);
		//对tail tmp _head结点完成链接
		tail->_next = tmp;
		tmp->_prev = tail;
		tmp->_next = _head;
		_head->_prev = tmp;
		*/
		Insert(End(), e);
	}

	void PopBack()
	{
		/*
		assert(_head->_prev);
		Node* tail = _head->_prev;
		Node* prev = tail->_prev;
		Node* next = tail->_next;

		prev->_next = next;
		next->_prev = prev;

		delete tail;
		*/
		
		Erase(--End());
	}

	void PushFront(const T& e)
	{
		/*
		Node* tmp = BuyNode(e);
		Node* next = _head->_next;

		tmp->_next = next;
		tmp->_prev = _head;
		next->_prev = tmp;
		_head->_next = tmp;
		*/

		Insert(Begin(), e);
	}

	void PopFront()
	{
		/*
		assert(_head->_next);
		Node* del = _head->_next;
		Node* next = del->_next;

		_head->_next = next;
		next->_prev = _head;
		delete del;
		*/
		
		Erase(Begin());
	}

	Iterator Insert(Iterator pos, const T& e)
	{
		assert(pos._node);//断言插入的位置

		Node* cur = pos._node;
		Node* prev = cur->_prev;

		Node* tmp = BuyNode(e);

		//prev tmp cur
		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = cur;
		cur->_prev = tmp;

		//返回tmp的迭代器
		return tmp;
	}

	//插件区间
	template <typename InputIterator>
	void Insert(Iterator pos, InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			Insert(pos, *first);
			++first;
		}
	}

	Iterator Erase(Iterator pos)
	{
		//不能删除头结点
		assert(pos._node && pos._node != _head);
		//保存prev和next
		Node* next = pos._node->_next;
		Node* prev = pos._node->_prev;
		//链接prev和next
		prev->_next = next;
		next->_prev = prev;
		//删除pos结点
		delete pos._node;
		//返回next的迭代器
		return Iterator(next);
	}

	Iterator Begin()
	{
		//构造和拷贝构造会合为一步完成
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	ConstIterator Begin() const
	{
		return _head->_next;
	}

	ConstIterator End() const
	{
		return _head;
	}

protected:
	Node* _head;
};
