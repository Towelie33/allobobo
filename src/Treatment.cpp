#include "Treatment.h"
#include <iostream>
#include <string>
#include "TreatmentType.h"
#include "TimeInterval.h"

Treatment::Treatment(TreatmentType type, TimeInterval schedule)
    :m_type(type), m_schedule(schedule), m_is_scheduled(false)
{}

std::string Treatment::to_string() const
{
    // Convert boolean is_scheduled to string
    std::string is_scheduled = "false";
    if (m_is_scheduled)
    {
        is_scheduled = "true";
    }

    return "{ type: " + m_type.to_string()
         + ", schedule: " + m_schedule.to_string()
         + ", is scheduled: " + is_scheduled
         + " }";
}

bool operator==(Treatment const& treatment1, Treatment const& treatment2)
{
    return (treatment1.type() == treatment2.type())
        && (treatment1.schedule() == treatment2.schedule())
        && (treatment1.is_scheduled() == treatment2.is_scheduled());
}

std::ostream& operator<<(std::ostream &flux, Treatment const& treatment)
{
    std::cout << treatment.to_string();
    return flux;
}
