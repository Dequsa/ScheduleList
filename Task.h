//
// Created by marci on 4/18/2026.
//

#ifndef LISTSCHEDULING_TASK_H
#define LISTSCHEDULING_TASK_H

class Task
{
    static int global_id;
    int id = 0;
    double length = 0.0;
public:
    Task() {
        id = global_id++;
    };

    ~Task() = default;
};

#endif // LISTSCHEDULING_TASK_H
