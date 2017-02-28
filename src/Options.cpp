#include "Options.h"

using namespace bkengine;

static bool contains(const KeyboardLayout &layout, const Keys &key)
{
    return layout.up == key || layout.left == key || layout.right == key || layout.action == key;
}

void Options::setup()
{
    auto options = parentGame->getData<OptionStorage>("options");
    KeyboardLayout layouts[2] = { options.player1, options.player2 };
    Resolution resolution = options.getResolution();

    Rect tableOffset { 0, 20, 20, 7 };
    float xAdvance = 20;
    float yAdvance = 2;
    Rect textPadding { 1, 1, 0, 0 };
    short columns = 2;
    float maxWidth = tableOffset.w * columns;

    if (columns > 1) {
        maxWidth += xAdvance * (columns - 1);
    }

    tableOffset.x = (100 - maxWidth) / 2;
    auto setElement = [&](int column, int elementId) {
        Rect tmp = tableOffset;
        tmp.x += (tableOffset.w + xAdvance) * column;
        tmp.y += (tableOffset.h + yAdvance) * elementId;
        return tmp;
    };
    auto setText = [&](int column, int elementId) {
        Rect tmp = setElement(column, elementId);
        tmp.x += textPadding.x;
        tmp.y += textPadding.y;
        tmp.w = 0;
        tmp.h = 0;
        return tmp;
    };
    auto setTextSize = [&]() {
        Rect tmp;
        tmp.w = 0;
        tmp.h = tableOffset.h - textPadding.y * 2;
        return tmp;
    };
    auto setLabel = [&](int elementId) {
        Rect tmp = tableOffset;
        tmp.x += tmp.w + textPadding.x;
        tmp.y += textPadding.y + (tableOffset.h + yAdvance) * elementId;
        tmp.w = 0;
        tmp.h = 0;
        return tmp;
    };
    auto setHeading = [&](int column) {
        Rect tmp = setElement(column, -1);
        tmp.w = 0;
        tmp.h = 0;
        return tmp;
    };
    addElement<Element>("options background", Rect { 100, 100 }).addAnimation<Animation>().addTexture(
        Texture("options_bg.png"));
    addElement<Element>("options keyboard layout player 1 heading",
                        setHeading(0)).addAnimation<Animation>().addTexture(Texture("futurab",
                                "Player 1", Rect { 0, 5 }, Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 2 heading",
                        setHeading(1)).addAnimation<Animation>().addTexture(Texture("futurab",
                                "Player 2", Rect { 0, 5 }, Color(), TextQuality::BLENDED));
    std::string paths[] = {"button.png", "button_light.png"};
    Element &p1Up =
        addElement<Element>("options keyboard layout player 1 up button", setElement(0,
                            0));
    p1Up.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p1Up.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p2Up =
        addElement<Element>("options keyboard layout player 2 up button", setElement(1,
                            0));
    p2Up.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p2Up.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p1Left =
        addElement<Element>("options keyboard layout player 1 left button",
                            setElement(0, 1));
    p1Left.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p1Left.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p2Left =
        addElement<Element>("options keyboard layout player 2 left button",
                            setElement(1, 1));
    p2Left.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p2Left.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p1Right =
        addElement<Element>("options keyboard layout player 1 right button",
                            setElement(0, 2));
    p1Right.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p1Right.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p2Right =
        addElement<Element>("options keyboard layout player 2 right button",
                            setElement(1, 2));
    p2Right.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p2Right.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p1Action =
        addElement<Element>("options keyboard layout player 1 action button",
                            setElement(0, 3));
    p1Action.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p1Action.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &p2Action =
        addElement<Element>("options keyboard layout player 2 action button",
                            setElement(1, 3));
    p2Action.addAnimation<Animation>().addTexture(Texture(paths[0]));
    p2Action.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Rect tmpRect { tableOffset.x, tableOffset.y + (tableOffset.h + yAdvance) * 5, maxWidth, tableOffset.h };
    Rect screenSizeRect = tmpRect;
    screenSizeRect.x += maxWidth / 4;
    screenSizeRect.w = maxWidth / 2;
    Rect screenLeftRect = tmpRect;
    screenLeftRect.w = maxWidth / 4 - 1;
    Rect screenRightRect = screenLeftRect;
    screenRightRect.x += 3 * maxWidth / 4 + 1;
    Element &screenSize = addElement<Element>("options screen size button",
                          screenSizeRect);
    screenSize.addAnimation<Animation>().addTexture(Texture(paths[0]));
    screenSize.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &screenLeft = addElement<Element>("options screen size left button",
                          screenLeftRect);
    screenLeft.addAnimation<Animation>().addTexture(Texture(paths[0]));
    screenLeft.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &screenRight = addElement<Element>("options screen size right button",
                           screenRightRect);
    screenRight.addAnimation<Animation>().addTexture(Texture(paths[0]));
    screenRight.addAnimation<Animation>().addTexture(Texture(paths[1]));
    tmpRect = { tableOffset.x, tableOffset.y + (tableOffset.h + yAdvance) * 7, maxWidth, tableOffset.h };
    Rect saveRect = tmpRect;
    saveRect.w = maxWidth / 2 - 1;
    Rect cancelRect = tmpRect;
    cancelRect.w = maxWidth / 2 - 1;
    cancelRect.x += maxWidth / 2 + 1;
    Element &save = addElement<Element>("options save button", saveRect);
    save.addAnimation<Animation>().addTexture(Texture(paths[0]));
    save.addAnimation<Animation>().addTexture(Texture(paths[1]));
    Element &cancel = addElement<Element>("options cancel button", cancelRect);
    cancel.addAnimation<Animation>().addTexture(Texture(paths[0]));
    cancel.addAnimation<Animation>().addTexture(Texture(paths[1]));
    cancelRect.w = cancelRect.h = 0;
    saveRect.w = saveRect.h = 0;
    saveRect.y += textPadding.y;
    saveRect.x += textPadding.x;
    cancelRect.y += textPadding.y;
    cancelRect.x += textPadding.x;
    Rect textRect = { 0, tableOffset.h - textPadding.y * 2 };
    addElement<Element>("options keyboard layout up label",
                        setLabel(0)).addAnimation<Animation>().addTexture(Texture("futurab", "UP",
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 1 up label", setText(0,
                        0)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[0].up,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 2 up label", setText(1,
                        0)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[1].up,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout left label",
                        setLabel(1)).addAnimation<Animation>().addTexture(Texture("futurab", "LEFT",
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 1 left label", setText(0,
                        1)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[0].left,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 2 left label", setText(1,
                        1)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[1].left,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout right label",
                        setLabel(2)).addAnimation<Animation>().addTexture(Texture("futurab", "RIGHT",
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 1 right label", setText(0,
                        2)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[0].right,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 2 right label", setText(1,
                        2)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[1].right,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout action label",
                        setLabel(3)).addAnimation<Animation>().addTexture(Texture("futurab", "ACTION",
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 1 action label", setText(0,
                        3)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[0].action,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options keyboard layout player 2 action label", setText(1,
                        3)).addAnimation<Animation>().addTexture(Texture("futurab", layouts[1].action,
                                setTextSize(), Color(), TextQuality::BLENDED));
    addElement<Element>("options screen size left label",
                        screenLeftRect).addAnimation<Animation>().addTexture(Texture("futurab", "<",
                                Rect(), Color(), TextQuality::BLENDED));
    addElement<Element>("options screen size right label",
                        screenRightRect).addAnimation<Animation>().addTexture(Texture("futurab", ">",
                                Rect(), Color(), TextQuality::BLENDED));
    addElement<Element>("options save label",
                        saveRect).addAnimation<Animation>().addTexture(Texture("futurab", "Save",
                                textRect, Color(), TextQuality::BLENDED));
    addElement<Element>("options cancel label",
                        cancelRect).addAnimation<Animation>().addTexture(Texture("futurab", "Cancel",
                                textRect, Color(), TextQuality::BLENDED));
    screenSizeRect.w = screenSizeRect.h = 0;
    screenSizeRect.y += textPadding.y;
    screenSizeRect.x += textPadding.x;
    // TODO: show right resolution
    addElement<Element>("options screen size label",
                        screenSizeRect).addAnimation<Animation>().addTexture(Texture("futurab",
                                std::to_string((int) resolution.w) + "x" + std::to_string((int) resolution.h),
                                textRect,
                                Color(), TextQuality::BLENDED));
    getElement("options keyboard layout player 1 up button").activate(1);
}

