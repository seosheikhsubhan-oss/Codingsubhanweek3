#include <iostream>
using namespace std;

class Employee {
public:
    virtual float calculateSalary() = 0;
};

class FullTimeEmployee : public Employee {
private:
    float salary;

public:
    FullTimeEmployee(float s) {
        salary = s;
    }
    float calculateSalary() {
        return salary;
    }
};
class PartTimeEmployee : public Employee {
private:
    int hoursworked;
    float hourlyrate;

public:
    PartTimeEmployee(int h, float r) {
        hoursworked =h;
        hourlyrate =r;
    }

    float calculateSalary() {
        return hoursworked * hourlyrate;
    }
};

int main() {
    FullTimeEmployee emp1(50000);      
    PartTimeEmployee emp2(40, 500);    
    cout << "Full-Time Employee Salary:" << emp1.calculateSalary() << endl;
    cout << "Part-Time Employee Salary:" << emp2.calculateSalary() << endl;

    return 0;
}