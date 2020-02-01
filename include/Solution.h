#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class Solution
{
    public:

        Solution();
        Solution(int nurses, int treatments_per_nurse, std::vector<int> code);
        Solution(int nurses, int treatments_per_nurse, Solution const& parent, int crossing_point);
        Solution(int nurses, int treatments_per_nurse, Solution const& parent, int crossing_point1, int crossing_point2);
        Solution(int nurses, int treatments_per_nurse, Solution const& parent,
                 std::vector<int> const& crossing_points1, std::vector<int> const& crossing_points2, bool keep_between_points = false);

        int nurses() const { return m_nurses; }
        int treatments_per_nurse() const { return m_treatments_per_nurse; }

        int treatments() const { return m_nurses * m_treatments_per_nurse; }

        int distance(int i, int j) const { return m_distances[i][j]; }
        void distance(int i, int j, int val) { m_distances[i][j] = val; }

        int fitness() const;
        int fitness(int nurse) const { return m_fitness_per_nurse[nurse]; }
        void fitness(int nurse, int val) { m_fitness_per_nurse[nurse] = val; }

        int get(int i, int j) const { return m_code[i][j]; }
        void set(int i, int j, int val);

        std::pair<int, int> longest_serial_car_distance(int nurse) const;
        std::pair<int, int> longest_serial_walk_distance(int nurse) const;

        void mutate(double rate);

        std::string code_to_string() const;
        std::string fitness_to_string() const;
        std::string to_string() const;


    private:

        void initialize_distances();

    	int m_nurses;
    	int m_treatments_per_nurse;
    	std::vector<std::vector<int> > m_code;
    	std::vector<std::vector<int> > m_distances;
    	std::vector<int> m_fitness_per_nurse;
};

std::ostream& operator<<(std::ostream &flux, Solution const& sol);

#endif // SOLUTION_H
