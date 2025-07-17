//
// Created by cpsch on 05.06.2025.
//

#ifndef LINKEDCELLCONTAINERTEST_H
#define LINKEDCELLCONTAINERTEST_H
#include <array>
#include <cstdint>

/**
 * cutoff radius to be used in tests
 */
inline const double cutoff=3.0;

/**
 * box_size to be used in tests
 */
inline const std::array<double, 3> box_size={cutoff,cutoff,1.0};
/**
 * cell_number to be used in tests
 */
inline const std::array<int, 3> cell_number = {1, 1, 1};

#endif //LINKEDCELLCONTAINERTEST_H
