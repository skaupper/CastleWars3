void loadMap(Scene *scene)
{
    float startx = getRelativeLocation(5, 0)->x;
    float starty = getRelativeLocation(0, 70)->y;
    float brickwidth = getRelativeSize(5, 0)->w;
    int count = 5;

    // Links nach Rechts
    for (int i = 0; i < count; i++) {
        Animation *brickAnimation = new Animation("brick", -1);
        brickAnimation->addImage("res/game/brick.png", getRelativeSize(5, 5));
        Element *brick = new Element(new Location{startx + brickwidth * i, starty},
                                     "brick",  true);
        brick->addAnimation(brickAnimation);
        scene->addElement(brick);
    }

    startx = getRelativeLocation(90, 0)->x;

    // Rechts nach Links
    for (int i = 0; i < count; i++) {
        Animation *brickAnimation = new Animation("brick", -1);
        brickAnimation->addImage("res/game/brick.png", getRelativeSize(5, 5));
        Element *brick = new Element(new Location{startx - (brickwidth * i), starty},
                                     "brick",  true);
        brick->addAnimation(brickAnimation);
        scene->addElement(brick);
    }

    // Mitte
    for (int i = 0; i < 8; i++) {
        Animation *brickAnimation = new Animation("brick", -1);
        brickAnimation->addImage("res/game/brick.png", getRelativeSize(5, 5));
        Element *brick = new Element(new Location{getRelativeLocation(30, 0)->x + (brickwidth * i), starty - brickwidth - getRelativeLocation(0, 15)->y},
                                     "brick",  true);
        brick->addAnimation(brickAnimation);
        scene->addElement(brick);
    }
}
