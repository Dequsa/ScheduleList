//
// Created by marci on 4/18/2026.
//

#include "TaskArray.h"

void TaskArray::Resize() {
    // if 1 then 2, if 2 then 4, if 4 then 8, etc.
    const size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

    // copy all the data to the new array
    const auto new_data = new Task[new_capacity];
    for (size_t i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;

    // set the new data and capacity
    data = new_data;
    capacity = new_capacity;
}

void TaskArray::PushBack(const Task &task) {
    if (size >= capacity) {
        Resize();
    }

    if (task.GetLength() > largest_task_length) {
        largest_task_length = task.GetLength();
    }

    data[size++] = task;
    total_length += task.GetLength();
}

void TaskArray::Delete(const size_t index) {
    if (index >= size) {
        return;
    }

    total_length -= data[index].GetLength();
    if (data[index].GetLength() == largest_task_length) {
        largest_task_length = 0;
    }

    // shift all the elements after the index to the left
    for (size_t i = index; i < size - 1; i++) {
        if (data[i].GetLength() > largest_task_length) largest_task_length = data[i].GetLength();

        data[i] = data[i + 1];
    }
    size--;
}

void TaskArray::DeleteById(const size_t n) {
    if (n > Task::GetGlobalMaxId()) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (data[i].GetId() == n) {
            Delete(i);
            return;
        }
    }
}

void TaskArray::Insert(const size_t index, const Task &task) {
    if (index > size) {
        return;
    }

    if (size >= capacity) {
        Resize();
    }

    // shift all the elements after the index to the right
    for (size_t i = size; i > index; i--) {
        data[i] = data[i - 1];
    }

    if (task.GetLength() > largest_task_length) {
        largest_task_length = task.GetLength();
    }

    data[index] = task;
    total_length += task.GetLength();
    size++;
}
