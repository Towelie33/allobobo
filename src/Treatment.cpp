#include "../include/Treatment.h"
#include <iostream>
#include <string>
#include "../include/Utils.h"
#include "../include/TreatmentType.h"
#include "../include/TimeInterval.h"
//#include <cpprest/json.h>

Treatment::Treatment(unsigned int id, unsigned int type_id, TimeInterval schedule)
    :m_id(id), m_type_id(type_id), m_schedule(schedule), m_is_scheduled(false)
{}
/*
Treatment::Treatment(web::json::object const& jobject)
	:m_id(jobject.at(L"_id").as_integer()), m_type_id(jobject.at(L"treatmentTypeId").as_integer()), 
	m_schedule(jobject.at(L"schedule").as_object()), m_is_scheduled(false)
{}
*/
std::string Treatment::to_string() const
{
    // Convert boolean is_scheduled to string
    std::string is_scheduled = "false";
    if (m_is_scheduled)
    {
        is_scheduled = "true";
    }

    return "{ _id: " + int_to_string(m_id)
         + ", type id: " + int_to_string(m_type_id)
         + ", schedule: " + m_schedule.to_string()
         + ", is scheduled: " + is_scheduled
         + " }";
}

bool operator==(Treatment const& treatment1, Treatment const& treatment2)
{
    return (treatment1.id() == treatment2.id());
}

std::ostream& operator<<(std::ostream &flux, Treatment const& treatment)
{
    std::cout << treatment.to_string();
    return flux;
}
