#ifndef TREATMENTTYPE_H
#define TREATMENTTYPE_H

#include <iostream>
#include <string>
#include "Time.h"

class TreatmentType
{
    public:

        TreatmentType(std::string name, Time duration);
        TreatmentType(std::string name, short duration);

        std::string name() const { return m_name; }
        Time duration() const { return m_duration; }

        std::string to_string() const;


    private:

        std::string m_name;
        Time m_duration;
};

bool operator==(TreatmentType const& type1, TreatmentType const& type2);
std::ostream& operator<<(std::ostream &flux, TreatmentType const& type);

#endif // TREATMENTTYPE_H
