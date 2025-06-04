// Created by cpsch on 12.05.2025.

#include "ParticleContainerTest.h"
#include <gtest/gtest.h>
#include "../../src/particles/ParticleContainer.h"
#include "../../src/utils/ArrayUtils.h"


/*!Test initialization of an empty Particle container*/
TEST(EmpytInitTest, ParticleContainerTests) {
    ParticleContainer emp=ParticleContainer();
    // Expect equality.
    EXPECT_EQ(0, emp.size());
    EXPECT_EQ(emp.begin(),emp.end());
}

/*!Test initialization of a Particle container*/
TEST(InitTest, ParticleContainerTests) {
    ParticleContainer con=ParticleContainer(coll);
    EXPECT_EQ(coll.size(), con.size());
    for(int i=0;i<coll.size();i++)
    {
        EXPECT_TRUE(particle_sem_eq(coll[i],con.getParticles()[i]));
    }
}
TEST(SizeTest,ParticleContainerTests)
{   ParticleContainer emp=ParticleContainer();
    ParticleContainer con=ParticleContainer(coll);
    ParticleContainer con2=ParticleContainer(coll3);
    ParticleContainer con3=ParticleContainer(coll);
    EXPECT_EQ(emp.size(),0);
    emp.addParticle(p4);
    EXPECT_EQ(emp.size(),1);

    EXPECT_NE(emp.size(),con.size());
    EXPECT_NE(con2.size(),con.size());
    EXPECT_EQ(con.size(),con3.size());
    con3.addParticle(p4);
    EXPECT_NE(con3.size(),con.size());
    EXPECT_EQ(con2.size(),con3.size());

}

TEST(AddParticleTest,ParticleContainerTests)
{   ParticleContainer con=ParticleContainer(coll);
    EXPECT_EQ(2,con.size());
    con.addParticle(p3);
    EXPECT_EQ(3,con.size());
    EXPECT_TRUE(particle_sem_eq(con.getParticles()[con.size()-1],p3));
}

TEST(AddParticlesTest,ParticleContainerTests)
{ ParticleContainer con=ParticleContainer();
  EXPECT_EQ(con.size(),0);
  con.addParticles(coll);
  EXPECT_EQ(con.size(),coll.size());
    for(int i=0;i<con.size();i++)
    {
        EXPECT_TRUE(particle_sem_eq(con.getParticles()[i],coll[i]));
    }
   ParticleContainer con2=ParticleContainer({p3});
    EXPECT_EQ(con2.size(),1);
    con2.addParticles(coll);
    EXPECT_EQ(con2.size(),coll3.size());
    for(int i=0;i<con2.size();i++)
    {
        EXPECT_TRUE(ParticleContainer::contains(con2,coll3[i]));
    }
}

TEST(GetParticlesTest,ParticleContainerTests)
{ ParticleContainer con=ParticleContainer(coll);
    EXPECT_EQ(con.size(),coll.size());
    for(int i=0;i<coll.size();i++)
    {
        EXPECT_TRUE(particle_sem_eq(coll[i],con.getParticles()[i]));
    }
}

TEST(IteratorTest,ParticleContainerTests)
{ ParticleContainer con=ParticleContainer(coll);
    auto j = coll.begin();
    for(auto & i : con)
    { EXPECT_TRUE(particle_sem_eq(i,*j));
        ++j;
    }

}
TEST(ContainsTest,ParticleContainerTests)
{ ParticleContainer con=ParticleContainer(coll);
  EXPECT_FALSE(ParticleContainer::contains(con,p3));
  con.addParticle(p3);
  EXPECT_TRUE(ParticleContainer::contains(con,p3)) ;
}
TEST(ContSemEquTest,ParticleContainerTests)
{   ParticleContainer con=ParticleContainer(coll);
    ParticleContainer con2=ParticleContainer(coll);
    ParticleContainer con3=ParticleContainer(coll3);
    EXPECT_FALSE(ParticleContainer::cont_sem_eq(con,con3));
    EXPECT_TRUE(ParticleContainer::cont_sem_eq(con,con2));
    con2.addParticle(p3);
    EXPECT_FALSE(ParticleContainer::cont_sem_eq(con,con2));
    EXPECT_TRUE(ParticleContainer::cont_sem_eq(con3,con2));

}
/*!Test the iteration over Particle Pairs and check that forces are updted correctly */
TEST(ParticlePairIterTest,ParticleContainerTests)
{   Particle t1=Particle({1.0,1.0,1.0},{0.0,0.0,0.0},1.0,0);
    ParticleContainer con=ParticleContainer(coll3);
    con.addParticle(t1);
    for (auto particle1 = con.begin(); particle1 != con.end(); ++particle1)
    {
        for (auto particle2 = con.begin(); particle2 != particle1; ++particle2)
        {
            particle1->setF(particle1->getF() + 5*(particle1->getX() - particle2->getX()));
            particle2->setF(particle2->getF() - 5*(particle1->getX() - particle2->getX()));

        }
    }
    for (auto particle=con.begin();particle!=con.end();++particle)
    {
        for (auto i=0;i<3;++i){
            EXPECT_NE(particle->getF()[i],0.0);
        }
    }
}
