#include "examDetails.h"
#include <cmath>

const double epsilon = pow(10,-6);
const int max_month = 12;
const int min_month = 0;
const int max_day = 30;
const int min_day = 0;
const double half = 0.5;
const int min_duration_time = 0;

// constructor of ExamDetails
ExamDetails::ExamDetails(int course_number, int month, int day, double starting_time, int duration_time, std::string zoom_link)
{
    if (month < min_month || month > max_month || day < min_day || day > max_day)
    {
        throw InvalidDateException();
    }
    if ((std::abs(ceil(starting_time) - starting_time - half) < epsilon) && (std::abs(starting_time - ceil(starting_time)) < epsilon))
    {
        throw InvalidTimeException();
    }
    if(duration_time < min_duration_time)
    {
        throw InvalidArgsException();
    }
    this->course_number = course_number;
    this->month = month;
    this->day = day;
    this->starting_time = starting_time;
    this->duration_time = duration_time;
    this->zoom_link = zoom_link;
}

// copy constructor if ExamDetails
ExamDetails::ExamDetails(const ExamDetails &copy_from)
{
    this->course_number = copy_from.course_number;
    this->month = copy_from.month;
    this->day = copy_from.day;
    this->starting_time = copy_from.starting_time;
    this->duration_time = copy_from.duration_time;
    this->zoom_link = copy_from.zoom_link;
}

std::string ExamDetails::getLink() const
{
    return this->zoom_link;
}
void ExamDetails::setLink(std::string zoom_link)
{
    this->zoom_link = zoom_link;
}
int ExamDetails::operator-(const ExamDetails &ExamDetails) const
{
    int month_to_days = (month * 30) - (ExamDetails.month * 30);
    return this->day - ExamDetails.day + month_to_days;
}
bool ExamDetails::operator<(const ExamDetails &ExamDetails) const
{
    if (*this - ExamDetails >= 0)
    {
        return false;
    }
    return true;
}
ExamDetails ExamDetails::makeMatamExam()
{
    ExamDetails res(234124, 7, 28, 13, 3, "https://tinyurl.com/59hzps6m");
    return res;
}

void ExamDetails::print() const
{
    std::cout << *this;
}
std::ostream &operator<<(std::ostream &os, const ExamDetails &r)
{
    os << "Course Number: " << r.course_number << std::endl
       << "Time: " << r.day << "." << r.month << " at " << (int)r.starting_time;
    if (r.starting_time - (int)r.starting_time == 0)
    {
        os << ":00" << std::endl;
    }
    else
    {
        os << ":30" << std::endl;
    }
    os << "Duration: " << r.duration_time << ":00" << std::endl
       << "Zoom Link: " << r.zoom_link<< std::endl;
    return os;
}
