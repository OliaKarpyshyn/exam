#include "code.h"

Code::Code()
{
    organisation = "organisation";
    component = "component";
    project = "project";
    classMethod = "class";
    method = "method";
}

Code::Code(QString o, QString c, QString p, QString cm, QString m)
{
    organisation = o;
    component = c;
    project = p;
    classMethod = cm;
    method = m;
}

bool Code::operator<(const Code &other)
{
    return method < other.method;
}

bool Code::operator>(const Code &other)
{
    return method > other.method;
}

bool Code::operator<=(const Code &other)
{
    return method <= other.method;
}

bool Code::operator>=(const Code &other)
{
    return method >= other.method;
}

bool Code::operator==(const Code &other)
{
    return method == other.method;
}

std::ostream& operator<< (std::ostream &out, const Code &code)
{
    out << "Organisation: " << code.organisation.toStdString() <<
            "\nComponent: " << code.component.toStdString() <<
            "\nProject: " << code.project.toStdString() <<
            "\nClass: " << code.classMethod.toStdString() <<
            "\nMethod: " << code.method.toStdString();
    return out;
}
