#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"
#include "TreatmentType.h"
#include "Treatment.h"
//#include <cpprest/json.h>

class Patient
{
    public:

        Patient(unsigned int id);
        Patient(unsigned int id, Point location, std::vector<Treatment> treatments);
        Patient(unsigned int id, Point location, Treatment treatment);
        Patient(unsigned int id, Point location, unsigned int treatment_id, unsigned int type_id);
	//Patient(web::json::object const& jobject);

        unsigned int id() const { return m_id; }
        Point location() const { return m_location; }
        std::vector<Treatment> treatments() const { return m_treatments; }

        int treatments_size() const { return m_treatments.size(); }
        int treatments_left() const;

        Treatment* get_treatment_by_index(int i);
        Treatment* get_treatment_by_id(unsigned int id);
        void add_treatment(Treatment treatment);

        void reset();

        std::string treatments_to_string() const;
        std::string to_string() const;


    private:

        const unsigned int m_id;
        const Point m_location;
        std::vector<Treatment> m_treatments;
};

bool operator==(Patient const& patient1, Patient const& patient2);
std::ostream& operator<<(std::ostream &flux, Patient const& patient);

#endif // PATIENT_H
