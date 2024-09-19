#include <iostream>
#include <mutex>
#include "Singleton.hpp"

// Singleton abstract base class
/*
 * Note: the class doesnt have a pure virtual functions (virtual ... = 0)
 * but, making the constructor protected, makes it abstract because it prevents direct instantiation
 * so you can't create an object of this class
 */


// init  static members of SingletonBase
std::mutex SingletonBase::mtx;
SingletonBase* SingletonBase::instance = nullptr;

SingletonBase* SingletonBase::getInstance() {
    // THIS SHOULDNT BE CALLED DIRECTLY, ONLY FROM DERIVED CLASS
    std::lock_guard<std::mutex> lock(mtx);      // lock mutex before creating instance
    if (!instance) {
        std::cerr << "Instance creation must be handled by derived class.\n";
    }
    return instance;
}


MySingleton* MySingleton::getInstance() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!instance) {
        instance = new MySingleton();  // Create the singleton instance
    }
    return static_cast<MySingleton*>(instance);
}

void MySingleton::displayMessage() {
    std::cout << "MySingleton instance is in action!" << std::endl;
}

MySingleton::MySingleton() {}