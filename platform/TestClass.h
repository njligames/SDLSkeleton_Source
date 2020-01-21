class TestClass {
    public:
        TestClass(int n = 0);
        virtual ~TestClass();
    
        void reset(int n);
        int increment(int n);
    private:
        int mNum;

};
