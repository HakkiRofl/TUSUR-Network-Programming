#include "Klimov.h"


template<typename T>
T Klimov::get_choice(const std::vector<std::string>& options) {
    int choice;
    while (true) {
        for (size_t i = 0; i < options.size(); ++i)
            std::cout << i + 1 << ". " << options[i] << "\n";
        std::cout << "Выберите (1-" << options.size() << "): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Попробуйте снова.\n";
            continue;
        }

        if (choice >= 1 && choice <= static_cast<int>(options.size())) {
            std::cin.ignore();
            return static_cast<T>(choice - 1);
        }
        std::cout << "Неверный вариант!\n";
    }
}


void Klimov::start() {
    std::cout << "=== ТЕСТ КЛИМОВА ===\n";
    std::cout << "=== Цели ===\n";
    Goal goal = get_choice<Goal>(goals);
    std::cout << "=== Объект деятельности ===\n";
    Subject subject = get_choice<Subject>(subjects);
    std::cout << "=== Инструменты ===\n";
    Tools tool = get_choice<Tools>(tools);
    std::cout << "=== Условия ===\n";
    Conditions cond = get_choice<Conditions>(conditions);

    std::vector<MatchResult> results;
    for (Profession p : professions) {
        int score = 0;
        score += (p.goal == goal);
        score += (p.subject == subject);
        score += (p.tools == tool);
        score += (p.conditions == cond);

        if (score >= 2) {// 50% совпадение (2/4)
            results.push_back({p, score});
        }
    }

    // Сортировка по количеству совпадений
    sort(results.begin(), results.end(), [](const MatchResult& a, const MatchResult& b) {
        return a.score > b.score;
        });

    std::cout << "\n=== РЕЗУЛЬТАТЫ ===\n";
    if (!results.empty()) {
        std::cout << "Рекомендуемые профессии:\n";
        for (MatchResult res : results) {
            std::cout << "[" << res.score << "/4] " << res.profession.name << "\n";
        }
    }
    else {
        std::cout << "Совпадений не найдено. Попробуйте смягчить критерии.\n";
    }
}


std::string Klimov::get_result() {
    std::string buffer;
    std::vector<MatchResult> results;
    for (Profession p : professions) {
        int score = 0;
        score += (p.goal == goal);
        score += (p.subject == subject);
        score += (p.tools == tool);
        score += (p.conditions == cond);

        if (score >= 2) {// 50% совпадение (2/4)
            results.push_back({ p, score });
        }
    }

    // Сортировка по количеству совпадений
    sort(results.begin(), results.end(), [](const MatchResult& a, const MatchResult& b) {
        return a.score > b.score;
        });

    buffer.append("\n=== РЕЗУЛЬТАТЫ ===\n");
    if (!results.empty()) {
       buffer.append("Рекомендуемые профессии:\n");
        for (MatchResult res : results) {
            buffer.append("[");
            buffer.append(std::to_string(res.score));
            buffer.append("/4] ");
            buffer.append(res.profession.name);
            buffer.append("\n");
        }
    }
    else {
        buffer.append("Совпадений не найдено. Попробуйте смягчить критерии.\n");
    }
    return buffer;
}