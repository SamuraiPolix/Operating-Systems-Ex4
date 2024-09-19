#ifndef GUARD_HPP
#define GUARD_HPP

#include <iostream>
#include <mutex>

// Guard (Scope Mutex) class for managing mutex locks
// should act as a lock guard
class Guard {
private:
    std::mutex& mtx;  // Reference to the mutex

public:
    // Constructor locks the mutex when it is created
    Guard(std::mutex& mtx);

    // Destructor unlocks the mutex when the object goes out of scope
    ~Guard();

    // Deleting the copy constructor and assignment operator to prevent unexpected behavior 
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;
};

#endif // GUARD_HPP