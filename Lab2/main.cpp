#include <iostream>
#include <string>
#include <cmath>
#include <clocale>

class Money {
private:
    long hryvnia;
    unsigned char kopeck; // Зберігається як число від 0 до 99

public:
    // Метод ініціалізації
    bool Init(long h, int k) {
        if (k >= 0 && k < 100 && h >= 0) {
            hryvnia = h;
            kopeck = static_cast<unsigned char>(k);
            return true;
        }
        return false;
    }

    // Метод введення з клавіатури
    void Read() {
        long h;
        int k;
        do {
            std::cout << "Введіть гривні: ";
            std::cin >> h;
            std::cout << "Введіть копійки (0-99): ";
            std::cin >> k;
            if (Init(h, k)) break;
            std::cout << "Помилка введення! Спробуйте ще раз.\n";
        } while (true);
    }

    // Перетворення в рядок (вивід через кому)
    std::string toString() const {
        std::string kopStr = std::to_string(static_cast<int>(kopeck));
        if (kopStr.length() == 1) {
            kopStr = "0" + kopStr; // Форматування для 0-9 копійок
        }
        return std::to_string(hryvnia) + "," + kopStr;
    }

    // Метод виведення на екран
    void Display() const {
        std::cout << toString() << " грн" << std::endl;
    }

    // Додавання сум
    Money Add(const Money& other) const {
        long totalKop = (hryvnia + other.hryvnia) * 100 + static_cast<int>(kopeck) + static_cast<int>(other.kopeck);
        Money result;
        result.Init(totalKop / 100, totalKop % 100);
        return result;
    }

    // Віднімання сум
    Money Sub(const Money& other) const {
        long long kop1 = hryvnia * 100 + static_cast<int>(kopeck);
        long long kop2 = other.hryvnia * 100 + static_cast<int>(other.kopeck);
        long long diff = kop1 - kop2;

        Money result;
        if (diff < 0) {
            std::cout << "Помилка: результат віднімання від'ємний!\n";
            result.Init(0, 0);
        }
        else {
            result.Init(diff / 100, diff % 100);
        }
        return result;
    }

    // Ділення суми на суму (отримуємо коефіцієнт)
    double Div(const Money& other) const {
        double kop1 = hryvnia * 100.0 + static_cast<int>(kopeck);
        double kop2 = other.hryvnia * 100.0 + static_cast<int>(other.kopeck);
        if (kop2 == 0) {
            std::cout << "Помилка: ділення на нуль!\n";
            return 0.0;
        }
        return kop1 / kop2;
    }

    // Ділення суми на дробове число
    Money DivNum(double factor) const {
        Money result;
        if (factor == 0) {
            std::cout << "Помилка: ділення на нуль!\n";
            result.Init(0, 0);
            return result;
        }
        double totalKop = (hryvnia * 100.0 + static_cast<int>(kopeck)) / factor;
        long roundedKop = std::round(totalKop);
        result.Init(roundedKop / 100, roundedKop % 100);
        return result;
    }

    // Множення суми на дробове число
    Money MulNum(double factor) const {
        double totalKop = (hryvnia * 100.0 + static_cast<int>(kopeck)) * factor;
        long roundedKop = std::round(totalKop);
        Money result;
        result.Init(roundedKop / 100, roundedKop % 100);
        return result;
    }

    // Операції порівняння (1 якщо >, -1 якщо <, 0 якщо =)
    int Compare(const Money& other) const {
        long kop1 = hryvnia * 100 + static_cast<int>(kopeck);
        long kop2 = other.hryvnia * 100 + static_cast<int>(other.kopeck);
        if (kop1 > kop2) return 1;
        if (kop1 < kop2) return -1;
        return 0;
    }
};

int main() {
    // Налаштування укр мови в консолі
    std::setlocale(LC_ALL, "uk_UA.UTF-8");

    Money m1, m2;

    std::cout << "--- Введення першої суми ---\n";
    m1.Read();

    std::cout << "--- Введення другої суми ---\n";
    m2.Read();

    std::cout << "\nПерша сума: "; m1.Display();
    std::cout << "Друга сума: "; m2.Display();

    std::cout << "\nРезультат додавання: ";
    m1.Add(m2).Display();

    std::cout << "Результат віднімання (Сума 1 - Сума 2): ";
    m1.Sub(m2).Display();

    std::cout << "Результат ділення сум: " << m1.Div(m2) << std::endl;

    double factor = 2.5;
    std::cout << "Множення першої суми на " << factor << ": ";
    m1.MulNum(factor).Display();

    std::cout << "Ділення першої суми на " << factor << ": ";
    m1.DivNum(factor).Display();

    int cmp = m1.Compare(m2);
    if (cmp > 0) std::cout << "Перша сума більша за другу.\n";
    else if (cmp < 0) std::cout << "Перша сума менша за другу.\n";
    else std::cout << "Суми рівні.\n";

    return 0;
}
