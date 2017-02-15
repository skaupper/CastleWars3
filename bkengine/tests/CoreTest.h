#ifndef CORE_TEST_H
#define CORE_TEST_H

#include "gtest/gtest.h"
#include "SDLMock.h"

class CoreTest : public ::testing::Test
{
    public:
        SDLMock *mock;

        CoreTest()
        {
        }

        virtual ~CoreTest()
        {
        }

        virtual void SetUp()
        {
            mock = new SDLMock;
        }

        virtual void TearDown()
        {
            delete mock;
        }
};

#endif