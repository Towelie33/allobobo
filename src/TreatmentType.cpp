#include "../include/TreatmentType.h"
#include <iostream>
#include <string>
#include "../include/Utils.h"
#include "../include/Time.h"
//#include <cpprest/json.h>

TreatmentType::TreatmentType(unsigned int id, Time duration)
    :m_id(id), m_duration(duration)
{}

TreatmentType::TreatmentType(unsigned int id, short duration)
    :m_id(id), m_duration(duration)
{}
/*
TreatmentType::TreatmentType(web::json::object const& jobject)
	:m_id(jobject.at(L"_id").as_integer()), m_duration(Time(jobject.at(L"duration").as_integer()))
{}
*/
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
