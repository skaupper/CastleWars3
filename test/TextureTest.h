#ifndef TEXTURE_TEST_H
#define TEXTURE_TEST_H

#include "gtest/gtest.h"
#include "SDLMock.h"

#include "Texture.h"

class TextureMock : public Texture
{
public:
    static int initCount;
    static int destructCount;

    TextureMock()
    {
        initCount++;
    }

    virtual ~TextureMock()
    {
        if(texture) {
            destructCount++;
        }
    }
};

class TextureTest : public ::testing::Test
{
    public:
        SDLMock *mock;

        TextureTest()
        {
        }

        virtual ~TextureTest()
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
