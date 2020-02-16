//
// Created by Domitille Prevost on 03/02/2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Solution.h"
#include "../include/Genetic.h"
#include "../include/Point.h"
#include <vector>


static const short CAR_SPEED = 15; // in km/h
static const short WALK_SPEED = 5; // in km/h
static const short MIN_CAR_DIST = 1000; // in m
static const Point ORIGIN = Point(0, 0);
static const TimeInterval FULL_DAY = TimeInterval(6 * 60, 20 * 60);
static const Time START_TIME = FULL_DAY.start_time(), END_TIME = FULL_DAY.end_time();

struct GeneticTest : testing::Test
{
    // TreatmentTypes
    TreatmentType flu = TreatmentType(0, 30);
    TreatmentType cancer = TreatmentType(1, 90);
    Inputs inputs_2x2 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);

    Solution sol_3x3_sorted = Solution(3, 3, {0, 1, 2, 3, 4, 5, 6, 7, 8});

    Solution sol_2x2_sorted = Solution(2, 2, {0, 1, 2, 3});

    Solution sol_3x3_random = Solution(3, 3, {1, 4, 6, 2, 0, 3, 5, 7, 8});

    Genetic gen = Genetic(&inputs_2x2, 4);

    GeneticTest() {
        inputs_2x2.add_type(flu);
        inputs_2x2.add_nurse(Nurse(0));
        inputs_2x2.add_nurse(Nurse(1));
        inputs_2x2.add_patient(Patient(0, Point(0, 0), 0, 0));
        inputs_2x2.add_patient(Patient(1, Point(0, 2000), 1, 0));
        inputs_2x2.add_patient(Patient(2, Point(2000, 2000), 2, 0));
        inputs_2x2.add_patient(Patient(3, Point(2000, 0), 3, 0));
    }
};

void test_generate_population(int pop_size, int nurses, int treatments_per_nurse, Genetic gen)
{
    std::vector<Solution> pop = gen.generate_population(pop_size, nurses, treatments_per_nurse);

    ASSERT_EQ(pop.size(), pop_size);
    ASSERT_EQ(pop[0].nurses(), nurses);
    ASSERT_EQ(pop[0].treatments_per_nurse(), treatments_per_nurse);
    std::cout << pop[0].code_to_string() << "..." << std::endl;
    if (pop_size > 1){
        ASSERT_NE(pop[0].code_to_string(), pop[1].code_to_string());
    }

    //Test use of random
    std::vector<Solution> pop2 = gen.generate_population(pop_size, nurses, treatments_per_nurse);
    if (pop_size > 1){
        EXPECT_NE(pop[0].code_to_string(), pop2[0].code_to_string());
        //Size matrix and values
        ASSERT_LE(pop[0].get(nurses - 1, treatments_per_nurse -1),
                nurses * treatments_per_nurse -1);
    }
}

//TEST_F(GeneticTest, generate_population){
//    test_generate_population(3, 2, 4, gen);
//    test_generate_population(8, 10, 10, gen);
//    test_generate_population(1, 1, 1, gen);
//}
//
//TEST_F(GeneticTest, update_best_solution){
//    Solution best_solution(2, 2, {0, 2, 1, 3});
//    std::vector<Solution> population;
//    population.push_back(sol_2x2_sorted);
//
//    TEST_SET_POPULATION(gen, population);
//    TEST_SET_BEST_SOLUTION(gen, best_solution);
//
//    int previous_fitness = Genetic::fitness(best_solution, &inputs_2x2);
//    TEST_SET_BEST_FITNESS(gen, previous_fitness);
//
//    gen.update_best_solution();
//
//    ASSERT_NE(gen.best_fitness(), previous_fitness);
//}


class MockSolution : public Solution {

    public:
        MockSolution(int nurses, int treatment, std::vector<int> code) :
        Solution{nurses, treatment, code}{}

        MOCK_METHOD((std::pair<int, int>), longest_serial_walk_distance, (int nurse), ());

};

