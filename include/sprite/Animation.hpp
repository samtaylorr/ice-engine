#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>

struct Animation
{
    public:
        std::string name;
        int frameStart, frameEnd, duration;
        Animation(std::string _name, int _start, int _end, int _dur){
            name = _name;
            frameStart = _start;
            frameEnd = _end;
            duration = _dur;
        }
};

#endif