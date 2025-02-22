#ifndef __PROPERTY_HPP__
#define __PROPERTY_HPP__

#include "GetterOnlyProperty.hpp"
#include "SetterOnlyProperty.hpp"

namespace nk {

	template<typename TValue>
	class Property : public GetterOnlyProperty<TValue>, public SetterOnlyProperty<TValue> {

	public:
		
		using GetterFunction = typename PropertyGetter<TValue>::GetterFunction;
		using SetterFunction = typename PropertySetter<TValue>::SetterFunction;

		Property(GetterFunction getter, SetterFunction setter = nullptr) :
			GetterOnlyProperty<TValue>(getter),
			SetterOnlyProperty<TValue>(setter ? setter : [&](const TValue&){}) {}

		using PropertySetter<TValue>::operator=;

	};

}

#endif 