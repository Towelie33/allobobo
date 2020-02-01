#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <utility>
#include "Algorithm.h"
#include "Inputs.h"
#include "Solution.h"

// It's supposed that there's only one treatment per patient
class Genetic : public Algorithm
{
    public:

        Genetic(Inputs *inputs, int population_size = 100, double crossover_rate = 0.5d, double mutation_rate = 0.006d, int max_generations = 10000);

        int nurses() const { return m_inputs->nurses_size(); }
        int treatments() const { return m_inputs->treatments_size(); }
        int treatments_per_nurse() const { return m_inputs->treatments_per_nurse(); }

        static std::vector<Solution> generate_population(int population_size, int nurses, int treatments_per_nurse);
        static int fitness(Solution &sol, Inputs *inputs); // the lower the fitter
        static std::pair<Solution, Solution> crossover(Solution const& parent1, Solution const& parent2, double rate, int method = 1);

        void generate_population();
        void selection(std::vector<Solution> &new_population, int method = 1);
        void crossover(std::vector<Solution> &new_population, double rate, int method = 4) const;
        void mutation(std::vector<Solution> &new_population) const;
        void update_best_solution();

        void process();

        static void print_solution(Solution const& sol);
        static void print_population(std::vector<Solution> const& population);
        void print_population() const;
        void print_best_solution(int generation) const;


    private:

    	void convert_to_appointments(Solution const& sol);

    	virtual void find_appointments();

    	int m_population_size;
    	double m_crossover_rate;
    	double m_mutation_rate;
    	int m_max_generations;
    	std::vector<Solution> m_population;

    	int m_best_fitness;
    	Solution m_best_solution;

    	/**
		 * Class used to compare solution using the fitness function
		 */
		class CompareSolutions
		{
		    public:

		    	CompareSolutions(Inputs *inputs):m_inputs(inputs) {}

		        bool operator()(Solution &sol1, Solution &sol2) { return fitness(sol1, m_inputs) < fitness(sol2, m_inputs); }


		    private:

		    	Inputs *m_inputs;
		};
};

#endif // GENETIC_H
