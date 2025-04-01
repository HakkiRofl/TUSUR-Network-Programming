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
        // Исходные профессии
        {"Инженер", MANUFACTURE, TECH, MANUAL, INDOOR},
        {"Учитель", TEACH, HUMAN, VOICE_GESTURES, INDOOR},
        {"Ветеринар", SERVE, ANIMALS_PLANTS, MANUAL, OUTDOOR},
        {"Программист", RESEARCH, INFORMATION, COMPUTER, INDOOR},
        {"Художник", CREATE_ART, ART, THINKING, HOME},
        {"Геолог", RESEARCH, NATURAL_RESOURCES, PHYSICAL_ABILITIES, OUTDOOR},
        {"Врач", SERVE, HUMAN, SENSES, HIGH_RESPONSIBILITY},
        {"Бухгалтер", EVALUATE, FINANCE, COMPUTER, INDOOR},
        {"Эколог", RESEARCH, NATURAL_RESOURCES, THINKING, OUTDOOR},

        // Новые профессии
        {"Архитектор", CREATE_ART, TECH, COMPUTER, INDOOR},
        {"Психолог", TEACH, HUMAN, VOICE_GESTURES, INDOOR},
        {"Агроном", MANUFACTURE, ANIMALS_PLANTS, MANUAL, OUTDOOR},
        {"Пилот", TRANSPORT, TECH, MECHANICAL, SPECIAL},
        {"Журналист", RESEARCH, INFORMATION, VOICE_GESTURES, TRAVEL},
        {"Спасатель", SERVE, HUMAN, PHYSICAL_ABILITIES, EXTREME},
        {"Дизайнер", CREATE_ART, ART, COMPUTER, HOME},
        {"Логист", MANAGE, PRODUCTS, COMPUTER, INDOOR},
        {"Океанолог", RESEARCH, NATURAL_RESOURCES, SENSES, OUTDOOR},
        {"Фермер", MANUFACTURE, ANIMALS_PLANTS, MECHANICAL, OUTDOOR}
    };
    std::vector<std::string> goals = { "Оценивать", "Исследовать", "Перевозить", "Изготавливать",
                       "Учить", "Творить", "Руководить", "Обслуживать" };
    std::vector<std::string> subjects = { "Люди", "Информация", "Финансы", "Техника", "Искусство",
                             "Животные/растения", "Изделия", "Природа" };
    std::vector<std::string> tools = { "Ручные", "Механизмы", "Автоматика", "Компьютеры",
                          "Мышление", "Речь/жесты", "Физ. возможности", "Органы чувств" };
    std::vector<std::string> conditions = { "Офис", "Толпа", "Разъезды", "Улица",
                               "Экстрим", "Дом", "Спецусловия", "Ответственность" };
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