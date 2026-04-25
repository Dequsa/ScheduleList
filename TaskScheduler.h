//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_INPUTHANDLER_H
#define LISTSCHEDULING_INPUTHANDLER_H
#include "TaskArray.h"
#include "CPU.h"
#pragma once
class TaskScheduler {

    int cpu_count_ = 0;

    bool ChooseCommand(TaskArray &task_array);

    void GetCommandParameters();

    size_t GetTaskCount() const;

    double GetTaskLength() const;

    void SchedulePrintTasksToCPUs(const TaskArray &task_array, CPU pc[]) const;

    void BackTrack( const int task_id, double loads[], const TaskArray &task_array, double &best_cmax, const int cpu_num) const;
    double FindBestCMax(const TaskArray &task_array) const;
    void PrintBestCmax(const TaskArray &task_array) const;

    void BasicListScheduling(const TaskArray &task_array) const;

    void LongestProcessingTimeFirstScheduling(const TaskArray &task_array) const;

    void ShortestProcessingTimeFirstScheduling(const TaskArray &task_array) const;
public:
    TaskScheduler() = default;

    ~TaskScheduler() = default;

    void RunScheduler();

    void AddTask(TaskArray &tasks);

    void RemoveTask(TaskArray &tasks);
};


#endif //LISTSCHEDULING_INPUTHANDLER_H
