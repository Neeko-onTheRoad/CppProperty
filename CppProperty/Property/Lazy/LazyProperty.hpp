#ifndef __LAZY_PROPERTY_HPP__
#define __LAZY_PROPERTY_HPP__

#include "../Property.hpp"

namespace nk {

	template<typename TValue>
	class LazyProperty : protected Property<TValue> {

	public:

		using GetterFunction = typename Property<TValue>::GetterFunction;
		using SetterFunction = typename Property<TValue>::SetterFunction;

	protected:

		bool needToUpdate = true;
		TValue& value = *new TValue();

	public:

		LazyProperty(GetterFunction getter, SetterFunction setter = set(TValue) {})
			: Property<TValue>(getter, setter) {}

		LazyProperty& operator=(const TValue& newValue) {

			if (value != newValue) {
				needToUpdate = true;
				value = newValue;
			}

			return *this;
		}

		LazyProperty& operator=(TValue&& other) {

			if (value != other) {
				needToUpdate = true;
				value = std::move(other);
			}

			return *this;
		}

		operator const TValue&() {
			
		}

	};

}

#endif