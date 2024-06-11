#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "identifiable.hpp"

namespace my {

Identifiable::Identifiable()
{
    id = monotonic_ids++;
}

int Identifiable::get_id() const
{
    return id;
}

}