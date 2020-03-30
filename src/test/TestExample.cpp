#include <string>
#include "TestExample.h"
#include "TestClass.h"

#include "GraphicsPlatform.h"

//using namespace google_test_sample;
using namespace std;

class Graphics
{
private:
  SDL_Window *_window;

public:
  Graphics(SDL_Window *window) { _window = window; }

  void update()
  {
//    njli::NJLIGameEngine::render();

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      
    SDL_GL_SwapWindow(_window);
  }
};



TestExample::TestExample() {}

TestExample::~TestExample() {};

//static void Update() {
//    while(!done) {
////        TestClass::get()->update();
//
////        std::thread::id this_id = std::this_thread::get_id();
////        g_display_mutex.lock();
////        std::cout << "thread " << this_id << " sleeping...\n";
////        g_display_mutex.unlock();
//    }
//}

static void UpdateFrame(void *param)
{
    Graphics *graphics = (Graphics *)param;
    graphics->update();
}

static void RenderFrame(void *param)
{
//  njli::NJLIGameEngine::update(1.0f / ((float)gDisplayMode.refresh_rate));
    
//    TestClass::get()->update();
//    while(true){
  Graphics *graphics = (Graphics *)param;
  graphics->update();
//    }
}

void TestExample::handleInput()
{
  bool callFinishKeys = false;
  SDL_Event event;
  SDL_PumpEvents();
  while (SDL_PollEvent(&event))
    {
        switch (event.type) {
                case SDL_KEYDOWN:
                done = true;
                break;
                case SDL_APP_WILLENTERBACKGROUND:
                                SDL_Log("SDL_APP_WILLENTERBACKGROUND");
                #if (defined(__IPHONEOS__) && __IPHONEOS__)
                                SDL_iPhoneSetAnimationCallback(state->windows[0], 1, NULL,
                                                               graphics.get());
                #endif
                break;
                case SDL_APP_DIDENTERFOREGROUND:
                                SDL_Log("SDL_APP_DIDENTERFOREGROUND");

                #if (defined(__IPHONEOS__) && __IPHONEOS__)
                                SDL_iPhoneSetAnimationCallback(state->windows[0], 1, UpdateFrame,
                                                               graphics.get());
                                SDL_iPhoneSetEventPump(SDL_TRUE);
                #endif
                                break;
        }
    }
}

void TestExample::holdView(unsigned int seconds){
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    
    while(!done){
        handleInput();
        #if !(defined(__IPHONEOS__) && __IPHONEOS__)
        RenderFrame(graphics.get());
#endif
        
        end = chrono::steady_clock::now();
        
        if(seconds < chrono::duration_cast<chrono::seconds>(end - start).count()) {
            done = true;
        }
    }
    done = false;
}

void TestExample::SetUp() {
    
    SDL_SetMainReady();
    
    char *argv[] = {"", nullptr};
    state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
    
    if (!SDLTest_CommonInit(state)) {
//        quit(2);
    }
    
    /* Create the windows and initialize the renderers */
    for (int i = 0; i < state->num_windows; ++i) {
        SDL_Renderer *renderer = state->renderers[i];
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);
    }
    
    glContext = SDL_GL_CreateContext(state->windows[0]);
    
    graphics = std::unique_ptr<Graphics>(new Graphics(state->windows[0]));
    done = false;
    
    glClearColor(1.0, 0.0, 0.0, 1.0f);
    
};

void TestExample::TearDown() {
    
    SDLTest_CommonQuit(state);
    SDL_GL_DeleteContext(glContext);
};

//TEST(test_cookie_interface, ShouldReturnZero) {
//    TestClass t(10);
//
//    ASSERT_EQ(t.increment(10), 20);
//}

TEST_F(TestExample, loadfile) {
    bool ret = true;
    
//    TestClass::create(nullptr, nullptr);
    TestClass::createInstance();
    
    drawstates = SDL_stack_alloc(DrawState, state->num_windows);
    for (int i = 0; i < state->num_windows; ++i) {
        DrawState *drawstate = &drawstates[i];

        drawstate->window = state->windows[i];
        drawstate->renderer = state->renderers[i];
        
//        ret = ret && TestClass::get()->loadfile(state->renderers[i]);
        ret = ret && TestClass::getInstance()->loadfile(state->renderers[i]);
        
//        SDL_QueryTexture(drawstate->sprite, NULL, NULL, &drawstate->sprite_rect.w, &drawstate->sprite_rect.h);
        drawstate->scale_direction = 1;
    }
    ASSERT_EQ(true, ret);
    
    holdView(3);
    
}
