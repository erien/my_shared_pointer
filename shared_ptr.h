#include <cstddef>

// Custom namespace for this implementation of shared_ptr
namespace custom
{
	template <class T>
	class shared_ptr;
}

	// Template class for custom::shared_ptr
	template <class T>
	class custom::shared_ptr
	{
	public:
		// Empty shared_ptr constructor
		constexpr shared_ptr() : m_ptr(nullptr), m_refCount(nullptr)
		{
		}

		// Empty shared_ptr constructor
		constexpr shared_ptr(std::nullptr_t) : m_ptr(nullptr), m_refCount(nullptr)
		{
		}
		
		// Construct shared_ptr from raw pointer
		// Cannot figure out if other shared_ptr already points to ptr,
		// so each time RefCount is instantiated
		shared_ptr(T * ptr) : m_ptr(ptr), m_refCount(ptr ? new RefCount<T> : nullptr)
		{
			m_refCount->increment();
			// if allocation failed - delete the resource?
		}

		// Construct shared_ptr from raw pointer with custom deleter
		template< class D>
		shared_ptr(T* ptr, D dtor)
		{

		}

		// Construct shared_ptr that owns same resource as other
		shared_ptr(const shared_ptr<T>& rhs) : m_ptr(rhs.get())
		{
			if (rhs.get())
			{
				m_refCount = rhs.m_refCount;
				m_refCount->increment();
			}
		}

		// Get the pointer
		T* get() const noexcept
		{
			return m_ptr;
		}

		// Dereference operator
		T& operator*() const noexcept
		{
			return *m_ptr;
		}

		// Usage counter
		long use_count() const
		{
			return (m_refCount ? m_refCount->useCount() : 0);
		}

		// Desctructor
		~shared_ptr()
		{
			if (m_ptr && m_refCount && m_refCount->decrement() == 0)
			{
				delete m_ptr;
				delete m_refCount;	
			}
		}

	private:
		// Reference Counter class
		template<class T>
		class RefCount
		{
		public:
			RefCount() : m_uses(0)
			{
			}

			RefCount(const long count) : m_uses(count)
			{
			}

			void increment()
			{
				++m_uses;
			}

			long decrement()
			{
				if (m_uses)
				{
					return --m_uses;
				}
				return m_uses;
			}

			const long useCount() const
			{
				return m_uses;
			}

			~RefCount()
			{
			}

		private:
			// Use counter of managed resource
			long m_uses;
		};


		//points on resource
		T* m_ptr;

		// reference counter
		RefCount<T>* m_refCount;
	};

	// Comparison operator
	template<class T1, class T2>
	bool operator==(
		const custom::shared_ptr<T1>& lhs, 
		const custom::shared_ptr<T2>& rhs)
	{
		return (lhs.get() == rhs.get());
	}

