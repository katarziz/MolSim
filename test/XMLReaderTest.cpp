//
// Created by cpsch on 04.06.2025.
//

#include "XMLReaderTest.h"
#include <io/XMLReader.h>
#include <gtest/gtest.h>

#include "objects/LinkedCellParticleContainer.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/sinks/stdout_sinks.h"


TEST(SingleParticleInputTest, XMLReaderTests)
{   std::shared_ptr<spdlog::logger> logger = nullptr;
    try {
    logger = spdlog::basic_logger_mt("default", "logs/log.txt", true);
#if SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_TRACE
    logger->set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG
    logger->set_level(spdlog::level::debug);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO
    logger->set_level(spdlog::level::info);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_WARN
    logger->set_level(spdlog::level::warn);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_ERROR
    logger->set_level(spdlog::level::err);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_CRITICAL
    logger->set_level(spdlog::level::critical);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_OFF
    logger->set_level(spdlog::level::off);
#else
    // Default to info if no match
    logger->set_level(spdlog::level::info);
#endif

} catch (const spdlog::spdlog_ex &ex) {
    spdlog::error("Could not create log file: {}", ex.what());
    exit(-1);
}

    const char *input= "../test/TestInput/XMLReaderTestInputSingleParticle.xml";
    LinkedCellParticleContainer particles= LinkedCellParticleContainer({10,10,10},{1,1,1},1.0,{0,0,0,0,0,0});
    BasicParticleContainer check= BasicParticleContainer({pt1});
    XMLReader::readFile(&particles,input);
     EXPECT_EQ(particles.size(),check.size());
     for (int i=0;i<particles.size();i++)
     {  Particle p=particles.getParticles()[i];
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
{   std::shared_ptr<spdlog::logger> logger = nullptr;
    try {
    logger = spdlog::basic_logger_mt("default", "logs/log.txt", true);
#if SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_TRACE
    logger->set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG
    logger->set_level(spdlog::level::debug);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO
    logger->set_level(spdlog::level::info);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_WARN
    logger->set_level(spdlog::level::warn);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_ERROR
    logger->set_level(spdlog::level::err);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_CRITICAL
    logger->set_level(spdlog::level::critical);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_OFF
    logger->set_level(spdlog::level::off);
#else
    // Default to info if no match
    logger->set_level(spdlog::level::info);
#endif

} catch (const spdlog::spdlog_ex &ex) {
    spdlog::error("Could not create log file: {}", ex.what());
    exit(-1);
}

    const char *input= "../test/TestInput/XMLReaderTestInputSingleCube.xml";
    BasicParticleContainer particles= BasicParticleContainer();
    XMLReader::readFile(&particles,input);
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
{   std::shared_ptr<spdlog::logger> logger = nullptr;
    try {
    logger = spdlog::basic_logger_mt("default", "logs/log.txt", true);
#if SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_TRACE
    logger->set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG
    logger->set_level(spdlog::level::debug);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO
    logger->set_level(spdlog::level::info);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_WARN
    logger->set_level(spdlog::level::warn);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_ERROR
    logger->set_level(spdlog::level::err);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_CRITICAL
    logger->set_level(spdlog::level::critical);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_OFF
    logger->set_level(spdlog::level::off);
#else
    // Default to info if no match
    logger->set_level(spdlog::level::info);
#endif

} catch (const spdlog::spdlog_ex &ex) {
    spdlog::error("Could not create log file: {}", ex.what());
    exit(-1);
}


    const char *input= "../test/TestInput/XMLReaderTestInputAll.xml";
     BasicParticleContainer particles= BasicParticleContainer();
    XMLReader::readFile(&particles,input);
    EXPECT_EQ(particles.size(),all.size());
    for (int i=0;i<particles.size();i++)
    {   Particle p=particles.getParticles()[i];
        Particle c=all.getParticles()[i];
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
{   std::shared_ptr<spdlog::logger> logger = nullptr;
    try {
        logger = spdlog::basic_logger_mt("default", "logs/log.txt", true);
#if SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_TRACE
        logger->set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG
        logger->set_level(spdlog::level::debug);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO
        logger->set_level(spdlog::level::info);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_WARN
        logger->set_level(spdlog::level::warn);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_ERROR
        logger->set_level(spdlog::level::err);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_CRITICAL
        logger->set_level(spdlog::level::critical);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_OFF
        logger->set_level(spdlog::level::off);
#else
        // Default to info if no match
        logger->set_level(spdlog::level::info);
#endif

    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::error("Could not create log file: {}", ex.what());
        exit(-1);
    }

    const char *input= "../test/TestInput/DiscTestInput.xml";
    BasicParticleContainer particles= BasicParticleContainer();
    XMLReader::readFile(&particles,input);
    EXPECT_EQ(particles.size(),disc_c.size());
    for (int i=0;i<particles.size();i++)
    {   Particle p=particles.getParticles()[i];
        Particle c=disc_c.getParticles()[i];
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
TEST(SphereInputTest,XMLReaderTests)
{   std::shared_ptr<spdlog::logger> logger = nullptr;
    try {
        logger = spdlog::basic_logger_mt("default", "logs/log.txt", true);
#if SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_TRACE
        logger->set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_DEBUG
        logger->set_level(spdlog::level::debug);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_INFO
        logger->set_level(spdlog::level::info);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_WARN
        logger->set_level(spdlog::level::warn);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_ERROR
        logger->set_level(spdlog::level::err);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_CRITICAL
        logger->set_level(spdlog::level::critical);
#elif SPDLOG_ACTIVE_LEVEL == SPDLOG_LEVEL_OFF
        logger->set_level(spdlog::level::off);
#else
        // Default to info if no match
        logger->set_level(spdlog::level::info);
#endif

    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::error("Could not create log file: {}", ex.what());
        exit(-1);
    }

    const char *input= "../test/TestInput/SphereTestInput.xml";
    BasicParticleContainer particles= BasicParticleContainer();
    XMLReader::readFile(&particles,input);
    EXPECT_EQ(particles.size(),sphere_c.size());
    for (int i=0;i<particles.size();i++)
    {   Particle p=particles.getParticles()[i];
        Particle c=sphere_c.getParticles()[i];
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
