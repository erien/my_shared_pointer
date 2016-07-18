#include <cstddef>

// Custom namespace for this implementation of shared_ptr
namespace custom
{
	template <class T>
	class shared_ptr;
}

	template <class T>
	class custom::shared_ptr
	{
	public:
		typedef shared_ptr<T> MyT;

		// Empty shared_ptr constructor
		constexpr shared_ptr() : m_ptr(nullptr)
		{
		}

		constexpr shared_ptr(std::nullptr_t) : m_ptr(nullptr)
		{
		}
		
		// Construct shared_ptr from raw pointer
		template<class Y>
		explicit shared_ptr(Y * ptr)
		{
			m_ptr = ptr;
			m_cnt = new RefCount;
		}

		template<class Y, class D>
		shared_ptr(Y* ptr, D dtor);

		// Get the pointer
		T* get() const noexcept
		{
			return m_ptr;
		}

		// Dereference operator
		T& operator*() const noexcept
		{
			return (*this->get());
		}

		// Desctructor
		~shared_ptr()
		{
		}

	private:
		struct RefCount
		{
			unsigned count;

			RefCount() : count(1)
			{
			};
		};

		//points on resource
		T* m_ptr;

		// reference counter
		RefCount* m_cnt;

	};

	template<class T>
	template<class Y, class D>
	inline custom::shared_ptr<T>::shared_ptr(Y * ptr, D dtor)
	{
	}

