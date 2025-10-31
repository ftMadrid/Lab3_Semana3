#include <QCoreApplication>

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "First commit, get cholomayork in your pocket!" << endl;

    return a.exec();
}
