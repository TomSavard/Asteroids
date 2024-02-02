/// Tom SAVARD 26/01/24 ///
// * Better comments
// Command to run scripts : 
// g++ -std=c++17 -c Fusion.cpp -I/usr/local/include
// g++ Fusion.o -o Fusion.exe -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
// ./Game.exe



// ! Not to do
// ? interrogation
// TODO : 

///// TODO : Faire un code plus propre avec une classe entite et des sous-classes.
///// TODO : mise en place d'un écran game over.
// TODO : Faire un code séparé avec des fichiers joints.
// TODO : Mise en place d'un mode multi en local

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include<math.h>
#include<time.h>

#include "interface/Menu.hpp"
#include "interface/GameOver.hpp"
#include "interface/TableauDesScores.hpp"
#include "global_variables.hpp"
#include "Animation.hpp"
#include "objet/Entite.hpp"

// class Animation
// {
//    public:
//    float Frame, speed;
//    sf::Sprite sprite;
//    std::vector<sf::IntRect> frames;

//    Animation(){}

//    Animation (sf::Texture &t, int x, int y, int w, int h, int count, float Speed)
//    {
//      Frame = 0;
//      speed = Speed;

//      for (int i=0;i<count;i++)
//       frames.push_back( sf::IntRect(x+i*w, y, w, h)  );

//      sprite.setTexture(t);
//      sprite.setOrigin(w/2,h/2);
//      sprite.setTextureRect(frames[0]);
//    }


//    void update()
//    {
//      Frame += speed;
//      int n = frames.size();
//      if (Frame >= n) Frame -= n;
//      if (n>0) sprite.setTextureRect( frames[int(Frame)] );
//    }

//    bool isEnd()
//    {
//      return Frame+speed>=frames.size();
//    }

// };

// class Entite
// {
//    public:
//    float x,y,vx,vy,R,angle;
//    bool life;
//    std::string name;
//    Animation anim;

//    Entite()
//    {
//      life=1;
//    }

//    void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
//    {
//      anim = a;
//      x=X; y=Y;
//      angle = Angle;
//      R = radius;
//    }

//    virtual void update(){};

//    void draw(sf::RenderWindow &app)
//    {
//      anim.sprite.setPosition(x,y);
//      anim.sprite.setRotation(angle+90);
//      app.draw(anim.sprite);

//      sf::CircleShape circle(R);
//      circle.setFillColor(sf::Color(255,0,0,170));
//      circle.setPosition(x,y);
//      circle.setOrigin(R,R);
//     //  app.draw(circle);
//    }

//    virtual ~Entite(){};
// };

class asteroide: public Entite
{
   public:
   asteroide()
   {
     vx=rand()%8-4;
     vy=rand()%8-4;
     name="asteroide";
   }

   void update()
   {
     x+=vx;
     y+=vy;

     if (x>LargeurFenetre) x=0;  if (x<0) x=LargeurFenetre;
     if (y>HauteurFenetre) y=0;  if (y<0) y=HauteurFenetre;
   }

};

class tir: public Entite
{
   public:
   tir()
   {
     name="tir";
   }

   void  update()
   {
     vx=cos(angle*DEGTORAD)*6;
     vy=sin(angle*DEGTORAD)*6;
     // angle+=rand()%7-3;  /*try this*/
     x+=vx;
     y+=vy;

     if (x>LargeurFenetre || x<0 || y>HauteurFenetre || y<0) life=0;
   }

};

class player: public Entite
{
   public:
   bool thrust;

   player()
   {
     name="player";
   }

   void update()
   {
     if (thrust)
      { vx+=cos(angle*DEGTORAD)*0.2;
        vy+=sin(angle*DEGTORAD)*0.2; }
     else
      { vx*=0.99;
        vy*=0.99; }

    int maxSpeed=15;
    float speed = sqrt(vx*vx+vy*vy);
    if (speed>maxSpeed)
     { vx *= maxSpeed/speed;
       vy *= maxSpeed/speed; }

    x+=vx;
    y+=vy;

    if (x>LargeurFenetre) x=0; if (x<0) x=LargeurFenetre;
    if (y>HauteurFenetre) y=0; if (y<0) y=HauteurFenetre;
   }

};

bool isCollide(Entite *a,Entite *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}



