#include "Algorithm.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Point.h"
#include "Time.h"
#include "TimeInterval.h"
#include "TreatmentType.h"
#include "Treatment.h"
#include "Patient.h"
#include "Nurse.h"
#include "Appointment.h"
#include "Inputs.h"

Algorithm::Algorithm(Inputs *inputs, short speed)
    :m_inputs(inputs), m_speed(speed)
{}

Algorithm::~Algorithm()
{
    // Delete appointments
    for (int i = 0, len = appointments_size(); i < len; ++i)
    {
        for (Appointment* appointment: m_appointments[i])
        {
            delete appointment;
        }
    }
}

void Algorithm::initialize_appointments()
{
    for (int i = 0, len = m_inputs->nurses_size(); i < len; ++i)
    {
        m_appointments.push_back(std::vector<Appointment*>());
    }
}

void Algorithm::reset_inputs() const
{
    m_inputs->reset();
}

Treatment* Algorithm::is_available(Patient *patient, Time const& time, Nurse const& nurse) const
{
    for (int i = 0, len = patient->treatments_size(); i < len; ++i)
    {
        Treatment *treatment = patient->get_treatment(i);
        if (!treatment->is_scheduled() && treatment->schedule().contains(time) && nurse.can_do(treatment->type()))
        {
            return treatment;
        }
    }
    return nullptr;
}

Appointment* Algorithm::nearest_appointment(Nurse const& nurse)
{
    Appointment *appointment = nullptr;
    long min_distance = -1;

    for (int i = 0, len = m_inputs->patients_size(); i < len; ++i)
    {
        Patient *patient = m_inputs->get_patient(i);
        long dist = distance(nurse.position(), patient->location());
        if (dist < min_distance || min_distance < 0)
        {
            Time arrival = nurse.available() + time_to_go(dist, m_speed);
            Treatment *treatment = is_available(patient, arrival, nurse);
            if (treatment != nullptr)
            {
                Time end_time = arrival + treatment->type().duration();
                if (end_time <= nurse.timetable().end_time())
                {
                    appointment = new Appointment(patient->location(), TimeInterval(arrival, end_time), treatment);
                    min_distance = dist;
                }
            }
        }
    }

    return appointment;
}

void Algorithm::run()
{
    // Initialize appointments
    initialize_appointments();

    // Find appointments
    find_appointments();

    // Reset inputs
    reset_inputs();
}

std::string Algorithm::to_string() const
{
    std::string str = "*** Appointments ***";

    for (int i = 0, len_i = appointments_size(); i < len_i; ++i)
    {
        // Convert nurse id to string
        std::stringstream sstream;
        sstream << m_inputs->nurses()[i].id();
        std::string id = sstream.str();

        str = str + "\n\nNurse ID " + id + ": [";
        for (int j = 0, len_j = m_appointments[i].size(); j < len_j; ++j)
        {
            str = str + "\n" + m_appointments[i][j]->to_string();
            if (j < len_j - 1)
            {
                str = str + ",";
            }
        }
        str = str + " ]";
    }

    return str;
}

std::ostream& operator<<(std::ostream &flux, Algorithm const& algo)
{
    std::cout << algo.to_string();
    return flux;
}
