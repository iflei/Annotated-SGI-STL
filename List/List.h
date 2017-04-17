#pragma once
#include <assert.h>

//__ListNode��Ա����Node* next��Node* _prev��T _data
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

//__ListIterator�ĳ�Ա����Node* _node
template <typename T, typename Ref, typename Ptr>
struct __ListIterator
{
	typedef __ListNode<T> Node;
	typedef __ListIterator<T, Ref, Ptr> Self;

	Node* _node; 

	__ListIterator(){} //�޲ι��캯��
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


//List��Ա����Node* _head
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
		//��β��㡢�����½��
		Node* tail = _head->_prev;
		Node* tmp = BuyNode(e);
		//��tail tmp _head����������
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
		assert(pos._node);//���Բ����λ��

		Node* cur = pos._node;
		Node* prev = cur->_prev;

		Node* tmp = BuyNode(e);

		//prev tmp cur
		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = cur;
		cur->_prev = tmp;

		//����tmp�ĵ�����
		return tmp;
	}

	//�������
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
		//����ɾ��ͷ���
		assert(pos._node && pos._node != _head);
		//����prev��next
		Node* next = pos._node->_next;
		Node* prev = pos._node->_prev;
		//����prev��next
		prev->_next = next;
		next->_prev = prev;
		//ɾ��pos���
		delete pos._node;
		//����next�ĵ�����
		return Iterator(next);
	}

	Iterator Begin()
	{
		//����Ϳ���������Ϊһ�����
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
