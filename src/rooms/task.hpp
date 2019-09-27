#pragma once

#include <cmath>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

enum class TaskState {
    Running,
    Finished,
};

class TaskPool {
public:
    void addTask(std::function<TaskState(float)>&& task)
    {
        _tasks.push_back(std::move(task));
    }

    void update(float delta)
    {
        for (size_t i = 0; i < _tasks.size(); ) {
            auto state = _tasks[i](delta);
            if (state == TaskState::Finished) {
                std::swap(_tasks[i], _tasks.back());
                _tasks.resize(_tasks.size() - 1);
            } else {
                i++;
            }
        }
    }

private:
    std::vector<std::function<TaskState(float)>> _tasks;
};

class SwayTask {
public:
    SwayTask(
            float period,
            std::function<void(float value)>&& setter)
        : _period(period)
        , _setter(std::move(setter))
    { }

    TaskState operator()(float delta)
    {
        _point = std::fmod(_point * _period + delta, _period) / _period;
        auto value = 0.5 + std::sin(_point * 2 * M_PI) / 2;
        _setter(value);
        return TaskState::Running;
    }

private:
    const float _period;
    const std::function<void(float value)> _setter;
    float _point = 0;
};