bool Options::onEvent(const Event &event)
{
    if (event.type == EventType::KEYBOARD) {
        if (event.keyboard.key == Keys::ESCAPE) {
            parentGame->activate("mainmenu");
        }
    }

    static std::vector<std::string> hoverableElements = {
        "options keyboard layout player 1 up button",
        "options keyboard layout player 2 up button",
        "options keyboard layout player 1 left button",
        "options keyboard layout player 2 left button",
        "options keyboard layout player 1 right button",
        "options keyboard layout player 2 right button",
        "options keyboard layout player 1 action button",
        "options keyboard layout player 2 action button",
        "options screen size left button",
        "options screen size right button",
        "options save button",
        "options cancel button"
    };
    static int selected = 0;
    static bool pressed = false;
    static std::string pressedButton = "";

    static auto options =  parentGame->getData<OptionStorage>("options");
    static int resolutionIndex = options.resolutionIndex;


    bool selectedChanged = false;
    if (event.type == EventType::KEYBOARD && event.keyboard.state == KeyState::DOWN) {
        Keys key = event.keyboard.key;

        if (pressed) {
            if (key != Keys::UNKNOWN && !contains(options.player1, key)
                    && !contains(options.player2, key)) {

                if (pressedButton == "options keyboard layout player 1 up button") {
                    options.player1.up = key;
                } else if (pressedButton == "options keyboard layout player 1 left button") {
                    options.player1.left = key;
                } else if (pressedButton == "options keyboard layout player 1 right button") {
                    options.player1.right = key;
                } else if (pressedButton == "options keyboard layout player 1 action button") {
                    options.player1.action = key;
                } else if (pressedButton == "options keyboard layout player 2 up button") {
                    options.player2.up = key;
                } else if (pressedButton == "options keyboard layout player 2 left button") {
                    options.player2.left = key;
                } else if (pressedButton == "options keyboard layout player 2 right button") {
                    options.player2.right = key;
                } else if (pressedButton == "options keyboard layout player 2 action button") {
                    options.player2.action = key;
                }

                std::string tmp = pressedButton;
                size_t start_pos = tmp.find("button");
                tmp.replace(start_pos, 6, "label");
                auto &element = getElement(tmp);
                Rect size = element.getAnimation(0).getCurrentTexture().getSize();
                element.removeAnimation(0);
                element.addAnimation<Animation>().addTexture(Texture("futurab", key, size, Color(), TextQuality::BLENDED));
            }

            pressed = false;
        } else if (key == options.player1.left || key == options.player2.left) {
            selected = (--selected + hoverableElements.size()) % hoverableElements.size();
            selectedChanged = true;
        } else if (key == options.player1.right || key == options.player2.right) {
            selected = ++selected % hoverableElements.size();
            selectedChanged = true;
        } else if (key == options.player1.action || key == options.player2.action) {
            bool resolutionChanged = false;
            if (hoverableElements[selected] == "options screen size left button") {
                resolutionIndex = (--resolutionIndex + options.getAvailableResolutions().size()) % options.getAvailableResolutions().size();
                resolutionChanged = true;
            } else if (hoverableElements[selected] == "options screen size right button") {
                resolutionIndex = ++resolutionIndex % options.getAvailableResolutions().size();
                resolutionChanged = true;
            } else if (hoverableElements[selected] == "options save button") {
                auto &optionsRef = parentGame->getData<OptionStorage>("options");
                optionsRef.player1 = options.player1;
                optionsRef.player2 = options.player2;
                optionsRef.resolutionIndex = resolutionIndex;
                parentGame->resizeWindow(optionsRef.getResolution().w, optionsRef.getResolution().h);
                parentGame->activate("mainmenu");
            } else if (hoverableElements[selected] == "options cancel button") {
                parentGame->activate("mainmenu");
            }

            if ((hoverableElements[selected]).find("options keyboard layout player") != std::string::npos) {
                pressedButton = hoverableElements[selected];
                pressed = true;
            }

            if (resolutionChanged) {
                auto &element = getElement("options screen size label");
                Rect size = element.getAnimation(0).getCurrentTexture().getSize();
                element.removeAnimation(0);
                std::string resolutionString = std::to_string((int) options.getAvailableResolutions()[resolutionIndex].w) + "x" + std::to_string((int) options.getAvailableResolutions()[resolutionIndex].h);
                element.addAnimation<Animation>().addTexture(Texture("futurab", resolutionString, size, Color(), TextQuality::BLENDED));
            }
        }

        if (selectedChanged) {
            for (auto &element : elements) {
                if (hoverableElements[selected] == (element->getDescription())) {
                    element->activate(1);
                } else {
                    element->activate(0);
                }
            }
        }
    }

    return true;
}
