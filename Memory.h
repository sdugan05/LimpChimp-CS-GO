//
// Created by Saul on 4/21/2021.
//

#ifndef LIMPCHIMP_CS_GO_MEMORY_H
#define LIMPCHIMP_CS_GO_MEMORY_H

#include <memory>

class Memory {
public:

    Memory();

    std::uintptr_t present;
    std::uintptr_t reset;
};

inline std::unique_ptr<const Memory> memory;
#endif //LIMPCHIMP_CS_GO_MEMORY_H
