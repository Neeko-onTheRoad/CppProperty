#ifndef __GETTER_ONLY_PROPERTY_HPP__
#define __GETTER_ONLY_PROPERTY_HPP__

#include <functional>

#define get(type) [&]() -> const type&

namespace nk {

	template<typename TValue>
	class GetterOnlyProperty {
		
	public:
		
		using GetterFunction = typename std::function<const TValue&()>;

		GetterOnlyProperty(GetterFunction getter)
			: _getter(getter) {}

		virtual ~GetterOnlyProperty() {}

		operator TValue() const {
			return _getter();
		}

	protected:

		GetterFunction _getter;

	};

}

#endif