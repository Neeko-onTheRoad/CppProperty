#ifndef __PROPERTY_SETTER_HPP__
#define __PROPERTY_SETTER_HPP__

#include <functional>

#define set(type) [&](const type& value)

namespace nk {

	template<typename TValue>
	class PropertySetter {

	public:

		using SetterFunction = typename std::function<void(const TValue&)>;

	protected:
		
		SetterFunction _setter;
		
		PropertySetter(SetterFunction setter)
			: _setter(setter) {}

	public:

		PropertySetter& operator=(const TValue& newValue) {
			_setter(newValue);
			return *this;
		}

		PropertySetter& operator=(TValue&& other) {
			_setter(std::move(other));
			return *this;
		}

	};

}

#endif