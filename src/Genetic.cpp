#include "../include/Genetic.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include "../include/Utils.h"
#include "../include/Point.h"
#include "../include/Patient.h"
#include "../include/Appointment.h"
#include "../include/Inputs.h"
#include "../include/Algorithm.h"
#include "../include/Solution.h"

Genetic::Genetic(Inputs *inputs, int population_size, double crossover_rate, double mutation_rate, int max_generations)
    :Algorithm(inputs), m_population_size((population_size / 4) * 4),
    m_crossover_rate(crossover_rate), m_mutation_rate(mutation_rate),
    m_max_generations(max_generations), m_best_fitness(-1)
{}

std::vector<Solution> Genetic::generate_population(int population_size, int nurses, int treatments_per_nurse)
{
	// Initialize population vector
	std::vector<Solution> population(population_size);

	// Generate a random initial population
	for (int i = 0; i < population_size; ++i)
	{
		// Generate a random solution
		Solution sol(nurses, treatments_per_nurse, generate_random_permutation(nurses * treatments_per_nurse));

		// Add it in the population
		population[i] = sol;
	}

	// Return population
	return population;
}

int Genetic::fitness(Solution &sol, Inputs *inputs)
{
	// Initialize total fitness
	int total_fitness = 0;

	// Calculate the total car distance for this solution
	for (int i = 0, nurses = inputs->nurses_size(); i < nurses; ++i)
	{
		// Initialize nurse fitness
		int nurse_fitness = sol.fitness(i);

		// Check if nurse fitness is already calculated
		if (nurse_fitness >= 0)
        {
            total_fitness += nurse_fitness;
            continue;
        }
        nurse_fitness = 0;
		// Calculate nurse fitness
        Point current(inputs->get_patient(sol.get(i, 0))->location());
        Point car(current);
        for (int j = 1, treatments_per_nurse = inputs->treatments_per_nurse(); j < treatments_per_nurse; ++j)
		{
            Point destination(inputs->get_patient(sol.get(i, j))->location());
            int dist = distance(current, destination);
            if (dist > inputs->min_car_dist())
			{
                dist = distance(car, destination);
                if (dist > inputs->min_car_dist())
                {
                    nurse_fitness += dist;
                    car = destination;

                    // Update distance in solution
                    sol.distance(i, j - 1, dist);
                }
                else
                {
                    // Update distance in solution
                    sol.distance(i, j - 1, 0);
                }
			}
			else
            {
                // Update distance in solution
                sol.distance(i, j - 1, 0);
            }
			current = destination;
		}

		// Update nurse fitness in solution
        sol.fitness(i, nurse_fitness);

        // Update total fitness
        total_fitness += nurse_fitness;
	}

	// Return total fitness
	return total_fitness;
}

