#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include"Player.h"
#include"Platform.h"
#include"RedOrge.h"
#include"M01.h"
#include"Background.h"
#include"Menu.h"
#include"Pause.h"
#include"PlayerHealthBar.h"
#include"SpeedUp_item.h"
#include"HealthUp_item.h"
#include"ShieldUp_item.h"
#include"Scores.h"
#include"Fireball.h"
#include"Bullet.h"
#include"GreenOrge.h"
using namespace std;

static const float VIEW_HEIGHT = 1080.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

template <typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

void Showtexet(int x, int y, string word, int size, sf::RenderWindow& window, sf::Font* font)
{
    sf::Text text;
    text.setFont(*font);
    text.setPosition(x, y);
    text.setString(word);
    text.setCharacterSize(size);
    window.draw(text);
}

void updatascore(string a, int b)
{
    FILE* fp;
    char temp[255];
    int score[6];
    string name[6];
    vector <pair<int, string>> userScore;
    fp = fopen("font/score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp, "%d", &score[i]);
        userScore.push_back(make_pair(score[i], name[i]));
    }
    name[5] = a;
    score[5] = b;
    userScore.push_back(make_pair(score[5], name[5]));
    sort(userScore.begin(), userScore.end());
    fclose(fp);
    fopen("font/score.txt", "w");
    for (int i = 5; i >= 1; i--)
    {
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, userScore[i].first);
    }
    fclose(fp);
}

void Showscoreboard(sf::RenderWindow& window, float x)
{
    sf::Font font;
    font.loadFromFile("font/EvilFont.ttf");
    FILE* fp;
    char temp[255];
    char score[255];
    fp = fopen("font/score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        char no[3] = { '1' + i };
        no[1] = '.';
        no[2] = '\0';
        Showtexet(x, -170 + 100 * i, no, 50, window, &font);
        fscanf(fp, "%s", temp);
        Showtexet(x + 50.0f, -170 + 100 * i, temp, 50, window, &font);
        fscanf(fp, "%s", score);
        Showtexet(x + 400, -170 + 100 * i, score, 50, window, &font);
    }
    fclose(fp);
}

//Game
int gameState = 0, itemRan = 0, MenuRan = 0, scores = 0, power = 0, Level = 1;
float tempscores=0, tempscores2=0, MeteorTime = 2.0f, MeteorLastPosX = -6500.0f, spopDuration=0, hpopDuration=0, ppopDuration=0;
bool item01_status=0, item02_status=0, item03_status=0, Meteor=0, MeteorON[20], x = 1, shieldpop=0, healthpop=0, speedpop=0;

//Player
int playerHealth = 7, MeteorCount = 0;
float playerInvi=0, item01_duration=0;
bool canRun = 1, playerAtk = 0, hit[10] = { 0 }, playerBuff01 = 0, playerShield = 0, hit2[10] = { 0 }, hit3[10] = { 0 };

//RedOrge
int redOrgeHealth[10] = { 0 }, redOrgeCap = 4;
float redOrgeInvi[10] = { 0 }, redOrgeDie[10] = { 0 };
bool redOrgeHurtEnd[10] = { 0 };

//Mushroom01
int M01Health[10] = { 0 }, M01Cap = 2;
float M01Invi[10] = { 0 }, M01Die[10] = { 0 };
bool M01HurtEnd[10] = { 0 };

