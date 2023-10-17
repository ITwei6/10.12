#pragma once




namespace tao
{
	template <class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~auto_ptr()
		{
			delete _ptr;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		auto_ptr(auto_ptr<T>& p)
			:_ptr(p._ptr)
		{
			//将资源转移后，被拷贝对象再置空
			p._ptr = nullptr;
			//如果不置空，就会释放两次
		}
	private:
		T* _ptr;
	};

	template <class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~unique_ptr()
		{
			delete _ptr;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		unique_ptr(unique_ptr<T>& p) = delete;//直接删除掉

		
	private:
		T* _ptr;
	};

	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr=nullptr)
			:_ptr(ptr)
			,_pcount(new int(1))
		{}

         //只有对象管理一个资源时，才会生成计数器。不然不会生成。
		//当拷贝时(没有资源的生成管理)就让其他对象的指针向生成的计数器。
		~shared_ptr()
		{
			//只有最后一个对象管理时才可以释放资源
			if (--(*_pcount) == 0)
			{
				cout << "delete" << _ptr << endl;
				delete _ptr;
				delete _pcount;
			}
			
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		shared_ptr(shared_ptr<T>& ps)
			:_ptr(ps._ptr)
			, _pcount(ps._pcount)
			//这个单纯指向没有再管理一个新的资源，所以不会生成计数器，只是指向原来生成的计数器。
		{
			++(*_pcount);
		}
		shared_ptr<T>& operator=(const shared_ptr<T>& ps)
		{
			if (_ptr == ps._ptr)return *this;
			//要注意被赋值对象管 6理的资源是否只有一个智能指针控制
			if (--(*_pcount) == 0)
			{
				delete _ptr;
				delete _pcount;
			}
			_ptr = ps._ptr;
			_pcount = ps._pcount;//正常转移指向即可
			//赋值对象的计数器++即可
			(*ps._pcount)++;
			return *this;
		}
		int use_count()
		{
			return *_pcount;
		}
		T* get()const 
		{
			return _ptr;
		}
	private:
		T* _ptr;
		int* _pcount;
	};

	template <class T>
	class weak_ptr
	{
	public:
		weak_ptr()
			:_ptr(nullptr)
		{}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get())
		{}
		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();
			return *this;
		}

	private:
		T* _ptr;
	};
};
