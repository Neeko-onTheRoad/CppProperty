#ifndef __OBSERVABLE_PROPERTY__
#define __OBSERVABLE_PROPERTY__

#include "../Property.hpp"
#include "./ObservableSetterOnlyProperty.hpp"

namespace nk {

	template<typename TValue>
	class ObservableProperty
		: public ObservableSetterOnlyProperty<TValue>,
		  protected Property<TValue> {
	
	public:
		
		using GetterFunction = typename Property<TValue>::GetterFunction;
		using SetterFunction = typename Property<TValue>::SetterFunction;

	public:

		ObservableProperty(const GetterFunction& getter, const SetterFunction& setter)
			: GetterOnlyProperty<TValue>(getter),
			  SetterOnlyProperty<TValue>(setter),
			  Property<TValue>(getter, setter),
			  ObservableSetterOnlyProperty<TValue>(setter) {}

	private:

		inline ObservableSetterOnlyProperty<TValue>& AsObservableSetterOnlyProperty() const noexcept {
			return static_cast<ObservableSetterOnlyProperty<TValue>&>(*this);
		}

	public:

		ObservableProperty& operator=(const TValue& newValue) {
			AsObservableSetterOnlyProperty() = newValue;
			return *this;
		}

		ObservableProperty& operator=(TValue&& newValue) {
			AsObservableSetterOnlyProperty() = std::move(newValue);
			return *this;
		}

		operator const TValue&() {
			return this->_getter();
		}

	};

}

#endif