//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_TASKARRAY_H
#define LISTSCHEDULING_TASKARRAY_H
#pragma once
#include "Task.h"

class TaskArray {
    size_t capacity = 0;
    size_t size = 0;
    double total_length = 0;
    double largest_task_length = 0;
    Task *data = nullptr;

    void Resize();

public:
    TaskArray(): capacity(5), data(new Task[5]) {
    }

    explicit TaskArray(const size_t n) : capacity(n) {
        data = new Task[n];
    }

    TaskArray(const TaskArray &other) {
        capacity = other.capacity;
        size = other.size;
        total_length = other.total_length;
        largest_task_length = other.largest_task_length;
        data = new Task[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~TaskArray() {
        delete[] data;
    };

    void PushBack(const Task &task);

    void Delete(const size_t index);

    void DeleteById(const int n);

    void Insert(const size_t index, const Task &task);

    size_t GetSize() const {
        return size;
    }

    double GetTotalLength() const { return total_length; }

    double GetLargestLengthTask() const { return largest_task_length; }

    // operators

    Task &operator[](const size_t index) {
        return data[index];
    }

    const Task &operator[](const size_t index) const {
        return data[index];
    }

    TaskArray &operator=(const TaskArray &other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        capacity = other.capacity;
        size = other.size;
        total_length = other.total_length;
        data = new Task[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }
};


#endif //LISTSCHEDULING_TASKARRAY_H
