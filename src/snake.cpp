#include<SFML/Graphics.hpp>
#include<iostream>
#include<algorithm>

uint8_t vec[4]{0,0,0,0};
const float CEL=20.0;
const float SIZE_M=20.0;
uint8_t r=255,g=255,b=255;
float sqx[7]={CEL*8.5+0.75*CEL,CEL*8.5+0.75*CEL,CEL*8.5+0.75*CEL,CEL*8.5+0.75*CEL,CEL*8.5+0.75*CEL,CEL*8.5+0.75*CEL,CEL*8.5+0.75*CEL};

#define Cxsr (float)(SIZE_M*CEL)
#define interc(A,B) A.getGlobalBounds().findIntersection(B.getGlobalBounds())
#define is_pr(A, B) if(A.getGlobalBounds().findIntersection(mouse.getGlobalBounds()) && is_pressed==true){B;is_pressed=false;}
#define wd(C) window.draw(C)
#define sgp(C) snake_part[C].getPosition()
#define spob(OB,h,w,x,y,tex) OB.setSize({h,w});OB.setPosition({x,y});OB.setTexture(&tex);

sf::RenderWindow window(sf::VideoMode({CEL*SIZE_M,CEL*SIZE_M}),"Snake Game with SFML");
sf::RectangleShape mouse({10.f,10.f});
sf::RectangleShape snake_part[(int)Cxsr],berry;
sf::Clock game_delay;
sf::Texture bar_t,conf_b_t,conf_t,ok_t,quit_t,snake_head_t,snake_body_t,start_t,startb_t,conf_r_t,gameover_t,game_back,berry_t;
sf::Font game_font;

sf::Vector2i dir;
unsigned size,score,lsc;
bool is_pressed;
uint8_t screen=1;

void start();
void config();

void restart();
float getRotationAngle(sf::Vector2i dir);
void m_snake();
void seg_snake();
void game();
void gameover();

int main(){
    mouse.setOrigin({5.f,5.f});
    bar_t.loadFromFile("../images/BAR.png");
    conf_b_t.loadFromFile("../images/CONFIG_BUTTON.png");
    conf_t.loadFromFile("../images/CONFIG_SCREEN.png");
    ok_t.loadFromFile("../images/OK.png");
    quit_t.loadFromFile("../images/QUIT.png");
    snake_head_t.loadFromFile("../images/SNAKE_HEAD.png");
    snake_body_t.loadFromFile("../images/SNAKE_BODY.png");
    start_t.loadFromFile("../images/START.png");
    startb_t.loadFromFile("../images/START_BUT.png");
    conf_r_t.loadFromFile("../images/CONFIG_ROLLER.png");
    gameover_t.loadFromFile("../images/GAME_OVER_SCREEN.png");
    game_back.loadFromFile("../images/GAME_B.png");
    berry_t.loadFromFile("../images/BERRY.png");
    game_font.openFromFile("../images/font.otf");

    while(window.isOpen()){
        is_pressed=false;
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if(event->is<sf::Event::MouseButtonPressed>()){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    is_pressed=true;
                }
            }
            if(event->is<sf::Event::KeyPressed>() && screen==3){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && dir.x!= 1 && dir.y!=0){
                    dir.x=1;
                    dir.y=0;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && dir.x!= -1 && dir.y!=0){
                    dir.x=-1;
                    dir.y=0;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && dir.x!=0 && dir.y!=-1){
                    dir.x=0;
                    dir.y=-1;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && dir.x!=0 && dir.y!=1){
                    dir.x=0;
                    dir.y=1;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && screen==3){
                    restart();
                    screen=1;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && screen==3){
                    restart();
                    screen=3;
                }
            }
        }

        mouse.setPosition({(float)sf::Mouse::getPosition(window).x ,(float)sf::Mouse::getPosition(window).y});

        switch (screen)
        {
        case 1:
            restart();
            start();
            break;
        case 2:
            config();
            break;
        case 3:
            game();
            break;
        case 4:
            gameover();
            break;
        default:
            window.close();
            break;
        }
        window.display();
    }
    return 0;
}

void start(){
    sf::RectangleShape start,close,config,start_back;

    spob(start_back,Cxsr,Cxsr,0,0,start_t)
    spob(start,CEL*6,CEL*3,Cxsr/2-start.getSize().x/2,CEL*8,startb_t)
    spob(config,CEL*6,CEL*3,Cxsr/2-config.getSize().x/2,CEL*12,conf_b_t)
    spob(close,CEL*6,CEL*3,Cxsr/2-config.getSize().x/2,CEL*16,quit_t)

    is_pr(start,screen=3)
    is_pr(close,screen=0)
    is_pr(config,screen=2)

    window.clear(sf::Color::Black);
    wd(start_back);
    wd(start);
    wd(close);
    wd(config);
}

