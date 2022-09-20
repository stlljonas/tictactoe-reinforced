#include "IAgent.h"

bool IAgent::operator==(const IAgent& other) const {
    return id() == other.id();
}