#include "TestClass.h"

#include "SDL.h"
//
//#include <string>
//
//#include "MLBJsonModel.h"
//
//#include "GameModelData.h"
//#include "GameModelViewData.h"
//

#include "GraphicsPlatform.h"



static void UpdateFrame(void *param) {
    //  njli::NJLIGameEngine::update(1.0f / ((float)gDisplayMode.refresh_rate));

    //        TestClass::getInstance()->update(0.06);
    //    TestClass::get()->render();

    //  Graphics *graphics = (Graphics *)param;
    //  graphics->update();
}



TestClass *TestClass::sInstance = nullptr;


TestClass::TestClass() : mWindow(nullptr), mRenderer(nullptr), mIsDone(true) {}


TestClass::~TestClass() {
    

    unInit();
}

void TestClass::createInstance(NJLICGame *game) {
    if (nullptr == sInstance) {
        sInstance = new TestClass();
        
    }
}



void TestClass::destroyInstance() {
    if (nullptr != sInstance)
        delete sInstance;
    
    

    sInstance = nullptr;
    
}

TestClass *TestClass::getInstance() { return sInstance; }



void TestClass::init() {

    mIsDone = false;
    
}
void TestClass::unInit() {
}
void TestClass::update(double step) {
    

    SDL_Log("Updating %f\n", step);
    
}
void TestClass::render() {
    
}

void TestClass::input() {
    mMutex.lock();

    bool callFinishKeys = false;
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PollEvent(&event)) {
        
        //        SDLTest_PrintEvent(&event);
        switch (event.type) {

#if defined(__MACOSX__) || defined(__EMSCRIPTEN__) || defined(__ANDROID__)
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:

                
            break;
#endif

#if (defined(__ANDROID__) && __ANDROID__)
        case SDL_FINGERMOTION:
        case SDL_FINGERDOWN:
        case SDL_FINGERUP:
            
                

            break;
#endif
        case SDL_APP_DIDENTERFOREGROUND:
            SDL_Log("SDL_APP_DIDENTERFOREGROUND");

#if (defined(__IPHONEOS__) && __IPHONEOS__)
            SDL_iPhoneSetAnimationCallback(mWindow, 1, UpdateFrame, nullptr);
#endif
            //            NJLI_HandleResume();
            break;

        case SDL_APP_DIDENTERBACKGROUND:
            SDL_Log("SDL_APP_DIDENTERBACKGROUND");

            //            njli::NJLIGameEngine::didEnterBackground();
            break;

        case SDL_APP_LOWMEMORY:
            SDL_Log("SDL_APP_LOWMEMORY");
                

            break;

        case SDL_APP_TERMINATING:
            SDL_Log("SDL_APP_TERMINATING");
            //            njli::NJLIGameEngine::willTerminate();
            break;

        case SDL_APP_WILLENTERBACKGROUND:
            SDL_Log("SDL_APP_WILLENTERBACKGROUND");
#if (defined(__IPHONEOS__) && __IPHONEOS__)
            SDL_iPhoneSetAnimationCallback(mWindow, 1, NULL, nullptr);
#endif
            //            NJLI_HandlePause();
            break;

        case SDL_APP_WILLENTERFOREGROUND:
            SDL_Log("SDL_APP_WILLENTERFOREGROUND");

            //            njli::NJLIGameEngine::willEnterForeground();
            break;

        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_RESTORED:
                //                NJLI_HandleResume();
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                //                NJLI_HandlePause();
                break;
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
                int w, h;
#if defined(__MACOSX__)
                SDL_GetWindowSize(mWindow, &w, &h);
#else
                SDL_GL_GetDrawableSize(mWindow, &w, &h);
#endif
                TestClass::getInstance()->resize(w, h);

                //                  NJLI_HandleResize(w, h,
                //                  gDisplayMode.format,
                //                                    gDisplayMode.refresh_rate);
            } break;
            case SDL_WINDOWEVENT_CLOSE: {
                SDL_Window *window = SDL_GetWindowFromID(event.window.windowID);
                if (window) {
                    if (window == mWindow) {
                        SDL_DestroyWindow(mWindow);
                        mWindow = nullptr;
                        break;
                    }
                }
            } break;
            }
            break;
        case SDL_KEYUP: {
            callFinishKeys = true;
            int temp = SDL_GetModState();
            temp = temp & KMOD_CAPS;
            bool withCapsLock = (temp == KMOD_CAPS);

            bool withControl = !!(event.key.keysym.mod & KMOD_CTRL);
            bool withShift = !!(event.key.keysym.mod & KMOD_SHIFT);
            bool withAlt = !!(event.key.keysym.mod & KMOD_ALT);
            bool withGui = !!(event.key.keysym.mod & KMOD_GUI);

            
        } break;
        case SDL_KEYDOWN: {
            callFinishKeys = true;
            int temp = SDL_GetModState();
            temp = temp & KMOD_CAPS;
            bool withCapsLock = (temp == KMOD_CAPS);

            bool withControl = !!(event.key.keysym.mod & KMOD_CTRL);
            bool withShift = !!(event.key.keysym.mod & KMOD_SHIFT);
            bool withAlt = !!(event.key.keysym.mod & KMOD_ALT);
            bool withGui = !!(event.key.keysym.mod & KMOD_GUI);

            

            break;
        }
        case SDL_QUIT:

                

            break;

        case SDL_MOUSEWHEEL:
            SDL_Log("SDL EVENT: Mouse: wheel scrolled %d in x and %d in y "
                    "(reversed: %d) in window %d",
                    event.wheel.x, event.wheel.y, event.wheel.direction,
                    event.wheel.windowID);
                

            break;
        case SDL_DROPFILE: {
            char *dropped_filedir = event.drop.file;
            
            SDL_free(dropped_filedir);
        } break;
#if !defined(__LINUX__)
        case SDL_DROPTEXT: {
            char *dropped_filedir = event.drop.file;
            
            SDL_free(dropped_filedir);
        } break;
        case SDL_DROPBEGIN: {
            printf("Dropped file begin: %u\n", event.drop.windowID);
        } break;
        case SDL_DROPCOMPLETE: {
            printf("Dropped file begin: %u\n", event.drop.windowID);
        }
#endif
        break;
        default:
            break;
        }
    }

    

#if !(defined(__MACOSX__) && __MACOSX__)
#endif

    mMutex.unlock();
}

void TestClass::resize(int w, int h) {}

bool TestClass::isDone() const { return mIsDone; }



