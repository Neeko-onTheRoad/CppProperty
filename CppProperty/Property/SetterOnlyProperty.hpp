#ifndef __SETTER_ONLY_PROPERTY_HPP__
#define __SETTER_ONLY_PROPERTY_HPP__

#include <functional>

#define set(type) [&](const type& value)

namespace nk {

	template<typename TValue>
	class SetterOnlyProperty {

	public:
		
		using SetterFunction = typename std::function<void(const TValue&)>;

		SetterOnlyProperty(SetterFunction setter)
			: _setter(setter) {}

		virtual ~SetterOnlyProperty() {}

		SetterOnlyProperty& operator=(const TValue& newValue) {
			_setter(newValue);
			return *this;
		}

		SetterOnlyProperty& operator=(TValue&& other) {
			_setter(std::move(other));
			return *this;
		}

	protected:

		SetterFunction _setter;

	};

}

#endif