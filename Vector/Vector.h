#pragma once
#include <assert.h>

template <typename T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;

	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{}

	~Vector()
	{
		Destory();
	}

	//这里不能用const引用否则Copy调用出问题
	Vector(Vector<T>& v)
		:_start(new T[v.Size()])
	{
		//容量和size一样大
		_finish = _start + v.Size();
		_endOfStorage = _start + v.Size();
		//把v的元素拷贝到_start开始的空间
		Copy(_start, v._start, v._finish);
	}

	void PushBack(const T& e)
	{
		CheckStorage();
		*_finish = e;
		++_finish;
	}

	void PopBack()
	{
		assert(Size());
		--_finish;
	}
	//默认是前插
	Iterator Insert(Iterator pos, const T& x)
	{
		assert(pos && pos >= _start && pos < _finish);
		size_t index = pos - Begin();
		if (index < Size())
		{
			CheckStorage();
			memmove(_start + index + 1, _start + index, (Size() - index)*sizeof(T));
			_start[index] = x;
		}

		//先检查容量
		/*CheckStorage();
		Iterator last = _finish;
		while (last >= pos)
		{
			*last = *(last - 1);
			--last;
		}
		*pos = x;*/

		++_finish;
		return pos;
	}
	//返回删除位置下一个位置，防止迭代器失效
	Iterator Erase(Iterator pos)
	{
		assert(_start && pos && pos >= _start && pos < _finish);
		//判断是不是尾删，防止vector满时，访问最后的元素的下一个位置会越界访问
		if (pos == _finish - 1)
			PopBack();
		else
		{
			Iterator cur = pos;
			while (cur < _finish - 1)
			{
				*cur = *(cur + 1);
				++cur;
			}
			--_finish;
		}
		//这里pos已经指向下一个元素了
		return pos;
	}

	/*
	Vector<T>& operator=(const Vector<T>& v)
	{
	if (this != &v)
	{
	//先开出v.Size()大的空间
	T* tmp = new T[v.Size()];
	//再销毁原来的空间
	Destory();
	//_start 指向新开的空间
	_start = tmp;
	//更新_finish和_endOfStorage
	_finish = _start + v.Size();
	_endOfStorage = _start + v.Size();
	//拷贝数据
	Copy(_start, v._start, v._finish);
	}

	return *this;
	}
	*/

	//赋值运算符重载现代写法
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (this != &v)
		{
			Vector<T> tmp(v);
			this->Swap(tmp);
		}

		return *this;
	}

	T& operator[](size_t index)
	{
		assert(index < Size());
		return _start[index];
	}

	const T& operator[](size_t index) const
	{
		assert(index < Size());
		return _start[index];
	}

	void Copy(Iterator pos, Iterator first, Iterator last)
	{
		//可以	类型萃取
		//memcpy(pos, first, sizeof(T)*(last-first));
		while (first != last)
		{
			*pos++ = *first++;
		}
	}

	void CheckStorage()
	{
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t capacity = Capacity();
			//计算新容量
			capacity = capacity * 2 + 3;
			//开辟空间
			T* tmp = new T[capacity];
			//如果本来就有元素
			if (_start)
			{
				//先深拷贝数据
				for (size_t i = 0; i < size; ++i)
					tmp[i] = _start[i];
				//再释放原空间
				delete[] _start;
			}
			//重置指针
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + capacity;
		}
	}

	void Destory()
	{
		if (_start)
		{
			delete[] _start;
		}

		_start = NULL;
		_finish = NULL;
		_endOfStorage = NULL;
	}

	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	ConstIterator Begin() const
	{
		return _start;
	}

	ConstIterator End() const
	{
		return _finish;
	}

	T& Front()
	{
		return *_start;
	}

	T& Back()
	{
		return *(_finish - 1);
	}

	size_t Size()
	{
		return _finish - _start;
	}

	size_t Capacity()
	{
		return _endOfStorage - _start;
	}

	void Empty()
	{
		return Size() == 0;
	}

protected:
	Iterator _start;//指向开始
	Iterator _finish;//指向最后一个元素后面
	Iterator _endOfStorage;//指向总空间的后面
};