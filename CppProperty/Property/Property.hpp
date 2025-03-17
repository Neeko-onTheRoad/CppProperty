#ifndef __PROPERTY_HPP__
#define __PROPERTY_HPP__

#include "./GetterOnlyProperty.hpp"
#include "./SetterOnlyProperty.hpp"

namespace nk {

	template<typename TValue>
	class Property
		: virtual public GetterOnlyProperty<TValue>,
		  virtual public SetterOnlyProperty<TValue> {

	public:

		using GetterFunction = typename GetterOnlyProperty<TValue>::GetterFunction;
		using SetterFunction = typename SetterOnlyProperty<TValue>::SetterFunction;

	public:

		Property(const GetterFunction& getter, const SetterFunction& setter = set(TValue) {})
			: GetterOnlyProperty<TValue>(getter),
			  SetterOnlyProperty<TValue>(setter) {}

		virtual ~Property() {}

	private:

		inline SetterOnlyProperty<TValue>& AsSetterOnlyProperty() noexcept {
			return static_cast<SetterOnlyProperty<TValue>&>(*this);
		}

	public:

		Property& operator=(const TValue& newValue) {
			AsSetterOnlyProperty() = newValue;
			return *this;
		}

		Property& operator=(TValue&& newValue) {
			AsSetterOnlyProperty() = std::move(newValue);
			return *this;
		}
		
	};

}

#endif