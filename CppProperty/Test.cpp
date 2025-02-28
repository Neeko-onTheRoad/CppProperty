#include <iostream>
#include "CppProperty.hpp"

using namespace nk;
using namespace std;

int main(void) {

	cout << "GetterOnlyProperty Test\n";
	GetterOnlyProperty<int> getterOnlyProperty1 {
		get(int) {
			cout << "GetterOnlyProperty1's getter method called.\n";
			return 10;
		}
	};

	cout << getterOnlyProperty1 << "\n\n";

	cout << "SetterOnlyProperty Test\n";
	SetterOnlyProperty<string> setterOnlyProperty1 {
		set(string) {
			cout << "SetterOnlyProperty1's setter method called.\n";
			cout << "New value is: " << value << "\n";
		}
	};

	setterOnlyProperty1 = "New Value1";
	setterOnlyProperty1 = "New Value2";

	cout << "\n";

	cout << "Property Test\n";
	float field1 = 0.f;
	Property<float> property1 {
		get(float) {
			cout << "Property1's getter method called.\n";
			return field1;
		},
		set(float) {
			cout << "Property1's setter method called.\n";
			cout << "Value was changed: " << field1 << " -> " << value << "\n";
			field1 = value;
		}
	};

	property1 = 3.14f;
	cout << property1 << "\n\n";

	cout << "Property To SetterOnlyProperty Cast Test\n";
	SetterOnlyProperty<float> setterOnlyProperty2 = property1;
	setterOnlyProperty2 = 10.f;
	cout << "\n";

	cout << "Property To GetterOnlyProperty Cast Test\n";
	GetterOnlyProperty<float> getterOnlyProperty2 = property1;
	cout << getterOnlyProperty2 << "\n\n";

	cout << "Property Default Setter Test\n";
	Property<bool> property2 {
		get(bool) {
			return true;
		}
	};

	property2 = false;
	cout << property2 << "\n\n";

	cout << "RValue Property Test\n";
	int field2 = 0;
	Property<int> property3 {
		get(int) {
			return field2;
		},
		set(int) {
			field2 = value;
		}
	};

	field2 = std::move(69);
	cout << field2 << "\n\n";

	cout << "LazyProperty Test\n";
	int field3 = 0;
	LazyProperty<int> lazyProperty1 {
		get(int) {
			cout << "Lazy Getter Called\n";
			return field2;
		},
		set(int) {
			cout << "Lazy Setter Called: " << value << "\n";
			field2 = value;
		}
	};

	cout << "Lazy Property Set\n";
	lazyProperty1 = 10;

	cout << "Lazy Property Set\n";
	lazyProperty1 = 20;

	cout << lazyProperty1 << "\n";

	cout << "Lazy Property Set Same Value\n";
	lazyProperty1 = 20;

	cout << lazyProperty1 << "\n\n";

	cout << "Lazy Property Set Same Value With RValue\n";
	lazyProperty1 = std::move(20);
	
	cout << lazyProperty1 << "\n\n";

	cout << "Lazy Property Set Same Value\n";
	lazyProperty1 = 20;

	cout << lazyProperty1 << "\n\n";

	cout << "Lazy Property Set RValue\n";
	lazyProperty1 = std::move(30);
	cout << lazyProperty1 << "\n\n";

	cout << "Lazy Property Set A -> B -> A (Not Changed)\n";
	lazyProperty1 = 20;
	lazyProperty1 = 30;
	cout << lazyProperty1 << "\n\n";

}