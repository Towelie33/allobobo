#include "Appointment.h"
#include <iostream>
#include <string>
#include "Utils.h"
#include "Point.h"
#include "TimeInterval.h"
#include "Treatment.h"

Appointment::Appointment(unsigned int nurse_id, Patient *patient, unsigned int treatment_id, TimeInterval schedule)
    :m_nurse_id(nurse_id), m_patient(patient), m_treatment_id(treatment_id), m_schedule(schedule)
{}

std::string Appointment::to_string() const
{
    return "{\n  nurse id: " + int_to_string(m_nurse_id)
         + ",\n  patient: { id: " + int_to_string(m_patient->id()) + ", location: " + location().to_string() + " }"
         + ",\n  treatment id: " + int_to_string(m_treatment_id)
         + ",\n  schedule: " + m_schedule.to_string()
         + "\n}";
}

std::ostream& operator<<(std::ostream &flux, Appointment const& appointment)
{
    std::cout << appointment.to_string();
    return flux;
}
