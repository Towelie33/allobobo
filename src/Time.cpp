#include "Time.h"
#include <iostream>
#include <string>
#include <sstream>
#include <math.h> // round
#include "Utils.h"
#include "Point.h"

const short Time::MINUTES_MAX = 24 * 60;

Time::Time()
    :m_minutes(0)
{}

Time::Time(short minutes)
    :m_minutes(std::min(minutes, MINUTES_MAX))
{}

Time::Time(short hours, short minutes)
    :m_minutes(std::min((short) (60 * hours + minutes), MINUTES_MAX))
{}

short Time::to_hours() const
{
    return m_minutes / 60;
}

short Time::to_minutes() const
{
    return m_minutes % 60;
}

std::string Time::to_string() const
{
    std::string str;
    short minutes = to_minutes();

    // Convert hours and minutes to string
    std::string h = int_to_string(to_hours());
    std::string m = int_to_string(minutes);

    if (minutes < 10)
    {
        str = h + "h0" + m;
    }
    else
    {
        str = h + "h" + m;
    }

    return str;
}

Time operator+(Time const& time1, Time const& time2)
{
    return Time(std::min((short) (time1.minutes() + time2.minutes()), Time::MINUTES_MAX));
}

bool operator==(Time const& time1, Time const& time2)
{
    return time1.minutes() == time2.minutes();
}

bool operator<(Time const& time1, Time const& time2)
{
    return time1.minutes() < time2.minutes();
}

bool operator<=(Time const& time1, Time const& time2)
{
    return time1.minutes() <= time2.minutes();
}

std::ostream& operator<<(std::ostream &flux, Time const& time)
{
    std::cout << time.to_string();
    return flux;
}

Time time_to_go(long dist, short speed)
{
    short minutes = (short) round((float) dist / ((float) speed / 0.06f));
    return Time(minutes);
}

Time time_to_go(Point const& from, Point const& to, short speed)
{
    return time_to_go(distance(from, to), speed);
}
