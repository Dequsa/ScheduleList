//
// Created by marci on 4/18/2026.
//

#include "TaskScheduler.h"
#include "CPU.h"
#include "utility.h"
#include <iostream>

using std::cin, std::cout, std::endl;

bool TaskScheduler::ChooseCommand(const TaskArray &task_array) {
    cin.clear();
    char cmd = '\0';
    cin >> cmd;

    switch (cmd) {
        case 'B':
            cin >> cpu_count_;
            BasicListScheduling(task_array);
            return true;
        case 'L':
            cin >> cpu_count_;
            LongestProcessingTimeFirstScheduling(task_array);
            return true;
        case 'S':
            cin >> cpu_count_;
            ShortestProcessingTimeFirstScheduling(task_array);
            return true;
        case '+':
            AddTask(task_array);
            return true;
        case '-':
            RemoveTask(task_array);
            return true;
        case 'Q':
            return false;
        default:
            cout << "Invalid command." << endl;
            return ChooseCommand(task_array);
    }
}

void TaskScheduler::GetCommandParameters() {
}

size_t TaskScheduler::GetTaskCount() const {
    size_t task_count;
    cin >> task_count;
    return task_count;
}

double TaskScheduler::GetTaskLength() const {
    double task_length;
    cin >> task_length;
    return task_length;
}

void TaskScheduler::BasicListScheduling(const TaskArray &task_array) const {
    // no sorting just run the tasks in the order they were added
    int cpu_id = 0;
    auto pc = new CPU[cpu_count_];

    for (int i = 0; i < task_array.GetSize(); i++) {
        int min_idx = cpu_count_ - 1;
        for (int j = 0; j < cpu_count_; j++) {
            if (pc[j].GetAvailability() < pc[min_idx].GetAvailability()) {
                min_idx = j;
            }
        }
        pc[min_idx].ScheduleTask(task_array[i]);
    }

    double Cmax = pc[0].GetAvailability();
    double SigmaC = 0;
    for (int i = 0; i < cpu_count_; i++) {
        if (pc[i].GetAvailability() > Cmax) {
            Cmax = pc[i].GetAvailability();
        }
        SigmaC += pc[i].GetAvailability();
    }

    cout << "Cmax: " << Cmax << '\n';
    cout << "sigmaC: " << SigmaC << '\n';

    for (int i = 0; i < cpu_count_; i++) {
        cout << pc[i] << '\n';
    }

    delete[] pc;
}

void TaskScheduler::LongestProcessingTimeFirstScheduling(const TaskArray &task_array) const {
    // sort the tasks by length in descending order and run them
    const auto LFS= Utility::QuickSort(task_array, 'D');

}

void TaskScheduler::ShortestProcessingTimeFirstScheduling(const TaskArray &task_array) const {
    // sort the tasks by length in ascending order and run them
    const auto SFS  = Utility::QuickSort(task_array, 'A');
}

void TaskScheduler::RunScheduler() {
    const auto task_count = GetTaskCount();

    TaskArray task_array;

    for (size_t i = 0; i < task_count; i++) {
        Task task(GetTaskLength());
        task_array.PushBack(task);
    }

    for (size_t i = 0; i < task_count; i++) {
        cout << task_array[i] << endl;
    }

    while (ChooseCommand(task_array)) {
        if (cpu_count_ < 0) {
            cout << "Invalid CPU count." << endl;
            continue;
        }

        cout << "CPU Count: " << cpu_count_ << endl;
        for (size_t i = 0; i < task_array.GetSize(); i++) {
            cout << task_array[i] << endl;
        }
    }
}

void TaskScheduler::AddTask(const TaskArray &tasks) {
}

void TaskScheduler::RemoveTask(const TaskArray &tasks) {
}
