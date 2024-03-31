#pragma once

class Time{

    public: 
        Time();
        ~Time();
        
        float _deltaTime; 
        float GetTime();
        float GetDeltaTime();
        void Update();

    private:

};