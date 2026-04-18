//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_INPUTHANDLER_H
#define LISTSCHEDULING_INPUTHANDLER_H
#include "TaskArray.h"
#pragma once
class TaskScheduler {

    int cpu_count_ = 0;

    bool ChooseCommand(const TaskArray &task_array);

    void GetCommandParameters();

    size_t GetTaskCount() const;

    double GetTaskLength() const;

    void BasicListScheduling(const TaskArray &task_array) const;

    void LongestProcessingTimeFirstScheduling(const TaskArray &task_array) const;

    void ShortestProcessingTimeFirstScheduling(const TaskArray &task_array) const;
public:
    TaskScheduler() = default;

    ~TaskScheduler() = default;

    void RunScheduler();

    void AddTask(const TaskArray &tasks);

    void RemoveTask(const TaskArray &tasks);
};


#endif //LISTSCHEDULING_INPUTHANDLER_H
