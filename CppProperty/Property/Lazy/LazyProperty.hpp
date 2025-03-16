#ifndef __LAZY_PROPERTY_HPP__
#define __LAZY_PROPERTY_HPP__

#ifdef get
	#undef get
	#define __TEMPORARY_UNDEFINED_GET__
#endif

#include <optional>
#include <variant>
#include "../Property.hpp"

namespace nk {

	template<typename TValue>
	class LazyProperty : protected Property<TValue> {

	public:

		using GetterFunction = typename Property<TValue>::GetterFunction;
		using SetterFunction = typename Property<TValue>::SetterFunction;

	protected:

		using ReferenceBuffer = typename std::reference_wrapper<const TValue>;
		using BufferContainer = typename std::variant<std::monostate, TValue, ReferenceBuffer>;

	protected:

		bool _needUpdate = false;
		BufferContainer _buffer;
		BufferContainer _lastValue;

	public:

		LazyProperty(GetterFunction getter, SetterFunction setter = set(TValue) {})
			: Property<TValue>(getter, setter) {}

	private:
		
		template<typename T>
		LazyProperty& AssignValue(T&& value) {

			if (auto* ptr = std::get_if<TValue>(&_lastValue)) {
				if (*ptr == value) {
					_needUpdate = false;
					return *this;
				}
			}
			if (auto* ref = std::get_if<ReferenceBuffer>(&_lastValue)) {
				if (*ref == value) {
					_needUpdate = false;
					return *this;
				}
			}

			_needUpdate = true;
			_buffer = std::forward<T>(value);

			return *this;

		}

		void CommitBuffer() {

			if (auto* ptr = std::get_if<TValue>(&_buffer)) {
				_lastValue = *ptr;
				this->_setter(*ptr);
			}
			else if (auto* ref = std::get_if<ReferenceBuffer>(&_buffer)) {
				_lastValue = ref->get();
				this->_setter(ref->get());
			}

			_needUpdate = false;

		}

	public:

		LazyProperty& operator=(const TValue& newValue) {
			return AssignValue(newValue);
		}

		LazyProperty& operator=(TValue&& other) {
			return AssignValue(std::move(other));
		}

		operator const TValue& () {
			if (_needUpdate) CommitBuffer();
			return this->_getter();
		}

	};

}

#ifdef __TEMPORARY_UNDEFINED_GET__
	#define get(type) [&]() -> const type&
	#undef __TEMPORARY_UNDEFINED_GET__
#endif

#endif