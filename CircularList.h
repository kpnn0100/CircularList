/*
* File: CircularList.h
* Description: This class is represent for a data structure called Ring Buffer
* The use of this class is similar to vector from std but faster in insert element to both end of list
* the best use case for this class is reading and processing sample at the same time
* create by kpnn (Gyrus Base)
* 
*/
#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
template <typename T>
class CircularList
{
private:
    // smartpointer is considering as cheating so no smartpointer here
    
    T *storage = nullptr;
    T *tempStorage = nullptr;
    int s;
    int cap;
    int head;
    int tail;
    void makeNewOnHeap()
    {
        tempStorage = storage;
        storage = new T[s * 2];
        for (int i = 0; i < cap; ++i)
        {
            *(storage + i) = *(tempStorage + (head + i) % cap);
        }
        head = 0;
        delete[] tempStorage;
        cap = s * 2;
    }

public:
    CircularList() // default constructor
    {
        s = cap = 0;
    }
    /**
     * @brief Constructs a CircularList with the given capacity.
     * @param ca The capacity of the list.
     */
    CircularList(int ca)
    {
        cap = ca;
        s = ca;
        storage = new T[ca];
        head = 0;
        tail = 0;
    }
    /**
     * @brief Constructs a CircularList with the given capacity, initialized with the specified value.
     * @param ca The capacity of the list.
     * @param value The initial value to fill the list with.
     */
    CircularList(int ca, T value)
    {
        cap = ca;
        s = ca;
        storage = new T[ca];
        head = 0;
        tail = ca;
        for (int i = 0; i < ca; ++i)
            *(storage + i) = value;
    }
    /**
     * @brief Destructor that clears all active pointers and deallocates memory.
     */
    ~CircularList() // destructor that clear all active pointers
    {
        if (storage != nullptr)
        {
            delete[] storage;
        }
    }
    /**
     * @brief Copy constructor that creates a new instance with separate memory allocation.
     * @param source The CircularList object to be copied.
     */
    CircularList(const CircularList &source) // copy constructor: make new memory location on heap
    {
        s = source.size();
        cap = source.cap;
        storage = new T[cap];
        head = source.head;
        tail = source.tail;
        for (int i = 0; i < s; ++i)
        {
            *(storage + (head + i) % cap) = *(source.storage + +(head + i) % cap);
        }
    }
    /**
     * @brief Move constructor that transfers ownership of the underlying array from the source object.
     * @param source The CircularList object to be moved.
     */
    CircularList(CircularList &&source) // move constructor: clear the source before getting the new instance
    {
        s = source.s;
        cap = source.cap;
        storage = source.storage;
        source.storage = nullptr;
        head = source.head;
        tail = source.tail;
    }
    /**
     * @brief Copy assignment operator that performs a deep copy of the source object.
     * @param source The CircularList object to be assigned.
     * @return Reference to the modified CircularList object.
     */
    CircularList operator=(const CircularList &source) // overload =: y chang copy luon
    {
        if (storage != nullptr)
        {
            delete[] storage;
        }
        s = source.s;
        cap = source.cap;
        storage = new T[cap];
        head = source.head;
        tail = source.tail;
        for (int i = 0; i < s; ++i)
        {
            *(storage + (head + i) % cap) = *(source.storage + (head + i) % cap);
        }
        return *this;
    }
    /**
     * @brief Overloaded indexing operator that provides access to the elements of the list.
     * @param index The index of the element to access.
     * @return Reference to the element at the specified index.
     */
    T &operator[](int index)
    {
        return *(storage + (head + index) % cap);
    }
    /**
     * @brief Overloaded indexing operator that provides access to the elements of the list.
     * @param index The index of the element to access.
     * @return Reference to the element at the specified index.
     */
    T operator[](int index) const
    {
        if (index > s - 1)
        {
            return 0;
        }
        return *(storage + (head + index) % cap);
    }
    /**
     * @brief Overloaded indexing operator that provides access to the elements of the list.
     * @param index The index of the element to access.
     * @return Reference to the element at the specified index.
     */
    CircularList operator*(double factor) // illegal for not a number
    {
        CircularList temp = *this;
        for (int i = 0; i < s; ++i)
        {
            temp[i] = (*this)[i] * factor;
        }
        return temp;
    }
    
