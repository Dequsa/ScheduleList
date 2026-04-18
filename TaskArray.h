//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_TASKARRAY_H
#define LISTSCHEDULING_TASKARRAY_H
#include "Task.h"

class TaskArray {
    size_t capacity = 0;
    size_t size = 0;
    Task* data = nullptr;

    void Resize();

public:
    TaskArray() = default;

    ~TaskArray() { 
        delete[] data;
    };

    void add(const Task& task);

    void Delete(const size_t index);
};


#endif //LISTSCHEDULING_TASKARRAY_H