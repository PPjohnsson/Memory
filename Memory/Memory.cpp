#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

// Funktion f�r att slumpa unika tal
std::vector<int> generateUniqueNumbers(int count, int maxNumber) {
    std::vector<int> numbers;
    for (int i = 0; i < maxNumber; ++i) {
        numbers.push_back(i);
    }
    std::random_shuffle(numbers.begin(), numbers.end());
    numbers.resize(count);
    return numbers;
}

// Funktion f�r att visa talen och starta nedr�kningen
void showNumbers(const std::vector<int>& numbers) {
    std::cout << "Memorera f�ljande nummer:";
    for (const auto& number : numbers) {
        std::cout << " " << number;
    }
    std::cout << std::endl;

    std::cout << "5...4...3...2...1..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for (int i = 0; i < 20; ++i) {
        std::cout << std::endl;
    }
}

// Funktion f�r att kontrollera om anv�ndaren har svarat r�tt
bool checkNumbers(const std::vector<int>& numbers, const std::vector<int>& guesses) {
    if (numbers.size() != guesses.size()) {
        return false;
    }

    std::vector<int> sortedNumbers = numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    std::vector<int> sortedGuesses = guesses;
    std::sort(sortedGuesses.begin(), sortedGuesses.end());

    for (size_t i = 0; i < numbers.size(); ++i) {
        if (sortedNumbers[i] != sortedGuesses[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    std::cout << "********* Minnesspel v1.0 **********" << std::endl;
    std::cout << "V�lkommen till minnesspelet." << std::endl;

    int level = 2;
    int maxNumber = level * 10;
    int score = 0;

    while (true) {
        std::cout << "Level " << level << ": " << level << " stycken unika tal mellan 0-" << maxNumber << std::endl;
        std::cout << "Tryck enter f�r att starta. Du har 5 sek p� dig n�r du startat." << std::endl;
        std::cin.ignore(); // V�ntar p� enter

        std::vector<int> numbers = generateUniqueNumbers(level, maxNumber);
        showNumbers(numbers);

        std::vector<int> guesses(level);
        std::cout << "Vilka var numren? Ordningen spelar ingen roll:";
        for (int i = 0; i < level; ++i) {
            std::cin >> guesses[i];
        }

        if (checkNumbers(numbers, guesses)) {
            std::cout << "R�tt!" << std::endl;
            ++score;
            ++level;
            maxNumber = level * 10;
        }
        else {
            std::cout << "Du hade bara: " << score << " r�tt av " << level << "." << std::endl;
            std::cout << "Sorry, du f�rlorade!" << std::endl;
            break;
        }
    }

    return 0;
}