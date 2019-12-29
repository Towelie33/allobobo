#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <string>
#include <vector>
#include "Nurse.h"
#include "Patient.h"

class Inputs
{
    public:

        Inputs();
        Inputs(std::vector<Nurse> nurses, std::vector<Patient> patients);

        std::vector<Nurse> nurses() { return m_nurses; }
        std::vector<Patient> patients() { return m_patients; }

        int nurses_size() const { return m_nurses.size(); }
        int patients_size() const { return m_patients.size(); }

        Nurse* get_nurse(int i);
        void add_nurse(Nurse nurse);
        Patient* get_patient(int i);
        void add_patient(Patient patient);

        int treatments_size() const;
        int treatments_left() const;

        void reset();

        std::string to_string() const;


    private:

        std::vector<Nurse> m_nurses;
        std::vector<Patient> m_patients;
};

std::ostream& operator<<(std::ostream &flux, Inputs const& inputs);

#endif // INPUTS_H