std::pair<Solution, Solution> Genetic::crossover(Solution const& parent1, Solution const& parent2, double rate, int method)
{
	// Initialize variables
	int nurses = parent1.nurses();
	int treatments_per_nurse = parent1.treatments_per_nurse();
	if (nurses != parent2.nurses() || treatments_per_nurse != parent2.treatments_per_nurse())
	{
		//TODO
	}
	std::pair<Solution, Solution> children;

	switch (method)
	{
		// Single-point crossover
		case 0:
		{
			// Get crossing point
			int crossing_point = (int) std::floor((1.0f - rate) * ((double) treatments_per_nurse));
			if (crossing_point == treatments_per_nurse)
			{
				--crossing_point;
			}

			// Initialize children
			Solution child1(nurses, treatments_per_nurse, parent1, crossing_point);
			Solution child2(nurses, treatments_per_nurse, parent2, crossing_point);

			// Get unchanged values
			std::vector<int> parent1_buf;
			std::vector<int> parent2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < crossing_point; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
					parent2_buf.push_back(parent2.get(i, j));
				}
			}

			// Get values to append
			std::vector<int> child1_buf;
			std::vector<int> child2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < treatments_per_nurse; ++j)
				{
					int val = parent2.get(i, j);
					if (std::find(parent1_buf.begin(), parent1_buf.end(), val) == parent1_buf.end())
					{
						child1_buf.push_back(val);
					}
					val = parent1.get(i, j);
					if (std::find(parent2_buf.begin(), parent2_buf.end(), val) == parent2_buf.end())
					{
						child2_buf.push_back(val);
					}
				}
			}

			// Fill children with child buffers
			int counter = 0;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = crossing_point; j < treatments_per_nurse; ++j)
				{
					child1.set(i, j, child1_buf[counter]);
					child2.set(i, j, child2_buf[counter]);
					++counter;
				}
			}

			// Put children in the pair
			children.first = child1;
			children.second = child2;

			break;
		}

		// Two-point crossover
		case 1:
		{
			// Get crossing length
			int crossing_length = (int) std::ceil(rate * ((double) treatments_per_nurse));
			if (crossing_length == 0)
			{
				++crossing_length;
			}

            // Generate crossing points
			int crossing_point1 = random(0, treatments_per_nurse - crossing_length);
			int crossing_point2 = crossing_point1 + crossing_length;

			// Initialize children
			Solution child1(nurses, treatments_per_nurse, parent1, crossing_point1, crossing_point2);
			Solution child2(nurses, treatments_per_nurse, parent2, crossing_point1, crossing_point2);

			// Get unchanged values
			std::vector<int> parent1_buf;
			std::vector<int> parent2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < crossing_point1; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
					parent2_buf.push_back(parent2.get(i, j));
				}
				for (int j = crossing_point2; j < treatments_per_nurse; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
					parent2_buf.push_back(parent2.get(i, j));
				}
			}

			// Get values to append
			std::vector<int> child1_buf;
			std::vector<int> child2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < treatments_per_nurse; ++j)
				{
					int val = parent2.get(i, j);
					if (std::find(parent1_buf.begin(), parent1_buf.end(), val) == parent1_buf.end())
					{
						child1_buf.push_back(val);
					}
					val = parent1.get(i, j);
					if (std::find(parent2_buf.begin(), parent2_buf.end(), val) == parent2_buf.end())
					{
						child2_buf.push_back(val);
					}
				}
			}

			// Fill children with child buffers
			int counter = 0;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = crossing_point1; j < crossing_point2; ++j)
				{
					child1.set(i, j, child1_buf[counter]);
					child2.set(i, j, child2_buf[counter]);
					++counter;
				}
			}

			// Put children in the pair
			children.first = child1;
			children.second = child2;

			break;
		}

		// Two-point crossover randomized for each nurse
		case 2:
		{
			// Get crossing length
			int crossing_length = (int) std::ceil(rate * ((double) treatments_per_nurse));
			if (crossing_length == 0)
			{
				++crossing_length;
			}

            // Generate crossing points for each nurse
            std::vector<int> crossing_points1_parent1(nurses);
            std::vector<int> crossing_points2_parent1(nurses);
            std::vector<int> crossing_points1_parent2(nurses);
            std::vector<int> crossing_points2_parent2(nurses);
            for (int i = 0; i < nurses; ++i)
            {
                // For parent1
                int crossing_point = random(0, treatments_per_nurse - crossing_length);
                crossing_points1_parent1[i] = crossing_point;
                crossing_points2_parent1[i] = crossing_point + crossing_length;

                // For parent2
                crossing_point = random(0, treatments_per_nurse - crossing_length);
                crossing_points1_parent2[i] = crossing_point;
                crossing_points2_parent2[i] = crossing_point + crossing_length;
            }

			// Initialize children
			Solution child1(nurses, treatments_per_nurse, parent1, crossing_points1_parent1, crossing_points2_parent1);
			Solution child2(nurses, treatments_per_nurse, parent2, crossing_points1_parent2, crossing_points2_parent2);

			// Get unchanged values
			std::vector<int> parent1_buf;
			std::vector<int> parent2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				// For parent1
				for (int j = 0; j < crossing_points1_parent1[i]; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
				}
				for (int j = crossing_points2_parent1[i]; j < treatments_per_nurse; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
				}

				// For parent2
				for (int j = 0; j < crossing_points1_parent2[i]; ++j)
				{
					parent2_buf.push_back(parent2.get(i, j));
				}
				for (int j = crossing_points2_parent2[i]; j < treatments_per_nurse; ++j)
				{
					parent2_buf.push_back(parent2.get(i, j));
				}
			}

			// Get values to append
			std::vector<int> child1_buf;
			std::vector<int> child2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < treatments_per_nurse; ++j)
				{
					int val = parent2.get(i, j);
					if (std::find(parent1_buf.begin(), parent1_buf.end(), val) == parent1_buf.end())
					{
						child1_buf.push_back(val);
					}
					val = parent1.get(i, j);
					if (std::find(parent2_buf.begin(), parent2_buf.end(), val) == parent2_buf.end())
					{
						child2_buf.push_back(val);
					}
				}
			}

			// Fill children with child buffers
			int counter1 = 0, counter2 = 0;
			for (int i = 0; i < nurses; ++i)
			{
				// For child1
				for (int j = crossing_points1_parent1[i]; j < crossing_points2_parent1[i]; ++j)
				{
					child1.set(i, j, child1_buf[counter1]);
					++counter1;
				}

				// For child2
				for (int j = crossing_points1_parent2[i]; j < crossing_points2_parent2[i]; ++j)
				{
					child2.set(i, j, child2_buf[counter2]);
					++counter2;
				}
			}

			// Put children in the pair
			children.first = child1;
			children.second = child2;

			break;
		}

		// Two-point crossover cutting longest car distance
		case 3:
		{
			// Generate crossing points for each nurse
            std::vector<int> crossing_points1_parent1(nurses);
            std::vector<int> crossing_points2_parent1(nurses);
            std::vector<int> crossing_points1_parent2(nurses);
            std::vector<int> crossing_points2_parent2(nurses);
            for (int i = 0; i < nurses; ++i)
            {
                // For parent1
                std::pair<int, int> points(parent1.longest_serial_car_distance(i));
                crossing_points1_parent1[i] = points.first;
                crossing_points2_parent1[i] = points.second;

                // For parent2
                points = parent2.longest_serial_car_distance(i);
                crossing_points1_parent2[i] = points.first;
                crossing_points2_parent2[i] = points.second;
            }

			// Initialize children
			Solution child1(nurses, treatments_per_nurse, parent1, crossing_points1_parent1, crossing_points2_parent1);
			Solution child2(nurses, treatments_per_nurse, parent2, crossing_points1_parent2, crossing_points2_parent2);

			// Get unchanged values
			std::vector<int> parent1_buf;
			std::vector<int> parent2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				// For parent1
				for (int j = 0; j < crossing_points1_parent1[i]; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
				}
				for (int j = crossing_points2_parent1[i]; j < treatments_per_nurse; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
				}

				// For parent2
				for (int j = 0; j < crossing_points1_parent2[i]; ++j)
				{
					parent2_buf.push_back(parent2.get(i, j));
				}
				for (int j = crossing_points2_parent2[i]; j < treatments_per_nurse; ++j)
				{
					parent2_buf.push_back(parent2.get(i, j));
				}
			}

			// Get values to append
			std::vector<int> child1_buf;
			std::vector<int> child2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < treatments_per_nurse; ++j)
				{
					int val = parent2.get(i, j);
					if (std::find(parent1_buf.begin(), parent1_buf.end(), val) == parent1_buf.end())
					{
						child1_buf.push_back(val);
					}
					val = parent1.get(i, j);
					if (std::find(parent2_buf.begin(), parent2_buf.end(), val) == parent2_buf.end())
					{
						child2_buf.push_back(val);
					}
				}
			}

			// Fill children with child buffers
			std::vector<int> range1(generate_random_permutation(child1_buf.size()));
			std::vector<int> range2(generate_random_permutation(child2_buf.size()));
			int counter1 = 0, counter2 = 0;
			for (int i = 0; i < nurses; ++i)
			{
				// For child1
				for (int j = crossing_points1_parent1[i]; j < crossing_points2_parent1[i]; ++j)
				{
					child1.set(i, j, child1_buf[range1[counter1]]);
					++counter1;
				}

				// For child2
				for (int j = crossing_points1_parent2[i]; j < crossing_points2_parent2[i]; ++j)
				{
					child2.set(i, j, child2_buf[range2[counter2]]);
					++counter2;
				}
			}

			// Put children in the pair
			children.first = child1;
			children.second = child2;

			break;
		}

		// Two-point crossover keeping longest walk distance
		case 4:
		{
			// Generate crossing points for each nurse
            std::vector<int> crossing_points1_parent1(nurses);
            std::vector<int> crossing_points2_parent1(nurses);
            std::vector<int> crossing_points1_parent2(nurses);
            std::vector<int> crossing_points2_parent2(nurses);
            for (int i = 0; i < nurses; ++i)
            {
                // For parent1
                std::pair<int, int> points(parent1.longest_serial_walk_distance(i));
                crossing_points1_parent1[i] = points.first;
                crossing_points2_parent1[i] = points.second;

                // For parent2
                points = parent2.longest_serial_walk_distance(i);
                crossing_points1_parent2[i] = points.first;
                crossing_points2_parent2[i] = points.second;
            }

			// Initialize children
			Solution child1(nurses, treatments_per_nurse, parent1, crossing_points1_parent1, crossing_points2_parent1, true);
			Solution child2(nurses, treatments_per_nurse, parent2, crossing_points1_parent2, crossing_points2_parent2, true);

			// Get unchanged values
			std::vector<int> parent1_buf;
			std::vector<int> parent2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				// For parent1
				for (int j = crossing_points1_parent1[i]; j < crossing_points2_parent1[i]; ++j)
				{
					parent1_buf.push_back(parent1.get(i, j));
				}

				// For parent2
				for (int j = crossing_points1_parent2[i]; j < crossing_points2_parent2[i]; ++j)
				{
					parent2_buf.push_back(parent2.get(i, j));
				}
			}

			// Get values to append
			std::vector<int> child1_buf;
			std::vector<int> child2_buf;
			for (int i = 0; i < nurses; ++i)
			{
				for (int j = 0; j < treatments_per_nurse; ++j)
				{
					int val = parent2.get(i, j);
					if (std::find(parent1_buf.begin(), parent1_buf.end(), val) == parent1_buf.end())
					{
						child1_buf.push_back(val);
					}
					val = parent1.get(i, j);
					if (std::find(parent2_buf.begin(), parent2_buf.end(), val) == parent2_buf.end())
					{
						child2_buf.push_back(val);
					}
				}
			}

			// Fill children with child buffers
			int counter1 = 0, counter2 = 0;
			for (int i = 0; i < nurses; ++i)
			{
				// For child1
				for (int j = 0; j < crossing_points1_parent1[i]; ++j)
				{
					child1.set(i, j, child1_buf[counter1]);
					++counter1;
				}
				for (int j = crossing_points2_parent1[i]; j < treatments_per_nurse; ++j)
				{
					child1.set(i, j, child1_buf[counter1]);
					++counter1;
				}

				// For child2
				for (int j = 0; j < crossing_points1_parent2[i]; ++j)
				{
					child2.set(i, j, child2_buf[counter2]);
					++counter2;
				}
				for (int j = crossing_points2_parent2[i]; j < treatments_per_nurse; ++j)
				{
					child2.set(i, j, child2_buf[counter2]);
					++counter2;
				}
			}

			// Put children in the pair
			children.first = child1;
			children.second = child2;

			break;
		}

		default:
			break;
	}

	// Return children
	return children;
}

