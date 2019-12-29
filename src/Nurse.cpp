#include "Nurse.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Point.h"
#include "Time.h"
#include "TimeInterval.h"
#include "TreatmentType.h"

Nurse::Nurse(unsigned short id, Point starting_point, TimeInterval timetable)
    :m_id(id), m_starting_point(starting_point), m_position(starting_point),
    m_timetable(timetable), m_available(timetable.start_time()), m_index(-1)
{}

Nurse::Nurse(unsigned short id, TreatmentType type, Point starting_point, TimeInterval timetable)
    :m_id(id), m_starting_point(starting_point), m_position(starting_point),
    m_timetable(timetable), m_available(timetable.start_time()), m_index(-1)
{
    m_cannot_do.push_back(type);
}

Nurse::Nurse(unsigned short id, std::vector<TreatmentType> cannot_do, Point starting_point, TimeInterval timetable)
    :m_id(id), m_cannot_do(cannot_do), m_starting_point(starting_point), m_position(starting_point),
    m_timetable(timetable), m_available(timetable.start_time()), m_index(-1)
{}

void Nurse::add_treatment_type(TreatmentType const& type)
{
    m_cannot_do.push_back(type);
}

bool Nurse::can_do(TreatmentType const& type) const
{
    return std::find(m_cannot_do.begin(), m_cannot_do.end(), type) == m_cannot_do.end();
}

void Nurse::reset()
{
    m_position = m_starting_point;
    m_available = m_timetable.start_time();
}

std::string Nurse::cannot_do_to_string() const
{
    std::string str = "[ ";

    for (int i = 0, len = m_cannot_do.size(); i < len; ++i)
    {
        str = str + m_cannot_do[i].name();
        if (i < len - 1)
        {
            str = str + ", ";
        }
    }
    str = str + " ]";

    return str;
}

std::string Nurse::to_string() const
{
    // Convert id to string
    std::stringstream sstream_id;
    sstream_id << m_id;
    std::string id = sstream_id.str();

    // Convert index to string
    std::stringstream sstream_idx;
    sstream_idx << m_index;
    std::string idx = sstream_idx.str();

    return "{\n  id: " + id
         + ",\n  cannot do: " + cannot_do_to_string()
         + ",\n  starting point: " + m_starting_point.to_string()
         + ",\n  position: " + m_position.to_string()
         + ",\n  timetable: " + m_timetable.to_string()
         + ",\n  available: " + m_available.to_string()
         + ",\n  index: " + idx
         + "\n}";
}

bool operator<(Nurse const& nurse1, Nurse const& nurse2)
{
    return nurse2.available() < nurse1.available();
}

std::ostream& operator<<(std::ostream &flux, Nurse const& nurse)
{
    std::cout << nurse.to_string();
    return flux;
}
