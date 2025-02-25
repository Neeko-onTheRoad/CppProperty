#ifndef __GETTER_ONLY_PROPERTY_HPP__
#define __GETTER_ONLY_PROPERTY_HPP__

#include <functional>

#define get(type) [&]() -> const type&

namespace nk {

	template<typename TValue>
	class GetterOnlyProperty {
		
	public:
		
		using GetterFunction = typename std::function<const TValue&()>;

	protected:

		GetterFunction _getter;

		GetterOnlyProperty(GetterFunction getter)
			: _getter(getter) {}

	public:
		
		operator const TValue&() {
			return _getter();
		}

	};

}

#endif