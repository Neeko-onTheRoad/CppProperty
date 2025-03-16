#ifndef __SETTER_ONLY_PROPERTY_HPP__
#define __SETTER_ONLY_PROPERTY_HPP__

#include <functional>

#define set(type) [&](const type& value)

namespace nk {

	template<typename TValue>
	class SetterOnlyProperty {

	public:
		
		using SetterFunction = typename std::function<void(const TValue&)>;

	protected:

		SetterFunction _setter;

	public:

		SetterOnlyProperty(SetterFunction setter)
			: _setter(setter) {}

		virtual ~SetterOnlyProperty() {}

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