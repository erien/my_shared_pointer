#include <cstddef>
#include <algorithm>

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
		typedef T element_type;

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
		template<class Y>
		explicit shared_ptr(Y * ptr) : m_ptr(ptr), m_refCount(ptr ? new RefCount<Y> : nullptr)
		{
			m_refCount->increment();
			// if allocation failed - delete the resource?
		}

		// Construct shared_ptr from raw pointer with custom deleter
		template< class Deleter>
		shared_ptr(T* ptr, Deleter d)
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

		// Dereference operator
		T& operator*() const noexcept
		{
			return *m_ptr;
		}

		// Dereference operator
		T& operator->() const noexcept
		{
			return *m_ptr;
		}

		// Assignment operator - assign shared ownership of resource owned by rhs
		shared_ptr<T>& operator=(const shared_ptr<T>& rhs) noexcept
		{
			shared_ptr<T>(rhs).swap(*this);
			return (*this);
		}

		// Assignment operator - assign shared ownership of resource owned by rhs
		template<class Y>
		shared_ptr<T>& operator=(const shared_ptr<Y>& rhs) noexcept
		{
			shared_ptr<T>(rhs).swap(*this);
			return (*this);
		}

		// Assignment operator - move-assign shared resource from rhs
		shared_ptr<T>& operator=(shared_ptr<T>&& rhs) noexcept
		{
			shared_ptr<T>(std::move(rhs)).swap(*this);
			return (*this);
		}

		// Assignment operator - move-assign shared resource from rhs
		template<class Y>
		shared_ptr<T>& operator=(shared_ptr<Y>&& rhs) noexcept
		{
			shared_ptr<T>(std::move(rhs)).swap(*this);
			return (*this);
		}

		// Assignment operator 
		template<class Y>
		shared_ptr<T>& operator=(std::auto_ptr<Y>&& rhs)
		{
			shared_ptr<T>(std::move(rhs)).swap(*this);
			return (*this);
		}

		// Assignment operator 
		template<class Y, class Deleter>
		shared_ptr<T>& operator=(std::unique_ptr<Y, Deleter>&& rhs)
		{
			shared_ptr<T>(std::move(rhs)).swap(*this);
			return (*this);
		}

		// checks if there is associated managed object 
		explicit operator bool() const noexcept
		{
			return (get() != nullptr);
		}

		// reset - replace the managed object with nullptr
		void reset()
		{
			shared_ptr<T>().swap(*this);
		}

		// reset - replace the managed object with an object pointed to by ptr
		template<class Y>
		void reset(Y* ptr)
		{
			shared_ptr<T>(ptr).swap(*this);
		}

		// reset - uses specified deleter d as deleter
		template<class Y, class Deleter>
		void reset(Y* ptr, Deleter d)
		{
			// TODO
		}

		// reset - additionally uses a copy of alloc for allocation of internal use
		template<class Y, class Deleter, class Alloc>
		void reset(Y* ptr, Deleter d, Alloc alloc)
		{
			// TODO
		}

		// swap - exchange the contents of *this and rhs
		void swap(shared_ptr<T>& rhs)
		{
			std::swap(m_refCount, rhs.m_refCount);
			std::swap(m_ptr, rhs.m_ptr);
		}

		// Get the pointer
		T* get() const noexcept
		{
			return m_ptr;
		}

		// Usage counter
		long use_count() const
		{
			return (m_refCount ? m_refCount->useCount() : 0);
		}

		// Unique - is managed object owned only by the current shared_ptr instance
		bool unique() const
		{
			return (use_count() == 1);
		}

		// provides owner-based ordering of shared pointers
		template <class Y>
		bool owner_before(const shared_ptr<Y>& rhs) const
		{
			return (m_refCount < rhs.m_refCount);
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

	// Specialization of std::swap for custom::shared_ptr
	template<class T>
	void swap(custom::shared_ptr<T>& lhs, custom::shared_ptr<T>& rhs) noexcept
	{
		lhs.swap(rhs);
	}

