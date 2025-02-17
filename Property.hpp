#ifndef __PROPERTY_HPP__
#define __PROPERTY_HPP__

#include "PropertySetter.hpp"
#include "GetterOnlyProperty.hpp"

namespace nk {

	template<typename TValue>
	class Property : public GetterOnlyProperty<TValue>, public PropertySetter<TValue> {

	public:
		
		using GetterFunction = typename PropertyGetter<TValue>::GetterFunction;
		using SetterFunction = typename PropertySetter<TValue>::SetterFunction;

		Property(GetterFunction getter, SetterFunction setter) :
			GetterOnlyProperty<TValue>(getter),
			PropertySetter<TValue>(setter) {}

		using PropertySetter<TValue>::operator=;

	};

}

#endif 