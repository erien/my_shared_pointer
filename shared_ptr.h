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
		// Empty shared_ptr constructor
		constexpr shared_ptr() : m_ptr(nullptr), m_cnt(nullptr)
		{
		}

		// Empty shared_ptr constructor
		constexpr shared_ptr(std::nullptr_t) : m_ptr(nullptr), m_cnt(nullptr)
		{
		}
		
		// Construct shared_ptr from raw pointer
		// Cannot figure out if other shared_ptr already points to ptr,
		// so each time RefCount is instantiated
		shared_ptr(T * ptr) : m_ptr(ptr), m_cnt(ptr ? new RefCount : nullptr)
		{
			m_cnt->increment();
			// if allocation failed - delete the resource?
		}

		// Construct shared_ptr from raw pointer with custom deleter
		template< class D>
		shared_ptr(T* ptr, D dtor)
		{

		}

		// Construct shared_ptr that owns same resource as other
		// wrong
		shared_ptr(const shared_ptr<T>& rhs) : m_ptr(rhs.get()), 
												m_cnt(new RefCount(rhs.use_count()+1))
		{
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
			return (m_cnt ? m_cnt->get() : 0);
		}

		// Desctructor
		~shared_ptr()
		{
			if (m_cnt && m_ptr && m_cnt->decrement() == 0)
			{
				delete m_cnt;
				delete m_ptr;
				std::cout << "Resource deleted." << std::endl;
			}
			std::cout << "custom::shared_ptr deleter called." << std::endl;
		}

	private:
		// Reference Counter
		class RefCount
		{
		public:
			RefCount() : m_count(0)
			{
			}

			RefCount(const long count) : m_count(count)
			{
			}

			void increment()
			{
				++m_count;
			}

			long decrement()
			{
				if (m_count)
				{
					return --m_count;
				}
			}

			const long get() const
			{
				return m_count;
			}

			~RefCount()
			{

			}
		private:
			long m_count;
		};

		//points on resource
		T* m_ptr;

		// reference counter
		RefCount* m_cnt;

	};

	// Comparison operator
	template<class T1, class T2>
	bool operator==(
		const custom::shared_ptr<T1>& lhs, 
		const custom::shared_ptr<T2>& rhs)
	{
		return (lhs.get() == rhs.get());
	}

