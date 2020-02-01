#include "../include/Inputs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../include/Utils.h"
#include "../include/Nurse.h"
#include "../include/Patient.h"
//#include <cpprest/json.h>

Inputs::Inputs(int car_speed, int walk_speed, int min_car_dist)
    :m_car_speed(car_speed), m_walk_speed(walk_speed), m_min_car_dist(min_car_dist)
{}

Inputs::Inputs(int car_speed, int walk_speed, int min_car_dist,
               std::vector<TreatmentType> types, std::vector<Nurse> nurses, std::vector<Patient> patients)
    :m_car_speed(car_speed), m_walk_speed(walk_speed), m_min_car_dist(min_car_dist),
    m_types(types), m_nurses(nurses), m_patients(patients)
{}
/*
Inputs::Inputs(web::json::object const& jobject)
	:m_car_speed(jobject.at(L"carSpeed").as_integer()), 
	m_walk_speed(jobject.at(L"walkSpeed").as_integer()), 
	m_min_car_dist(jobject.at(L"minCarDist").as_integer())
{
	// Set treatment types
	web::json::array types = jobject.at(L"treatmentTypes").as_array();
	for (auto const& type: types)
	{
		m_types.push_back(TreatmentType(type.as_object()));
	}

	// Set nurses
	web::json::array nurses = jobject.at(L"nurses").as_array();
	for (auto const& nurse: nurses)
	{
		m_nurses.push_back(Nurse(nurse.as_object()));
	}

	// Set patients
	web::json::array patients = jobject.at(L"patients").as_array();
	for (auto const& patient: patients)
	{
		m_patients.push_back(Patient(patient.as_object()));
	}
}
*/
TreatmentType* Inputs::get_type_by_index(int i)
{
    if (i >= 0 && i < types_size())
    {
        return &m_types[i];
    }
    return nullptr;
}

TreatmentType* Inputs::get_type_by_id(unsigned int id)
{
	for (int i = 0, len = types_size(); i < len; ++i)
	{
		if (m_types[i].id() == id)
		{
			return &m_types[i];
		}
	}
	return nullptr;
}

void Inputs::add_type(TreatmentType type)
{
    m_types.push_back(type);
}

Nurse* Inputs::get_nurse(int i)
{
    if (i >= 0 && i < nurses_size())
    {
        return &m_nurses[i];
    }
    return nullptr;
}

void Inputs::add_nurse(Nurse nurse)
{
    m_nurses.push_back(nurse);
}

Patient* Inputs::get_patient(int i)
{
    if (i >= 0 && i < patients_size())
    {
        return &m_patients[i];
    }
    return nullptr;
}

void Inputs::add_patient(Patient patient)
{
    m_patients.push_back(patient);
}

int Inputs::treatments_size() const
{
    int res = 0;
    for (Patient const& patient: m_patients)
    {
        res += patient.treatments_size();
    }
    return res;
}

int Inputs::treatments_left() const
{
    int res = 0;
    for (Patient const& patient: m_patients)
    {
        res += patient.treatments_left();
    }
    return res;
}

int Inputs::treatments_per_nurse() const
{
    int nurses = nurses_size();
    if (nurses == 0)
    {
        return 0;
    }
    return treatments_size() / nurses;
}

void Inputs::reset()
{
    // Reset nurses position
    for (Nurse& nurse: m_nurses)
    {
        nurse.reset();
    }

    // Reset patients treatments
    for (Patient& patient: m_patients)
    {
        patient.reset();
    }
}

std::string Inputs::to_string() const
{
    // Add consts to the string
    std::string str = "*** Consts ***";
    str = str + "\nCar speed: " + int_to_string(m_car_speed);
    str = str + "\nWalk speed: " + int_to_string(m_walk_speed);
    str = str + "\nMin car speed: " + int_to_string(m_min_car_dist);

    // Add types to the string
    str = str + "\n\n*** " + int_to_string(types_size()) + " Treatment type(s) ***";
    for (int i = 0, len = types_size(); i < len; ++i)
    {
        str = str + "\n" + m_types[i].to_string();
        if (i < len - 1)
        {
            str = str + ",";
        }
    }

    // Add nurses to the string
    str = str + "\n\n*** " + int_to_string(nurses_size()) + " Nurse(s) ***";
    for (int i = 0, len = nurses_size(); i < len; ++i)
    {
        str = str + "\n" + m_nurses[i].to_string();
        if (i < len - 1)
        {
            str = str + ",";
        }
    }

    // Add patients to the string
    str = str + "\n\n*** " + int_to_string(patients_size()) + " Patient(s) ***";
    for (int i = 0, len = patients_size(); i < len; ++i)
    {
        str = str + "\n" + m_patients[i].to_string();
        if (i < len - 1)
        {
            str = str + ",";
        }
    }

    return str;
}

std::ostream& operator<<(std::ostream &flux, Inputs const& inputs)
{
    std::cout << inputs.to_string();
    return flux;
}
