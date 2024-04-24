#pragma once

namespace CyberCore {
    class CC_Time {
        public:
        CC_Time();
        ~CC_Time();
        
            static float timestarted;
            static float getTime();
            static float deltaTime();
        private:
            // float deltaTime;
    };
}