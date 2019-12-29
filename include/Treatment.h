#ifndef TREATMENT_H
#define TREATMENT_H

#include <iostream>
#include <string>
#include "TreatmentType.h"
#include "TimeInterval.h"

class Treatment
{
    public:

        Treatment(TreatmentType type, TimeInterval schedule = TimeInterval::GET_FULL_DAY());

        TreatmentType type() const { return m_type; }
        TimeInterval schedule() const { return m_schedule; }
        bool is_scheduled() const { return m_is_scheduled; }
        void is_scheduled(bool val) { m_is_scheduled = val; }

        std::string to_string() const;


    private:

        TreatmentType m_type;
        TimeInterval m_schedule;
        bool m_is_scheduled;
};

bool operator==(Treatment const& treatment1, Treatment const& treatment2);
std::ostream& operator<<(std::ostream &flux, Treatment const& treatment);

#endif // TREATMENT_H
