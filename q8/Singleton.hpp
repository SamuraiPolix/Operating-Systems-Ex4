#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <mutex>

// Singleton abstract base class
/*
 * Note: the class doesnt have a pure virtual functions (virtual ... = 0)
 * but, making the constructor protected, makes it abstract because it prevents direct instantiation
 * so you can't create an object of this class
 */
class SingletonBase {
protected:
    // mutex to lock instance creation
    static std::mutex mtx;

    // implementing singleton instance
    static SingletonBase* instance;

    // constuctor is protected to prevent direct instantiation
    SingletonBase() {}

public:
    // Deleting the copy constructor and assignment operator to prevent copies
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    // virtual destructor to ensure derived class destructor is called
    virtual ~SingletonBase() {}

    // static method to get the instance of the singleton
    static SingletonBase* getInstance();
};

// Derived Singleton class
class MySingleton : public SingletonBase {
public:
    // Static method to get the instance of MySingleton
    static MySingleton* getInstance();

    // Used to display a message for testing
    void displayMessage();

private:
    // Private constructor to prevent direct creation
    MySingleton();
};

#endif // SINGLETON_HPP