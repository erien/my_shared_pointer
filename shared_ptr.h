#include <cstddef>

namespace custom
{
	template <class T>
	class shared_ptr;
}

	template <class T>
	class custom::shared_ptr
	{
	public:
		typedef T element_type;

		// construct empty shared_ptr
		shared_ptr();
		
		template<class Other>
		explicit shared_ptr(Other * ptr);

		template<class Other, class D>
		shared_ptr(Other * ptr, D dtor);

		~shared_ptr();

	private:
		struct rcount
		{
			unsigned count;

			rcount() : count(1)
			{
			};
		};

		//points on resource
		T *ptr;

		//points on reference counter
		rcount *cnt;
	};

	template<class T>
	template<class Other>
	inline custom::shared_ptr<T>::shared_ptr()
	{
	}

	template<class T>
	template<class Other>
	inline custom::shared_ptr<T>::shared_ptr(Other * ptr)
	{
	}

	template<class T>
	template<class Other, class D>
	inline custom::shared_ptr<T>::shared_ptr(Other * ptr, D dtor)
	{
	}

