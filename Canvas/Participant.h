#pragma once
#include <string>

using namespace std;

// Класс реализующий участника
class Participant
{
private:
    string name = "base";
    int id;
    double points;

public:
    Participant(string name, int id, double points);
    string get_name();
    int get_id();
    double get_points();
    void add_points(double add);

};

