#ifndef EXAMDETAILS_H_
#define EXAMDETAILS_H_

#include <iostream>
#include <string>

class ExamDetails
{
private:
    int course_number;
    int month;
    int day;
    double starting_time;
    int duration_time;
    std::string zoom_link;

public:
    ExamDetails(int course_number,
                int month,
                int day,
                double starting_time,
                int duration_time,
                std::string zoom_link = "");                                      //constructor
    ExamDetails(const ExamDetails &copy_from);                               //copy constructor
    ExamDetails &operator=(const ExamDetails &copy_from) = default;                    //copy assignment
    int operator-(const ExamDetails &exam_details) const;                    //time sub assignment
    bool operator<(const ExamDetails &exam_details) const;                   //early time assignment
    std::string getLink() const;                                                  // accessor function
    void setLink(std::string zoom_link);                                          // accessor function
    void print() const;                                                      //print function
    static ExamDetails makeMatamExam();                                      //static function makeMatamExam
    ~ExamDetails() = default;                                                          //destructor
    friend std::ostream &operator<<(std::ostream &os, const ExamDetails &r); // cout << s1;
    class InvalidDateException                                               //exceptions
    {
    };
    class InvalidTimeException                                              //exceptions
    {
    };
    class InvalidArgsException                                               //exceptions
    {
    };
};

#endif //EXAMDETAILS_H_