//
// Created by marci on 4/18/2026.
//

#include "TaskArray.h"

void TaskArray::Resize() {
    // if 1 then 2, if 2 then 4, if 4 then 8, etc.
    size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

    // copy all the data to the new array
    Task* new_data = new Task[new_capacity];
    for (size_t i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    
    // set the new data and capacity
    data = new_data;
    capacity = new_capacity;
}

void TaskArray::add(const Task &task) {
    if (size >= capacity) {
        Resize();
    }
    data[size++] = task;
}

void TaskArray::Delete(const size_t index) {
    if (index >= size) {
        return;
    }

    // shift all the elements after the index to the left
    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}
