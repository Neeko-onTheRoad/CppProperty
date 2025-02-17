# C\# style C++ properties

This is a simple library that makes you easy to write get/set function.

## In C\#

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

## In C++ with this library

```cpp
#include <iostream>
#include "Property.hpp"

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

Getter and Setter is mecro.  
You can replace `get(type)` to `[&]() -> type&`  
And `set(type)` to `[&](const type&)`
