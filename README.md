# CircularList

CircularList is a C++ template class that implements a circular list data structure. It allows you to store and manipulate a list of elements with a dynamic capacity. The circular list provides constant-time insertion and deletion operations at both ends of the list, making it efficient for use cases where elements are frequently added or removed.

## Usage

To use the CircularList class, include the "CircularList.h" header file in your C++ program:

```cpp
#include "CircularList.h"
```

### Creating a CircularList object

You can create a CircularList object by specifying the capacity of the list:

```cpp
CircularList<int> myList(10);  // Creates a CircularList with capacity 10
```

You can also create a CircularList object with an initial value for all elements:

```cpp
CircularList<int> myList(10, 5);  // Creates a CircularList with capacity 10 and initializes all elements to 5
```

### Inserting and accessing elements

To insert an element at a specific index in the list, use the `insert` method:

```cpp
myList.insert(0, 10);  // Inserts the value 10 at index 0
```

To access an element at a specific index, use the indexing operator:

```cpp
int value = myList[0];  // Retrieves the value at index 0
```

### Modifying elements

You can modify elements in the CircularList by assigning new values using the indexing operator:

```cpp
myList[0] = 20;  // Assigns the value 20 to the element at index 0
```

### Removing elements

To remove an element at a specific index, use the `erase` method:

```cpp
myList.erase(0);  // Removes the element at index 0
```

You can also remove the first or last element using the `pop_front` and `pop_back` methods, respectively:

```cpp
myList.pop_front();  // Removes the first element
myList.pop_back();   // Removes the last element
```

### Other operations

The CircularList class provides several other methods and functionalities:

- `size()`: Returns the number of elements currently in the list.
- `empty()`: Checks if the list is empty.
- `front()`: Retrieves the first element in the list.   
- `back()`: Retrieves the last element in the list.
- `push_front()`: Inserts a new element at the front of the list.
- `push_back()`: Inserts a new element at the end of the list.
- `push_front_and_pop_back()`: Inserts a new element at the front of the list and removes the last element. This keeps the size of the list.
- `clear()`: Removes all elements from the list.
- `operator<<()`: Overloaded output stream operator for printing the list.

## License

This code is licensed under the [MIT License](LICENSE).