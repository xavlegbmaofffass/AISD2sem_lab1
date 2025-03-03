#include <iostream>
#include <chrono>
#include <limits>
using namespace std::chrono;
using namespace std;

unsigned long int recursion(unsigned long int n) {
    if (n <= 0) {
        return 0;
    }
    if (n <= 1) {
        return 1;
    }
    return recursion(n - 1) + recursion(n - 2);
}

unsigned long int fibonacci_array(unsigned long int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long int* ch = new unsigned long int[n + 1];
    ch[0] = 0;
    ch[1] = 1;
    for (unsigned long int i = 2; i <= n; i++) {
        ch[i] = ch[i - 1] + ch[i - 2];
    }
    unsigned long int result = ch[n];
    delete[] ch;
    return result;
}

void measure_time(unsigned long int n, unsigned long int (*fib_func)(unsigned long int), const string& method_name) {
    auto start = high_resolution_clock::now();
    unsigned long int result = fib_func(n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    auto minutes = duration.count() / 60000;
    auto seconds = (duration.count() % 60000) / 1000;
    auto milliseconds = duration.count() % 1000;
    auto microseconds = duration.count() % 1000;

    cout << "Число под номером n: " << result << endl;
    cout << "Расчетное время выполнения " << method_name << ": "
        << minutes << " минут " << seconds << " секунд " << milliseconds << " миллисекунд " << microseconds << " микросекунд" << endl;
}

int main() {
    setlocale(LC_ALL, "Ru");
    long long int n;
    while (true) {
        cout << "Введите номер числа n: ";

        if (!(cin >> n)) {
            cout << "Ошибка: Введено нечисловое значение. Пожалуйста, введите целое число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (n < 0) {
            cout << "Ошибка: номер числа должен быть неотрицательным." << endl;
            continue;
        }

        int choice;
        cout << "Выберите вариант выполнения (1 - линейный, 2 - рекурсия, 3 - выход): ";

        if (!(cin >> choice)) {
            cout << "Ошибка: Введено нечисловое значение. Пожалуйста, введите целое число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            measure_time(n, fibonacci_array, "циклом");
        }
        else if (choice == 2) {
            measure_time(n, [](unsigned long int n) -> unsigned long int { return recursion(n); }, "рекурсией");
        }
        else if (choice == 3) {
            cout << "Выход из программы." << endl;
            break;
        }
        else {
            cout << "Ошибка: Неверный выбор. Пожалуйста, выберите 1, 2 или 3." << endl;
        }
    }

    return 0;
}