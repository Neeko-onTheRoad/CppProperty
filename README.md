# C\# style C++ properties

This is simple libray that make you easy to make get/set function.

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

    private string _stringField;
    public string StringProperty {
        get {
            _intField++;
            _stringField = value;
        }
    }
}
```

## In C++ with this libray

```cpp
#include <iostream>
#include "Property.hpp"

class TestClass {

private:

    int _intField;
    std::string _stringField;

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

};
```

Getter and Setter is mecro.  
You can replace `get(type)` to `[&]() -> type&`,
And `set(type)` to `[&](const type&)`
