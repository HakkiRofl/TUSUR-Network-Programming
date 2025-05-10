#include "Klimov.h"


template<typename T>
T Klimov::get_choice(const std::vector<std::string>& options) {
    int choice;
    while (true) {
        for (size_t i = 0; i < options.size(); ++i)
            std::cout << i + 1 << ". " << options[i] << "\n";
        std::cout << "�������� (1-" << options.size() << "): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������ �����. ���������� �����.\n";
            continue;
        }

        if (choice >= 1 && choice <= static_cast<int>(options.size())) {
            std::cin.ignore();
            return static_cast<T>(choice - 1);
        }
        std::cout << "�������� �������!\n";
    }
}


void Klimov::start() {
    std::cout << "=== ���� ������� ===\n";
    std::cout << "=== ���� ===\n";
    Goal goal = get_choice<Goal>(goals);
    std::cout << "=== ������ ������������ ===\n";
    Subject subject = get_choice<Subject>(subjects);
    std::cout << "=== ����������� ===\n";
    Tools tool = get_choice<Tools>(tools);
    std::cout << "=== ������� ===\n";
    Conditions cond = get_choice<Conditions>(conditions);

    std::vector<MatchResult> results;
    for (Profession p : professions) {
        int score = 0;
        score += (p.goal == goal);
        score += (p.subject == subject);
        score += (p.tools == tool);
        score += (p.conditions == cond);

        if (score >= 2) {// 50% ���������� (2/4)
            results.push_back({p, score});
        }
    }

    // ���������� �� ���������� ����������
    sort(results.begin(), results.end(), [](const MatchResult& a, const MatchResult& b) {
        return a.score > b.score;
        });

    std::cout << "\n=== ���������� ===\n";
    if (!results.empty()) {
        std::cout << "������������� ���������:\n";
        for (MatchResult res : results) {
            std::cout << "[" << res.score << "/4] " << res.profession.name << "\n";
        }
    }
    else {
        std::cout << "���������� �� �������. ���������� �������� ��������.\n";
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

        if (score >= 2) {// 50% ���������� (2/4)
            results.push_back({ p, score });
        }
    }

    // ���������� �� ���������� ����������
    sort(results.begin(), results.end(), [](const MatchResult& a, const MatchResult& b) {
        return a.score > b.score;
        });

    buffer.append("\n=== ���������� ===\n");
    if (!results.empty()) {
       buffer.append("������������� ���������:\n");
        for (MatchResult res : results) {
            buffer.append("[");
            buffer.append(std::to_string(res.score));
            buffer.append("/4] ");
            buffer.append(res.profession.name);
            buffer.append("\n");
        }
    }
    else {
        buffer.append("���������� �� �������. ���������� �������� ��������.\n");
    }
    return buffer;
}