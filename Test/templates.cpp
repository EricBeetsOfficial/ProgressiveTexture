#include <gtest/gtest.h>
#include <DynamicTemplate.h>
#include <Log.h>

class ITasks
{
 public:
    template<typename T>
    friend class MyClass;
public:
    ITasks() {}
    virtual ~ITasks() = default;

public:
    void pubFOO()
    {
        DEBUG();
    }
    int pubFOO1(int a)
    {
        DEBUG(a);
        return 25;
    }
    bool pubFOO2()
    {
        DEBUG();
        return true;
    }

protected:
    char proFOO(int a)
    {
        DEBUG(a);
        return 'z';
    }
private:
    std::string priFOO(int a)
    {
        DEBUG(a);
        return "Hello";
    }

    void priFOO1(int a)
    {
        DEBUG(a);
    }

    void priFOO2()
    {
        DEBUG();
    }
};

class TextureTasks : public ITasks
{
 public:
    virtual ~TextureTasks() = default;
};

class StandAlone {};

template <typename T>
class MyClass
{
public:
    void callFOO()
    {
        T obj;
        CALL_METHOD(&obj, pubFOO);
        auto r2 = CALL_METHOD(&obj, pubFOO1, 3); cerr << r2 << " " << typeid(r2).name() << endl;
        auto r1 = CALL_METHOD(&obj, pubFOO2); cerr << r1 << " " << typeid(r1).name() << endl;
        auto r3 = CALL_METHOD(&obj, proFOO, 4); cerr << r3 << " " << typeid(r3).name() << endl;
        auto r4 = CALL_METHOD(&obj, priFOO, 5); cerr << r4 << " " << typeid(r4).name() << endl;
        CALL_METHOD(&obj, priFOO1, 6);
        CALL_METHOD(&obj, priFOO2);
    }
private:
    DEFINE_METHOD(pubFOO)
    DEFINE_METHOD(pubFOO1)
    DEFINE_METHOD(pubFOO2)
    DEFINE_METHOD(proFOO)
    DEFINE_METHOD(priFOO)
    DEFINE_METHOD(priFOO1)
    DEFINE_METHOD(priFOO2)
};

TEST(TestTemplates, Test01)
{
    MyClass<StandAlone> myStandAlone;
    testing::internal::CaptureStderr();
    myStandAlone.callFOO();
    ASSERT_EQ(testing::internal::GetCapturedStderr(), "\
0 bool\n\
0 bool\n\
0 bool\n\
0 bool\n\
");

    MyClass<TextureTasks> myClass;
    testing::internal::CaptureStderr();
    myClass.callFOO();
    ASSERT_EQ(testing::internal::GetCapturedStderr(), "\
25 int\n\
1 bool\n\
z char\n\
Hello class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >\n\
");
}