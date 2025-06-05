//
// Created by cpsch on 04.06.2025.
//

#include "XMLReaderTest.h"
#include "../src/inputReader/XMLReader.h"
#include <gtest/gtest.h>


TEST(SingleParticleInputTest,XMLReaderTests)
{
    const char *input= "../test/TestInput/XMLReaderTestInputSingleParticle.xml";
    ParticleContainer particles=ParticleContainer();
    ParticleContainer check=ParticleContainer({pt1});
    XMLReader fileReader;
    fileReader.readFile(particles,input);
    EXPECT_EQ(particles.size(),check.size());
    for (int i=0;i<particles.size();i++)
    {   Particle p=particles.getParticles()[i];
        Particle c=check.getParticles()[i];
        EXPECT_FLOAT_EQ(p.getM(),c.getM());
        for (auto j=0;j<3;++j)
        {
            EXPECT_FLOAT_EQ(p.getX()[j],c.getX()[j]);
            EXPECT_FLOAT_EQ(p.getOldF()[j],c.getOldF()[j]);
            EXPECT_FLOAT_EQ(p.getF()[j],c.getF()[j]);
            EXPECT_FLOAT_EQ(p.getV()[j],c.getV()[j]);
        }
    }

}

TEST(SingleCubeInputTest,XMLReaderTests)
{  const char *input= "../test/TestInput/XMLReaderTestInputSingleCube.xml";
    ParticleContainer particles=ParticleContainer();
    XMLReader::readFile(particles,input);
    EXPECT_EQ(particles.size(),cube1.size());
    for (int i=0;i<particles.size();i++)
    {   Particle p=particles.getParticles()[i];
        Particle c=cube1.getParticles()[i];
        EXPECT_FLOAT_EQ(p.getM(),c.getM());
        for (auto j=0;j<3;++j)
        {

            EXPECT_FLOAT_EQ(p.getX()[j],c.getX()[j]);
            EXPECT_FLOAT_EQ(p.getOldF()[j],c.getOldF()[j]);
            EXPECT_FLOAT_EQ(p.getF()[j],c.getF()[j]);
            EXPECT_FLOAT_EQ(p.getV()[j],c.getV()[j]);
        }
    }
}

TEST(SingleMixedInputTest,XMLReaderTests)
{ const char *input= "../test/TestInput/XMLReaderTestInputAll.xml";
    ParticleContainer particles=ParticleContainer();
    XMLReader::readFile(particles,input);
    EXPECT_EQ(particles.size(),all.size());
    for (int i=0;i<particles.size();i++)
    {   Particle p=particles.getParticles()[i];
        Particle c=all.getParticles()[i];
        std::cout<<p.toString()<<std::endl;
        std::cout<<c.toString()<<std::endl;
        EXPECT_FLOAT_EQ(p.getM(),c.getM());
        for (auto j=0;j<3;++j)
        {
            EXPECT_FLOAT_EQ(p.getX()[j],c.getX()[j]);
            EXPECT_FLOAT_EQ(p.getOldF()[j],c.getOldF()[j]);
            EXPECT_FLOAT_EQ(p.getF()[j],c.getF()[j]);
            EXPECT_FLOAT_EQ(p.getV()[j],c.getV()[j]);
        }
    }
}
TEST(DiscInputTest,XMLReaderTests)
{ const char *input= "../test/TestInput/DiscTestInput.xml";
    ParticleContainer particles=ParticleContainer();
    XMLReader::readFile(particles,input);
    //EXPECT_EQ(particles.size(),all.size());
    for (int i=0;i<particles.size();i++)
    {   std::cout<<particles.getParticles()[i].toString()<<std::endl;
    }
}