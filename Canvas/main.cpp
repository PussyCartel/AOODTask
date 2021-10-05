#include <iostream>
#include "Participant.h"
#include "Canvas.h"

int main()
{
    setlocale(LC_ALL, "rus");
    int choice = 1;
    Canvas fest;
    while (choice == 1) {
        cout << "Фестиваль открыт!\n";
        fest.festival_open();
        while (true && choice != 4) {
            cout << "Выберите текущее действие\n1 - Регистрация участника\n2 - Окончание регистрации\n3 - Проведение конкурса (добавление баллов к участнику)\n4 - Подвести итоги" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1: {
                fest.add_participant(); break;
            }
            case 2: {
                fest.close_registration(); break;
            }
            case 3: {
                fest.add_points_to_participant(); break;
            }
            case 4: {
                fest.festival_close(); break;
            }
            default:
                break;
            }
        }
        cout << "Выберите текущее действие\n1 - Открыть новый конкурс \n2 - Выйти из программы\n";
        cin >> choice;
    }
}