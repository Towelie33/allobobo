#include "Inputs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Utils.h"
#include "Nurse.h"
#include "Patient.h"

Inputs::Inputs()
{}

Inputs::Inputs(std::vector<TreatmentType> types, std::vector<Nurse> nurses, std::vector<Patient> patients)
    :m_types(types), m_nurses(nurses), m_patients(patients)
{}

TreatmentType* Inputs::get_type(int i)
{
    if (i >= 0 && i < types_size())
    {
        return &m_types[i];
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
    // Add types to the string
    std::string str = "*** " + int_to_string(types_size()) + " treatment type(s) ***";
    for (int i = 0, len = types_size(); i < len; ++i)
    {
        str = str + "\n" + m_types[i].to_string();
        if (i < len - 1)
        {
            str = str + ",";
        }
    }

    // Add nurses to the string
    str = str + "\n\n*** " + int_to_string(nurses_size()) + " nurse(s) ***";
    for (int i = 0, len = nurses_size(); i < len; ++i)
    {
        str = str + "\n" + m_nurses[i].to_string();
        if (i < len - 1)
        {
            str = str + ",";
        }
    }

    // Add patients to the string
    str = str + "\n\n*** " + int_to_string(patients_size()) + " patient(s) ***";
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
