#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"
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
    Inputs inputs1 = Inputs();
    inputs1.add_type(flu);
    inputs1.add_type(cancer);
    inputs1.add_nurse(Nurse(0, cancer));
    inputs1.add_patient(Patient(0, Point(0, 1000), 0, flu));
    inputs1.add_patient(Patient(1, Point(1000, 2000), 1, flu));

    Inputs inputs2 = Inputs();
    inputs2.add_type(flu);
    inputs2.add_type(cancer);
    inputs2.add_nurse(Nurse(0));
    inputs2.add_nurse(Nurse(1, cancer));
    inputs2.add_patient(Patient(0, Point(0, 1000), 0, flu));
    inputs2.add_patient(Patient(1, Point(1000, 2000), 1, flu));

    Inputs random_inputs = Inputs();
    random_inputs.add_type(flu);
    random_inputs.add_type(cancer);
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
        const Treatment treatment(i, flu, schedule);
        random_inputs.add_patient(Patient(i, point, treatment));
    }

    // Select inputs
    Inputs *inputs = &inputs2;

    /// TEST GLUTTON BREADTH
    test(inputs, Algo(GLUTTON_BREADTH), AVERAGE_CAR_SPEED);
    //*/

    /// TEST GLUTTON DEPTH
    test(inputs, Algo(GLUTTON_DEPTH), AVERAGE_CAR_SPEED);
    //*/

    return 0;
}
