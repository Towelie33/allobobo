#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
#include "Point.h"
#include "TimeInterval.h"
#include "Treatment.h"

class Appointment
{
    public:

        Appointment(Point location, TimeInterval schedule, Treatment *treatment);

        Point location() const { return m_location; }
        TimeInterval schedule() const { return m_schedule; }
        Treatment* treatment() const { return m_treatment; }

        std::string to_string() const;


    private:

        Point m_location;
        TimeInterval m_schedule;
        Treatment *m_treatment;
};

std::ostream& operator<<(std::ostream &flux, Appointment const& appointment);

#endif // APPOINTMENT_H
