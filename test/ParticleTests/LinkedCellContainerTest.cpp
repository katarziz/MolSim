//
// Created by cpsch on 05.06.2025.
//

#include "LinkedCellContainerTest.h"
#include <gtest/gtest.h>
#include "../../src/utils/ArrayUtils.h"
#include "../src/objects/LinkedCellParticleContainer.h"

/*!Test initialization of an empty Linked CellParticle container*/
TEST(EmpytInitTest, LinkedCellContainerTests) {
    LinkedCellParticleContainer emp=LinkedCellParticleContainer(box_size,cell_number,cutoff);
    // Expect equality.
    EXPECT_EQ(0, emp.size());
    EXPECT_EQ(emp.begin(),emp.end());
}