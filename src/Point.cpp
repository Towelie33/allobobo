#include "../include/Point.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../include/Utils.h"
//#include <cpprest/json.h>

Point Point::ORIGIN = Point();

Point::Point()
    :m_pos_x(0), m_pos_y(0)
{}

Point::Point(int pos_x, int pos_y)
    :m_pos_x(pos_x), m_pos_y(pos_y)
{}
/*
Point::Point(web::json::object const& jobject)
	:m_pos_x(jobject.at(L"x").as_integer()), m_pos_y(jobject.at(L"y").as_integer())
{}
*/
std::string Point::to_string() const
{
    return "(" + int_to_string(m_pos_x) + ", " + int_to_string(m_pos_y) + ")";
}

bool operator==(Point const& point1, Point const& point2)
{
    return (point1.pos_x() == point2.pos_x())
        && (point1.pos_y() == point2.pos_y());
}

std::ostream& operator<<(std::ostream &flux, Point const& point)
{
    std::cout << point.to_string();
    return flux;
}

int distance(Point const& point1, Point const& point2)
{
    return abs(point1.pos_x() - point2.pos_x()) + abs(point1.pos_y() - point2.pos_y());
}