TEST_F(GeneticTest, fitness){

    // Each nurse covers one side of the square of length 2000
    EXPECT_EQ(sol_2x2_sorted.fitness(0), -1);
    EXPECT_EQ(sol_2x2_sorted.fitness(1), -1);
    EXPECT_EQ(gen.fitness(sol_2x2_sorted, &inputs_2x2), 4000);
    EXPECT_EQ(sol_2x2_sorted.fitness(0), 2000);
    EXPECT_EQ(sol_2x2_sorted.fitness(1), 2000);

    // Check that a pre calculated fitness is not re calculated
    sol_2x2_sorted.fitness(0, 3);
    EXPECT_EQ(gen.fitness(sol_2x2_sorted, &inputs_2x2), 2003);

    // Each nurse joins diagonally opposed points
    Solution sol_2x2_diag = Solution(2, 2, {0, 2, 1, 3});
    EXPECT_EQ(gen.fitness(sol_2x2_diag, &inputs_2x2), 8000);

    // Walking distances are not taken into account
    // Here patient 1 and patient 2 are distant from a walking distance
    // We take into account where the car was left
    Inputs inputs_walk = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs_walk.add_nurse(Nurse(0));
    inputs_walk.add_patient(Patient(0, Point(0, 0), 0, 0));
    inputs_walk.add_patient(Patient(1, Point(0, 3), 1, 0));
    inputs_walk.add_patient(Patient(2, Point(0, 2000), 2, 0));
    inputs_walk.add_patient(Patient(3, Point(0, 3), 3, 0));
    Solution sol1x3 = Solution(1, 4, {0, 1, 2, 3});
    EXPECT_EQ(gen.fitness(sol1x3, &inputs_walk), 3997);
    EXPECT_EQ(sol1x3.fitness(0), 3997);
}

TEST_F(GeneticTest, crossover){
    std::cout << sol_3x3_sorted << std::endl;
    std::cout << sol_3x3_random << std::endl;
    TEST_SET_DISTANCES(sol_3x3_sorted, {0, 0, 4, 10, 0, 0});
    TEST_SET_DISTANCES(sol_3x3_random, {0, 0, 0, 0, 5, 4});

    std::pair<Solution, Solution> sol = gen.crossover(sol_3x3_sorted, sol_3x3_random, 0.6, 4);
    std::cout << sol.first << std::endl;
    std::cout << sol.second << std::endl;
}


// Clusters with 10 patients per cluster (= number of patients per nurse)
TEST_F(GeneticTest, algo_cluster){
    Inputs inputs_clusters = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs_clusters.add_type(flu);
    int nurses = 50, patients_per_nurse = 10, patient_counter = 0;
    for (int i = 0; i < nurses; ++i)
    {
        inputs_clusters.add_nurse(Nurse(i));
        for (int j = 0; j < patients_per_nurse; ++j)
        {
            inputs_clusters.add_patient(Patient(patient_counter, Point(i * 1500, j * 10), patient_counter, 0));
            ++patient_counter;
        }
    }
    Genetic gen(&inputs_clusters);
    gen.process();
    ASSERT_EQ(TEST_GET_BEST_FITNESS(gen), 0);
}


// Patients are scattered around the map equally distributed
TEST_F(GeneticTest, algo_grid){
    Inputs inputs_grid = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs_grid.add_type(flu);
    int nurses = 20, patients_per_nurse = 10, patient_counter = 0;
    for (int i = 0; i < nurses; ++i)
    {
        inputs_grid.add_nurse(Nurse(i));
        for (int j = 0; j < patients_per_nurse; ++j)
        {
            inputs_grid.add_patient(Patient(patient_counter, Point(i * 400, j * 400), patient_counter, 0));
            ++patient_counter;
        }
    }
    Genetic gen(&inputs_grid, 100, 0.5, 0.006, 10000);
    gen.process();
    ASSERT_EQ(TEST_GET_BEST_FITNESS(gen), 0);
}