#include "Appointment.h"
#include <iostream>
#include <string>
#include "Point.h"
#include "TimeInterval.h"
#include "Treatment.h"

Appointment::Appointment(Point location, TimeInterval schedule, Treatment *treatment)
    :m_location(location), m_schedule(schedule), m_treatment(treatment)
{}

std::string Appointment::to_string() const
{
    return "{\n  location: " + m_location.to_string()
         + ",\n  schedule: " + m_schedule.to_string()
         + ",\n  treatment: " + m_treatment->type().name()
         + "\n}";
}

std::ostream& operator<<(std::ostream &flux, Appointment const& appointment)
{
    std::cout << appointment.to_string();
    return flux;
}
