#include "TreatmentType.h"
#include <iostream>
#include <string>
#include "Time.h"

TreatmentType::TreatmentType(std::string name, Time duration)
    :m_name(name), m_duration(duration)
{}

TreatmentType::TreatmentType(std::string name, short duration)
    :m_name(name), m_duration(Time(duration))
{}

std::string TreatmentType::to_string() const
{
    return "{ name: " + m_name
         + ", duration: " + m_duration.to_string()
         + " }";
}

bool operator==(TreatmentType const& type1, TreatmentType const& type2)
{
    return (type1.name() == type2.name())
        && (type1.duration() == type2.duration());
}

std::ostream& operator<<(std::ostream &flux, TreatmentType const& type)
{
    std::cout << type.to_string();
    return flux;
}
