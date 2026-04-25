//
// Created by marci on 4/18/2026.
//

#include "TaskScheduler.h"
#include "utility.h"
#include <iostream>
using std::cin, std::cout, std::endl;

bool TaskScheduler::ChooseCommand(TaskArray &task_array, const char cmd) {
    switch (cmd) {
        case 'A':
            cin >> cpu_count_;
            PrintBestCmax(task_array);
            return EXIT_SUCCESS;
        case 'B':
            cin >> cpu_count_;
            BasicListScheduling(task_array);
            return EXIT_SUCCESS;
        case 'L':
            cin >> cpu_count_;
            LongestProcessingTimeFirstScheduling(task_array);
            return EXIT_SUCCESS;
        case 'S':
            cin >> cpu_count_;
            ShortestProcessingTimeFirstScheduling(task_array);
            return EXIT_SUCCESS;
        case '+':
            AddTask(task_array);
            return EXIT_SUCCESS;
        case '-':
            RemoveTask(task_array);
            return EXIT_SUCCESS;
        case 'Q':
            return EXIT_FAILURE;
        default:
            cout << "Invalid command." << endl;
            return EXIT_FAILURE;
    }
}

size_t TaskScheduler::GetTaskCount() {
    size_t task_count;
    cin >> task_count;
    return task_count;
}

double TaskScheduler::GetTaskLength() {
    double task_length;
    cin >> task_length;
    return task_length;
}

void TaskScheduler::BackTrack(const int task_id, double loads[], const TaskArray &task_array, double &best_cmax, const int cpu_num) const {
    // perform the checking if and only if there is no more task in the queue
    if (task_id == task_array.GetSize()) {
        double max = loads[0];

        // look for highest loaded cpu task
        for (int i = 1; i < cpu_num; i++) {
            if (loads[i] > max) {
                max = loads[i];
            }
        }

        if (max < best_cmax) {
            // best cmax is the longest because cpu can't compute faster than 100% speed
            best_cmax = max;
        }
        return;
    }

    // assign tasks to each cpu one by one
    for (int i = 0; i < cpu_num; i++) {

        // if cpu_i length + new task is longer then cmax don't search
        if (loads[i] + task_array[task_id].GetLength() >= best_cmax) {
            continue;
        }

        // add task to cpu
        loads[i] += task_array[task_id].GetLength();

        // just go to another task
        BackTrack(task_id + 1, loads, task_array, best_cmax, cpu_num);

        // remove the task from the cpu slot and go assign it to another cpu and do all over again
        loads[i] -= task_array[task_id].GetLength();
    }
}

double TaskScheduler::FindBestCMax(const TaskArray &task_array) const {
    auto *loads = new double[cpu_count_]{};

    double best_cmax = 0.0;

    // make Cmax length of all tasks so it is larger than the largest task from the list
    for (size_t i = 0; i < task_array.GetSize(); i++) {
        best_cmax += task_array[i].GetLength();
    }

    BackTrack(0, loads, task_array, best_cmax, cpu_count_);

    delete []loads;

    return best_cmax;
}

void TaskScheduler::PrintBestCmax(const TaskArray &task_array) const {
    const auto Copt = FindBestCMax(task_array);
    cout << "Copt: " << Copt << '\n';
}

void TaskScheduler::LowestUsageCPUFirst(const TaskArray &task_array, CPU pc[]) const {
    if (cpu_count_ < 0) return;

    for (size_t i = 0; i < task_array.GetSize(); i++) {

        int min_idx = 0;

        for (int j = 0; j < cpu_count_; j++) {
            if (pc[j].GetAvailability() < pc[min_idx].GetAvailability()) {
                min_idx = j;
            }
        }

        pc[min_idx].ScheduleTask(task_array[i]);
    }
}

void TaskScheduler::RoundRobinAssign(const TaskArray &task_array, CPU pc[]) const {
    if (cpu_count_ < 0) return;

    // assign task to CPUs 1 2 3 4 1 2 3 4 1 2 ...
    for (size_t i = 0; i < task_array.GetSize(); i++) {
        pc[i % cpu_count_].ScheduleTask(task_array[i]);
    }
}

void TaskScheduler::PrintCPUs(const CPU pc[]) const {
    double Cmax = pc[0].GetAvailability();
    double SigmaC = 0;
    for (int i = 0; i < cpu_count_; i++) {
        if (pc[i].GetAvailability() > Cmax) {
            Cmax = pc[i].GetAvailability();
        }
        SigmaC += pc[i].GetSigmaC();
    }

    cout << "Cmax: " << Cmax << '\n';
    cout << "sigmaC: " << SigmaC << '\n';

    for (int i = 0; i < cpu_count_; i++) {
        cout << pc[i] << '\n';
    }
}

void TaskScheduler::BasicListScheduling(const TaskArray &task_array) const {
    // no sorting just run the tasks in the order they were added
    const auto pc = new CPU[cpu_count_];

    for (int i = 0; i < cpu_count_; i++) {
        pc[i].SetId(i);
    }

    LowestUsageCPUFirst(task_array, pc);
    PrintCPUs(pc);

    delete[] pc;
}

void TaskScheduler::LongestProcessingTimeFirstScheduling(const TaskArray &task_array) const {
    // sort the tasks by length in descending order and run them
    const auto LFS = Utility::QuickSort(task_array, 'D');

    const auto pc = new CPU[cpu_count_];
    for (int i = 0; i < cpu_count_; i++) {
        pc[i].SetId(i);
    }

    LowestUsageCPUFirst(LFS, pc);
    PrintCPUs(pc);

    delete[] pc;
}

void TaskScheduler::ShortestProcessingTimeFirstScheduling(const TaskArray &task_array) const {
    // sort the tasks by length in ascending order and run them
    const auto SFS = Utility::QuickSort(task_array, 'D');

    const auto pc = new CPU[cpu_count_];
    for (int i = 0; i < cpu_count_; i++) {
        pc[i].SetId(i);
    }

    RoundRobinAssign(SFS, pc);

    for (size_t i = 0; i < cpu_count_; i++) {
        // sort in non-increasing order
        pc[i].SortExecutionOrder('A');
        pc[i].ReCalculateSigmaC();
    }

    PrintCPUs(pc);

    delete[] pc;
}

void TaskScheduler::RunScheduler() {
    const auto task_count = GetTaskCount();

    TaskArray task_array;

    for (size_t i = 0; i < task_count; i++) {
        Task task(GetTaskLength());
        task_array.PushBack(task);
    }

    char cmd = '\0';
    while (cin >> cmd) {
        ChooseCommand(task_array, cmd);
    }
}

void TaskScheduler::AddTask(TaskArray &tasks) {
    double l = 0;
    size_t i = 0;
    cin >> i >> l;
    const Task task{l};
    tasks.Insert(i - 1, task);
}

void TaskScheduler::RemoveTask(TaskArray &tasks) {
    size_t i = 0;
    cin >> i;
    tasks.DeleteById(i);
}
