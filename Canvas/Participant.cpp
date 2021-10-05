#include "Participant.h"

Participant::Participant(string name, int id, double points) {
    this->name = name;
    this->id = id;
    this->points = points;
}

string Participant::get_name() {
    return this->name;
}

int Participant::get_id() {
    return this->id;
}

double Participant::get_points() {
    return points;
}

void Participant::add_points(double add) {
    this->points += add;
}