int main() {
    
    sf::Music musicHub;
    if (!musicHub.openFromFile("Ressources/audio/Dofus2.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
    musicHub.play();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroid Game");
    TableauDesScores LeScore;
    Menu menu(window, musicHub);
    Menu::ActionMenu action = menu.run();

    musicHub.stop();

    sf::SoundBuffer shootSoundBuffer;
    sf::Sound shootSound;
    if (!shootSoundBuffer.loadFromFile("Ressources/audio/tir.wav")) {
    std::cerr << "Failed to load shoot sound file" << std::endl;}
    shootSound.setBuffer(shootSoundBuffer);
    int shootVolume = 3;
    shootSound.setVolume(shootVolume);

    
    sf::SoundBuffer DeathSoundBuffer;
    sf::Sound DeathSound;
    if (!DeathSoundBuffer.loadFromFile("Ressources/audio/death.wav")) {
    std::cerr << "Failed to load death sound file" << std::endl;}
    DeathSound.setBuffer(DeathSoundBuffer);
    int DeathVolume = 100;
    DeathSound.setVolume(DeathVolume);

    sf::SoundBuffer clickSoundBuffer;
    if (!clickSoundBuffer.loadFromFile("Ressources/audio/Bouton2.wav")) {std::cerr << "Failed to load click sound file" << std::endl;}
    sf::Sound clickSound;
    clickSound.setBuffer(clickSoundBuffer);


    if (action == Menu::ActionMenu::Jouer) {

        bool VeuxJouer = true; // Mettons en place un statut qui permet de boucler le jeu. On arrete de jouer lorsque l'on en a marre (quit lors du GameOver)

        while(VeuxJouer){
            sf::Music musicGame;
            if (!musicGame.openFromFile("Ressources/audio/Glory.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
            int musicVolume = 30;
            musicGame.setVolume(musicVolume);
            musicGame.play();

            srand(time(0));

            sf::RenderWindow app(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroides!");
            app.setFramerateLimit(60);

            sf::Texture t1,t3,t4,t5,t6,t7;
            t1.loadFromFile("Ressources/animation/spaceship.png");
            // t2.loadFromFile("Ressources/image/Fond.png"); // * L'image rallenti le lancement
            t3.loadFromFile("Ressources/animation/explosions/type_C.png");
            t4.loadFromFile("Ressources/animation/rock.png");
            t5.loadFromFile("Ressources/animation/fire_red.png");
            t6.loadFromFile("Ressources/animation/rock_small.png");
            t7.loadFromFile("Ressources/animation/explosions/type_B.png");

            t1.setSmooth(true);
            // t2.setSmooth(true);

            // sf::Sprite background(t2);

            Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
            Animation sRock(t4, 0,0,64,64, 16, 0.2);
            Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
            Animation sBullet(t5, 0,0,32,64, 16, 0.8);
            Animation sPlayer(t1, 40,0,40,40, 1, 0);
            Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
            Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


            std::list<Entite*> entities;

            for(int i=0;i<15;i++)
            {
                asteroide *a = new asteroide();
                a->settings(sRock, rand()%LargeurFenetre, rand()%HauteurFenetre, rand()%360, 25);
                entities.push_back(a);
            }

            player *p = new player();
            p->settings(sPlayer,200,200,0,20);
            entities.push_back(p);



            ///main loop///
            while (app.isOpen())
            {
                sf::Event event;
                while (app.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        app.close();

                    if (event.type == sf::Event::KeyPressed)
                        if (event.key.code == sf::Keyboard::Space)
                        {
                            tir *b = new tir();
                            b->settings(sBullet,p->x,p->y,p->angle,10);
                            entities.push_back(b);
                            shootSound.play();
                        }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle+=3;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p->angle-=3;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p->thrust=true;
                else p->thrust=false;


                for(auto a:entities)
                    for(auto b:entities)
                    {
                        if (a->name=="asteroide" && b->name=="tir")
                            if ( isCollide(a,b) )
                                {
                                    a->life=false;
                                    b->life=false;

                                    Entite *e = new Entite();
                                    e->settings(sExplosion,a->x,a->y);
                                    e->name="explosion";
                                    entities.push_back(e);

                                    LeScore.increaseScore(1);

                                    for(int i=0;i<2;i++)
                                    {
                                    if (a->R==15) continue;
                                    Entite *e = new asteroide();
                                    e->settings(sRock_small,a->x,a->y,rand()%360,15);
                                    entities.push_back(e);
                                    }

                                }

                            if (a->name=="player" && b->name=="asteroide")
                                if ( isCollide(a,b) )
                                {
                                    b->life=false;

                                    Entite *e = new Entite();
                                    e->settings(sExplosion_ship,a->x,a->y);
                                    e->name="explosion";
                                    entities.push_back(e);

                                    app.close();
                                    DeathSound.play();
                                    musicGame.stop();

                                    p->settings(sPlayer,LargeurFenetre/2,HauteurFenetre/2,0,20);
                                    p->vx=0; p->vy=0;
                                }
                        }  


                    if (p->thrust)  p->anim = sPlayer_go;
                    else   p->anim = sPlayer;


                    for(auto e:entities)
                        if (e->name=="explosion")
                        if (e->anim.isEnd()) e->life=0;

                        if (rand()%150==0)
                        {
                            asteroide *a = new asteroide();
                            a->settings(sRock, 0,rand()%HauteurFenetre, rand()%360, 25);
                            entities.push_back(a);
                        }

                    for(auto i=entities.begin();i!=entities.end();)
                    {
                        Entite *e = *i;

                        e->update();
                        e->anim.update();

                        if (e->life==false) {i=entities.erase(i); delete e;}
                        else i++;
                    }

            ///draw///
            app.clear();
            // app.draw(background);
            for(auto i:entities) i->draw(app);
            LeScore.drawScore(app);
            app.display();
            }

            sf::RenderWindow window(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroid Game Over");
            int scoreFinal = LeScore.getScore();
            GameOverScreen gameOverScreen(scoreFinal);
            bool actionRecu = false; //permet de savoir si le joueur a interragit
            while (window.isOpen() && !actionRecu) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                    window.close();
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::R) {
                            clickSound.play(); // Jouer le son de clic
                            VeuxJouer = true;
                            actionRecu = true;
                            LeScore.reset();
                            std::cout << "Restarting the game..." << std::endl;}
                        else if (event.key.code == sf::Keyboard::Q) {
                            clickSound.play(); // Jouer le son de clic
                            VeuxJouer=false;
                            actionRecu = true;
                            window.close();}
                    }
                }

                window.clear();
                gameOverScreen.draw(window);
                window.display();
            }
        }// fin boucle Veux jouer
    }// fin de la boucle if Jouer // TODO : optimiser ces deux boucles redondantes.
    return 0;
}
