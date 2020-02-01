#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <string>
#include <vector>
#include "Nurse.h"
#include "Patient.h"
//#include <cpprest/json.h>

class Inputs
{
    public:

        Inputs(int car_speed, int walk_speed, int min_car_dist);
        Inputs(int car_speed, int walk_speed, int min_car_dist,
               std::vector<TreatmentType> types, std::vector<Nurse> nurses, std::vector<Patient> patients);
		//Inputs(web::json::object const& jobject);

        int car_speed() const { return m_car_speed; }
        int walk_speed() const { return m_walk_speed; }
        int min_car_dist() const { return m_min_car_dist; }
        std::vector<TreatmentType> types() const { return m_types; }
        std::vector<Nurse> nurses() const { return m_nurses; }
        std::vector<Patient> patients() const { return m_patients; }

        int types_size() const { return m_types.size(); }
        int nurses_size() const { return m_nurses.size(); }
        int patients_size() const { return m_patients.size(); }

        TreatmentType* get_type_by_index(int i);
		TreatmentType* get_type_by_id(unsigned int id);
        void add_type(TreatmentType type);
        Nurse* get_nurse(int i);
        void add_nurse(Nurse nurse);
        Patient* get_patient(int i);
        void add_patient(Patient patient);

        int treatments_size() const;
        int treatments_left() const;
        int treatments_per_nurse() const;

        void reset();

        std::string to_string() const;


    private:

        const int m_car_speed;
        const int m_walk_speed;
        const int m_min_car_dist;

        std::vector<TreatmentType> m_types;
        std::vector<Nurse> m_nurses;
        std::vector<Patient> m_patients;
};

std::ostream& operator<<(std::ostream &flux, Inputs const& inputs);

#endif // INPUTS_H
