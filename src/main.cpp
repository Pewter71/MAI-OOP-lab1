#include <cstddef>
#include <iostream>
#include <limits>
#include "array_ops.h"

constexpr std::size_t maxSize{1000000};

void print_array(const int* arr, std::size_t size) {
    std::cout << "Текущий массив: ";
    array_print(arr, size);
}

int main() {
    int* arr{array_create(0)};
    std::size_t size{0};
    int choice{-1};
    while (choice != 0) {
        std::cout << "\n1. Создать массив\n"
                  << "2. Напечатать\n"
                  << "3. Вставить элемент\n"
                  << "4. Удалить элемент\n"
                  << "5. Изменить размер\n"
                  << "6. Поиск\n"
                  << "7. Медиана\n"
                  << "0. Выход\n"
                  << "Выберите пункт: ";
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            choice = -1;
        }

        switch (choice) {
        case 1: {
            std::cout << "Введите размер массива: ";
            std::size_t new_size{};
            if (!(std::cin >> new_size) || new_size > maxSize) {
                std::cout << "Введите корректное число\n";
                break;
            }
            array_delete(arr);
            arr = array_create(new_size);
            size = new_size;
            if (size != 0) {
                std::cout << "Введите " << size << " чисел: ";
                for (std::size_t i{0}; i < size; ++i) {
                    std::cin >> arr[i];
                }
                if (!std::cin) {
                    std::cout << "Не все элементы введены корректно\n";
                }
        }
            print_array(arr, size);
            break;
        }
        case 2:
            print_array(arr, size);
            break;
        case 3: {
            std::cout << "Введите позицию от 0 до " << size << " и значение: ";
            std::size_t pos{};
            int value{};
            if (!(std::cin >> pos >> value) || pos > size) {
                std::cout << "Не все элементы введены корректно\n";
                break;
            }
            arr = array_insert(arr, size, pos, value);
            print_array(arr, size);
            break;
        }
        case 4: {
            if (size == 0) {
                std::cout << "Массив пуст\n";
                break;
            }
            std::cout << "Введите позицию от 0 до " << size - 1 << ": ";
            std::size_t pos{};
            if (!(std::cin >> pos) || pos >= size) {
                std::cout << "Не все элементы введены корректно\n";
                break;
            }
            arr = array_remove(arr, size, pos);
            print_array(arr, size);
            break;
        }
        case 5: {
            std::cout << "Введите новый размер: ";
            std::size_t new_size{};
            if (!(std::cin >> new_size) || new_size >maxSize) {
                std::cout << "Не все элементы введены корректно\n";
                break;
            }
            arr = array_resize(arr, size, new_size);
            size = new_size;
            print_array(arr, size);
            break;
        }
        case 6: {
            std::cout << "Введите искомое число: ";
            int target{};
            if (!(std::cin >> target)) {
                std::cout << "Не все элементы введены корректно\n";
                break;
            }
            if (std::size_t index{}; array_search(arr, size, target, index)) {
                std::cout << "Найден индекс " << index << ", элемент " << arr[index] << '\n';
            } else {
                std::cout << "Не найдено\n";
            }
            break;
        }
        case 7:
            if (size == 0) {
                std::cout << "Массив пуст\n";
                break;
            }
            array_merge_sort(arr, size);
            array_print(arr, size);
            std::cout << "Медиана: " << array_median(arr, size) << '\n';
            break;
        case 0:
            break;
        default:
            std::cout << "Введите корректный пункт\n";
            break;
        }

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    array_delete(arr);
    return 0;
}