void config(){
    sf::RectangleShape b[4],sq[4],back,ok;
    
    spob(back,Cxsr,Cxsr,0,0,conf_t);
    spob(ok,CEL*6,CEL*3,SIZE_M*CEL/2 - CEL*3,CEL*17,ok_t)

    for(int i=0; i < 4;i++){
        spob(b[i],CEL*11,CEL,CEL*8.5,CEL*3.5+CEL*2.1*i-(CEL/4*i),bar_t)
        spob(sq[i],CEL*1.5,CEL*1.5,sqx[i],b[i].getPosition().y+CEL/2,conf_r_t)
        sq[i].setOrigin({sq[i].getSize().x/2,sq[i].getSize().y/2});
    }

    window.clear(sf::Color::White);

    wd(back);
    wd(ok);
    for(int i=0; i < 4;i++){
        wd(b[i]);
        wd(sq[i]);
    }
    is_pr(ok,screen=1)
    for(int i=0; i < 4;i++){
        if(interc(sq[i],mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            if(mouse.getPosition().x >= CEL*8.5+0.75*CEL && mouse.getPosition().x <=CEL*8.5+CEL*11-0.75*CEL){
                
                vec[i] = (int)(((mouse.getPosition().x - 8.5*CEL)-15)*255)/190;
                sqx[i]=mouse.getPosition().x;
            }
        }
    }
}

void restart(){
    score=0;
    size=4;
    dir={1,0};

    spob(snake_part[0],CEL,CEL,CEL*(SIZE_M/2)-0.5*CEL,CEL*(SIZE_M/2)-0.5*CEL,snake_head_t)
    snake_part[0].setFillColor(sf::Color(255-vec[0],255-vec[1], 255-vec[2]));
    snake_part[0].setOrigin({snake_part[0].getSize().x/2,snake_part[0].getSize().x/2});
    for(int i=1; i < CEL*CEL;i++){
        spob(snake_part[i],CEL,CEL,CEL*(SIZE_M/2)-0.5*CEL-SIZE_M*CEL,CEL*(SIZE_M/2)-0.5*CEL,snake_body_t)
        snake_part[i].setFillColor(sf::Color(255-vec[0],255-vec[1],255-vec[2]));
        snake_part[i].setOrigin({snake_part[i].getSize().x/2,snake_part[i].getSize().x/2});
    }
    for(int i=0;i<size;i++){
        while(interc(snake_part[i],berry)){
            berry.setPosition({CEL*(rand()%(int)(SIZE_M-2)+2),CEL*(rand()%(int)(SIZE_M-2)+2)});
        }
    }

    berry.setTexture(&berry_t);
    berry.setSize({(float)CEL,(float)CEL});
    berry.setPosition({CEL*((rand()%(int)(SIZE_M-2)+2)),CEL*((rand()%(int)(SIZE_M-2)+2))});

}

float getRotationAngle(sf::Vector2i dir) {
    if (dir == sf::Vector2i(0, -1)) return 0.f;
    else if (dir == sf::Vector2i(1, 0))  return 90.f;
    else if (dir == sf::Vector2i(0, 1))  return 180.f;
    else if (dir == sf::Vector2i(-1, 0)) return 270.f;
    return 0.f;
}

void m_snake() {
    sf::Vector2f pos = sgp(0);
    snake_part[0].setRotation(sf::degrees(getRotationAngle(dir)));
    snake_part[0].setPosition({sgp(0).x+dir.x*CEL,sgp(0).y+dir.y*CEL});
    for (size_t i = 1; i < size; i++) {
        float rotate = getRotationAngle({(int)(snake_part[i].getPosition().x-pos.x)/CEL,(int)(snake_part[i].getPosition().y-pos.y)/CEL});
        snake_part[i].setRotation(sf::degrees(rotate));
        sf::Vector2f temp = snake_part[i].getPosition();
        snake_part[i].setPosition(pos);
        pos = temp;
    }
}

void seg_snake(){
    berry.setPosition({CEL*(rand()%(int)(SIZE_M-2)+2),CEL*(rand()%(int)(SIZE_M-2)+2)});
    size++;
    snake_part[size-1].setPosition({snake_part[size-2].getPosition().x+CEL,snake_part[size-2].getPosition().y});
    for(int i=0;i<size;i++){
        while(interc(snake_part[i],berry)){
            berry.setPosition({CEL*((rand()%(int)(SIZE_M-2)+2)),CEL*((rand()%(int)(SIZE_M-2)+2))});
        }
    }
}

void game(){
    sf::RectangleShape back;
    sf::Text score_text(game_font);
    score_text.setCharacterSize(16);
    score_text.setFillColor(sf::Color::Red);
    score_text.setString("Score "+ std::to_string(score));
    score_text.setPosition({Cxsr/2,Cxsr/2});
    spob(back,Cxsr,Cxsr,0,0,game_back);
    score_text.setPosition({Cxsr/2-55, 10});

    if(game_delay.getElapsedTime().asMilliseconds() >= vec[3]+50){
        window.clear(sf::Color::Green);
        wd(back);

        if(interc(snake_part[0],berry)){
            seg_snake();
            score+=2;
            score_text.setString("Score "+ std::to_string(score));
        }
        for(int i=0; i < size; i++){
            wd(snake_part[i]);
        }
            wd(berry);
        for(int i=1; i < size; i++){
            if(interc(snake_part[0],snake_part[i])){
                lsc=score;
                screen=4;
            }
        }
        if(sgp(0).x > CEL*SIZE_M ||  sgp(0).x < 0 || sgp(0).y > CEL*SIZE_M || sgp(0).y < SIZE_M*2){
            lsc=score;
            screen=4;
        }
        m_snake();
        wd(score_text);
        game_delay.restart();
    }
}

void gameover(){
    sf::Text score_text(game_font);
    score_text.setCharacterSize(16);
    score_text.setFillColor(sf::Color::Red);
    score_text.setString("Score "+ std::to_string(lsc));
    score_text.setPosition({Cxsr/2-55,Cxsr/2});

    restart();
    sf::RectangleShape close,ok,gameover_back;

    spob(gameover_back,Cxsr,Cxsr,0,0,gameover_t)
    spob(ok,CEL*10,CEL*2,CEL*5,CEL*12.5,ok_t)
    spob(close,CEL*10,CEL*2,CEL*5,CEL*15,quit_t)

    window.clear(sf::Color::Black);
    wd(gameover_back);
    wd(ok);
    wd(close);
    wd(score_text);

    is_pr(ok,screen=1)
    is_pr(close,screen=0)
}