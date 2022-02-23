/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

struct Person
{
    int age = 0;
    int height = 0;
    float hairLength = 0.f;
    float GPA = 0.f;
    unsigned int SATScore = 0;
    float distanceTraveled = 0;
    std::string name;

    Person(std::string personsName) : name(personsName)
    {
        DBG("Person constructor:" + name); 
    }
    ~Person() 
    {
        DBG("Person Destructor:" + name);
    }
};

/*void  PersonFunction()
{
    Person p;
}*/

//Person::Person() {}

struct IntValue
{
    IntValue()
    {
        DBG("IntValue constructor");
    }
    ~IntValue()
    {
        DBG("IntValue destructor");
    }
    int value;
};

int functionA(int val)
{
    IntValue a;
    a.value = 5;
    return val * 2 + a.value;
}

void functionB()
{
    IntValue val;
    val.value = functionA(3);
    val.value *= 4;
}

void functionC()
{
    int i = 0;
    while (i < 3)
    {
        IntValue a;
        a.value += i;
        i += 1;
    }
    for (int i = 0; i < 3; i += 1)
    {
        IntValue a;
        a.value += i;
    }
}

void whileTest()
{
    bool b = true;
    while (b)
    {
        b = false;
        DBG("b is " << (b ? "true" : "false"));
    }
}

struct Family
{
    Family() { DBG( "Family constructor" ); }
    ~Family() { DBG( "Family Desctructor" ); }

    Person mom{ "mom" };
    Person dad{ "dad" };
    Person child1{ "child1" };
    Person child2{ "child2" };
};

void familyFunction()
{
    Family family;
    //family.mom.age = 42;
}

/*struct ColorPickerWidget // EXAMPLE of Desctructor
{
    ColorPickerWidget()
    {
        loadsettingsFromDisk();
    }
    ~ColorPickerWidget()
    {
        saveSettingstoDisk(); 
    }
}*/

//==============================================================================
class HelloWorldApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    HelloWorldApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        //whileTest();
        familyFunction();
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (HelloWorldApplication)
