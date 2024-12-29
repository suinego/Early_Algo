#include <iostream>
#include <string>
#include "hpp/Grammar.hpp"
#include "hpp/Parser.hpp"

void PrintMenu() {
    std::cout << "-------------" << std::endl;
    std::cout << "1. Добавить правило грамматики" << std::endl;
    std::cout << "2. Проверить строку" << std::endl;
    std::cout << "3. Правила грамматики" << std::endl;
    std::cout << "4. Выйти" << std::endl;
    std::cout << "................" << std::endl;
    std::cout << "Номер: ";
}

void PrintGrammar(const Grammar& grammar) {
    std::cout << "Текущая грамматика:" << std::endl;
    for (const auto& rule : grammar.rules_) {
        std::cout << rule.GetTerminal() << " -> ";
        for (int i = 0; i < rule.GetSizeRule(); i++) {
            std::cout << rule.GetLetterRight(i).GetLetter();
        }
        std::cout << std::endl;
    }
}

int main() {
    Grammar grammar;
    ParserEarley parser;

    while (true) {
        PrintMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string rule;
            std::cout << "Правило грамматики (в формате S->abc), пустые правила можно добавлять вот так (S->): ";
            std::cin >> rule;
            grammar.SetRule(rule);
            std::cout << "Правило добавлено!" << std::endl;
        } else if (choice == 2) {
            std::string word;
            std::cout << "Введите строку для проверки: ";
            std::cin >> word;

            bool result = parser.Earley(word, grammar);
            if (result) {
                std::cout << "Строка соответствует грамматике! :)" << std::endl;
            } else {
                std::cout << "Строка не соответствует грамматике :(" << std::endl;
            }
        } else if (choice == 3) {
            PrintGrammar(grammar);
        } else if (choice == 4) {
            std::cout << "Выход из программы." << std::endl;
            break;
        } else {
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}
