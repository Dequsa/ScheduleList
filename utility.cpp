#include "utility.h"
#include <iostream>
#include "TaskArray.h"

int Partition(TaskArray &task_array, int low, int high, const char order) {
    Task pivot = task_array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (order == 'A' && task_array[j] < pivot) {
            i++;
            std::swap(task_array[i], task_array[j]);
        } else if (order == 'D' && pivot < task_array[j]) {
            i++;
            std::swap(task_array[i], task_array[j]);
        }
    }
    std::swap(task_array[i + 1], task_array[high]);
    return i + 1;
}

void Sort(TaskArray &task_array, int low, int high, const char order) {
    if (low < high) {
        int pi = Partition(task_array, low, high, order);

        Sort(task_array, low, pi - 1, order);
        Sort(task_array, pi + 1, high, order);
    }
}

TaskArray Utility::QuickSort(const TaskArray &task_array, const char order) {
    TaskArray sorted_array = task_array;
    int low = 0;
    int high = sorted_array.GetSize() - 1;

    Sort(sorted_array, low, high, order);

    return sorted_array;
}
