#ifndef __GETTER_ONLY_PROPERTY_HPP__
#define __GETTER_ONLY_PROPERTY_HPP__

#include "Interfaces/PropertyGetter.hpp"

namespace nk {

	template<typename TValue>
	class GetterOnlyProperty : public PropertyGetter<TValue> {

	public:
		
		using GetterFunction = typename PropertyGetter<TValue>::GetterFunction;

		GetterOnlyProperty(GetterFunction getter)
			: PropertyGetter<TValue>(getter) {}

	};

}

#endif