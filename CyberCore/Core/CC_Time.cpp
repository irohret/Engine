#include "CC_Time.hpp"
#include <chrono>

namespace CyberCore {
    float CC_Time::timestarted = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    float CC_Time::getTime(){
        auto current = std::chrono::high_resolution_clock::now();
        //return std::chrono::duration<float>(current.time_since_epoch()).count();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(current.time_since_epoch()).count();
    }

    float CC_Time::deltaTime(){
        auto current = std::chrono::high_resolution_clock::now();
        // return std::chrono::duration<float>(current.time_since_epoch()).count() - timestarted;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(current.time_since_epoch()).count() - timestarted;
    }
}