#pragma once

#include <SDL2/SDL.h>
#include <sstream>
#include <cmath>

namespace utils
{
    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();
        t *= 0.001f;
        return t;
    };
    inline void logTexts(std::string firstChar, std::string secondChar)
    {
        std::cout << firstChar << " : " << secondChar << std::endl;
    };
    inline void logTime()
    {
        std::ostringstream ss;
        ss << utils::hireTimeInSeconds();
        std::string s(ss.str());
        utils::logTexts("Time", s);
    };
    inline void logNumber(std::string firstChar,float number){
        std::ostringstream ss;
        ss << number;
        std::string s(ss.str());
        utils::logTexts(firstChar, s);
    };
    inline float distanceFrom2Object(Vector2f& first,Vector2f& second){
        return sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2) * 1.0);
    };
}
