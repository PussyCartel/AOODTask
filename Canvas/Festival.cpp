#include "Festival.h"

Festival::Festival()
{
    fstream file("result.txt");
    string txt, del = ";";
    int counter = 1;
    string name;
    int id;
    double points;
    while (getline(file, txt)) {
        size_t pos = 0;
        std::string token;
        while ((pos = txt.find(del)) != string::npos) {
            token = txt.substr(0, pos);
            if (counter == 1) {
                name = token;
            }
            else if (counter == 2) {
                id = stoi(token);
            }
            counter += 1;
            txt.erase(0, pos + del.length());
        }
        points = stoi(txt);
        this->participants.push_back(Participant(name, id, points));
    }
}

// Метод задает параметры конкурса и меняет его статус на
void Festival::festival_open() {
    this->festival_status = true;
    cout << "Введите количество участников и количество призовых мест" << endl;
    cin >> this->participant_number >> this->prize_number;
    if (this->prize_number > this->participant_number) {
        throw exception("Количество призовых мест не может быть больше количества участников");
    }
    if (this->participant_number <= 0) {
        throw exception("Количество участников не может быть <= 0");
    }
    cout << "Конкурс открыт" << endl;
}

// На основе введённых данных добавляет экземпляр Participant в вектор partacipants класса Concurs
bool Festival::add_participant() {
    if (this->registration_status) {
        string name;
        int id;
        double points;
        cout << "Name" << endl;
        cin >> name;
        cout << "ID" << endl;
        cin >> id;
        if (id > participant_number || id < 0) return false; // id не может быть больше количества участников и меньше нуля
        for (auto it = participants.begin(); it != participants.end(); ++it) {
            if (it->get_id() == id) {
                cout << "Участник с таким id уже существует" << endl;
                return false;
            }
        }
        cout << "Points" << endl;
        cin >> points;
        if (points < 0) return false; // участник не может начинать с отрицательным кол-вом очков
        this->participants.push_back(Participant(name, id, points));
        fstream file("result.txt", ios::app);
        file << name << " " << id << " " << points << endl;
        file.close();
        return true;
    }
    else return false;
}

// Метод для блокировки метода add_participant
void Festival::close_registration() {
    this->registration_status = false;
}

bool Festival::get_status() {
    return this->registration_status;
}

bool Festival::get_number_of_participants() {
    return this->participants.size() != this->participant_number;
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
            cout << points << " успешно добавлены участнику " << it->get_name() << endl;
            break;
        }
    }
    cout << "Участник с таким id не найден" << endl;
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
    fstream report;
    report.open("report\\report.txt", ios::app);
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        report << it->get_name() << " / " << it->get_points() << endl;
    }
}

