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
    bool is_remainder = false;

public:
    explicit Task(const double task_length) : length(task_length) { id = global_id++; }

    Task(const double task_length, const int id) : id(id), length(task_length) {}

    Task(const Task &other) = default;

    Task()= default;

    ~Task() = default;

    // setters
    void SetLength(double new_length) { length = new_length; }

    void SetId(int new_id) { id = new_id; }

    void DecreaseLength(double n) { length -= n; }

    void SetRemainderFlag( const bool what) { is_remainder = what; }

    // getters
    int GetId() const { return id; }

    double GetLength() const { return length; }

    static size_t GetGlobalMaxId() { return global_id; }

    bool IsRemainder() const { return is_remainder; }

    // operators
    friend std::ostream &operator<<(std::ostream &os, const Task &task) {
        os << "Task ID: " << task.id << " | Length: " << task.length;
        return os;
    }

    bool operator==(const Task &other) const {
        return id == other.id && length == other.length;
    }

    bool operator<(const Task &other) const {
        if (length == other.length) {
            return id < other.id;
        }
        return length < other.length;
    }

    Task &operator=(const Task &other) {
        id = other.id;
        length = other.length;
        is_remainder = other.is_remainder;
        return *this;
    }
};

#endif // LISTSCHEDULING_TASK_H
