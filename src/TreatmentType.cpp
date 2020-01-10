#include "TreatmentType.h"
#include <iostream>
#include <string>
#include "Utils.h"
#include "Time.h"

TreatmentType::TreatmentType(unsigned int id, Time duration)
    :m_id(id), m_duration(duration)
{}

TreatmentType::TreatmentType(unsigned int id, short duration)
    :m_id(id), m_duration(Time(duration))
{}

std::string TreatmentType::to_string() const
{
    return "{ _id: " + int_to_string(m_id)
         + ", duration: " + m_duration.to_string()
         + " }";
}

bool operator==(TreatmentType const& type1, TreatmentType const& type2)
{
    return (type1.id() == type2.id());
}

std::ostream& operator<<(std::ostream &flux, TreatmentType const& type)
{
    std::cout << type.to_string();
    return flux;
}
