#include "Festival.h"

Festival::Festival()
{
    fstream file("result.txt", ios::in);
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
    fstream stats("info.txt", ios::in);
    string line, text;
    while (getline(stats, line)) {
        text = line;
    }
    if (text[0]) {
        this->festival_status = true;
        this->registration_status = text[1];
        this->participant_number = text[2] - 48;
        this->prize_number = text[3] - 48;
    }
    if (!text[0]) {
        this->festival_open();
        cout << "Фестиваль открыт!\n";
    }
    else cout << "Конкурс продолжается\n";
    file.close();
    stats.close();
}

// Метод задает параметры конкурса и меняет его статус на
void Festival::festival_open() {
    fstream stats("info.txt", ios::app);
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
    this->update_stats();
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
        file << name << ";" << id << ";" << points << endl;
        file.close();
        return true;
    }
    else return false;
    this->update_stats();
}

// Метод для блокировки метода add_participant
void Festival::close_registration() {
    this->registration_status = false;
    this->update_stats();
}

bool Festival::get_registration_status() {
    return this->registration_status;
}

bool Festival::get_status() {
    return this->festival_status;
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
    this->update_stats();
}

// вспомогительный метод для дебага, который выводит вектор участников
void Festival::show_participants() {
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        cout << it->get_name() << endl;
        cout << it->get_points() << endl;
    }
}

void Festival::update_stats() {
    fstream stats("info.txt", ios::app);
    stats << this->festival_status << this->registration_status
        << this->participant_number << this-> prize_number << endl;
    stats.close();
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
    report.open("report\\report.txt", ios::out);
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        report << it->get_name() << " / " << it->get_points() << endl;
    }
    report.close();
    this->update_stats();
}
