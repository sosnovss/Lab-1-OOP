#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

class ZavdClass
{
    double a, b;

public:
    ZavdClass() : a(0.0), b(0.0) {}

    // Метод для обчислення функції b[x, y, z]
    void Fn_b(double x, double y, double z)
    {
        double tg_val = std::tan(std::pow(std::abs(x), 0.3));

        // Захист від ділення на нуль, якщо tg_val дуже близький до 0 (наприклад, при x = 0)
        if (std::abs(tg_val) < 1e-9) {
            b = 0.0;
            return;
        }

        double term1_num = x * x + (z * z / std::pow(tg_val, 2));
        double term1_den = 3 + x + (y * y) / Faktr(2) + std::pow(z, 3) / Faktr(3);

        double log_val = std::log(std::pow(std::abs(y / z), 1.0 / 3.0));
        double term2 = std::pow(std::abs(log_val), 0.3);

        b = (term1_num / term1_den) + term2;
    }

    // Метод для обчислення функції a[x, y, z, b]
    void Fn_a(double x, double y, double z)
    {
        double num = 2 * std::cos(std::pow(std::abs(x), 1.0 / 3.0)) - (x * x) / 6.0;
        
        // Захист від ділення на нуль, якщо b дорівнює 0
        if (std::abs(b) < 1e-9) {
            a = 0.0;
            return;
        }

        double den = (z / b) + std::pow(std::sin(std::pow(y + z, 3)), 2);
        double term2 = std::pow(std::log(std::pow(std::abs(z), 0.6)), 2);

        a = (num / den) + term2;
    }

    double Faktr(int n)
    {
        double f = 1;
        if (n > 1)
            for (int i = 2; i <= n; i++)
                f *= i;
        return f;
    }

    double geta() const { return a; }
    double getb() const { return b; }
};

int main()
{
    // Налаштування кодування консолі
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int N = 5; // Варіант

    // Розрахунок 1 (базовий)
    double x_base = 0.48 * N;
    double y = 0.47 * N;
    double z = -1.32 * N;

    ZavdClass Zavd;

    Zavd.Fn_b(x_base, y, z);
    Zavd.Fn_a(x_base, y, z);

    // Використовуємо англійські букви, щоб уникнути появи "???" в консолі
    std::cout << "=== TASK 1 (Base calculation) ===" << std::endl;
    std::cout << "x = " << x_base << ", y = " << y << ", z = " << z << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "a = " << Zavd.geta() << std::endl;
    std::cout << "b = " << Zavd.getb() << std::endl;

    // Розрахунок 2 (Таблиця)
    std::cout << "\n=== TASK 2 (Tabulation) ===" << std::endl;
    double x_start = -1.0;
    double x_end = 1.0;
    double dx = 0.2;

    // Заголовки таблиці
    std::cout << std::setw(10) << "x" << " | "
              << std::setw(15) << "b" << " | "
              << std::setw(15) << "a" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    for (double x = x_start; x <= x_end + dx / 2; x += dx)
    {
        if (std::abs(x) < 1e-9) x = 0.0;

        Zavd.Fn_b(x, y, z);
        Zavd.Fn_a(x, y, z);

        // Виведення рядка таблиці з фіксованою точністю (4 знаки після коми)
        std::cout << std::setw(10) << x << " | "
                  << std::setw(15) << Zavd.getb() << " | "
                  << std::setw(15) << Zavd.geta() << std::endl;
    }

    return 0;
}