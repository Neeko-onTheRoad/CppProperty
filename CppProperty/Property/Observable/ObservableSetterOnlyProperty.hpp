#ifndef __OBSERVABLE_SETTER_ONLY_PROPERTY__
#define __OBSERVABLE_SETTER_ONLY_PROPERTY__

#include "../SetterOnlyProperty.hpp"
#include "../../General/Event.hpp"

namespace nk {

	template<typename TValue>
	class ObservableSetterOnlyProperty
		: virtual protected SetterOnlyProperty<TValue> {

	public:
		
		using SetterFunction = typename SetterOnlyProperty<TValue>::SetterFunction;

	public:

		Event<TValue> OnValueChanged;

	public:

		ObservableSetterOnlyProperty(const SetterFunction& setter)
			: SetterOnlyProperty<TValue>(setter) {}

	private:
		
		inline SetterOnlyProperty<TValue>& AsSetterOnlyProperty() const noexcept {
			return static_cast<SetterOnlyProperty<TValue>&>(*this);
		}

	public:

		ObservableSetterOnlyProperty& operator=(const TValue& newValue) {
			AsSetterOnlyProperty()  = newValue;
			OnValueChanged(newValue);
			return *this;
		}

		ObservableSetterOnlyProperty& operator=(TValue&& newValue) {
			AsSetterOnlyProperty() = std::move(newValue);
			OnValueChanged(newValue);
			return *this;
		}

	};

}

#endif