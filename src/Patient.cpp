#include "Patient.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Point.h"
#include "TreatmentType.h"
#include "Treatment.h"

Patient::Patient()
    :m_location(Point())
{}

Patient::Patient(Point location, std::vector<Treatment> treatments)
    :m_location(location), m_treatments(treatments)
{}

Patient::Patient(Point location, Treatment treatment)
    :m_location(location)
{
    m_treatments.push_back(treatment);
}

Patient::Patient(Point location, TreatmentType type)
    :m_location(location)
{
    m_treatments.push_back(Treatment(type, TimeInterval::GET_FULL_DAY()));
}

int Patient::treatments_left() const
{
    int res = 0;
    for (Treatment const& treatment: m_treatments)
    {
        if (!treatment.is_scheduled())
        {
            ++res;
        }
    }
    return res;
}

Treatment* Patient::get_treatment(int i)
{
    if (i >= 0 && i < treatments_size())
    {
        return &m_treatments[i];
    }
    return nullptr;
}

void Patient::add_treatment(Treatment treatment)
{
    m_treatments.push_back(treatment);
}

void Patient::reset()
{
    for (Treatment& treatment: m_treatments)
    {
        treatment.is_scheduled(false);
    }
}

std::string Patient::treatments_to_string() const
{
    std::string str = "[ ";

    for (int i = 0, len = treatments_size(); i < len; ++i)
    {
        str = str + "{ " + m_treatments[i].type().name() + ", " + m_treatments[i].schedule().to_string() + " }";
        if (i < len - 1)
        {
            str = str + ", ";
        }
    }
    str = str + " ]";

    return str;
}

std::string Patient::to_string() const
{
    return "{\n  location: " + m_location.to_string()
         + ",\n  treatments: " + treatments_to_string()
         + "\n}";
}

bool operator==(Patient const& patient1, Patient const& patient2)
{
    return (patient1.location() == patient2.location())
        && (patient1.treatments() == patient2.treatments());
}

std::ostream& operator<<(std::ostream &flux, Patient const& patient)
{
    std::cout << patient.to_string();
    return flux;
}
