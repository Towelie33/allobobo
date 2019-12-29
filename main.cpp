#include <iostream>
#include <string>
#include <vector>

#include "Point.h"
#include "Time.h"
#include "TimeInterval.h"
#include "TreatmentType.h"
#include "Treatment.h"
#include "Nurse.h"
#include "Patient.h"
#include "Appointment.h"
#include "Inputs.h"
#include "Algorithm.h"
#include "GluttonBreadth.h"
#include "GluttonDepth.h"

/* CONSTS */
static const short AVERAGE_CAR_SPEED = 15; // in km/h
static const Point ORIGIN = Point(0, 0);
static const TimeInterval FULL_DAY = TimeInterval(6 * 60, 20 * 60);
static const Time START_TIME = FULL_DAY.start_time(), END_TIME = FULL_DAY.end_time();

enum Algo
{
    GLUTTON_BREADTH,
    GLUTTON_DEPTH
};

void test(Inputs *inputs, Algo algo_name)
{
    // Initialize algo
    Algorithm *algo = 0;
    switch (algo_name)
    {
        case GLUTTON_BREADTH:
            std::cout << "GLUTTON BREADTH" << std::endl << std::endl;
            algo = new GluttonBreadth(inputs, AVERAGE_CAR_SPEED);
            break;

        case GLUTTON_DEPTH:
            std::cout << "GLUTTON DEPTH" << std::endl << std::endl;
            algo = new GluttonDepth(inputs, AVERAGE_CAR_SPEED);
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

/*
 * returns a random number between >= inf and <= sup
 */
short random(short inf, short sup)
{
    return inf + (rand() % (sup - inf + 1));
}

int main()
{
    // Set random seed
    srand(4895);

    // Set static attributes
    Point::SET_ORIGIN(ORIGIN);
    TimeInterval::SET_FULL_DAY(FULL_DAY);

    // Treatment types
    TreatmentType flu = TreatmentType("Influenza", 30);
    TreatmentType cancer = TreatmentType("Cancer", 90);

    // Inputs
    Inputs inputs1 = Inputs();
    inputs1.add_nurse(Nurse(42, cancer));
    inputs1.add_patient(Patient(Point(0, 1000), flu));
    inputs1.add_patient(Patient(Point(1000, 2000), flu));

    Inputs inputs2 = Inputs();
    inputs2.add_nurse(Nurse(0));
    inputs2.add_nurse(Nurse(1, cancer));
    inputs2.add_patient(Patient(Point(0, 1000), flu));
    inputs2.add_patient(Patient(Point(1000, 2000), flu));

    Inputs random_inputs = Inputs();
    const short nurses_min = 2, nurses_max = 4, patients_min = 8, patients_max = 15;
    const short nurse_duration = 7, delta_start = 12, min_duration = 2, max_duration = 14; // in hours
    const short min_xy = -10 * 1000, max_xy = 10 * 1000; // in m
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
        const Treatment treatment(flu, schedule);
        random_inputs.add_patient(Patient(point, treatment));
    }

    // Select inputs
    Inputs *inputs = &inputs2;

    /// TEST GLUTTON BREADTH
    test(inputs, Algo(GLUTTON_BREADTH));
    //*/

    /// TEST GLUTTON DEPTH
    test(inputs, Algo(GLUTTON_DEPTH));
    //*/

    return 0;
}
