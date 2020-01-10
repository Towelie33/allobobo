#include "Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Inputs.h"
#include "Algorithm.h"
#include "GluttonBreadth.h"
#include "GluttonDepth.h"

std::string int_to_string(int i)
{
    // Do the converstion with a stringstream
    std::stringstream sstream;
    sstream << i;
    return sstream.str();
}

int random(int inf, int sup)
{
    return inf + (rand() % (sup - inf + 1));
}

void test(Inputs *inputs, Algo algo_name, short speed)
{
    // Initialize algo
    Algorithm *algo = 0;
    switch (algo_name)
    {
        case GLUTTON_BREADTH:
            std::cout << "GLUTTON BREADTH" << std::endl << std::endl;
            algo = new GluttonBreadth(inputs, speed);
            break;

        case GLUTTON_DEPTH:
            std::cout << "GLUTTON DEPTH" << std::endl << std::endl;
            algo = new GluttonDepth(inputs, speed);
            break;

        default:
            return;
    }

    // Print inputs
    std::cout << *inputs << std::endl << std::endl;

    // Run algorithm
    algo->run();

    // Print output
    std::cout << *algo << std::endl << std::endl;

    // Delete algo
    delete algo;
}
