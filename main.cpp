#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "include/Utils.h"
#include "include/Point.h"
#include "include/Time.h"
#include "include/TimeInterval.h"
#include "include/TreatmentType.h"
#include "include/Treatment.h"
#include "include/Nurse.h"
#include "include/Patient.h"
#include "include/Appointment.h"
#include "include/Inputs.h"
#include "include/Algorithm.h"
#include "include/GluttonBreadth.h"
#include "include/GluttonDepth.h"
#include "include/Solution.h"
#include "include/Genetic.h"

#include "include/WebServer.h"

/* CONSTS */
static const short CAR_SPEED = 15; // in km/h
static const short WALK_SPEED = 5; // in km/h
static const short MIN_CAR_DIST = 1000; // in m
static const Point ORIGIN = Point(0, 0);
static const TimeInterval FULL_DAY = TimeInterval(6 * 60, 20 * 60);
static const Time START_TIME = FULL_DAY.start_time(), END_TIME = FULL_DAY.end_time();

int main()
{
    // Set random seed
    srand(4895);

    // Set static attributes
    Point::SET_ORIGIN(ORIGIN);
    TimeInterval::SET_FULL_DAY(FULL_DAY);

    // Treatment types
    TreatmentType flu = TreatmentType(0, 30);
    TreatmentType cancer = TreatmentType(1, 90);

    // Inputs
    Inputs inputs1 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs1.add_type(flu);
    inputs1.add_type(cancer);
    inputs1.add_nurse(Nurse(0, 1));
    inputs1.add_patient(Patient(0, Point(0, 1000), 0, 0));
    inputs1.add_patient(Patient(1, Point(1000, 2000), 1, 0));

    Inputs inputs2 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs2.add_type(flu);
    inputs2.add_type(cancer);
    inputs2.add_nurse(Nurse(0));
    inputs2.add_nurse(Nurse(1, 1));
    inputs2.add_patient(Patient(0, Point(0, 1000), 0, 0));
    inputs2.add_patient(Patient(1, Point(1000, 2000), 1, 0));

    Inputs inputs3 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs3.add_type(flu);
    inputs3.add_nurse(Nurse(0));
    inputs3.add_nurse(Nurse(1));
    inputs3.add_nurse(Nurse(2));
    inputs3.add_patient(Patient(0, Point(0, 0), 0, 0));
    inputs3.add_patient(Patient(1, Point(0, 100), 1, 0));
    inputs3.add_patient(Patient(2, Point(100, 0), 2, 0));
    inputs3.add_patient(Patient(3, Point(5000, 5000), 3, 0));
    inputs3.add_patient(Patient(4, Point(5000, 5100), 4, 0));
    inputs3.add_patient(Patient(5, Point(5100, 5000), 5, 0));
    inputs3.add_patient(Patient(6, Point(-5000, -5000), 6, 0));
    inputs3.add_patient(Patient(7, Point(-5000, -5100), 7, 0));
    inputs3.add_patient(Patient(8, Point(-5100, -5000), 8, 0));

    Inputs inputs4 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    Inputs inputs5 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    Inputs inputs6 = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    inputs4.add_type(flu);
    inputs5.add_type(flu);
    inputs6.add_type(flu);
    int nurses = 20, treatments_per_nurse = 12, patient_counter = 0;
    for (int i = 0; i < nurses; ++i)
    {
        inputs4.add_nurse(Nurse(i));
        inputs5.add_nurse(Nurse(i));
        inputs6.add_nurse(Nurse(i));
        for (int j = 0; j < treatments_per_nurse; ++j)
        {
            inputs4.add_patient(Patient(patient_counter, Point(400 * patient_counter, 400 * patient_counter), patient_counter, 0));
            inputs5.add_patient(Patient(patient_counter, Point(i * 1500, j * 10), patient_counter, 0));
            inputs6.add_patient(Patient(patient_counter, Point(i * 400, j * 400), patient_counter, 0));
            ++patient_counter;
        }
    }

    Inputs random_inputs = Inputs(CAR_SPEED, WALK_SPEED, MIN_CAR_DIST);
    random_inputs.add_type(flu);
    random_inputs.add_type(cancer);
    const short nurses_min = 8, nurses_max = 8, patients_min = 64, patients_max = 64;
    const short nurse_duration = 7, delta_start = 12, min_duration = 2, max_duration = 14; // in hours
    const short min_xy = -5 * 1000, max_xy = 5 * 1000; // in m
    for (int i = 0, len = random(nurses_min, nurses_max); i < len; ++i)
    {
        const Time start_time = START_TIME + Time(random(0, END_TIME.to_hours() - nurse_duration), 0);
        const TimeInterval timetable(start_time, 60 * nurse_duration);
        random_inputs.add_nurse(Nurse(i, ORIGIN, timetable));
    }
    for (int i = 0, len = random(patients_min, patients_max); i < len; ++i)
    {
        const Point point(random(min_xy, max_xy), random(min_xy, max_xy));
        const Time start_time = START_TIME + Time(random(0, delta_start), 0);
        const short duration = 60 * random(min_duration, max_duration);
        const TimeInterval schedule(start_time, duration);
        const Treatment treatment(i, 0, schedule);
        random_inputs.add_patient(Patient(i, point, treatment));
    }

    // Select inputs
    Inputs *inputs = &inputs5;

    /*// TEST GLUTTON BREADTH
    run_algo(inputs, Algo(GLUTTON_BREADTH));
    //*/

    /*// TEST GLUTTON DEPTH
    run_algo(inputs, Algo(GLUTTON_DEPTH));
    //*/

    /*// TEST PERMUTATIONS
    std::cout << "*** TEST: RANDOM PERMUTATIONS ***" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::vector<int> permutation(generate_random_permutation(9));
        for (int j = 0; j < 9; ++j)
        {
            std::cout << "  " << permutation[j] << std::endl;
        }
    }
    std::cout << std::endl;
    //*/

    /// TEST GENETIC
    /*Genetic gen(inputs, 4);

    std::vector<int> code(9);
    for (int i = 0; i < 9; ++i)
    {
        code[i] = i;
    }
    Solution sol(3, 3, code);
    std::cout << "*** TEST: FITNESS ***" << std::endl << std::endl;
    Genetic::print_solution(sol);
    std::cout << "Fitness (expected 0): " << Genetic::fitness(sol, inputs) << std::endl;
    code[2] = 3;
    code[3] = 2;
    sol = Solution(3, 3, code);
    Genetic::print_solution(sol);
    std::cout << "Fitness (expected 20000): " << Genetic::fitness(sol, inputs) << std::endl << std::endl;

    gen.generate_population();
    std::cout << "*** TEST: GENERATE POPULATION ***" << std::endl << std::endl;
    gen.print_population();
    std::cout << std::endl;

    std::vector<Solution> new_pop;
    gen.selection(new_pop);
    std::cout << "*** TEST: SELECTION ***" << std::endl << std::endl;
    Genetic::print_population(new_pop);
    std::cout << std::endl;
*/
    run_algo(inputs, Algo(GENETIC));
    //*/

    /*// TEST LOCAL SERVER
	std::unique_ptr<WebServer> server;
	utility::string_t address = L"http://localhost";
	utility::string_t port = L"4242";

	server = std::unique_ptr<WebServer>(new WebServer(address + L":" + port));
	server->run();
    //*/

    return 0;
}
