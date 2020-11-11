class SDL_Renderer;
class SDL_Window;

#include <mutex>
#include <vector>

//#include "PubSub.h"

//#include "Camera.h"
//#include "Node.h"
//#include "Scene.h"
//#include "Shader.h"
//#include "SpriteGeometry.h"
//
//#include "curl.h"

class GameModelViewData;
class GameModelData;
class BitmapFont;
class GameModelData;

class NJLICGame;

class TestClass { //} : public Subscriber {
    static TestClass *sInstance;

    TestClass();
    virtual ~TestClass();

    TestClass(const TestClass &rhs) = delete;
    TestClass &operator=(const TestClass &rhs) = delete;

  public:
    static void createInstance(NJLICGame *game);
    //    static void create(SDL_Window *window, SDL_Renderer *renderer);
    static void destroyInstance();
    static TestClass *getInstance();

  public:
    //    bool loadfile(SDL_Renderer *renderer);

    void reset(int n);
    int increment(int n);

    void init();
    void unInit();
    void update(double step);
    void render();
    void input();

    void resize(int w, int h);

    bool isDone() const;

    //    virtual void update(Publisher *who, void *userdata = 0) override;

  protected:
    static std::string loadStringData(char *path);

  private:
    //    int mNum;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    std::mutex mMutex;
    bool mIsDone;

    //    NJLIC::Shader *mShader;
    //    NJLIC::Camera *mCamera;
    //    NJLIC::Node *mCameraNode;
    //    NJLIC::Scene *mScene;
    //    std::vector<NJLIC::Node *> mCubeNodes;
    //    float m_Rotation = 0.0;
    //
    //    std::vector<GameModelViewData *> mGameModelViewVector;
    //    GameModelViewData *mpSelectedNode = nullptr;
    //    int mSelectedIndex = 0;
    //
    //    int mNumItemsReeachDestination = 0;
    //    bool mIsScrolling = false;
    //
    //    std::vector<GameModelViewData *> mListItems;
};
