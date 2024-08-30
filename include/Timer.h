#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
    Timer();

    void Update(double dt);
    void Restart();
    double Get();

private:
    double time;
};

#endif // TIMER_H
