#ifndef TREATMENTTYPE_H
#define TREATMENTTYPE_H

#include <iostream>
#include <string>
#include "Time.h"

class TreatmentType
{
    public:

        TreatmentType(unsigned int id, Time duration);
        TreatmentType(unsigned int id, short duration);

        unsigned int id() const { return m_id; }
        Time duration() const { return m_duration; }

        std::string to_string() const;


    private:

        const unsigned int m_id;
        const Time m_duration;
};

bool operator==(TreatmentType const& type1, TreatmentType const& type2);
std::ostream& operator<<(std::ostream &flux, TreatmentType const& type);

#endif // TREATMENTTYPE_H
