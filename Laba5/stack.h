#pragma once

//stack implementation

template <typename T>
class stack
{
private:
    int p_t;
    T STACK[256];
public:
    stack()
    {
        p_t = -1;
    }
    T pop()
    {
        p_t--;
        return STACK[p_t + 1];
    }
    void push(T v)
    {
        p_t++;
        STACK[p_t] = v;
    }
    int check_pt()
    {
        return p_t;
    }
};

