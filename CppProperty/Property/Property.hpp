#ifndef __PROPERTY_HPP__
#define __PROPERTY_HPP__

#include "./GetterOnlyProperty.hpp"
#include "./SetterOnlyProperty.hpp"

namespace nk {

	template<typename TValue>
	class Property
		: public GetterOnlyProperty<TValue>,
		  public SetterOnlyProperty<TValue>
	{

	public:

		using GetterFunction = typename GetterOnlyProperty<TValue>::GetterFunction;
		using SetterFunction = typename SetterOnlyProperty<TValue>::SetterFunction;

		Property(GetterFunction getter, SetterFunction setter = nullptr)
			: GetterOnlyProperty<TValue>(getter),
			  SetterOnlyProperty<TValue>(setter ? setter : [&](const TValue&) {}) {}

		using SetterOnlyProperty<TValue>::operator=;

	};

}

#endif