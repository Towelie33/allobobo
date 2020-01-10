#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Inputs.h"
#include "Algorithm.h"

/**
 * Convert an integer into a string
 * @param i The integer to convert
 * @return The integer as a string
 */
std::string int_to_string(int i);

/**
 * Generate a random integer >= inf and <= sup
 * @param inf The minimal value that can be taken
 * @param sup The maximal value that can be taken
 * @return The random number
 */
int random(int inf, int sup);

/**
 * Class used to compare the value refered by the pointers
 * instead of the pointers itself
 */
class ComparePointers
{
    public:

        template<typename T>
        bool operator()(T *a, T *b) { return (*a) < (*b); }
};

/**
 * The different available algorithms to solve the problem
 */
enum Algo
{
    GLUTTON_BREADTH,
    GLUTTON_DEPTH
};

/**
 * Run the chosen algorithm on the inputs
 * @param inputs The nurses and patients
 * @param algo_name The algorithm to use
 */
void test(Inputs *inputs, Algo algo_name, short speed);

#endif // UTILS_H
