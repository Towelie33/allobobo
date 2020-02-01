#include "../include/Nurse.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../include/Utils.h"
#include "../include/Point.h"
#include "../include/Time.h"
#include "../include/TimeInterval.h"
#include "../include/TreatmentType.h"
//#include <cpprest/json.h>

Nurse::Nurse(unsigned int id, Point starting_point, TimeInterval timetable)
    :m_id(id), m_starting_point(starting_point), m_position(starting_point),
    m_timetable(timetable), m_available(timetable.start_time())
{}

Nurse::Nurse(unsigned int id, unsigned int type_id, Point starting_point, TimeInterval timetable)
    :m_id(id), m_starting_point(starting_point), m_position(starting_point),
    m_timetable(timetable), m_available(timetable.start_time())
{
    m_cannot_do.push_back(type_id);
}

Nurse::Nurse(unsigned int id, std::vector<unsigned int> cannot_do, Point starting_point, TimeInterval timetable)
    :m_id(id), m_cannot_do(cannot_do), m_starting_point(starting_point), m_position(starting_point),
    m_timetable(timetable), m_available(timetable.start_time())
{}
/*
Nurse::Nurse(web::json::object const& jobject)
	:m_id(jobject.at(L"_id").as_integer()), 
	m_starting_point(jobject.at(L"position").as_object()), 
	m_timetable(jobject.at(L"timetable").as_object())
{
	// Set cannot_do
	web::json::array type_ids = jobject.at(L"treatmentTypeIds").as_array();
	for (auto const& type_id: type_ids)
	{
		m_cannot_do.push_back(type_id.as_integer());
	}

	m_position = m_starting_point;
	m_available = m_timetable.start_time();
}
*/
void Nurse::add_treatment_type(unsigned int type_id)
{
    m_cannot_do.push_back(type_id);
}

bool Nurse::can_do(unsigned int type_id) const
{
    return std::find(m_cannot_do.begin(), m_cannot_do.end(), type_id) == m_cannot_do.end();
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
        str = str + int_to_string(m_cannot_do[i]);
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
    return "{\n  _id: " + int_to_string(m_id)
         + ",\n  cannot do: " + cannot_do_to_string()
         + ",\n  starting point: " + m_starting_point.to_string()
         + ",\n  position: " + m_position.to_string()
         + ",\n  timetable: " + m_timetable.to_string()
         + ",\n  available: " + m_available.to_string()
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
