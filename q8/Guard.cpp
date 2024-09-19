#include "Guard.hpp"

Guard::Guard(std::mutex& mtx) : mtx(mtx) {
    mtx.lock();
}

Guard::~Guard() {
    mtx.unlock();
}