    /**
     * @brief Retrieves the first element in the list.
     * @return The value of the first element.
     */
    T front()
    {
        return *(storage + head);
    }
    /**
     * @brief Retrieves the last element in the list.
     * @return The value of the last element.
     */
    T back()
    {
        return *(storage + (head + size() - 1) % cap);
    }
    /**
     * @brief Inserts a new element at the front of the list and removes the last element. This will keep the size of the list
     * @param data The data to be inserted.
     */
    void push_front_and_pop_back(T data)
    {
        if (size() < cap)
        {
            push_front(data);
            pop_back();
        }
        else
        {
            pop_back();
            push_front(data);
        }
    }
    /**
     * @brief Inserts a new element at the end of the list.
     * @param data The data to be inserted.
     */
    void push_back(T data)
    {

        s++;
        if (s > cap)
        {
            makeNewOnHeap();
        }
        *(storage + (head + s - 1) % cap) = data;
    }
    /**
     * @brief Removes the last element from the list.
     */
    void pop_back()
    {

        s--;
        if (s < cap / 2 + 1)
        {

            tempStorage = storage;
            storage = new T[cap / 2];
            for (int i = 0; i < cap / 2; ++i)
            {
                *(storage + i) = *(tempStorage + (head + i) % cap);
            }
            head = 0;
            delete[] tempStorage;
            cap /= 2;
        }
    }
    /**
     * @brief Removes the last element from the list.
     */
    void clear()
    {
        s = 0;
        cap = 0;

        delete[] storage;
        storage = nullptr;
    }
    /**
     * @brief Inserts a new element at the specified index in the list.
     * @param index The index at which to insert the element.
     * @param data The data to be inserted.
     */
    void insert(int index, T data)
    {
        if (index == 0)
        {
            push_front(data);
        }
        else
        {

            s++;
            if (s > cap)
            {

                tempStorage = storage;
                storage = new T[s * 2];
                int offset = 0;
                for (int i = 0; i < cap; ++i)
                {
                    if (i == index)
                    {
                        *(storage + (head + i) % cap) = data;
                        offset = 1;
                    }
                    *(storage + (head + i) % cap + offset) = *(tempStorage + (head + i) % cap);
                }
                delete[] tempStorage;
                cap = s * 2;
            }
            else
            {
                for (int i = s - 1; i > index; --i)
                {
                    *(storage + (head + i) % cap) = *(storage + (head + i) % cap - 1);
                }
                *(storage + (head + index) % cap) = data;
            }
        }
    }
    /**
     * @brief Removes the element at the specified index from the list.
     * @param index The index of the element to remove.
     */
    void erase(int index)
    {
        for (int i = index; i < s - 1; ++i)
        {
            *(storage + (head + i) % cap) = *(storage + (head + i) % cap + 1);
        }
        s--;
        if (s < cap / 2 + 1)
        {

            tempStorage = storage;
            storage = new T[cap / 2];
            for (int i = 0; i < cap / 2; ++i)
            {
                *(storage + i) = *(tempStorage + (head + i) % cap);
            }
            head = 0;
            delete[] tempStorage;
            cap /= 2;
        }
    }
    /**
     * @brief Removes the element at the specified index from the list.
     * @param index The index of the element to remove.
     */
    void push_front(T data)
    {
        s++;
        if (s > cap)
        {
            makeNewOnHeap();
        }
        head = ((head - 1) + cap) % cap;
        *(storage + head) = data;
    }
    /**
     * @brief Removes the first element from the list.
     */
    void pop_front()
    {
        s--;
        head = (head + 1) % cap;
    }
    /**
     * @brief Checks if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool empty()
    {
        return (storage == nullptr) ? true : false;
    }
    /**
     * @brief Returns the number of elements currently in the list.
     * @return The size of the list.
     */
    int size() const
    {
        return s;
    }
private:
    friend ostream &operator<<(ostream &out, CircularList<T> value)
    {
        out << "[";
        for (int i = 0; i < value.size() - 1; i++)
            out << value[i] << ",";
        out << value[value.size() - 1] << "]";
        return out;
    }
};
#endif