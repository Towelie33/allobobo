#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"
#include "TreatmentType.h"
#include "Treatment.h"

class Patient
{
    public:

        Patient();
        Patient(Point location, std::vector<Treatment> treatments);
        Patient(Point location, Treatment treatment);
        Patient(Point location, TreatmentType type);

        Point location() const { return m_location; }
        std::vector<Treatment> treatments() const { return m_treatments; }

        int treatments_size() const { return m_treatments.size(); }
        int treatments_left() const;

        Treatment* get_treatment(int i);
        void add_treatment(Treatment treatment);

        void reset();

        std::string treatments_to_string() const;
        std::string to_string() const;


    private:

        Point m_location;
        std::vector<Treatment> m_treatments;
};

bool operator==(Patient const& patient1, Patient const& patient2);
std::ostream& operator<<(std::ostream &flux, Patient const& patient);

#endif // PATIENT_H
