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

	//���ﲻ����const���÷���Copy���ó�����
	Vector(Vector<T>& v)
		:_start(new T[v.Size()])
	{
		//������sizeһ����
		_finish = _start + v.Size();
		_endOfStorage = _start + v.Size();
		//��v��Ԫ�ؿ�����_start��ʼ�Ŀռ�
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
	//Ĭ����ǰ��
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

		//�ȼ������
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
	//����ɾ��λ����һ��λ�ã���ֹ������ʧЧ
	Iterator Erase(Iterator pos)
	{
		assert(_start && pos && pos >= _start && pos < _finish);
		//�ж��ǲ���βɾ����ֹvector��ʱ����������Ԫ�ص���һ��λ�û�Խ�����
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
		//����pos�Ѿ�ָ����һ��Ԫ����
		return pos;
	}

	/*
	Vector<T>& operator=(const Vector<T>& v)
	{
	if (this != &v)
	{
	//�ȿ���v.Size()��Ŀռ�
	T* tmp = new T[v.Size()];
	//������ԭ���Ŀռ�
	Destory();
	//_start ָ���¿��Ŀռ�
	_start = tmp;
	//����_finish��_endOfStorage
	_finish = _start + v.Size();
	_endOfStorage = _start + v.Size();
	//��������
	Copy(_start, v._start, v._finish);
	}

	return *this;
	}
	*/

	//��ֵ����������ִ�д��
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
		//����	������ȡ
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
			//����������
			capacity = capacity * 2 + 3;
			//���ٿռ�
			T* tmp = new T[capacity];
			//�����������Ԫ��
			if (_start)
			{
				//���������
				for (size_t i = 0; i < size; ++i)
					tmp[i] = _start[i];
				//���ͷ�ԭ�ռ�
				delete[] _start;
			}
			//����ָ��
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
	Iterator _start;//ָ��ʼ
	Iterator _finish;//ָ�����һ��Ԫ�غ���
	Iterator _endOfStorage;//ָ���ܿռ�ĺ���
};