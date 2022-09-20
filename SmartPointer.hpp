// Smart pointer class. Maintains references by counting. Code inspired by Yale CS 327 lecture and online sources (https://www.geeksforgeeks.org/smart-pointers-cpp/)

#pragma once

#include <cstddef>

class ReferenceCounter
{
    int count; // Reference count
public:
    void increment() {
        count++;
    }
    int decrement() {
        return --count;
    }
};

template <typename T>
class SmartPointer
{
    // private instance variables for dumb pointer and ReferenceCounter
    T* dumb_pointer;
    ReferenceCounter* rc;

public:
    SmartPointer(T *pValue) {
        // initialize dumb pointer
        // set up and increment reference counter
        dumb_pointer = pValue;
        rc = new ReferenceCounter();
        rc->increment();
    }

    // Copy constructor
    SmartPointer(const SmartPointer<T> &sp) {
        // Copy the data and reference pointer
        // increment the reference count
        dumb_pointer = sp.dumb_pointer;
        rc = sp.rc;
        rc->increment();
    }

    // Destructor
    ~SmartPointer() {
        // Decrement the reference count
        // if reference become zero delete the data
        int count = rc->decrement();
        if(count == 0){
            delete dumb_pointer;
            delete rc;
        }
    }

    T& operator*() {
        // delegate
        return *dumb_pointer;
    }

    T* operator->() {
        // delegate
        return dumb_pointer;
    }

    // Assignment operator
    SmartPointer<T> &operator=(const SmartPointer<T> &sp)
    {
        // Deal with old SmartPointer that is being overwritten

        // Copy sp into this (similar to copy constructor)

        // return this
        if (this != &sp){ // Avoid self assignment
            if (rc->decrement() == 0){
                delete dumb_pointer;
                delete rc;
            }
            dumb_pointer = sp.dumb_pointer;
            rc = sp.rc;
            rc->increment();
        }
        return *this;
    }

    // Check equal to nullptr
    bool operator==(std::nullptr_t rhs) const
    {
        // compare dumb pointer to rhs
        return dumb_pointer == rhs;
    }
};