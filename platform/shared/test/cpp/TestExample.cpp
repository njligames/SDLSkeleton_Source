#include <string>
#include "TestExample.h"
#include "TestClass.h"

//using namespace google_test_sample;
using namespace std;

TestExample::TestExample() {}

TestExample::~TestExample() {};

void TestExample::SetUp() {
    
    char *argv[] = {"", nullptr};
    state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
    
    if (!SDLTest_CommonInit(state)) {
//        quit(2);
    }
};

void TestExample::TearDown() {};

TEST(test_cookie_interface, ShouldReturnZero) {
    TestClass t(10);
    
    ASSERT_EQ(t.increment(10), 20);
}

TEST_F(TestExample, loadfile) {
    bool ret = true;
    
    TestClass t;
    
    drawstates = SDL_stack_alloc(DrawState, state->num_windows);
    for (int i = 0; i < state->num_windows; ++i) {
        DrawState *drawstate = &drawstates[i];

        drawstate->window = state->windows[i];
        drawstate->renderer = state->renderers[i];
        
        ret = ret && t.loadfile(state->renderers[i]);
        
//        SDL_QueryTexture(drawstate->sprite, NULL, NULL, &drawstate->sprite_rect.w, &drawstate->sprite_rect.h);
        drawstate->scale_direction = 1;
    }
    ASSERT_EQ(true, ret);
}
