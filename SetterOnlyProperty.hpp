#ifndef __SETTER_ONLY_PROPERTY_HPP__
#define __SETTER_ONLY_PROPERTY_HPP__

#include "Interfaces/PropertySetter.hpp";

namespace nk {

	template<typename TValue>
	class SetterOnlyProperty : public PropertySetter<TValue> {

	public:
		
		using SetterFunction = typename PropertySetter<TValue>::SetterFunction;

		SetterOnlyProperty(SetterFunction setter)
			: PropertySetter<TValue>(setter) {}

		using PropertySetter<TValue>::operator=;

	};

}

#endif