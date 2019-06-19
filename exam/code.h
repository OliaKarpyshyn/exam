#ifndef CODE_H
#define CODE_H
#include <QString>

class Code
{
public:
    Code();
    Code(QString, QString, QString, QString, QString);

    bool operator<(const Code&other);
    bool operator<=(const Code&other);
    bool operator>(const Code&other);
    bool operator>=(const Code&other);
    bool operator==(const Code&other);
    friend std::ostream& operator<< (std::ostream &out, const Code &point);


private:
    //організація, проект, компонент, клас, метод
    QString organisation;
    QString project;
    QString component;
    QString classMethod;
    QString method;

};


#endif // CODE_H
