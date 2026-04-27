//
// Created by marci on 4/18/2026.
//

#include "CPU.h"
#include "utility.h"

void CPU::ScheduleTask(const Task &task) {
    scheduled_tasks_.PushBack(task);
    available_in_ += task.GetLength();
    SigmaC_ += available_in_;
}

void CPU::ScheduleSegment(const Task &task, const double start, const double end, const bool is_remainder) {
    const double length = end - start;
    Task t(length, task.GetId());

    t.SetRemainderFlag(is_remainder);

    scheduled_tasks_.PushBack(t);

    available_in_ = end;
    // SigmaC_ += available_in_;
}

void CPU::SortExecutionOrder(const char order) {
    scheduled_tasks_ = Utility::QuickSort(scheduled_tasks_, order);
}

void CPU::ReCalculateSigmaC() {
    available_in_ = 0;
    SigmaC_ = 0;

    for (size_t i = 0; i < scheduled_tasks_.GetSize(); i++) {
        const Task &task = scheduled_tasks_[i];
        available_in_ += task.GetLength();
        SigmaC_ += available_in_;
    }
}

