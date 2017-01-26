#include "CoreTest.h"

#include "Core.h"

TEST_F(CoreTest, init)
{
    SDLMock mock;
    EXPECT_CALL(mock, SDL_Init(_)).Times(1);

    SDLProvider::setInstance(&mock);
    Core::init();
}
