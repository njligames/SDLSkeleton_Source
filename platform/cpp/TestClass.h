class SDL_Renderer;

class TestClass {
    public:
        TestClass(int n = 0);
        virtual ~TestClass();
    
    bool loadfile(SDL_Renderer *renderer);
    
        void reset(int n);
        int increment(int n);
    private:
        int mNum;

};
