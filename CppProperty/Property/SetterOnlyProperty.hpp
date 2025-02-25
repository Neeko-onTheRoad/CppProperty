#ifndef __SETTER_ONLY_PROPERTY_HPP__
#define __SETTER_ONLY_PROPERTY_HPP__

#include <functional>

namespace nk {

	template<typename TValue>
	class SetterOnlyProperty {

	public:
		
		using SetterFunction = typename std::function<void(const TValue&)>;

	public:

		SetterFunction _setter;

		SetterOnlyProperty(SetterFunction setter)
			: _setter(setter) {}

	public:

		SetterOnlyProperty& operator=(const TValue& newValue) {
			_setter(newValue);
			return *this;
		}

		SetterOnlyProperty& operator=(TValue&& other) {
			_setter(std::move(other));
			return *this;
		}

	};

}

#endif