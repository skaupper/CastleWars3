#ifndef CORE_TEST_H
#define CORE_TEST_H

#include "gtest/gtest.h"
#include "SDLMock.h"

class CoreTest : public ::testing::Test
{
    public:
        CoreTest()
        {
        }

        virtual ~CoreTest()
        {
        }

        virtual void SetUp()
        {
        }

        virtual void TearDown()
        {
        }
};

#endif
