#include <iostream>
#include "Participant.h"
#include <stdio.h>
#include "Festival.h"

int main()
{
    setlocale(LC_ALL, "rus");
    int choice = 1;
    Festival fest;
    fstream file("result.txt", ios::app);
    while (choice != 4) {
        if (fest.get_registration_status() && fest.get_number_of_participants()) {
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
            fest.festival_close(); 
            ofstream ofs;
            ofs.open("info.txt", std::ios::out | std::ios::trunc);
            ofs.close();
            ofs.open("result.txt", std::ios::out | std::ios::trunc);
            ofs.close();
            break;   
        }
        default:
            break;
        }
    }
}