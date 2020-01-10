#ifndef NURSE_H
#define NURSE_H

#include <iostream>
#include <string>
#include <vector>
#include "Point.h"
#include "Time.h"
#include "TimeInterval.h"
#include "TreatmentType.h"

class Nurse
{
    public:

        Nurse(unsigned int id,
              Point starting_point = Point::GET_ORIGIN(),
              TimeInterval timetable = TimeInterval::GET_FULL_DAY());

        Nurse(unsigned int id,
              TreatmentType type,
              Point starting_point = Point::GET_ORIGIN(),
              TimeInterval timetable = TimeInterval::GET_FULL_DAY());

        Nurse(unsigned int id,
              std::vector<TreatmentType> cannot_do,
              Point starting_point = Point::GET_ORIGIN(),
              TimeInterval timetable = TimeInterval::GET_FULL_DAY());

        unsigned int id() const { return m_id; }
        std::vector<TreatmentType> cannot_do() const { return m_cannot_do; }
        Point starting_point() const { return m_starting_point; }
        Point position() const { return m_position; }
        void position(Point const& val) { m_position = val; }
        TimeInterval timetable() const { return m_timetable; }
        Time available() const { return m_available; }
        void available(Time const& val) { m_available = val; }
        int index() const { return m_index; }
        void index(int val) { m_index = val; }

        void add_treatment_type(TreatmentType const& type);
        bool can_do(TreatmentType const& type) const;
        void reset();

        std::string cannot_do_to_string() const;
        std::string to_string() const;


    private:

        const unsigned int m_id;
        std::vector<TreatmentType> m_cannot_do;
        const Point m_starting_point;
        Point m_position;
        const TimeInterval m_timetable;
        Time m_available;
        int m_index;
};

bool operator<(Nurse const& nurse1, Nurse const& nurse2);
std::ostream& operator<<(std::ostream &flux, Nurse const& nurse);

#endif // NURSE_H
