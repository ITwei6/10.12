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
			//����Դת�ƺ󣬱������������ÿ�
			p._ptr = nullptr;
			//������ÿգ��ͻ��ͷ�����
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
		unique_ptr(unique_ptr<T>& p) = delete;//ֱ��ɾ����

		
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

         //ֻ�ж������һ����Դʱ���Ż����ɼ���������Ȼ�������ɡ�
		//������ʱ(û����Դ�����ɹ���)�������������ָ�������ɵļ�������
		~shared_ptr()
		{
			//ֻ�����һ���������ʱ�ſ����ͷ���Դ
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
			//�������ָ��û���ٹ���һ���µ���Դ�����Բ������ɼ�������ֻ��ָ��ԭ�����ɵļ�������
		{
			++(*_pcount);
		}
		shared_ptr<T>& operator=(const shared_ptr<T>& ps)
		{
			if (_ptr == ps._ptr)return *this;
			//Ҫע�ⱻ��ֵ����� 6�����Դ�Ƿ�ֻ��һ������ָ�����
			if (--(*_pcount) == 0)
			{
				delete _ptr;
				delete _pcount;
			}
			_ptr = ps._ptr;
			_pcount = ps._pcount;//����ת��ָ�򼴿�
			//��ֵ����ļ�����++����
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
