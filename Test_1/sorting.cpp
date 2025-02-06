#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>

// Глобальный мютекс для синхронизации вывода, избегания перемешивания строк
std::mutex coutMutex;

// Функция для вывода вектора (без собственной синхронизации)
void printVector(const std::vector<int>& vec, const std::string& threadName) {
    std::lock_guard<std::mutex> guard(coutMutex);
    std::cout << threadName << std::endl << "Результат: ";
    bool first = true;
    for (int elem : vec) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << elem;
        first = false;
    }
    std::cout << std::endl;
}

// Поток, выполняющий быструю сортировку 
void quickSortThread(std::vector<int> arr) {
    // Сортировка с использованием алгоритма 
    std::sort(arr.begin(), arr.end());
    printVector(arr, "Быстрая сортировка");
}

// Поток, выполняющий пузырьковую сортировку
void bubbleSortThread(std::vector<int> arr) {
    // Реализация пузырьковой сортировки
    bool swapped;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
    printVector(arr, "Сортировка пузырьком");
}

int main() {
    setlocale(LC_ALL, "ru");

    // Исходный массив
    std::vector<int> data = { 4, 2, 3, 1 };

    // Создаем потоки для разных сортировок (каждому даем копию массива)
    std::thread t1(quickSortThread, data);
    std::thread t2(bubbleSortThread, data);

    // Ожидание завершения потоков
    t1.join();
    t2.join();

    return 0;
}
