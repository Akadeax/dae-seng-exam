#pragma once

#include <string>

class SetupContext
{
public:
    SetupContext(const tstring& title, int width, int height)
        : windowTitle(title)
        , windowWidth(width)
        , windowHeight(height) {}

    void setWindowSize(int width, int height)
    {
        windowWidth = width;
        windowHeight = height;
    }

    void setWindowTitle(const tstring& title)
    {
        windowTitle = title;
    }

    const tstring& getWindowTitle() const { return windowTitle; }
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }

private:
    tstring windowTitle;
    int windowWidth;
    int windowHeight;
};
