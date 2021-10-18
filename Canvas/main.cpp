#include <iostream>
#include "Participant.h"
#include "Festival.h"

int main()
{
    setlocale(LC_ALL, "rus");
    int choice = 1;
    Festival fest;
    while (choice == 1) {
        cout << "��������� ������!\n";
        fest.festival_open();
        while (choice != 4) {
            if (fest.get_status() && fest.get_number_of_participants()) {
                cout << "�������� ������� ��������\n1 - ����������� ���������\n2 - ��������� �����������\n3 - ���������� �������� (���������� ������ � ���������)\n4 - �������� �����" << endl;
            }
            else {
                cout << "�������� ������� ��������\n3 - ���������� �������� (���������� ������ � ���������)\n4 - �������� �����" << endl;
            }
            cin >> choice;
            switch (choice)
            {
            case 1: {
                if (fest.add_participant()) cout << "�������� ������� ��������" << endl;
                else cout << "��������� ������� ���������� ���������" << endl;
                break;
            }
            case 2: {
                fest.close_registration(); 
                break;
                
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
        cout << "�������� ������� ��������\n1 - ������� ����� ������� \n2 - ����� �� ���������\n";
        cin >> choice;
    }
}