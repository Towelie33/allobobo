#include "../include/TimeInterval.h"
#include <iostream>
#include <string>
#include "../include/Time.h"
//#include <cpprest/json.h>

TimeInterval TimeInterval::FULL_DAY = TimeInterval(0, 24 * 60);

TimeInterval::TimeInterval(Time start_time, Time end_time)
    :m_start_time(start_time), m_end_time(end_time)
{}

TimeInterval::TimeInterval(short start_time, short end_time)
    :m_start_time(start_time), m_end_time(end_time)
{}

TimeInterval::TimeInterval(Time start_time, short duration)
    :m_start_time(start_time), m_end_time(start_time.minutes() + duration)
{}
/*
TimeInterval::TimeInterval(web::json::object const& jobject)
	:m_start_time(jobject.at(L"start").as_integer()), m_end_time(jobject.at(L"end").as_integer())
{}
*/
bool TimeInterval::contains(Time const& time) const
{
    return (m_start_time <= time) && (time <= m_end_time);
}

std::string TimeInterval::to_string() const
{
    return "(" + m_start_time.to_string() + " -> " + m_end_time.to_string() + ")";
}

bool operator==(TimeInterval const& interval1, TimeInterval const& interval2)
{
    return (interval1.start_time() == interval2.start_time())
        && (interval1.end_time() == interval2.end_time());
}

std::ostream& operator<<(std::ostream &flux, TimeInterval const& interval)
{
    std::cout << interval.to_string();
    return flux;
}
