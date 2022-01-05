#ifndef ACBUFFER_HPP
#define ACBUFFER_HPP

#include <atomic>
#include <type_traits>
#include <mutex>
#include <memory>
#include <typeindex>
#include <variant>


/**
 * \brief create a interface of reader for the storage \p T
 *
 * The container resolution is taken from here https://devblogs.microsoft.com/oldnewthing/20190619-00/?p=102599
 * \todo implement for scalar
 */
template<typename C,
    typename T = std::decay_t<decltype(*begin(std::declval<C>()))>>
class acbuffer
{
	public:
	acbuffer(std::unique_ptr<C> arg, lock_strategy lock_type) : c(arg) {}

	protected:
	using lock_strategy = std::variant<std::defer_lock_t, std:: try_to_lock_t, std::adopt_lock_t>;
	std::unique_ptr<C> c;
	std::atomic<unsigned>pos;
};

#endif
