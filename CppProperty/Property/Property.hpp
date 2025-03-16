#ifndef __PROPERTY_HPP__
#define __PROPERTY_HPP__

#include "./GetterOnlyProperty.hpp"
#include "./SetterOnlyProperty.hpp"

namespace nk {

	template<typename TValue>
	class Property
		: public GetterOnlyProperty<TValue>,
		  virtual public SetterOnlyProperty<TValue>
	{

	public:

		using GetterFunction = typename GetterOnlyProperty<TValue>::GetterFunction;
		using SetterFunction = typename SetterOnlyProperty<TValue>::SetterFunction;

	public:

		Property(GetterFunction getter, SetterFunction setter = set(TValue) {})
			: GetterOnlyProperty<TValue>(getter),
			  SetterOnlyProperty<TValue>(setter) {}

		virtual ~Property() {}

		Property& operator=(const TValue& newValue) {
			static_cast<SetterOnlyProperty<TValue>&>(*this) = newValue;
			return *this;
		}

		Property& operator=(TValue&& newValue) {
			static_cast<SetterOnlyProperty<TValue>&>(*this) = std::move(newValue);
			return *this;
		}

	};

}

#endif