//GreenOrge
int greenOrgeHealth[10] = { 0 }, greenOrgeCap = 1;
float greenOrgeInvi[10] = { 0 }, greenOrgeDie[10] = { 0 }, greenOrgeAttack[10] = { 0 };
bool greenOrgeHurtEnd[10] = { 0 }, greenOrgeHit[10] = { 0 };

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Vanquisher" , sf::Style::Close | sf::Style::Fullscreen);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920.0f, VIEW_HEIGHT));
    sf::Image icon;
    icon.loadFromFile("Pics/icon.png");
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    string name;
    //Texture
    //Game States
    sf::Texture GameMenu01, GameMenu02, GameMenu03, PausePic, GameOverMenu, Leaderboard;
    sf::Texture RedOrgeWikiPic, ArmedMushroomWikiPic, ShieldOrgeWikiPic, MonGalleryPic;
    //Player & Monsters
    sf::Texture playerTexture, healthbar[8];
    sf::Texture redOrgeTexture,M01Texture,greenOrgeTexture;
    //Items
    sf::Texture speedup, healthup, shieldup, meteorSkill;
    //Other Entities
    sf::Texture platformTexture, gBackground, ground, number[10], FireB, BulletPic;

    //Sound Buffer
    sf::SoundBuffer OrgeBuffer,M01Buffer,SpeedBuffer,HealthBuffer,ShieldBuffer,ShieldBreakBuffer,PlayerBuffer,MainMenuBuffer,RockCrackBuffer,LevelOneMusicBuffer,LevelTwoMusicBuffer,ClickBuffer,SkillSoundBuffer;
    OrgeBuffer.loadFromFile("Sounds/OrgeHurtSound.wav");
    M01Buffer.loadFromFile("Sounds/M01HurtSound.wav");
    SpeedBuffer.loadFromFile("Sounds/SpeedSound.wav");
    HealthBuffer.loadFromFile("Sounds/HealthSound.wav");
    ShieldBuffer.loadFromFile("Sounds/ShieldSound.wav");
    ShieldBreakBuffer.loadFromFile("Sounds/ShieldBreak.wav");
    PlayerBuffer.loadFromFile("Sounds/PlayerHurtSound.wav");
    MainMenuBuffer.loadFromFile("Sounds/MainMenuMusic.wav");
    RockCrackBuffer.loadFromFile("Sounds/RockCrack.wav");
    LevelOneMusicBuffer.loadFromFile("Sounds/Level_1.wav");
    LevelTwoMusicBuffer.loadFromFile("Sounds/Level_2.wav");
    ClickBuffer.loadFromFile("Sounds/ClickSound.wav");
    SkillSoundBuffer.loadFromFile("Sounds/MeteorSound.wav");


    //Sound
    sf::Sound OrgeHurtSound,M01HurtSound,SpeedSound,HealthSound,ShieldSound,ShieldBreakSound,PlayerHurtSound,MainMenuMusic,RockCrack,LevelOneMusic,LevelTwoMusic,ClickSound,SkillSound;
    OrgeHurtSound.setBuffer(OrgeBuffer);
    M01HurtSound.setBuffer(M01Buffer);
    SpeedSound.setBuffer(SpeedBuffer);
    HealthSound.setBuffer(HealthBuffer);
    ShieldSound.setBuffer(ShieldBuffer);
    ShieldBreakSound.setBuffer(ShieldBreakBuffer);
    PlayerHurtSound.setBuffer(PlayerBuffer);
    MainMenuMusic.setBuffer(MainMenuBuffer); MainMenuMusic.setLoop(1);
    RockCrack.setBuffer(RockCrackBuffer);
    LevelOneMusic.setBuffer(LevelOneMusicBuffer); LevelOneMusic.setLoop(1);
    LevelTwoMusic.setBuffer(LevelTwoMusicBuffer); LevelTwoMusic.setLoop(1);
    ClickSound.setBuffer(ClickBuffer);
    SkillSound.setBuffer(SkillSoundBuffer);

    sf::Vector2f ran;
    sf::Vector2f redorgePos[10],M01Pos[10],greenorgePos[10];

    sf::Font font,font2;
    font.loadFromFile("font/EvilFont.ttf");
    font2.loadFromFile("font/THSarabunNew.ttf");

    sf::Text skillpoint,Ready,NReady,ShieldPick,HealthPick,SpeedPick,PowerText,LevelOne,LevelTwo,LevelThree,MyName,Item02_Time;
    sf::Text PowerShow(toString<int>(power), font);

    Item02_Time.setFont(font);
    Item02_Time.setString("");
    Item02_Time.setFillColor(sf::Color::Red);
    Item02_Time.setCharacterSize(40);
    Item02_Time.setPosition(sf::Vector2f(940.0f, 755.0f));

    MyName.setFont(font2);
    MyName.setString("Mr.Burit Sereewattana 64010462");
    MyName.setFillColor(sf::Color::White);
    MyName.setCharacterSize(40);
    MyName.setPosition(sf::Vector2f(0.0f, 750.0f));

    LevelOne.setFont(font);
    LevelOne.setString("Level 1");
    LevelOne.setFillColor(sf::Color::Blue);
    LevelOne.setCharacterSize(45);
    LevelOne.setPosition(sf::Vector2f(1000.0f, -170.0f));

    LevelTwo.setFont(font);
    LevelTwo.setString("Level 2");
    LevelTwo.setFillColor(sf::Color::Blue);
    LevelTwo.setCharacterSize(45);
    LevelTwo.setPosition(sf::Vector2f(1000.0f, -170.0f));

    LevelThree.setFont(font);
    LevelThree.setString("Level HELL !!");
    LevelThree.setFillColor(sf::Color::Blue);
    LevelThree.setCharacterSize(45);
    LevelThree.setPosition(sf::Vector2f(915.0f, -170.0f));

    PowerShow.setPosition(-570.0f, -170.0f);
    PowerShow.setCharacterSize(40);
    PowerShow.setFillColor(sf::Color::Blue);
    
    PowerText.setFont(font);
    PowerText.setString("Power : ");
    PowerText.setFillColor(sf::Color::Blue);
    PowerText.setCharacterSize(40);
    PowerText.setPosition(sf::Vector2f(-725.0f, -170.0f));

    Ready.setFont(font);
    Ready.setString(": Ready !!");
    Ready.setFillColor(sf::Color::Blue);
    Ready.setCharacterSize(40);
    Ready.setPosition(sf::Vector2f(-600.0f, 750.0f));
    NReady.setFont(font);
    NReady.setString(": Not Ready");
    NReady.setFillColor(sf::Color::Blue);
    NReady.setCharacterSize(40);
    NReady.setPosition(sf::Vector2f(-600.0f, 750.0f));
    ShieldPick.setFont(font);
    ShieldPick.setString("Shield Up !!");
    ShieldPick.setFillColor(sf::Color::Red);
    ShieldPick.setCharacterSize(30);
    ShieldPick.setPosition(sf::Vector2f(-600.0f, 750.0f));

    HealthPick.setFont(font);
    HealthPick.setString("Health Up !!");
    HealthPick.setFillColor(sf::Color::Red);
    HealthPick.setCharacterSize(30);
    HealthPick.setPosition(sf::Vector2f(-600.0f, 750.0f));

    SpeedPick.setFont(font);
    SpeedPick.setString("Speed Up !!");
    SpeedPick.setFillColor(sf::Color::Red);
    SpeedPick.setCharacterSize(30);
    SpeedPick.setPosition(sf::Vector2f(-600.0f, 750.0f));

    srand(time(NULL));

    GameOverMenu.loadFromFile("Pics/GameOver.png");
    GameOverMenu.setSmooth(true);
    Leaderboard.loadFromFile("Pics/Leaderboard.png");
    Leaderboard.setSmooth(true);
    GameMenu01.loadFromFile("Pics/GameMenu.png");
    GameMenu01.setSmooth(true);
    GameMenu02.loadFromFile("Pics/GameMenu02.png");
    GameMenu02.setSmooth(true);
    GameMenu03.loadFromFile("Pics/GameMenu03.png");
    GameMenu03.setSmooth(true);
    MonGalleryPic.loadFromFile("Pics/MonsterGallery.png");
    MonGalleryPic.setSmooth(true);
    RedOrgeWikiPic.loadFromFile("Pics/RedOrgeWiki.png");
    RedOrgeWikiPic.setSmooth(true);
    ArmedMushroomWikiPic.loadFromFile("Pics/Armed-mushroomWiki.png");
    ArmedMushroomWikiPic.setSmooth(true);
    ShieldOrgeWikiPic.loadFromFile("Pics/GreenOgreWiki.png");
    ShieldOrgeWikiPic.setSmooth(true);
    PausePic.loadFromFile("Pics/Pausing.png");
    PausePic.setSmooth(true);
    gBackground.loadFromFile("Pics/Background.jpg");
    gBackground.setSmooth(true);
    ground.loadFromFile("Pics/Black.jpg");
    ground.setSmooth(true);
    FireB.loadFromFile("Pics/Fireball.png");
    FireB.setSmooth(true);
    BulletPic.loadFromFile("Pics/Bullet.png");
    BulletPic.setSmooth(true);
    platformTexture.loadFromFile("Pics/Platform.png");
    platformTexture.setSmooth(true);
    playerTexture.loadFromFile("Pics/Player_TEST.png");
    playerTexture.setSmooth(true);
    redOrgeTexture.loadFromFile("Pics/Red_Orge_Test.png");
    redOrgeTexture.setSmooth(true);
    M01Texture.loadFromFile("Pics/Mushroom01.png");
    M01Texture.setSmooth(true);
    greenOrgeTexture.loadFromFile("Pics/GreenOrge.png");
    greenOrgeTexture.setSmooth(true);
    speedup.loadFromFile("Pics/SpeedUp_item.png");
    speedup.setSmooth(true);
    healthup.loadFromFile("Pics/HealthUp_item.png");
    healthup.setSmooth(true);
    shieldup.loadFromFile("Pics/ShieldUp_item.png");
    shieldup.setSmooth(true);
    meteorSkill.loadFromFile("Pics/MeteorSkill.png");
    meteorSkill.setSmooth(true);
    healthbar[0].loadFromFile("Pics/PlayerHealthBar0.png");
    healthbar[1].loadFromFile("Pics/PlayerHealthBar1.png");
    healthbar[2].loadFromFile("Pics/PlayerHealthBar2.png");
    healthbar[3].loadFromFile("Pics/PlayerHealthBar3.png");
    healthbar[4].loadFromFile("Pics/PlayerHealthBar4.png");
    healthbar[5].loadFromFile("Pics/PlayerHealthBar5.png");
    healthbar[6].loadFromFile("Pics/PlayerHealthBar6.png");
    healthbar[7].loadFromFile("Pics/PlayerHealthBar7.png");
    number[0].loadFromFile("Pics/Number_0.png");
    number[1].loadFromFile("Pics/Number_1.png");
    number[2].loadFromFile("Pics/Number_2.png");
    number[3].loadFromFile("Pics/Number_3.png");
    number[4].loadFromFile("Pics/Number_4.png");
    number[5].loadFromFile("Pics/Number_5.png");
    number[6].loadFromFile("Pics/Number_6.png");
    number[7].loadFromFile("Pics/Number_7.png");
    number[8].loadFromFile("Pics/Number_8.png");
    number[9].loadFromFile("Pics/Number_9.png");
    for (int i = 0; i <= 9; i++)
        number[i].setSmooth(true);
    for (int i = 0; i <= 7; i++)
        healthbar[i].setSmooth(true);

    Menu MonsterGallery(&MonGalleryPic, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Menu RedOrgeWiki(&RedOrgeWikiPic, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Menu GameOver(&GameOverMenu, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Menu Scoreboard(&Leaderboard, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Menu ArmedMushroomWiki(&ArmedMushroomWikiPic, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Menu ShieldOrgeWiki(&ShieldOrgeWikiPic, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Pause pause(&PausePic, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Player player(&playerTexture, sf::Vector2u(4, 4), 0.2f, 100.0f, 200.0f);
    Background bg1(&gBackground, sf::Vector2f(2500.0f, 1500.0f), sf::Vector2f(200.0f, 140.0f));
    Background bbg(&ground, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f));
    Platform plat1(&ground,sf::Vector2f(5000.0f, 600.0f), sf::Vector2f(300.0f, 1000.0f));
    SpeedUp_item item01(&speedup, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(300.0f, 500.0f)), item01_show(&speedup, sf::Vector2f(80.0f, 80.0f), sf::Vector2f(950.0f, 775.0f));
    HealthUp_item item02(&healthup, sf::Vector2f(50.0f, 60.0f), sf::Vector2f(300.0f, 500.0f));
    ShieldUp_item item03(&shieldup, sf::Vector2f(50.0f, 60.0f), sf::Vector2f(300.0f, 500.0f)), item03_show(&shieldup, sf::Vector2f(80.0f, 80.0f), sf::Vector2f(1050.0f, 775.0f));
    ShieldUp_item skill01(&meteorSkill, sf::Vector2f(100.0f, 80.0f), sf::Vector2f(-675.0f, 775.0f));
    std::vector<Platform> platforms;
    std::vector<Fireball> fireballs;
    std::vector<RedOrge> redorges;
    std::vector<M01> m01s;
    std::vector<GreenOrge> greenorges;
    std::vector<PlayerHealthBar> pHealths;
    std::vector<Menu> menus;
    std::vector<Scores> scoreShow1, scoreShow2, scoreShow3, scoreShow4, scoreShow5, scoreShow6;
    std::vector<Bullet> bullets;

    menus.push_back(Menu(&GameMenu01, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f)));
    menus.push_back(Menu(&GameMenu02, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f)));
    menus.push_back(Menu(&GameMenu03, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(0.0f, 0.0f)));
    MenuRan = rand() % 3;

    //Monsters Spawn
    for (int i = 0; i < 6; i++)
    {
        redorges.push_back(RedOrge(&redOrgeTexture, sf::Vector2u(6, 5), 0.2f, 40.0f));
    }
    for (int i = 0; i < 4; i++)
    {
        m01s.push_back(M01(&M01Texture, sf::Vector2u(4, 5), 0.2f, 120.0f));
    }
    for (int i = 0; i < 3; i++)
    {
        greenorges.push_back(GreenOrge(&greenOrgeTexture, sf::Vector2u(6, 5), 0.2f, 40.0f));
    }

    for (int i = 0; i < 20; i++)
    {
        fireballs.push_back(Fireball(&FireB, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(300.0f, 500.0f)));
        MeteorON[i] = 0;
    }

    for (int i = 0; i < 8; i++)
    {
        pHealths.push_back(PlayerHealthBar(&healthbar[i], sf::Vector2f(500.0f, 50.0f), sf::Vector2f(-525.0f, -200.0f)));
    }

    for (int i = 0; i <= 9; i++)
    {
        if(i==1)
            scoreShow1.push_back(Scores(&number[i], sf::Vector2f(60.0f, 70.0f), sf::Vector2f(1100.0f, -200.0f)));
        else
            scoreShow1.push_back(Scores(&number[i], sf::Vector2f(60.0f, 60.0f), sf::Vector2f(1100.0f, -200.0f)));
    }
    scoreShow2 = scoreShow1;
    scoreShow3 = scoreShow1;
    scoreShow4 = scoreShow1;
    scoreShow5 = scoreShow1;
    scoreShow6 = scoreShow1;

    sf::Vector2f setView;
    setView.x = -525.0f;
    setView.y = -200.0f;
    for (int i = 0; i < 8; i++)
        pHealths[i].SetPos(setView);
    setView.x += 1625.0f;
    for (int i = 0; i <= 9; i++)
        scoreShow1[i].SetPos(setView);
    setView.x -= 60.0f;
    for (int i = 0; i <= 9; i++)
        scoreShow2[i].SetPos(setView);
    setView.x -= 60.0f;
    for (int i = 0; i <= 9; i++)
        scoreShow3[i].SetPos(setView);
    setView.x -= 60.0f;
    for (int i = 0; i <= 9; i++)
        scoreShow4[i].SetPos(setView);
    setView.x -= 60.0f;
    for (int i = 0; i <= 9; i++)
        scoreShow5[i].SetPos(setView);
    setView.x -= 60.0f;
    for (int i = 0; i <= 9; i++)
        scoreShow6[i].SetPos(setView);

    window.clear(sf::Color(150, 150, 150));

    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(700.0f, 350.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(500.0f, 530.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(50.0f, 450.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(-250.0f, 260.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(0.0f, 80.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(1000.0f, 170.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(-700.0f, 500.0f)));

    float deltaTime = 0.0f,lastdeltaTime = 0.0f;
    sf::Clock clock;
    sf::Time delayTime = sf::milliseconds(100);

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;
        
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (gameState == 6)
            {
                if (evnt.type == sf::Event::TextEntered)
                    name.push_back(evnt.text.unicode);
                if (!name.empty() && name.back() == 8)
                {
                    name.pop_back();
                    if (!name.empty())
                        name.pop_back();

                }
                if (!name.empty() && !(name.back() >= 'a' && name.back() <= 'z' || name.back() >= 'A' && name.back() <= 'Z' || name.back() >= '0' && name.back() <= '9'))
                {
                    name.pop_back();
                }
            }
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }
        
        if (gameState == 0)
        {
            view.setCenter(0.0f, 0.0f);
            menus[MenuRan].Draw(window);
            
            MainMenuMusic.play();
            sf::Vector2i mousePos = sf::Mouse::getPosition();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 700 && mousePos.x <= 1215 && mousePos.y <= 415 && mousePos.y >= 265) // Play
            {
                ClickSound.play();
                gameState = 1;
                redOrgeCap = 3;
                M01Cap = 2;
                greenOrgeCap = 1;
                for (int i = 0; i < redOrgeCap; i++)
                {
                    ran.x = rand() % 1720 - 710;
                    while (ran.x < 300 && ran.x > -100)
                        ran.x = rand() % 1720 - 710;
                    ran.y = 0.0f;
                    redorges[i].SetPos(ran);
                    redOrgeHealth[i] = 3;
                    redOrgeDie[i] = 0;
                    redOrgeInvi[i] = 4;
                }
                for (int i = 0; i < M01Cap; i++)
                {
                    ran.x = rand() % 1720 - 710;
                    while (ran.x < 300 && ran.x > -100)
                        ran.x = rand() % 1720 - 710;
                    ran.y = 0.0f;
                    m01s[i].SetPos(ran);
                    M01Health[i] = 1;
                    M01Die[i] = 0;
                    M01Invi[i] = 4;
                }
                for (int i = 0; i < greenOrgeCap; i++)
                {
                    ran.x = rand() % 1720 - 710;
                    while (ran.x < 300 && ran.x > -100)
                        ran.x = rand() % 1720 - 710;
                    ran.y = 0.0f;
                    greenorges[i].SetPos(ran);
                    greenOrgeHealth[i] = 1;
                    greenOrgeDie[i] = 0;
                    greenOrgeInvi[i] = 4;
                    greenOrgeAttack[i] = 0;
                    greenOrgeHit[i] = 0.0f;
                }
                sf::Vector2f TempPOS;
                TempPOS.x = 200.0f;
                TempPOS.y = 1000.0f;
                player.SetPosition(TempPOS);
                playerHealth = 7;
                scores = 0;
                power = 0;
                tempscores = 0;
                tempscores2 = 0;
                item01_status = 0;
                item02_status = 0;
                item03_status = 0;
                item01_duration = 0;
                playerBuff01 = 0;
                playerInvi = 0;
                Level = 1;
                bullets.clear();
                name.clear();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 1745 && mousePos.x <= 1875 && mousePos.y <= 1040 && mousePos.y >= 890) // Gallery
            {
                ClickSound.play();
                gameState = 30;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 700 && mousePos.x <= 1215 && mousePos.y <= 615 && mousePos.y >= 465) // Leaderboard
            {
                gameState = 7;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 700 && mousePos.x <= 1215 && mousePos.y <= 820 && mousePos.y >= 675) // Exit
            {
                ClickSound.play();
                window.close();
                break;
            }
        }
        else if (gameState == 30)
        {
            bbg.Draw(window);
            MonsterGallery.Draw(window);
            sf::Vector2i mousePos = sf::Mouse::getPosition();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 270 && mousePos.x <= 515 && mousePos.y <= 325 && mousePos.y >= 130) // Mushroom
            {
                ClickSound.play();
                gameState = 31;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 590 && mousePos.x <= 835 && mousePos.y <= 325 && mousePos.y >= 130) // RedOrge
            {
                ClickSound.play();
                gameState = 32;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 270 && mousePos.x <= 515 && mousePos.y <= 590 && mousePos.y >= 390) // ShieldOrge
            {
                ClickSound.play();
                gameState = 33;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 1590 && mousePos.x <= 1690 && mousePos.y <= 925 && mousePos.y >= 885) // Back
            {
                ClickSound.play();
                gameState = 0;
                MenuRan = rand() % 3;
            }
        }
        else if (gameState == 31)
        {
            bbg.Draw(window);
            ArmedMushroomWiki.Draw(window);
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 1590 && mousePos.x <= 1690 && mousePos.y <= 925 && mousePos.y >= 885) // Back
            {
                ClickSound.play();
                gameState = 30;
                sf::sleep(delayTime);
            }
        }
        else if (gameState == 32)
        {
            bbg.Draw(window);
            RedOrgeWiki.Draw(window);
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 1590 && mousePos.x <= 1690 && mousePos.y <= 925 && mousePos.y >= 885) // Back
            {
                ClickSound.play();
                gameState = 30;
                sf::sleep(delayTime);
            }
        }
        else if (gameState == 33)
        {
            bbg.Draw(window);
            ShieldOrgeWiki.Draw(window);
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 1590 && mousePos.x <= 1690 && mousePos.y <= 925 && mousePos.y >= 885) // Back
            {
                ClickSound.play();
                gameState = 30;
                sf::Time delayTime = sf::milliseconds(100);
                sf::sleep(delayTime);
            }
        }
        else if (gameState == 6)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                ClickSound.play();
                char temp[100];
                strcpy(temp, name.c_str());
                if (strlen(temp) == 0)
                    strcpy(temp, "anonymous");
                updatascore(temp, scores);
                gameState = 0;
            }
            view.setCenter(0.0f, 0.0f);
            GameOver.Draw(window);
            Showtexet(-750, -50, "Score : ", 100, window, &font);
            Showtexet(-450, -50, to_string(scores), 100, window, &font);
            if (name.empty())
               Showtexet(-525, -250, "Enter name", 100, window, &font);
            else
               Showtexet(-600, -250, name, 100, window, &font);
        }
        else if (gameState == 7)
        {
            Scoreboard.Draw(window);
            Showscoreboard(window, -250.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                ClickSound.play();
                gameState = 0;
            }
        }
        else if (gameState == 1)
        {
            sf::Vector2f playerPos = player.GetPosition();
            Collider playerCollider = player.GetCollider();
            sf::Vector2f direction;

            //Bullet
            for (int i = 0; i < greenOrgeCap; i++)
            {
                greenOrgeAttack[i] += deltaTime;
                if (greenOrgeAttack[i] > 6.0f && greenOrgeHealth[i] > 0)
                {
                    sf::Vector2f AttackPOS = greenorges[i].GetPosition();
                    bullets.push_back(Bullet(&BulletPic, sf::Vector2f(15.0f, 15.0f), playerPos, AttackPOS));
                    greenOrgeAttack[i] = 0.0f;
                    greenOrgeHit[i] = 1;
                }
            }

            if (scores >= 50000 && Level == 1)
            {
                Level = 2;
                redOrgeCap++;
                M01Cap++;
                greenOrgeCap++;
                redOrgeDie[4] = 3.0f;
                M01Die[2] = 3.0f;
                greenOrgeDie[1] = 3.0f;
            }
            else if (scores >= 150000 && Level == 2)
            {
                Level = 3;
                redOrgeCap++;
                M01Cap++;
                greenOrgeCap++;
                redOrgeDie[5] = 3.0f;
                M01Die[3] = 3.0f;
                greenOrgeDie[2] = 3.0f;
            }

            //Invisible Time After Hit For Monsters
            for (int i = 0; i < redOrgeCap; i++)
            {
                redOrgeInvi[i] += (deltaTime);
            }
            for (int i = 0; i < M01Cap; i++)
            {
                M01Invi[i] += (deltaTime);
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                greenOrgeInvi[i] += (deltaTime);
            }

            playerInvi += (deltaTime);

            if (playerBuff01 == 1)
            {
                item01_duration -= (deltaTime);
            }

            //Monsters Respawn
            for (int i = 0; i < redOrgeCap; i++)
            {
                if (redOrgeHealth[i] < 0)
                    redOrgeDie[i] += deltaTime;
                if (redOrgeDie[i] >= 3.0f)
                {
                    ran.x = rand() % 1720 - 710;
                    ran.y = 0.0f;
                    redorges[i].SetPos(ran);
                    redOrgeHealth[i] = 3;
                    redOrgeDie[i] = 0;
                    redOrgeInvi[i] = 1.0f;
                }
            }
            for (int i = 0; i < M01Cap; i++)
            {
                if (M01Health[i] < 0)
                    M01Die[i] += deltaTime;
                if (M01Die[i] >= 3.0f)
                {
                    ran.x = rand() % 1720 - 710;
                    ran.y = 0.0f;
                    m01s[i].SetPos(ran);
                    M01Health[i] = 1;
                    M01Die[i] = 0;
                    M01Invi[i] = 1.0f;
                }
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                if (greenOrgeHealth[i] < 0)
                    greenOrgeDie[i] += deltaTime;
                if (greenOrgeDie[i] >= 3.0f)
                {
                    ran.x = rand() % 1720 - 710;
                    ran.y = 0.0f;
                    greenorges[i].SetPos(ran);
                    greenOrgeHealth[i] = 1;
                    greenOrgeDie[i] = 0;
                    greenOrgeInvi[i] = 1.0f;
                    greenOrgeAttack[i] = 0.0f;
                }
            }

            //Power
            if (tempscores2 >= 1500.0f)
            {
                tempscores2 -= 1500.0f;
                if(power < 10)
                    power += 1;
            }

            //Items
            if (tempscores >= 3000.0f)
            {
                tempscores -= 3000.0f;

                ran.x = rand() % 1720 - 710;
                while (ran.x < 300 && ran.x > -100)
                    ran.x = rand() % 1720 - 710;
                ran.y = -150.0f;

                itemRan = rand() % 3 + 1;
                if (itemRan == 1)
                {
                    item01_status = 1;
                    item01.SetPos(ran);
                }
                else if (itemRan == 2)
                {
                    item02_status = 1;
                    item02.SetPos(ran);
                }
                else if (itemRan == 3)
                {
                    item03_status = 1;
                    item03.SetPos(ran);
                }
            }

            if (item01_status == 1)
            {
                item01.Update(deltaTime);
                Collider item01Collider = item01.GetCollider();

                for (Platform& platform : platforms)
                {
                    if (platform.GetCollider().CheckCollision(item01Collider, direction, 1.0f, 1))
                        item01.OnCollision(direction);
                }
                if (plat1.GetCollider().CheckCollision(item01Collider, direction, 1.0f, 1))
                    item01.OnCollision(direction);
                if (player.GetCollider().CheckCollision(item01Collider, direction, 1.0f, 1))
                {
                    SpeedSound.play();
                    speedpop = 1;
                    ppopDuration = 0.0f;
                    SpeedPick.setPosition(playerPos.x, playerPos.y + 20);
                    item01_status = 0;
                    playerBuff01 = 1;
                    player.SetSpeed(150.0f);
                    item01_duration += 10;
                }
            }
            if (item02_status == 1)
            {
                item02.Update(deltaTime);
                Collider item02Collider = item02.GetCollider();
                
                for (Platform& platform : platforms)
                {
                    if (platform.GetCollider().CheckCollision(item02Collider, direction, 1.0f, 1))
                        item02.OnCollision(direction);
                }
                if (plat1.GetCollider().CheckCollision(item02Collider, direction, 1.0f, 1))
                    item02.OnCollision(direction);
                if (player.GetCollider().CheckCollision(item02Collider, direction, 1.0f, 1))
                {
                    HealthSound.play();
                    healthpop = 1;
                    hpopDuration = 0.0f;
                    HealthPick.setPosition(playerPos.x, playerPos.y + 20);
                    item02_status = 0;
                    if (playerHealth < 7)
                        playerHealth++;
                }
            }
            if (item03_status == 1)
            {
                item03.Update(deltaTime);
                Collider item03Collider = item03.GetCollider();
                
                for (Platform& platform : platforms)
                {
                    if (platform.GetCollider().CheckCollision(item03Collider, direction, 1.0f, 1))
                        item03.OnCollision(direction);
                }
                if (plat1.GetCollider().CheckCollision(item03Collider, direction, 1.0f, 1))
                    item03.OnCollision(direction);
                if (player.GetCollider().CheckCollision(item03Collider, direction, 1.0f, 1))
                {
                    ShieldSound.play();
                    shieldpop = 1;
                    spopDuration = 0.0f;
                    ShieldPick.setPosition(playerPos.x,playerPos.y+20);
                    item03_status = 0;
                    playerShield = 1;
                }
            }
            if (item01_duration < 0.0f)
            {
                playerBuff01 = 0;
                item01_duration = 0;
                player.SetSpeed(100.0f);
            }
            
            for(int i=0;i<redOrgeCap;i++)
                redorgePos[i] = redorges[i].GetPosition();
            for (int i = 0; i < M01Cap; i++)
                M01Pos[i] = m01s[i].GetPosition();
            for (int i = 0; i < greenOrgeCap; i++)
                greenorgePos[i] = greenorges[i].GetPosition(); 

            for (Platform& platform : platforms)
            {
                if (platform.GetCollider().CheckCollision(playerCollider, direction, 1.0f, 1))
                    player.OnCollision(direction);
                for(int i=0;i<redOrgeCap;i++)
                {
                    Collider RedOrgeCollider = redorges[i].GetCollider();
                    if (platform.GetCollider().CheckCollision(RedOrgeCollider, direction, 1.0f, 1))
                        redorges[i].OnCollision(direction);
                }
                for (int i = 0; i < M01Cap; i++)
                {
                    Collider M01Collider = m01s[i].GetCollider();
                    if (platform.GetCollider().CheckCollision(M01Collider, direction, 1.0f, 1))
                        m01s[i].OnCollision(direction);
                }
                for (int i = 0; i < greenOrgeCap; i++)
                {
                    Collider GreenOrgeCollider = greenorges[i].GetCollider();
                    if (platform.GetCollider().CheckCollision(GreenOrgeCollider, direction, 1.0f, 1))
                        greenorges[i].OnCollision(direction);
                }
            }

            if (plat1.GetCollider().CheckCollision(playerCollider, direction, 1.0f, 1))
                player.OnCollision(direction);

            //On ground
            for (int i = 0; i < redOrgeCap; i++)
            {
                Collider RedOrgeCollider = redorges[i].GetCollider();
                if (plat1.GetCollider().CheckCollision(RedOrgeCollider, direction, 1.0f, 1))
                    redorges[i].OnCollision(direction);
            }
            for (int i = 0; i < M01Cap; i++)
            {
                Collider M01Collider = m01s[i].GetCollider();
                if (plat1.GetCollider().CheckCollision(M01Collider, direction, 1.0f, 1))
                    m01s[i].OnCollision(direction);
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                Collider GreenOrgeCollider = greenorges[i].GetCollider();
                if (plat1.GetCollider().CheckCollision(GreenOrgeCollider, direction, 1.0f, 1))
                    greenorges[i].OnCollision(direction);
            }

            //Player Attack
            for (int i = 0; i < redOrgeCap; i++)
            {
                Collider RedOrgeCollider = redorges[i].GetCollider();
                if (player.GetCollider().CheckCollision(RedOrgeCollider, direction, 1.0f, 0) == 1)
                {
                    hit[i] = 1;
                }
            }
            for (int i = 0; i < M01Cap; i++)
            {
                Collider M01Collider = m01s[i].GetCollider();
                if (player.GetCollider().CheckCollision(M01Collider, direction, 1.0f, 0) == 1)
                {
                    hit2[i] = 1;
                }
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                Collider GreenOrgeCollider = greenorges[i].GetCollider();
                if (player.GetCollider().CheckCollision(GreenOrgeCollider, direction, 1.0f, 0) == 1)
                {
                    hit3[i] = 1;
                }
            }

            playerPos = player.GetPosition();

            if (playerPos.x <= 1125.0f && playerPos.x >= -725.0f)
                canRun = 1;
            else
                canRun = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && power == 10)
            {
                Meteor = 1;
                power = 0;
                SkillSound.play();
            }

            if (Meteor == 1)
            {
                if (MeteorCount < 20)
                {
                    MeteorTime += deltaTime;
                    if (MeteorTime >= 0.25f)
                    {
                        ran.x = rand() % 1720 - 710;
                        ran.y = -200.0f;
                        fireballs[MeteorCount].SetPos(ran);
                        MeteorON[MeteorCount] = 1;
                        MeteorCount++;
                        MeteorTime = 0.0f;
                    }
                }
                else
                {
                    Meteor = 0;
                    MeteorCount = 0;
                    MeteorTime = 2.0f;
                }
            }

            for (int i = 0; i < 20; i++)
            {   
                fireballs[i].Update(deltaTime);
                Collider fireballCollider = fireballs[i].GetCollider();
                if (MeteorON[i] == 1)
                {
                    for (int j = 0; j < redOrgeCap; j++)
                    {
                        if (redorges[j].GetCollider().CheckCollision(fireballCollider, direction, 1.0f, 0) == 1 && redOrgeHealth[j] > 0 && redOrgeInvi[j] > 1.5f)
                        {
                            OrgeHurtSound.play();
                            redOrgeHurtEnd[j] = redorges[j].Update(deltaTime, playerPos, redorgePos[j], 1);
                            redOrgeInvi[j] = 0.0f;
                        }
                    }
                    for (int j = 0; j < M01Cap; j++)
                    {
                        if (m01s[j].GetCollider().CheckCollision(fireballCollider, direction, 1.0f, 0) == 1 && M01Health[j] > 0 && M01Invi[j] > 1.5f)
                        {
                            M01HurtSound.play();
                            M01HurtEnd[j] = m01s[j].Update(deltaTime, playerPos, M01Pos[j], 1);
                            M01Invi[j] = 0.0f;
                        }
                    }
                    for (int j = 0; j < greenOrgeCap; j++)
                    {
                        if (greenorges[j].GetCollider().CheckCollision(fireballCollider, direction, 1.0f, 0) == 1 && greenOrgeHealth[j] > 0 && greenOrgeInvi[j] > 1.5f)
                        {
                            OrgeHurtSound.play();
                            greenOrgeHurtEnd[j] = greenorges[j].Update(deltaTime, playerPos, greenorgePos[j], 1, greenOrgeHit[j]);
                            greenOrgeInvi[j] = 0.0f;
                        }
                    }
                }
                if (plat1.GetCollider().CheckCollision(fireballCollider, direction, 1.0f, 1))
                {
                        fireballs[i].OnCollision(direction);
                        MeteorON[i] = 0;
                }
            }

            playerAtk = player.Update(deltaTime, canRun, playerPos.x);
            playerPos = player.GetPosition();

            for (int i = 0; i < bullets.size(); i++)
            {
                bullets[i].Update();
                sf::Vector2f BulletPOS = bullets[i].GetPosition();
                if (bullets[i].GetCollider().CheckCollision(playerCollider, direction, 1.0f, 1))
                {
                    bullets.erase(bullets.begin() + i);
                    if(playerAtk == 1)
                        RockCrack.play();
                    else if (playerAtk == 0 && playerShield == 0 && playerInvi > 4.0f)
                    {
                        PlayerHurtSound.play();
                        playerHealth -= 2;
                        playerInvi = 0;
                    }
                    else if (playerAtk == 0 && playerShield == 1 && playerInvi > 4.0f)
                    {
                        ShieldBreakSound.play();
                        playerShield = 0;
                        playerInvi = 0;
                    }
                }
                else if (BulletPOS.x > 1125 || BulletPOS.x < -725 || BulletPOS.y > 820 || BulletPOS.y < -235)
                    bullets.erase(bullets.begin() + i);
            }

            //Player Attack Monsters           
            for (int i = 0; i < redOrgeCap; i++)
            {
                if (hit[i] == 1 && playerAtk == 1 && redOrgeInvi[i] > 1.5f && redOrgeHealth[i] > 0)
                {
                    OrgeHurtSound.play();
                    redOrgeHurtEnd[i] = redorges[i].Update(deltaTime, playerPos, redorgePos[i], 1);
                    redOrgeInvi[i] = 0.0f;
                }
                else if (hit[i] == 1 && playerInvi > 4.0f && redOrgeInvi[i] > 1.5f && redOrgeHealth[i] > 0 && playerShield == 1)
                {
                    ShieldBreakSound.play();
                    redOrgeHurtEnd[i] = redorges[i].Update(deltaTime, playerPos, redorgePos[i], 0);
                    playerInvi = 0.0f;
                    playerShield = 0;
                }
                else if (hit[i] == 1 && playerInvi > 4.0f && redOrgeInvi[i] > 1.5f && redOrgeHealth[i] > 0)
                {
                    PlayerHurtSound.play();
                    redOrgeHurtEnd[i] = redorges[i].Update(deltaTime, playerPos, redorgePos[i], 0);
                    playerHealth--;
                    playerInvi = 0.0f;
                }
                else
                {
                        redOrgeHurtEnd[i] = redorges[i].Update(deltaTime, playerPos, redorgePos[i], 0);
                }
            }
            for (int i = 0; i < M01Cap; i++)
            {
                if (hit2[i] == 1 && playerAtk == 1 && M01Invi[i] > 1.5f && M01Health[i] > 0)
                {
                    M01HurtSound.play();
                    M01HurtEnd[i] = m01s[i].Update(deltaTime, playerPos, M01Pos[i], 1);
                    M01Invi[i] = 0.0f;
                }
                else if (hit2[i] == 1 && playerInvi > 4.0f && M01Invi[i] > 1.5f && M01Health[i] > 0 && playerShield == 1)
                {
                    ShieldBreakSound.play();
                    M01HurtEnd[i] = m01s[i].Update(deltaTime, playerPos, M01Pos[i], 0);
                    playerInvi = 0.0f;
                    playerShield = 0;
                }
                else if (hit2[i] == 1 && playerInvi > 4.0f && M01Invi[i] > 1.5f && M01Health[i] > 0)
                {
                    PlayerHurtSound.play();
                    M01HurtEnd[i] = m01s[i].Update(deltaTime, playerPos, M01Pos[i], 0);
                    playerHealth -= 3;
                    playerInvi = 0.0f;
                }
                else
                {
                    M01HurtEnd[i] = m01s[i].Update(deltaTime, playerPos, M01Pos[i], 0);
                }
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                if (hit3[i] == 1 && playerAtk == 1 && greenOrgeInvi[i] > 1.5f && greenOrgeHealth[i] > 0)
                {
                    OrgeHurtSound.play();
                    greenOrgeHurtEnd[i] = greenorges[i].Update(deltaTime, playerPos, greenorgePos[i], 1, greenOrgeHit[i]);
                    greenOrgeInvi[i] = 0.0f;
                }
                else if (hit3[i] == 1 && playerInvi > 4.0f && greenOrgeInvi[i] > 1.5f && greenOrgeHealth[i] > 0 && playerShield == 1)
                {
                    ShieldBreakSound.play();
                    greenOrgeHurtEnd[i] = greenorges[i].Update(deltaTime, playerPos, greenorgePos[i], 0, greenOrgeHit[i]);
                    playerInvi = 0.0f;
                    playerShield = 0;
                }
                else if (hit3[i] == 1 && playerInvi > 4.0f && greenOrgeInvi[i] > 1.5f && greenOrgeHealth[i] > 0)
                {
                    PlayerHurtSound.play();
                    greenOrgeHurtEnd[i] = greenorges[i].Update(deltaTime, playerPos, greenorgePos[i], 0, greenOrgeHit[i]);
                    playerHealth -= 2;
                    playerInvi = 0.0f;
                }
                else
                {
                    greenOrgeHurtEnd[i] = greenorges[i].Update(deltaTime, playerPos, greenorgePos[i], 0, greenOrgeHit[i]);
                }
            }

            for (int i = 0; i < redOrgeCap; i++)
            {
                if (redOrgeHurtEnd[i] == true)
                {
                    redOrgeHealth[i]--;
                }
            }
            for (int i = 0; i < M01Cap; i++)
            {
                if (M01HurtEnd[i] == true)
                {
                    M01Health[i]--;
                }
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                if (greenOrgeHurtEnd[i] == true)
                {
                    greenOrgeHealth[i]--;
                }
            }

            setView.x = 200.0f;
            setView.y = 300.0f;
            view.setCenter(setView);

            window.clear(sf::Color(150, 150, 150));

            bg1.Draw(window);
            plat1.SetPos(playerPos);
            plat1.Draw(window);
            player.Draw(window);
            skill01.Draw(window);

            PowerShow.setString(toString<int>(power));
            window.draw(PowerText);
            window.draw(PowerShow);

            for (Platform& platform : platforms)
                platform.Draw(window);
            for (Bullet& bullet : bullets)
                bullet.Draw(window);
            if (item01_status == 1)
                item01.Draw(window);
            if (item02_status == 1)
                item02.Draw(window);
            if (item03_status == 1)
                item03.Draw(window);
            if (playerHealth >= 0)
                pHealths[playerHealth].Draw(window);
            else
                pHealths[0].Draw(window);
            if (playerBuff01 == 1)
            {
                item01_show.Draw(window);
                int showTime = ceil(item01_duration);
                Item02_Time.setString(to_string(showTime));
                window.draw(Item02_Time);
            }
            if(playerShield == 1)
                item03_show.Draw(window);
            scoreShow1[scores%10].Draw(window);
            scoreShow2[scores%100/10].Draw(window);
            scoreShow3[scores%1000/100].Draw(window);
            scoreShow4[scores%10000/1000].Draw(window);
            scoreShow5[scores%100000/10000].Draw(window);
            scoreShow6[scores/100000].Draw(window);

            // PopUp When Pick Item
            //Shield
            if (spopDuration < 0.5f)
            {
                spopDuration += deltaTime;
                sf::Vector2f item03_Pos = ShieldPick.getPosition();
                ShieldPick.setPosition(item03_Pos.x, item03_Pos.y-0.1f);
            }
            else
            {
                shieldpop = 0;
            }

            if (shieldpop == 1)
            {
                window.draw(ShieldPick);
            }
            //Health
            if (hpopDuration < 0.5f)
            {
                hpopDuration += deltaTime;
                sf::Vector2f item02_Pos = HealthPick.getPosition();
                HealthPick.setPosition(item02_Pos.x, item02_Pos.y - 0.1f);
            }
            else
            {
                healthpop = 0;
            }

            if (healthpop == 1)
            {
                window.draw(HealthPick);
            }
            //Speed
            if (ppopDuration < 0.5f)
            {
                ppopDuration += deltaTime;
                sf::Vector2f item01_Pos = SpeedPick.getPosition();
                SpeedPick.setPosition(item01_Pos.x, item01_Pos.y - 0.1f);
            }
            else
            {
                speedpop = 0;
            }

            if (speedpop == 1)
            {
                window.draw(SpeedPick);
            }

            //Meteor Skill Draw
            for (int i = 0; i < 20; i++)
            {
                if (MeteorON[i] == 1)
                    fireballs[i].Draw(window);
            }
            for (int i = 0; i < redOrgeCap; i++)
            {
                if (redOrgeHealth[i] > 0)
                    redorges[i].Draw(window);
                else if (redOrgeHealth[i] == 0)
                {
                    redorges[i].Draw(window);
                    redOrgeHealth[i]--;
                    scores += 300;
                    tempscores += 300.0f;
                    tempscores2 += 300.0f;
                }
            }
            for (int i = 0; i < M01Cap; i++)
            {
                if (M01Health[i] > 0)
                    m01s[i].Draw(window);
                else if (M01Health[i] == 0)
                {
                    m01s[i].Draw(window);
                    M01Health[i]--;
                    scores += 500;
                    tempscores += 500.0f;
                    tempscores2 += 500.0f;
                }
            }
            for (int i = 0; i < greenOrgeCap; i++)
            {
                if (greenOrgeHealth[i] > 0)
                    greenorges[i].Draw(window);
                else if (greenOrgeHealth[i] == 0)
                {
                    greenorges[i].Draw(window);
                    greenOrgeHealth[i]--;
                    scores += 700;
                    tempscores += 700.0f;
                    tempscores2 += 700.0f;
                }
            }

            if (power == 10)
                window.draw(Ready);
            else
                window.draw(NReady);

            if (Level == 1)
            {
                window.draw(LevelOne);
            }
            else if (Level == 2)
            {
                window.draw(LevelTwo);
            }
            else
            {
                window.draw(LevelThree);
            }

            for (int i = 0; i < redOrgeCap; i++)
                hit[i] = 0;
            for (int i = 0; i < M01Cap; i++)
                hit2[i] = 0;
            for (int i = 0; i < greenOrgeCap; i++)
                hit3[i] = 0;
            for (int i = 0; i < greenOrgeCap; i++)
                greenOrgeHit[i] = 0;

            if (playerHealth <= 0)
                gameState = 6;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                ClickSound.play();
                gameState = 2;
            }

        }
        else if (gameState == 2)
        {
            view.setCenter(0.0f, 0.0f);
            pause.Draw(window);
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 700 && mousePos.x <= 1215 && mousePos.y <= 470 && mousePos.y >= 320) // Continue
            {
                ClickSound.play();
                gameState = 1;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= 700 && mousePos.x <= 1215 && mousePos.y <= 715 && mousePos.y >= 565) // Return to Mainmenu
            {
                ClickSound.play();
                gameState = 0;
                MenuRan = rand() % 3;
                sf::sleep(delayTime);
            }
        }
        if (gameState != 1)
            MyName.setPosition(-200.0f, 450.0f);
        else
            MyName.setPosition(0.0f, 750.0f);
        window.draw(MyName);
        window.setView(view);
        window.display();
    }

    return 0;
}