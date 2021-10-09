#pragma once
#include "Participant.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Данный класс реализует логику конкурса
class Festival {

private:
    bool festival_status = false;
    bool registration_status = true;
    int participant_number = 0;
    int prize_number = 0;
    vector <Participant> participants;

public:
    void festival_open();
    void add_participant();
    void close_registration();
    void add_points_to_participant();
    void show_participants();
    void festival_close();
};


