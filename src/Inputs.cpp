#include "Inputs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Nurse.h"
#include "Patient.h"

Inputs::Inputs()
{}

Inputs::Inputs(std::vector<Nurse> nurses, std::vector<Patient> patients)
    :m_nurses(nurses), m_patients(patients)
{
    // Set nurse indexes
    for (int i = 0, len = m_nurses.size(); i < len; ++i)
    {
        m_nurses[i].index(i);
    }
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
    nurse.index(m_nurses.size());
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
    // Convert nurses number to string
    std::stringstream sstream_nurses;
    sstream_nurses << nurses_size();
    std::string nurse_nb = sstream_nurses.str();

    // Add nurses to the string
    std::string str = "*** " + nurse_nb + " nurse(s) ***";
    for (int i = 0, len = m_nurses.size(); i < len; ++i)
    {
        str = str + "\n" + m_nurses[i].to_string();
        if (i < len - 1)
        {
            str = str + ",";
        }
    }

    // Convert nurses number to string
    std::stringstream sstream_patients;
    sstream_patients << patients_size();
    std::string patient_nb = sstream_patients.str();

    // Add patients to the string
    str = str + "\n\n*** " + patient_nb + " patient(s) ***";
    for (int i = 0, len = m_patients.size(); i < len; ++i)
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
