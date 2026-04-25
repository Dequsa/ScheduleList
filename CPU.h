//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_CPU_H
#define LISTSCHEDULING_CPU_H
#include "TaskArray.h"


class CPU {
    int id_ = 0;
    double available_in_ = 0;
    double SigmaC_ = 0;
    TaskArray scheduled_tasks_;

public:
    CPU() = default;

    ~CPU() = default;

    void ScheduleTask(const Task &task);

    // getters
    double GetAvailability() const { return available_in_; }

    double GetSigmaC() const { return SigmaC_; }

    // setters
    void SetId(const int id) { id_ = id; };

    // operators
    CPU &operator=(CPU *cpu) {
        available_in_ = cpu->available_in_;
        scheduled_tasks_ = cpu->scheduled_tasks_;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const CPU &cpu) {
        os << "M" << cpu.id_ + 1 << ":";
        double task_completed_in = 0;
        for (int i = 0; i < cpu.scheduled_tasks_.GetSize(); i++) {
            const size_t task_id = cpu.scheduled_tasks_[i].GetId();
            task_completed_in += cpu.scheduled_tasks_[i].GetLength();
            os << "( C" << task_id << " = " << task_completed_in << " )";
        }
        return os;
    }
};


#endif //LISTSCHEDULING_CPU_H
