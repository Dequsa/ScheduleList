//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_TASK_H
#define LISTSCHEDULING_TASK_H
#pragma once
#include <iostream>

class Task {
    static int global_id;
    int id = 0;
    double length = 0.0;

public:
    Task(const double task_length) : length(task_length) { id = global_id++; };

    Task() = default;

    ~Task() = default;

    // setters
    void SetLength(double new_length) { length = new_length; }

    void SetId(int new_id) { id = new_id; }

    // getters
    int GetId() const { return id; }

    double GetLength() const { return length; }

    // operators
    friend std::ostream &operator<<(std::ostream &os, const Task &task) {
        os << "Task ID: " << task.id << " | Length: " << task.length;
        return os;
    }

    bool operator==(const Task &other) const {
        return id == other.id && length == other.length;
    }

    bool operator<(const Task &other) const {
        return length < other.length;
    }
};

#endif // LISTSCHEDULING_TASK_H
