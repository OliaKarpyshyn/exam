#ifndef CODE_H
#define CODE_H
#include <QString>

class Code
{
public:
    Code();
    Code(QString, QString, QString, QString, QString);

    friend bool operator<(const Code&other, const Code&other1);
    friend bool operator<=(const Code&other, const Code&other1);
    friend bool operator>(const Code&other, const Code&other1);
    friend bool operator>=(const Code&other, const Code&other1);
    friend bool operator==(const Code&other, const Code&other1);
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
