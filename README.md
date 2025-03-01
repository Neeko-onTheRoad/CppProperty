# C\# style C++ properties

This is a simple library that makes you easy to write get/set function.  
You can use Properties by include `"CppProperty.hpp"`.  
It includes all properties.  

Or you can use specific property by include `"Property/<PropertyName>.hpp"`.

## Property

### In C\#

```cs
using System;

public class TestClass {

    private int _intField;
    public int IntProperty {
        get => _intField;
        set {
            Console.WriteLine($"Value Changed: {value}");
            _intField = value;
        }
    }

    public string StringProperty {
        get {
            _intField++;
            return "This is property";
        }
    }
}
```

### In C++ with this library

```cpp
#include <iostream>
#include "CppProperty.hpp"

class TestClass {

private:

    int _intField;

public:

    nk::Property<int> IntProperty {
        get(int) {
            return _intField;
        }
        set(int) {
            std::cout << "Value Changed: " << value;
            _intField = value;
        }
    };

    nk::GetterOnlyProperty<std::string> {
        get(int) {
            _intField++;
            return "This is property";
        }
    }

};
```

Getter and Setter is macro.  
You can replace `get(type)` to `[&]() -> const type&`  
And `set(type)` to `[&](const type&)`  

### Caution

Avoid retruning literal or temporary, local variable in getter.  
It can cause invalid reference.

```cpp
nk::GetterOnlyProperty<int> property1 {
    get(int) {
        return 10; // Not prefered
    }
}

nk::GetterOnlyProperty<int> property2 {
    get(int) {
        static const int value = 10;
        return value; // Prefered
    }
}
```

## Special properties

Some properties for special purposes.  

### Lazy Property

This property only run setter when getter called and the value changes.  
It can be useful when setter need large operation.

```cpp
#include <iostream>
#include "CppProperty"

class TestClass {

private:
    int _fiboField;

public:
    nk::LazyProperty<int> Property {
        get(int) {
            std::cout << "Getter Called.\n";
            return _fiboField;
        },
        set(int) {
            std::cout << "Setter Called.\n";
            _fiboField = Fibo(value);
        }
    };
}

int main(void) {

    TestClass tc;

    tc.Property = 5; // Setter was not called
    tc.Property = 10; // Setter was not called too
    std::cout << tc.Property << std::endl; // Setter will called autometically befoure getter

    tc.Property = 10;
    std::cout << tc.Property << std::endl; // Setter will not called because value was not changed

    tc.Property = 5;
    tc.Property = 10;
    std::cout << tc.Property << std::endl; // Setter will also not called 

}
```  

This code will print:

```text
Setter Called.
Getter Called.
55
Getter Called.
55
Getter Called.
55
```
