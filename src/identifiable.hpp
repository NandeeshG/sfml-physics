#ifndef IDENTIFIABLE_HPP
#define IDENTIFIABLE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace my {

static int monotonic_ids = 1;

class Identifiable {
public:
    Identifiable();
    int get_id() const;

private:
    int id;
};

}

#endif