void Genetic::generate_population()
{
	m_population = generate_population(m_population_size, nurses(), treatments_per_nurse());
}

void Genetic::selection(std::vector<Solution> &new_population, int method)
{
	switch (method)
	{
		// Random selection
		case 0:
		{
			std::vector<int> range(random_vector(0, m_population_size - 1, m_population_size / 2));
			for (int i: range)
			{
				new_population.push_back(m_population[i]);
			}
			break;
		}

		// Rank selection
		case 1:
		{
			std::sort(m_population.begin(), m_population.end(), CompareSolutions(m_inputs));
			std::vector<int> range(generate_random_permutation(m_population_size / 2));
			for (int i: range)
			{
				new_population.push_back(m_population[i]);
			}
			break;
		}

		// Proportionate selection
		case 2:
		{
			// Get min and max fitness
			int fitness_min = std::min_element(m_population.begin(), m_population.end(), CompareSolutions(m_inputs))->fitness();
			int fitness_max = std::max_element(m_population.begin(), m_population.end(), CompareSolutions(m_inputs))->fitness();
			int inverser = fitness_max + fitness_min + 1;

			// Calculate the sum of all inversed fitnesses to normalize
			int total_fitness = 0;
			for (int i = 0; i < m_population_size; ++i)
            {
                total_fitness += inverser - fitness(m_population[i], m_inputs);
            }

            // Calculate the probability for each solution to get selected
			std::vector<double> proba(m_population_size);
			for (int i = 0; i < m_population_size; ++i)
            {
                proba[i] = ((double) (inverser - m_population[i].fitness())) / ((double) total_fitness);
            }

            // Proceed the stochastic selection
            int counter = 0, index = 0;
            std::vector<int> range(generate_random_permutation(m_population_size));
            std::vector<Solution*> selected_solutions(m_population_size / 2);
            while (counter < m_population_size / 2)
            {
                if (random01() < proba[range[index % m_population_size]])
                {
                    selected_solutions[counter] = &m_population[range[index % m_population_size]];
                    ++counter;
                }
                ++index;
            }

            // Push the selected solutions in new population in a random order
			range = generate_random_permutation(m_population_size / 2);
			for (int i: range)
			{
				new_population.push_back(*selected_solutions[i]);
			}
			break;
		}

		// Tournament selection
		case 3:
		{
			// Choose two random solutions and push the fitest in new population
			std::vector<int> range(generate_random_permutation(m_population_size));
			for (int i = 0; i < m_population_size; i += 2)
			{
				if (fitness(m_population[range[i]], m_inputs) < fitness(m_population[range[i + 1]], m_inputs))
                {
                    new_population.push_back(m_population[range[i]]);
                }
				else
                {
                    new_population.push_back(m_population[range[i + 1]]);
                }
			}
			break;
		}

		default:
			break;
	}
}

