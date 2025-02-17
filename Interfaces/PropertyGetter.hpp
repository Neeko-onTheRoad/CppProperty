#ifndef __PROPERTY_GETTER_HPP__
#define __PROPERTY_GETTER_HPP__

#include <functional>

#define get(type) [&]() -> type&

namespace nk {

	template<typename TValue>
	class PropertyGetter {

	public:

		using GetterFunction = typename std::function<TValue&()>;

	protected:

		GetterFunction _getter;

		PropertyGetter(GetterFunction getter)
			: _getter(getter) {}

	public:
		
		operator TValue&() {
			return _getter();
		}
		
	};

}

#endif