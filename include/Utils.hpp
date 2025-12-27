#pragma once

#include <SDL2/SDL.h>
#include <sstream>
#include <cmath>
#include "Math.hpp"

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
    inline float distanceFrom2Object(Vector2f first,Vector2f second){
        float dx = second.x - first.x;
        float dy = second.y - first.y;
        return std::sqrt(dx * dx + dy * dy);
    };

    inline bool AABBIntersect(const Vector2f& aPos, int aW, int aH, const Vector2f& bPos, int bW, int bH){
        return !(aPos.x + aW <= bPos.x || aPos.x >= bPos.x + bW ||
                 aPos.y + aH <= bPos.y || aPos.y >= bPos.y + bH);
    };
}
