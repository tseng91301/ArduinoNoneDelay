#include<iostream>
#include<functional>
#include<vector>

class _NoneDelay{
    private:
        struct stored_function{
            std::function<auto()> trigger;
            std::function<auto()> dofunc;
        }
}