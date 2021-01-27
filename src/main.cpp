#include "main.h"

int main() {
    srand(time(nullptr));
    RenderWindow window(VideoMode(1900, 1000), "ZUMA 2020");
    window.setFramerateLimit(60);


    Image icon;
    icon.loadFromFile("frog.png");

    bool won = false;

    //Backgorund
    Texture textBackground;
    textBackground.loadFromFile("background.jfif");
    Sprite Background;
    Vector2u size = textBackground.getSize();
    Background.setTexture(textBackground);
    Background.setOrigin(size.x / 2.f, size.y / 2.f);

    //Score
    int intScore = 0;
    Text Score;
    Score.setPosition(10, 10);
    Score.setCharacterSize(30);

    Font arial;
    arial.loadFromFile("ARCADECLASSIC.TTF");
    Score.setFont(arial);

    ostringstream stringScore;
    stringScore << "Score " << intScore;
    Score.setString(stringScore.str());

    //Win screen
    Text you_win;
    you_win.setPosition(window.getSize().x / 2.f - 500, window.getSize().y / 2.f);
    you_win.setCharacterSize(60);
    you_win.setFont(arial);
    you_win.setFillColor(Color::Green);
    ostringstream win;
    win << "YOU SAVED THE WORLD FROM A PANDEMIC!";
    you_win.setString(win.str());

    //Lose screen
    Text Lose;
    Lose.setPosition(window.getSize().x / 2.f - 500, window.getSize().y / 2.f);
    Lose.setCharacterSize(60);
    Lose.setFont(arial);
    Lose.setFillColor(Color::Red);
    ostringstream loss;
    loss << "STAY SAFE AND GET IN QUARANTINE!";
    Lose.setString(loss.str());

    //Lives
    int intLives = 3;
    Text lives;
    lives.setPosition(10, 50);
    lives.setCharacterSize(30);
    lives.setFont(arial);
    lives.setFillColor(Color::Green);
    ostringstream stringLives;
    stringLives << "Lives " << intLives;
    lives.setString(stringLives.str());

    //Frog
    Texture FrogTexture;
    FrogTexture.loadFromFile("frog.png");
    Sprite Frog;
    Frog.setTexture(FrogTexture);
    Vector2f FrogPostition(window.getSize().x - Frog.getGlobalBounds().width, 0.f);
    Frog.setPosition(FrogPostition);

    //finishline
    Texture FinishLineTexture;
    FinishLineTexture.loadFromFile("finishline.png");
    Sprite finish;
    finish.setTexture(FinishLineTexture);
    finish.setPosition(window.getSize().x - finish.getGlobalBounds().width, window.getSize().y -300.f);

    //Balls
    CircleShape projectile;
    projectile.setFillColor(Color::Green);
    projectile.setRadius(5.f); // leave

    // BLock to display the enemy
    Texture enemyTextureRed;
    enemyTextureRed.loadFromFile("red.png");
    Sprite enemyRed;
    enemyRed.setTexture(enemyTextureRed);
    enemyRed.setScale(Vector2f(0.2f, 0.2f));
    enemyRed.setColor(Color::Red);

    //BlockOfYellow
    Texture enemyTextureYellow;
    enemyTextureYellow.loadFromFile("yellow.png");
    Sprite enemyYellow;
    enemyYellow.setTexture(enemyTextureYellow);
    enemyYellow.setScale(Vector2f(0.2f, 0.2f));
    enemyYellow.setColor(Color::Yellow);

    //Block of pink
    Texture enemyTexturePink;
    enemyTexturePink.loadFromFile("pink.png");
    Sprite enemyPink;
    enemyPink.setTexture(enemyTexturePink);
    enemyPink.setScale(Vector2f(0.2f, 0.2f));
    enemyPink.setColor(Color::Magenta);

    //Block of Blue
    Texture enemyTextureBlue;
    enemyTextureBlue.loadFromFile("blue.png");
    Sprite enemyBlue;
    enemyBlue.setTexture(enemyTextureBlue);
    enemyBlue.setScale(Vector2f(0.2f, 0.2f));
    enemyBlue.setColor(Color(0,165,255));

    //BlockOfGreen
    Texture enemyTextureGreen;
    enemyTextureGreen.loadFromFile("green.png");
    Sprite enemyGreen;
    enemyGreen.setTexture(enemyTextureGreen);
    enemyGreen.setScale(Vector2f(0.2f, 0.2f));
    enemyGreen.setColor(Color::Green);

    //Player
    Texture playerTexture;
    playerTexture.loadFromFile("syringe.png");
    Sprite player;
    player.setTexture(playerTexture);
    player.setScale(Vector2f(0.3f, 0.3f));
    player.setColor(Color::Green);

    player.setPosition(window.getSize().x / 2.f, window.getSize().y - 200.f);
    Vector2f playerCenter;
    int shootTimer = 0;

    vector<CircleShape> projectiles;
    projectiles.push_back(CircleShape(projectile));

    vector<Sprite> enemies;

    int enemySpawnTimer = 0;
    float movementspeed = 0.9f;
    int speedSpawning = 120;
    int shootingTime = 30;
    int previous_color;
    int adjacent = 1;

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
                /////////////////////////////Switch colors when RIGHT CLICKED///////////////////
                int random_color = rand() % 5 + 1;
                switch (random_color) {
                    case 1://Green
                        if (previous_color != 1) {
                            projectile.setFillColor(Color::Green);
                            player.setColor(Color::Green);
                            previous_color = 1;
                            break;
                        } else {//if previous was Green
                            random_color = rand() % 4 + 1;
                            switch (random_color) {
                                case 1://set either to Red
                                    projectile.setFillColor(Color::Red);
                                    player.setColor(Color::Red);
                                    previous_color = 2;
                                    break;
                                case 2://set either to yellow
                                    projectile.setFillColor(Color::Yellow);
                                    player.setColor(Color::Yellow);
                                    previous_color = 3;
                                    break;
                                case 3://set either to pink
                                    projectile.setFillColor(Color::Magenta);
                                    player.setColor(Color::Magenta);
                                    previous_color = 4;
                                    break;
                                case 4://set either to blue
                                    projectile.setFillColor(Color(0,165,255));
                                    player.setColor(Color(0,165,255));
                                    previous_color = 5;
                                    break;
                            }
                        }

                    case 2://Red
                        if (previous_color != 2) {
                            projectile.setFillColor(Color::Red);
                            player.setColor(Color::Red);
                            previous_color = 2;
                            break;
                        }else {//if previous was Red
                            random_color = rand() % 4 + 1;
                            switch (random_color) {
                                case 1://set either to green
                                    projectile.setFillColor(Color::Green);
                                    player.setColor(Color::Green);
                                    previous_color = 1;
                                    break;
                                case 2://set either to pink
                                    projectile.setFillColor(Color::Magenta);
                                    player.setColor(Color::Magenta);
                                    previous_color = 4;
                                    break;
                                case 3://set either to yellow
                                    projectile.setFillColor(Color::Yellow);
                                    player.setColor(Color::Yellow);
                                    previous_color = 3;
                                    break;
                                case 4://set either to Blue
                                    projectile.setFillColor(Color(0,165,255));
                                    player.setColor(Color(0,165,255));
                                    previous_color = 5;
                                    break;
                            }
                        }

                    case 3: //Yellow
                        if (previous_color != 3) {
                            projectile.setFillColor(Color::Yellow);
                            player.setColor(Color::Yellow);
                            previous_color = 3;
                            break;
                        } else {//if previous was Yellow
                            random_color = rand() % 4 + 1;
                            switch (random_color) {
                                case 1://set either to green
                                    projectile.setFillColor(Color::Green);
                                    player.setColor(Color::Green);
                                    previous_color = 1;
                                    break;
                                case 2://set either to red
                                    projectile.setFillColor(Color::Red);
                                    player.setColor(Color::Red);
                                    previous_color = 2;
                                    break;
                                case 3://set either to pink
                                    projectile.setFillColor(Color::Magenta);
                                    player.setColor(Color::Magenta);
                                    previous_color = 4;
                                    break;
                                case 4://set either to Blue
                                    projectile.setFillColor(Color(0,165,255));
                                    player.setColor(Color(0,165,255));
                                    previous_color = 5;
                                    break;
                            }
                        }

                    case 4://Pink
                        if (previous_color != 4) {
                            projectile.setFillColor(Color::Magenta);
                            player.setColor(Color::Magenta);
                            previous_color = 4;
                            break;
                        } else {//if previous was pink
                            random_color = rand() % 4 + 1;
                            switch (random_color) {
                                case 1://set either to green
                                    projectile.setFillColor(Color::Green);
                                    player.setColor(Color::Green);
                                    previous_color = 1;
                                    break;
                                case 2://set either to red
                                    projectile.setFillColor(Color::Red);
                                    player.setColor(Color::Red);
                                    previous_color = 2;
                                    break;
                                case 3://set either to yellow
                                    projectile.setFillColor(Color::Yellow);
                                    player.setColor(Color::Yellow);
                                    previous_color = 3;
                                    break;
                                case 4://set either to Blue
                                    projectile.setFillColor(Color(0,165,255));
                                    player.setColor(Color(0,165,255));
                                    previous_color = 5;
                                    break;
                            }
                        }

                    case 5: //Blue
                        if (previous_color != 5) {
                            projectile.setFillColor(Color(0,165,255));
                            player.setColor(Color(0,165,255));
                            previous_color = 5;
                            break;
                        } else {//if previous was Blue
                            random_color = rand() % 4 + 1;
                            switch (random_color) {
                                case 1://set either to green
                                    projectile.setFillColor(Color::Green);
                                    player.setColor(Color::Green);
                                    previous_color = 1;
                                    break;
                                case 2://set either to red
                                    projectile.setFillColor(Color::Red);
                                    player.setColor(Color::Red);
                                    previous_color = 2;
                                    break;
                                case 3://set either to yellow
                                    projectile.setFillColor(Color::Yellow);
                                    player.setColor(Color::Yellow);
                                    previous_color = 3;
                                    break;
                                case 4://set either to Pink
                                    projectile.setFillColor(Color::Magenta);
                                    player.setColor(Color::Magenta);
                                    previous_color = 4;
                                    break;
                            }
                        }
                }
                /////////////////////////////Switch colors when RIGHT CLICKED///////////////////
            }
        }


        //If lives is 0
        if (intLives <= 0) {
            Frog.setPosition(window.getSize().x/2.f - 200, window.getSize().y/2.f - Frog.getGlobalBounds().height);
            window.clear();
            window.draw(Background);
            window.draw(Frog);
            window.draw(Lose);
            window.draw(lives);
            window.display();
        }

            //Game loop
        else if (!won) {
            //Update
            //Player
            playerCenter = Vector2f(player.getPosition().x, player.getPosition().y);
            player.setPosition(Mouse::getPosition(window).x, player.getPosition().y);

            //Blocks out the boarders
            if (player.getPosition().x >= window.getSize().x * 0.75)
                player.setPosition(window.getSize().x * 0.75, player.getPosition().y);
            if (player.getPosition().x <= 0)
                player.setPosition(0, player.getPosition().y);


            //Projectiles
            if (shootTimer < shootingTime)
                shootTimer++;
            if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= shootingTime) // shoot
            {
                projectile.setPosition(playerCenter);
                projectiles.push_back(CircleShape(projectile));
                shootTimer = 0;
            }
            for (size_t i = 0; i < projectiles.size(); i++) {
                projectiles[i].move(0.f, -10.f);
                if (projectiles[i].getPosition().y <= 0)
                    projectiles.erase(projectiles.begin() + i);
            }
            int color;
            //Enemies
            if (enemySpawnTimer < speedSpawning)
                enemySpawnTimer++;
            //Spawn enemies
            if (enemySpawnTimer >= speedSpawning) {
                enemyRed.setPosition(0.f+enemyRed.getGlobalBounds().height, 20.f);
                enemyYellow.setPosition(0.f+enemyYellow.getGlobalBounds().height, 20.f);
                enemyGreen.setPosition(0.f+enemyGreen.getGlobalBounds().height, 20.f);
                enemyPink.setPosition(0.f+enemyPink.getGlobalBounds().height, 20.f);
                enemyBlue.setPosition(0.f+enemyBlue.getGlobalBounds().height, 20.f);

                //handler for intersection of red and yellow balls
                color = rand() % 5+1;
                if (color ==1) enemies.push_back(Sprite(enemyYellow));
                if (color ==2) enemies.push_back(Sprite(enemyRed));
                if (color ==3) enemies.push_back(Sprite(enemyGreen));
                if (color ==4) enemies.push_back(Sprite(enemyPink));
                if (color ==5) enemies.push_back(Sprite(enemyBlue));
                enemySpawnTimer = 0;
            }

            //Enemy hits boundary Lives counter
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i].getPosition().y ==  20.f )//starting position
                    enemies[i].move(movementspeed,0.f);
                if (enemies[i].getPosition().x >= window.getSize().x - 514.f)//right top moves down #1
                    enemies[i].move(0.f,movementspeed);
                if (enemies[i].getPosition().y >= (window.getSize().y - 808.f) && enemies[i].getPosition().y <= (window.getSize().y - 800.f))//top rights down then moves left #2
                    enemies[i].move(-movementspeed,0.f);
                if (enemies[i].getPosition().x <=  200.f && enemies[i].getPosition().y >=window.getSize().y - 808.f ) //top right down left then down #3
                    enemies[i].move(0.f,movementspeed);
                if (enemies[i].getPosition().x >=  190.f && enemies[i].getPosition().x <= window.getSize().x - 514.f && enemies[i].getPosition().y >= window.getSize().y - 600.f)//top right down left down then right #4
                    enemies[i].move(movementspeed,0.f);

                if (enemies[i].getPosition().y >= window.getSize().y - enemies[i].getGlobalBounds().height) {
                    enemies.erase(enemies.begin() + i);
                    intLives--;
                    stringLives.str("");
                    stringLives << "Lives " << intLives;
                    lives.setString(stringLives.str());
                }
            }
            if (intLives == 2)
                lives.setFillColor(Color::Yellow);
            if (intLives == 1)
                lives.setFillColor(Color::Red);
            if (intLives == 0) {
                lives.setFillColor(Color::Red);
            }
            //Collision
            for (size_t i = 0; i < projectiles.size(); i++) {
                for (size_t j = 0; j < enemies.size(); j++) {
                    if (projectiles[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                        ///////////////////////////////////////////////////////////////////
                        //change color when shooting
                        int random_color = rand() % 5 + 1;
                        switch (random_color) {
                            case 1://Green
                                if (previous_color != 1) {
                                    projectile.setFillColor(Color::Green);
                                    player.setColor(Color::Green);
                                    previous_color = 1;
                                    break;
                                } else {//if previous was Green
                                    random_color = rand() % 4 + 1;
                                    switch (random_color) {
                                        case 1://set either to Red
                                            projectile.setFillColor(Color::Red);
                                            player.setColor(Color::Red);
                                            previous_color = 2;
                                            break;
                                        case 2://set either to yellow
                                            projectile.setFillColor(Color::Yellow);
                                            player.setColor(Color::Yellow);
                                            previous_color = 3;
                                            break;
                                        case 3://set either to pink
                                            projectile.setFillColor(Color::Magenta);
                                            player.setColor(Color::Magenta);
                                            previous_color = 4;
                                            break;
                                        case 4://set either to blue
                                            projectile.setFillColor(Color(0,165,255));
                                            player.setColor(Color(0,165,255));
                                            previous_color = 5;
                                            break;
                                    }
                                }

                            case 2://Red
                                if (previous_color != 2) {
                                    projectile.setFillColor(Color::Red);
                                    player.setColor(Color::Red);
                                    previous_color = 2;
                                    break;
                                }else {//if previous was Red
                                    random_color = rand() % 4 + 1;
                                    switch (random_color) {
                                        case 1://set either to green
                                            projectile.setFillColor(Color::Green);
                                            player.setColor(Color::Green);
                                            previous_color = 1;
                                            break;
                                        case 2://set either to pink
                                            projectile.setFillColor(Color::Magenta);
                                            player.setColor(Color::Magenta);
                                            previous_color = 4;
                                            break;
                                        case 3://set either to yellow
                                            projectile.setFillColor(Color::Yellow);
                                            player.setColor(Color::Yellow);
                                            previous_color = 3;
                                            break;
                                        case 4://set either to Blue
                                            projectile.setFillColor(Color(0,165,255));
                                            player.setColor(Color(0,165,255));
                                            previous_color = 5;
                                            break;
                                    }
                                }

                            case 3: //Yellow
                                if (previous_color != 3) {
                                    projectile.setFillColor(Color::Yellow);
                                    player.setColor(Color::Yellow);
                                    previous_color = 3;
                                    break;
                                } else {//if previous was Yellow
                                    random_color = rand() % 4 + 1;
                                    switch (random_color) {
                                        case 1://set either to green
                                            projectile.setFillColor(Color::Green);
                                            player.setColor(Color::Green);
                                            previous_color = 1;
                                            break;
                                        case 2://set either to red
                                            projectile.setFillColor(Color::Red);
                                            player.setColor(Color::Red);
                                            previous_color = 2;
                                            break;
                                        case 3://set either to pink
                                            projectile.setFillColor(Color::Magenta);
                                            player.setColor(Color::Magenta);
                                            previous_color = 4;
                                            break;
                                        case 4://set either to Blue
                                            projectile.setFillColor(Color(0,165,255));
                                            player.setColor(Color(0,165,255));
                                            previous_color = 5;
                                            break;
                                    }
                                }

                            case 4://Pink
                                if (previous_color != 4) {
                                    projectile.setFillColor(Color::Magenta);
                                    player.setColor(Color::Magenta);
                                    previous_color = 4;
                                    break;
                                } else {//if previous was pink
                                    random_color = rand() % 4 + 1;
                                    switch (random_color) {
                                        case 1://set either to green
                                            projectile.setFillColor(Color::Green);
                                            player.setColor(Color::Green);
                                            previous_color = 1;
                                            break;
                                        case 2://set either to red
                                            projectile.setFillColor(Color::Red);
                                            player.setColor(Color::Red);
                                            previous_color = 2;
                                            break;
                                        case 3://set either to yellow
                                            projectile.setFillColor(Color::Yellow);
                                            player.setColor(Color::Yellow);
                                            previous_color = 3;
                                            break;
                                        case 4://set either to Blue
                                            projectile.setFillColor(Color(0,165,255));
                                            player.setColor(Color(0,165,255));
                                            previous_color = 5;
                                            break;
                                    }
                                }

                            case 5: //Blue
                                if (previous_color != 5) {
                                    projectile.setFillColor(Color(0,165,255));
                                    player.setColor(Color(0,165,255));
                                    previous_color = 5;
                                    break;
                                } else {//if previous was Blue
                                    random_color = rand() % 4 + 1;
                                    switch (random_color) {
                                        case 1://set either to green
                                            projectile.setFillColor(Color::Green);
                                            player.setColor(Color::Green);
                                            previous_color = 1;
                                            break;
                                        case 2://set either to red
                                            projectile.setFillColor(Color::Red);
                                            player.setColor(Color::Red);
                                            previous_color = 2;
                                            break;
                                        case 3://set either to yellow
                                            projectile.setFillColor(Color::Yellow);
                                            player.setColor(Color::Yellow);
                                            previous_color = 3;
                                            break;
                                        case 4://set either to Pink
                                            projectile.setFillColor(Color::Magenta);
                                            player.setColor(Color::Magenta);
                                            previous_color = 4;
                                            break;
                                    }
                                }
                        }
                        /////////////////////////////////////////////////////////////////////////////////

                        //if the colour of projectile is equal to the enemy shot at
                        if (enemies[j].getColor() == projectiles[i].getFillColor()) {
                            /////////////////////////////////ERASES ADJACENT ELEMENTS///////////////////////////////////
                            adjacent = 1;
                            int L = 0, R = 0;
                            bool left = true, right = true;
                            while (left || right) {
                                if (enemies[j + adjacent].getColor() == projectiles[i].getFillColor() && right) {
                                    L++;
                                } else right = false;
                                if (enemies[j - adjacent].getColor() == projectiles[i].getFillColor() && left) {
                                    R++;
                                } else left = false;
                                adjacent++;
                            }


                            if (L > 0 || R > 0) {
                                enemies.erase(enemies.begin() + j - R, enemies.begin() + j + L+1);
                                projectiles.erase(projectiles.begin() + i);
                                intScore += L + R + 1;
                                stringScore.str("");
                                stringScore << "Score " << intScore;
                                Score.setString(stringScore.str());
                                break;
                            } else {
                                enemies.erase(enemies.begin() + j);
                                projectiles.erase(projectiles.begin() + i);
                                intScore++;
                                stringScore.str("");
                                stringScore << "Score " << intScore;
                                Score.setString(stringScore.str());
                                break;
                            }
                        }
                        else {
                            projectiles.erase(projectiles.begin() + i);
                        }
                    }
                }
            }
            /////////////////////////////////ERASES ADJACENT ELEMENTS///////////////////////////////////


            ////////////////////////////////LEVELS///////////////////////////////////////////
            //Slow 2
            if (intScore >= 15 && intScore < 35) {
                shootingTime = 31;
                speedSpawning = 110;
                movementspeed = 1.f;
                Score.setFillColor(Color::Green);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 50.f);
            }
            //Average 3
            if (intScore >= 35 && intScore < 55) {
                shootingTime = 31;
                speedSpawning = 100;
                movementspeed = 1.1f;
                Score.setFillColor(Color::Green);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 100.f);
            }
            //Medium 4
            if (intScore >= 55 && intScore < 80) {
                shootingTime = 30;
                speedSpawning = 95;
                movementspeed = 1.2f;
                Score.setFillColor(Color::Yellow);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 150.f);
            }
            //Intermediate 5
            if (intScore >= 80 && intScore < 100) {
                shootingTime = 28;
                speedSpawning = 90;
                movementspeed = 1.3f;
                Score.setFillColor(Color::Yellow);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 200.f);
            }
            //Fast 6
            if (intScore >= 100 && intScore <130) {
                shootingTime = 25;
                speedSpawning = 85;
                movementspeed = 1.35f;
                Score.setFillColor(Color::Magenta);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 300.f);
            }

            //Next level with Big enemies 7
            if (intScore >= 130 && intScore < 160) {
                shootingTime = 23;
                speedSpawning = 80;
                movementspeed = 1.4f;
                Score.setFillColor(Color::Magenta);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 400.f);

            }//8
            if (intScore >= 160) {
                shootingTime = 20;
                speedSpawning = 75;
                movementspeed = 1.45f;
                Score.setFillColor(Color::Red);
                Frog.setPosition(window.getSize().x - Frog.getGlobalBounds().width, 500.f);
            }

            if ((Frog.getPosition().y == (500.f)) && intScore==200) {
                won = true;
            }
            ////////////////////////////////LEVELS///////////////////////////////////////////

            //Draw
            window.clear();
            window.draw(Background);
            window.draw(Frog);
            window.draw(finish);
            window.draw(player);
            window.draw(Score);
            window.draw(lives);

            for (size_t i = 0; i < enemies.size(); i++) {
                window.draw(enemies[i]);
            }
            for (size_t i = 0; i < projectiles.size(); i++) {
                window.draw(projectiles[i]);
            }
            window.display();
        }

            //Winning screen
        else {
            window.clear();
            window.draw(Background);
            window.draw(Frog);
            window.draw(finish);
            window.draw(you_win);
            window.display();
        }
    }
    return 0;
}
