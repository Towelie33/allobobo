#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Inputs.h"
#include "Algorithm.h"
//#include <cpprest/json.h>

/**
 * Convert an integer into a string
 * @param i The integer to convert
 * @return The integer as a string
 */
std::string int_to_string(int i);

/**
 * Generate a random double >= 0 and < 1
 * @return The random double
 */
double random01();

/**
 * Generate a random integer >= inf and <= sup
 * @param inf The minimal value that can be taken
 * @param sup The maximal value that can be taken
 * @return The random number
 */
int random(int inf, int sup);

/**
 * Generate a vector of random different integers >= inf and <= sup
 * @param inf The minimal value that can be taken
 * @param sup The maximal value that can be taken
 * @param n The size of the vector (must be > sup - inf)
 * @return The random vector
 */
std::vector<int> random_vector(int inf, int sup, int n);

/**
 * Generate a random permutation of integers between 0 and n - 1
 * @param n The size of the permutation
 * @return The random permutation
 */
std::vector<int> generate_random_permutation(int n);

/*
 * Display a json object as a string
 * @param jvalue The json object to display
 * @param prefix A string to display before the json
 */
//void display_json(web::json::value const& jvalue, utility::string_t const& prefix = L"");

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
    GLUTTON_DEPTH,
    GENETIC
};

/**
 * Run the chosen algorithm on the inputs
 * @param inputs The nurses and patients
 * @param algo_name The algorithm to use
 */
void run_algo(Inputs *inputs, Algo algo_name);//, web::json::value& answer = web::json::value::null());

#endif // UTILS_H
