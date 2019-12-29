#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <string>
#include <vector>
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

        void initialize_appointments();
        void reset_inputs() const;

        Treatment* is_available(Patient* patient, Time const& time, Nurse const& nurse) const;
        Appointment* nearest_appointment(Nurse const& nurse);

        void run();

        virtual void find_appointments() = 0;

        std::string to_string() const;


    protected:

        Inputs *m_inputs;
        std::vector<std::vector<Appointment*> > m_appointments;

        short m_speed;
};

std::ostream& operator<<(std::ostream &flux, Algorithm const& algo);

class ComparePointers
{
    public:

        template<typename T>
        bool operator()(T *a, T *b) { return (*a) < (*b); }
};

#endif // ALGORITHM_H
