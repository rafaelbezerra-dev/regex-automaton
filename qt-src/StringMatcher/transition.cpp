#include "transition.h"

Transition::Transition(){}

Transition::Transition(int from, int to, string symbol)
    : from(from), to(to), symbol(symbol)
{
}
