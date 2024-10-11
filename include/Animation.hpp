#ifndef ANIMATION_H_
#define ANIMATION_H_

struct Animation
{
    public:
        int frameStart, frameEnd, duration;
        Animation(int _start, int _end, int _dur){
            frameStart = _start;
            frameEnd = _end;
            duration = _dur;
        }
};

#endif