#ifndef GLUTTONBREADTH_H
#define GLUTTONBREADTH_H

#include "Algorithm.h"
#include "Inputs.h"

class GluttonBreadth : public Algorithm
{
    public:

        GluttonBreadth(Inputs *inputs, short speed);

        virtual void find_appointments();
};

#endif // GLUTTONBREADTH_H
