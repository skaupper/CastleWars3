#ifndef FORMSFUNCTIONS_H
#define FORMSFUNCTIONS_H

bool inRect(SDL_Rect *large, SDL_Rect *small)
{
    return small->x > large->x && small->x + small->w < large->x + large->w
           && small->y > large->y && small->y + small->h < large->y + large->h;
}

int getPercentageWidth(double percent)
{
    int window_width = Core::getInstance()->WINDOW_WIDTH;
    return window_width * (percent / 100);
}

int getPercentageHeight(double percent)
{
    int window_height = Core::getInstance()->WINDOW_HEIGHT;
    return window_height * (percent / 100);
}

Location getRelativeLocation(double percent_x, double percent_y)
{
    return { getPercentageWidth(percent_x), getPercentageHeight(percent_y) };
}

SDL_Rect getRelativeSize(double percent_x, double percent_y)
{
    return { 0, 0, getPercentageWidth(percent_x), getPercentageHeight(percent_y) };
}

Entity getImage(std::string path, std::string id, Location *location,
                SDL_Rect *size,
                Scene *scene)
{
    Animation animation(id, -1);
    animation.addImage(path, size);
    Entity element(location, scene, id);
    element.addAnimation(animation);
    return element;
}

Entity *getImage(const string path[], const string id, Location *location,
                 SDL_Rect *size, Scene *scene)
{
    stringstream ss;
    Entity *element = new Entity(location, scene, id);

    for (int i = 0; i < 2; i++) {
        ss << i;
        Animation *animation = new Animation(ss.str(), -1);
        animation->addImage(path[i], size);
        element->addAnimation(animation);
    }

    return element;
}

Entity *getText(string text, const string id, Location *location, short size,
                Scene *scene)
{
    Animation *animation = new Animation(id, -1);
    animation->addText(text, new SDL_Color{255, 255, 255}, size);
    Entity *entity = new Entity(location, scene, id);
    entity->addAnimation(animation);
    return entity;
}

#endif // FORMSFUNCTIONS_H
