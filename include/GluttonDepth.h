#ifndef GLUTTONDEPTH_H
#define GLUTTONDEPTH_H

#include "Algorithm.h"
#include "Inputs.h"

class GluttonDepth : public Algorithm
{
    public:

        GluttonDepth(Inputs *inputs, short speed);

        virtual void find_appointments();
};

#endif // GLUTTONDEPTH_H
