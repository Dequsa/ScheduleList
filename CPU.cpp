//
// Created by marci on 4/18/2026.
//

#include "CPU.h"

void CPU::ScheduleTask(const Task task) {
    scheduled_tasks_.PushBack(task);
    available_in_ += task.GetLength();
    SigmaC_ += available_in_;
}

