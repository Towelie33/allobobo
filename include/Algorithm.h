#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"
#include "Point.h"
#include "Time.h"
#include "Treatment.h"
#include "Patient.h"
#include "Nurse.h"
#include "Appointment.h"
#include "Inputs.h"

class Algorithm
{
    public:

        Algorithm(Inputs *inputs, short speed);

        virtual ~Algorithm();

        int appointments_size() const { return m_appointments.size(); }

        void reset_inputs() const;

        Treatment* is_available(Patient* patient, Time const& time, Nurse const& nurse) const;
        Appointment* nearest_appointment(Nurse const& nurse);

        void run();

        virtual void find_appointments() = 0;

        std::string to_string() const;


    protected:

        // The inputs
        Inputs *m_inputs;

        // The output
        std::vector<Appointment*> m_appointments;

        // The average car speed
        const short m_speed;
};

std::ostream& operator<<(std::ostream &flux, Algorithm const& algo);

#endif // ALGORITHM_H
