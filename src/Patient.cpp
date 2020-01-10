#include "Patient.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Utils.h"
#include "Point.h"
#include "TreatmentType.h"
#include "Treatment.h"

Patient::Patient(unsigned int id)
    :m_id(id), m_location(Point())
{}

Patient::Patient(unsigned int id, Point location, std::vector<Treatment> treatments)
    :m_id(id), m_location(location), m_treatments(treatments)
{}

Patient::Patient(unsigned int id, Point location, Treatment treatment)
    :m_id(id), m_location(location)
{
    m_treatments.push_back(treatment);
}

Patient::Patient(unsigned int id, Point location, unsigned int treatment_id, TreatmentType type)
    :m_id(id), m_location(location)
{
    m_treatments.push_back(Treatment(treatment_id, type, TimeInterval::GET_FULL_DAY()));
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

Treatment* Patient::get_treatment_by_index(int i)
{
    if (i >= 0 && i < treatments_size())
    {
        return &m_treatments[i];
    }
    return nullptr;
}

Treatment* Patient::get_treatment_by_id(unsigned int id)
{
    for (int i = 0, len = treatments_size(); i < len; ++i)
    {
        Treatment *treatment = &m_treatments[i];
        if (treatment->id() == id)
        {
            return treatment;
        }
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
        str = str + "{ _id: " + int_to_string(m_treatments[i].id())
            + ", type id: " + int_to_string(m_treatments[i].type().id())
            + ", schedule: " + m_treatments[i].schedule().to_string() + " }";
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
    return "{\n  _id: " + int_to_string(m_id)
         + ",\n  location: " + m_location.to_string()
         + ",\n  treatments: " + treatments_to_string()
         + "\n}";
}

bool operator==(Patient const& patient1, Patient const& patient2)
{
    return (patient1.id() == patient2.id());
}

std::ostream& operator<<(std::ostream &flux, Patient const& patient)
{
    std::cout << patient.to_string();
    return flux;
}
