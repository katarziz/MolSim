//
// Created by cpsch on 05.06.2025.
//

#include "LinkedCellContainerTest.h"
#include <gtest/gtest.h>
#include <utils/ArrayUtils.h>
#include <objects/LinkedCellParticleContainer.h>

/*!Test initialization of an empty Linked CellParticle container*/
TEST(EmpytInitTest, LinkedCellContainerTests) {
    LinkedCellParticleContainer emp=LinkedCellParticleContainer(box_size,cell_number,cutoff,{0,0,0,0,0,0});
    // Expect equality.
    EXPECT_EQ(0, emp.size());
    EXPECT_EQ(emp.begin(),emp.end());
}

TEST(OutflowTest,BoundaryTests){}
TEST(ReflectionTest,BoundaryTests){}
TEST(PeriodicTest,BoundaryTests){}