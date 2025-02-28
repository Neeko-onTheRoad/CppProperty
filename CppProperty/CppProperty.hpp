#include "Property/GetterOnlyProperty.hpp"
#include "Property/SetterOnlyProperty.hpp"
#include "Property/Property.hpp"

#include "Property/Lazy/LazyProperty.hpp"

#include "Property/Observable/ObservableProperty.hpp"
#include "Property/Observable/SetterOnlyObservableProperty.hpp"

#ifndef get
	#define get(type) [&]() -> const type&
	#undef __TEMPORARY_UNDEFINED_GET__
#endif

#ifndef set
	#define set(type) [&](const type& value)
	#undef __TEMPORARY_UNDEFINED_SET__
#endif