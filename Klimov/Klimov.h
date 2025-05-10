#ifndef KLIMOV_H
#define KLIMOV_H


#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>


enum Goal { EVALUATE, RESEARCH, TRANSPORT, MANUFACTURE, TEACH, CREATE_ART, MANAGE, SERVE };
enum Subject { HUMAN, INFORMATION, FINANCE, TECH, ART, ANIMALS_PLANTS, PRODUCTS, NATURAL_RESOURCES };
enum Tools { MANUAL, MECHANICAL, AUTOMATIC, COMPUTER, THINKING, VOICE_GESTURES, PHYSICAL_ABILITIES, SENSES };
enum Conditions { INDOOR, CROWDED, TRAVEL, OUTDOOR, EXTREME, HOME, SPECIAL, HIGH_RESPONSIBILITY };


struct Profession {
    std::string name;
    Goal goal;
    Subject subject;
    Tools tools;
    Conditions conditions;
};


struct MatchResult {
    Profession profession;
    int score;
};


class Klimov {
protected:
    std::vector<Profession> professions = {
        // �������� ���������
        {"�������", MANUFACTURE, TECH, MANUAL, INDOOR},
        {"�������", TEACH, HUMAN, VOICE_GESTURES, INDOOR},
        {"���������", SERVE, ANIMALS_PLANTS, MANUAL, OUTDOOR},
        {"�����������", RESEARCH, INFORMATION, COMPUTER, INDOOR},
        {"��������", CREATE_ART, ART, THINKING, HOME},
        {"������", RESEARCH, NATURAL_RESOURCES, PHYSICAL_ABILITIES, OUTDOOR},
        {"����", SERVE, HUMAN, SENSES, HIGH_RESPONSIBILITY},
        {"���������", EVALUATE, FINANCE, COMPUTER, INDOOR},
        {"������", RESEARCH, NATURAL_RESOURCES, THINKING, OUTDOOR},

        // ����� ���������
        {"����������", CREATE_ART, TECH, COMPUTER, INDOOR},
        {"��������", TEACH, HUMAN, VOICE_GESTURES, INDOOR},
        {"�������", MANUFACTURE, ANIMALS_PLANTS, MANUAL, OUTDOOR},
        {"�����", TRANSPORT, TECH, MECHANICAL, SPECIAL},
        {"���������", RESEARCH, INFORMATION, VOICE_GESTURES, TRAVEL},
        {"���������", SERVE, HUMAN, PHYSICAL_ABILITIES, EXTREME},
        {"��������", CREATE_ART, ART, COMPUTER, HOME},
        {"������", MANAGE, PRODUCTS, COMPUTER, INDOOR},
        {"���������", RESEARCH, NATURAL_RESOURCES, SENSES, OUTDOOR},
        {"������", MANUFACTURE, ANIMALS_PLANTS, MECHANICAL, OUTDOOR}
    };
    std::vector<std::string> goals = { "���������", "�����������", "����������", "�������������",
                       "�����", "�������", "����������", "�����������" };
    std::vector<std::string> subjects = { "����", "����������", "�������", "�������", "���������",
                             "��������/��������", "�������", "�������" };
    std::vector<std::string> tools = { "������", "���������", "����������", "����������",
                          "��������", "����/�����", "���. �����������", "������ ������" };
    std::vector<std::string> conditions = { "����", "�����", "��������", "�����",
                               "�������", "���", "�����������", "���������������" };
    Goal goal;
    Subject subject;
    Tools tool;
    Conditions cond;
public:
    template<typename T>
    T get_choice(const std::vector<std::string>&options);
    Klimov() {};
    ~Klimov() {};
    void start();
    std::string get_result();
};
#endif