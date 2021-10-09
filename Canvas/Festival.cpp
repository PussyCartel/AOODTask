#include "Festival.h"

// Метод задает параметры конкурса и меняет его статус на
void Festival::festival_open() {
    this->festival_status = true;
    cout << "Введите количество участников и количество призовых мест" << endl;
    cin >> this->participant_number >> this->prize_number;
    if (this->prize_number > this->participant_number) {
        //throw exception("Количество призовых мест не может быть больше количества участников");
    }
    cout << "Конкурс открыт" << endl;
}

// На основе введённых данных добавляет экземпляр Participant в вектор partacipants класса Concurs
void Festival::add_participant() {
    string name;
    int id;
    double points;
    cout << "Name" << endl;
    cin >> name;
    cout << "ID" << endl;
    cin >> id;
    cout << "Points" << endl;
    cin >> points;
    this->participants.push_back(Participant(name, id, points));
}

// Метод для блокировки метода add_participant
void Festival::close_registration() {
    this->registration_status = false;
}

// Метод итеррируется по вектору участников и добавляет очки нужному кандидату
void Festival::add_points_to_participant() {
    int id;
    double points;
    cout << "Введите ID участника" << endl;
    cin >> id;
    cout << "Введите количество очков которые нужно добавить участнику" << endl;
    cin >> points;
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        if (it->get_id() == id) {
            it->add_points(points);
            break;
        }
    }
}

// вспомогительный метод для дебага, который выводит вектор участников
void Festival::show_participants() {
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        cout << it->get_name() << endl;
        cout << it->get_points() << endl;
    }
}

// Закрытие фестиваля
void Festival::festival_close() {
    this->festival_status = false;
    cout << "Объявляется закрытие конкурса" << endl;
    sort(participants.begin(), participants.end(), [](Participant a, Participant b) -> bool {
        return a.get_points() > b.get_points();
        });
    this->show_participants();
    ofstream f("result.txt");
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        f << it->get_name() << " - " << it->get_points() << endl;
    }
    f.close();
}

