#ifndef __SETTER_ONLY_OBSERVABLE_PROPERTY__
#define __SETTER_ONLY_OBSERVABLE_PROPERTY__

#include "../SetterOnlyProperty.hpp"
#include "../../General/Event.hpp"

namespace nk {

	template<typename TValue>
	class ObservableSetterOnlyProperty : virtual protected SetterOnlyProperty<TValue> {

	public:
		
		using SetterFunction = typename SetterOnlyProperty<TValue>::SetterFunction;

	public:

		Event<TValue> OnValueChanged;

	public:

		ObservableSetterOnlyProperty(SetterFunction setter)
			: SetterOnlyProperty<TValue>(setter) {}

	public:

		ObservableSetterOnlyProperty& operator=(const TValue& newValue) {
			static_cast<SetterOnlyProperty<TValue>&>(*this) = newValue;
			OnValueChanged(newValue);
			return *this;
		}

		ObservableSetterOnlyProperty& operator=(const TValue&& newValue) {

		}

	};

}

#endif