void Genetic::crossover(std::vector<Solution> &new_population, double rate, int method) const
{
	// Generate offspring
	for (int i = 0; i < m_population_size / 2; i += 2)
	{
		// Recombination between two selected solutions
		std::pair<Solution, Solution> children(crossover(new_population[i], new_population[i + 1], rate, method));

		// Add children in new population
		new_population.push_back(children.first);
		new_population.push_back(children.second);
	}
}

void Genetic::mutation(std::vector<Solution> &new_population) const
{
	for (int i = 0; i < m_population_size; ++i)
	{
		new_population[i].mutate(m_mutation_rate);
	}
}

void Genetic::update_best_solution()
{
	Solution sol = *std::min_element(m_population.begin(), m_population.end(), CompareSolutions(m_inputs));
	int min_fitness = fitness(sol, m_inputs);
	if (min_fitness < m_best_fitness || m_best_fitness < 0)
	{
		m_best_fitness = min_fitness;
		m_best_solution = sol;
	}
}

void Genetic::process()
{
	// Initialize population
	generate_population();

	// Evolution process
	int generation = 0;
	while (generation < m_max_generations && m_best_fitness != 0)
	{
		// Create new population
		std::vector<Solution> new_population;

		// Selection process
		selection(new_population);

		// Crossover process
		double rate = m_crossover_rate;
		//rate *=  1.0d - (((double) generation) / ((double) m_max_generations * 2.0d));
		crossover(new_population, rate);

		// Mutation process
		mutation(new_population);

		// Set new population to new population
		m_population = new_population;

		// Update best solution
		update_best_solution();

		// Increment generation counter
		++generation;

		// Print best solution to debug
		if (generation % 100 == 0 || m_best_fitness == 0)
		{
			print_best_solution(generation);
		}
	}
}

void Genetic::print_solution(Solution const& sol)
{
	std::cout << sol << std::endl;
}

void Genetic::print_population(std::vector<Solution> const& population)
{
	std::cout << "--Population--" << std::endl;
	std::cout << "Size: " << population.size() << std::endl;
	for (int i = 0, len = population.size(); i < len; ++i)
	{
		std::cout << "N°" << i << std::endl;
		print_solution(population[i]);
	}
}

void Genetic::print_population() const
{
	print_population(m_population);
}

void Genetic::print_best_solution(int generation) const
{
	std::cout << "--Best Solution--" << std::endl;
	std::cout << "Generation: " << generation << std::endl;
	std::cout << "Fitness: " << m_best_fitness << std::endl;
	print_solution(m_best_solution);
}

void Genetic::convert_to_appointments(Solution const& sol)
{
	//TODO
}

void Genetic::find_appointments()
{
	// Process genetic algorithm
	process();

	// Set appointments from best solution
	convert_to_appointments(m_best_solution);
}
