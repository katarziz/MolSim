// Created by cpsch on 12.05.2025.

#include "ParticleContainerTest.h"
#include <gtest/gtest.h>
#include "../../src/utils/ArrayUtils.h"
#include "objects/BasicParticleContainer.h"


/*!Test initialization of an empty Particle container*/
TEST(EmpytInitTest, ParticleContainerTests) {
    BasicParticleContainer emp = BasicParticleContainer();
    // Expect equality.
    EXPECT_EQ(0, emp.size());
    EXPECT_EQ(emp.begin(), emp.end());
}

/*!Test initialization of a Particle container*/
TEST(InitTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer(coll);
    EXPECT_EQ(coll.size(), con.size());
    for (int i = 0; i < coll.size(); i++) {
        EXPECT_TRUE(particle_sem_eq(coll[i],con.getParticles()[i]));
    }
}

TEST(SizeTest, ParticleContainerTests) {
    BasicParticleContainer emp = BasicParticleContainer();
    BasicParticleContainer con = BasicParticleContainer(coll);
    BasicParticleContainer con2 = BasicParticleContainer(coll3);
    BasicParticleContainer con3 = BasicParticleContainer(coll);
    EXPECT_EQ(emp.size(), 0);
    emp.addParticle(p4);
    EXPECT_EQ(emp.size(), 1);

    EXPECT_NE(emp.size(), con.size());
    EXPECT_NE(con2.size(), con.size());
    EXPECT_EQ(con.size(), con3.size());
    con3.addParticle(p4);
    EXPECT_NE(con3.size(), con.size());
    EXPECT_EQ(con2.size(), con3.size());
}

TEST(AddParticleTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer(coll);
    EXPECT_EQ(2, con.size());
    con.addParticle(p3);
    EXPECT_EQ(3, con.size());
    EXPECT_TRUE(particle_sem_eq(con.getParticles()[con.size()-1],p3));
}

TEST(AddParticlesTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer();
    EXPECT_EQ(con.size(), 0);
    con.addParticles(coll);
    EXPECT_EQ(con.size(), coll.size());
    for (int i = 0; i < con.size(); i++) {
        EXPECT_TRUE(particle_sem_eq(con.getParticles()[i],coll[i]));
    }
    BasicParticleContainer con2 = BasicParticleContainer({p3});
    EXPECT_EQ(con2.size(), 1);
    con2.addParticles(coll);
    EXPECT_EQ(con2.size(), coll3.size());
    for (int i = 0; i < con2.size(); i++) {
        EXPECT_TRUE(BasicParticleContainer::contains(con2,coll3[i]));
    }
}

TEST(GetParticlesTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer(coll);
    EXPECT_EQ(con.size(), coll.size());
    for (int i = 0; i < coll.size(); i++) {
        EXPECT_TRUE(particle_sem_eq(coll[i],con.getParticles()[i]));
    }
}

TEST(IteratorTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer(coll);
    auto j = coll.begin();
    for (auto &i: con) {
        EXPECT_TRUE(particle_sem_eq(i,*j));
        ++j;
    }
}

TEST(ContainsTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer(coll);
    EXPECT_FALSE(BasicParticleContainer::contains(con,p3));
    con.addParticle(p3);
    EXPECT_TRUE(BasicParticleContainer::contains(con,p3));
}

TEST(ContSemEquTest, ParticleContainerTests) {
    BasicParticleContainer con = BasicParticleContainer(coll);
    BasicParticleContainer con2 = BasicParticleContainer(coll);
    BasicParticleContainer con3 = BasicParticleContainer(coll3);
    EXPECT_FALSE(BasicParticleContainer::cont_sem_eq(con,con3));
    EXPECT_TRUE(BasicParticleContainer::cont_sem_eq(con,con2));
    con2.addParticle(p3);
    EXPECT_FALSE(BasicParticleContainer::cont_sem_eq(con,con2));
    EXPECT_TRUE(BasicParticleContainer::cont_sem_eq(con3,con2));
}

/*!Test the iteration over Particle Pairs and check that forces are updted correctly */
TEST(ParticlePairIterTest, ParticleContainerTests) {
    Particle t1 = Particle({1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, 1.0, 5, 1, 0);
    BasicParticleContainer con = BasicParticleContainer(coll3);
    con.addParticle(t1);
    for (auto particle1 = con.begin(); particle1 != con.end(); ++particle1) {
        for (auto particle2 = con.begin(); particle2 != particle1; ++particle2) {
            particle1->setF(particle1->getF() + 5 * (particle1->getX() - particle2->getX()));
            particle2->setF(particle2->getF() - 5 * (particle1->getX() - particle2->getX()));
        }
    }
    for (auto particle = con.begin(); particle != con.end(); ++particle) {
        for (auto i = 0; i < 3; ++i) {
            EXPECT_NE(particle->getF()[i], 0.0);
        }
    }
}
