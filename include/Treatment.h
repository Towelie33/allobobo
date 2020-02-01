#ifndef TREATMENT_H
#define TREATMENT_H

#include <iostream>
#include <string>
#include "TreatmentType.h"
#include "TimeInterval.h"
//#include <cpprest/json.h>

class Treatment
{
    public:

        Treatment(unsigned int id, unsigned int type_id, TimeInterval schedule = TimeInterval::GET_FULL_DAY());
	//Treatment(web::json::object const& jobject);

        unsigned int id() const { return m_id; }
	unsigned int type_id() const { return m_type_id; }
        TimeInterval schedule() const { return m_schedule; }
        bool is_scheduled() const { return m_is_scheduled; }
        void is_scheduled(bool val) { m_is_scheduled = val; }

        std::string to_string() const;


    private:

        const unsigned int m_id;
        const unsigned int m_type_id;
        const TimeInterval m_schedule;
        bool m_is_scheduled;
};

bool operator==(Treatment const& treatment1, Treatment const& treatment2);
std::ostream& operator<<(std::ostream &flux, Treatment const& treatment);

#endif // TREATMENT_H
