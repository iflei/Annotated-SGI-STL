#include <iostream>
#include <assert.h>
using namespace std;

typedef void(*Handler)();

//一级空间配置器
template <int inst>
class __MallocAllocTemplate
{
private:
	static Handler __MallocAlloc_oom_Handler; //静态成员需要在类外初始化

	static void* oom_Malloc(size_t n)
	{
		Handler my_malloc_handler;
		void* result;

		while (1)
		{
			my_malloc_handler = __MallocAlloc_oom_Handler;
			if (0 == my_malloc_handler)
			{
				cerr << "out of memory" << endl;
				exit(1);
			}

			my_malloc_handler();
			result = malloc(n);
			if (result)
				return result;
		}
	}

	static void* oom_Realloc(void* p, size_t n)
	{
		Handler my_malloc_handler;
		void* result;

		while (1)
		{
			my_malloc_handler = __MallocAlloc_oom_Handler;
			if (0 == my_malloc_handler)
			{
				cerr << "out of memory" << endl;
				exit(1);
			}

			my_malloc_handler();
			result = realloc(p, n);
			if (result)
				return result;
		}
	}

public:
	static void* Allocate(size_t n)
	{
		void* result = malloc(n);
		if (0 == result)
			result = oom_Malloc(n);
		return result;
	}

	//二级空间配置器调用的时候会传n，这里用不到
	static void Deallocate(void* p, size_t /* n */)
	{
		free(p);
	}

	static void* Reallocate(void* p, size_t /* old_sz */, size_t new_sz)
	{
		void* result = realloc(p, new_sz);
		if (0 == result)
			result = oom_Realloc(p, new_sz);
		return result;
	}

	static Handler SetMallocHandler(Handler f)
	{
		Handler old = __MallocAlloc_oom_Handler;
		__malloc_alloc_oom_handler = f;
		return(old);
	}
};

//静态成员初始化
template <int inst> 
Handler __MallocAllocTemplate<inst>::__MallocAlloc_oom_Handler = 0;

typedef __MallocAllocTemplate<0> MallocAlloc; //一级空间配置器别名MallocAlloc