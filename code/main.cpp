/// Tom SAVARD 26/01/24 ///
// * Better comments
// Command to run scripts : g++ -std=c++17 -c Fusion.cpp -I/usr/local/include
// g++ Fusion.o -o Fusion.exe -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
// ./Game.exe

// ! Not to do
// ? interrogation
// TODO : 

// TODO : Faire un code plus propre avec une classe entite et des sous-classes.

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include<math.h>
#include<time.h>

// Définir la couleur normale et la couleur survolée des boutons
sf::Color normalColor = sf::Color::White;
sf::Color hoverColor = sf::Color(200, 200, 200); // Couleur gris clair pour simuler le survol

const int LargeurFenetre = 1200;
const int HauteurFenetre = 800;

float DEGTORAD = 0.017453f;


class Animation
{
   public:
   float Frame, speed;
   sf::Sprite sprite;
   std::vector<sf::IntRect> frames;

   Animation(){}

   Animation (sf::Texture &t, int x, int y, int w, int h, int count, float Speed)
   {
     Frame = 0;
     speed = Speed;

     for (int i=0;i<count;i++)
      frames.push_back( sf::IntRect(x+i*w, y, w, h)  );

     sprite.setTexture(t);
     sprite.setOrigin(w/2,h/2);
     sprite.setTextureRect(frames[0]);
   }


   void update()
   {
     Frame += speed;
     int n = frames.size();
     if (Frame >= n) Frame -= n;
     if (n>0) sprite.setTextureRect( frames[int(Frame)] );
   }

   bool isEnd()
   {
     return Frame+speed>=frames.size();
   }

};

class Entite
{
   public:
   float x,y,vx,vy,R,angle;
   bool life;
   std::string name;
   Animation anim;

   Entite()
   {
     life=1;
   }

   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
   }

   virtual void update(){};

   void draw(sf::RenderWindow &app)
   {
     anim.sprite.setPosition(x,y);
     anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);

     sf::CircleShape circle(R);
     circle.setFillColor(sf::Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
    //  app.draw(circle);
   }

   virtual ~Entite(){};
};

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



// Les différentes classes d'objets :
class Projectile {
public:
    Projectile(sf::Vector2f position) : shape(sf::Vector2f(5.f, 5.f)), lifetime(sf::Time::Zero) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    void update(sf::Time dt) {
    sf::Vector2f velocity(0.f, -200.f); // Vitesse du projectile
    shape.move(velocity * dt.asSeconds()); // Mettre à jour la position du projectile en fonction de la vitesse
    lifetime += dt; // Mettre à jour la durée de vie du projectile
    }

    bool isExpired() const {
        return lifetime >= maxLifetime; // Vérifier si la durée de vie dépasse la limite
    }

private:
    sf::RectangleShape shape;
        sf::Time lifetime;
    const sf::Time maxLifetime = sf::seconds(5.f); // Durée de vie maximale du projectile
};

class Player
{
friend class Projectile; // Déclaration d'amitié

private:
    sf::Vector2f position;
    sf::Time shootTimer;
    sf::ConvexShape shape;
    const sf::Time shootCooldown = sf::seconds(0.3f); // Cooldown entre deux tirs

public:

// Constructeur 
Player(sf::Vector2f startPos) : position(startPos), shootTimer(sf::seconds(0.f)) {
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setPoint(1, sf::Vector2f(20, 40));
    shape.setPoint(2, sf::Vector2f(0, 30));
    shape.setPoint(3, sf::Vector2f(-20, 40));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(startPos);
}

void update(sf::Time dt, std::vector<std::unique_ptr<Projectile>>& projectiles) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= shootCooldown) {
        shoot(projectiles);
        shootTimer = sf::Time::Zero; // Réinitialiser la minuterie de tir
    }
    // Mettre à jour la minuterie de tir
    shootTimer += dt;
}


//Les différentes fonctions de player
        //Le déplacement
    void move(sf::Vector2f offset) {
        position += offset;
        shape.move(offset);
    }

        //lire sa position
    sf::Vector2f getPosition() const {
        return position;
    }
        //l'affichage du vaisseau
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }
    // Tire des projectiles
    void shoot(std::vector<std::unique_ptr<Projectile>>& projectiles) {
        projectiles.push_back(std::unique_ptr<Projectile>(new Projectile(position + sf::Vector2f(0.f, -50.f))));
    }
        //???
    void setPosition(sf::Vector2f pos) {
        position = pos;
    }

};


// Pour les fenetres
class Menu {
public:
    enum class ActionMenu {
        Quitter,
        Jouer
    };
    Menu(sf::RenderWindow& window, sf::Music& music) : window(window), music(music) {}

    ActionMenu run() {
        sf::Font font;
        if (!font.loadFromFile("../Ressources/police/arial/arial.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
            return ActionMenu::Quitter;
        }

        sf::Text title("Asteroid Game", font, 50);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition(200, 100);

        sf::Text playButton("Play", font, 30);
        playButton.setFillColor(sf::Color::White);
        playButton.setPosition(300, 250);

        sf::Text exitButton("Exit", font, 30);
        exitButton.setFillColor(sf::Color::White);
        exitButton.setPosition(300, 350);

        sf::RectangleShape volumeBar(sf::Vector2f(200, 20));
        volumeBar.setFillColor(sf::Color(200, 200, 200)); // Couleur gris clair
        volumeBar.setPosition(window.getSize().x - 250, window.getSize().y - 50);

        sf::CircleShape volumeIndicator(10);
        volumeIndicator.setFillColor(sf::Color::White);
        volumeIndicator.setOutlineColor(sf::Color::Black);
        volumeIndicator.setOutlineThickness(2);
        volumeIndicator.setOrigin(5, 5);
        volumeIndicator.setPosition(window.getSize().x - 250 + volume * 200, window.getSize().y - 45);

        bool isDragging = false;

        // Chargez le son pour le clic sur le bouton
        sf::SoundBuffer clickSoundBuffer;
        if (!clickSoundBuffer.loadFromFile("../Ressources/audio/Bouton2.wav")) {std::cerr << "Failed to load click sound file" << std::endl;}
        sf::Sound clickSound;
        clickSound.setBuffer(clickSoundBuffer);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        // Action lorsque le bouton "Jouer" est cliqué
                        std::cout << "Bouton Jouer cliqué" << std::endl;
                        clickSound.play(); // Jouer le son de clic
                        window.close(); // Fermer la fenêtre lorsque le bouton "Jouer" est cliqué
                        return ActionMenu::Jouer;
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos)) {
                        // Action lorsque le bouton "Quitter" est cliqué
                        std::cout << "Bouton quitter cliqué!" << std::endl;
                        clickSound.play(); // Jouer le son de clic
                        window.close(); // Fermer la fenêtre lorsque le bouton "Quitter" est cliqué
                        return ActionMenu::Quitter;
                    }
                    else if (volumeIndicator.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                    }
                } 
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                } 
                else if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    // Gestion du survol des boutons
                    if (playButton.getGlobalBounds().contains(mousePos)) {playButton.setFillColor(hoverColor);} 
                    else {playButton.setFillColor(normalColor);}
                    if (exitButton.getGlobalBounds().contains(mousePos)) {exitButton.setFillColor(hoverColor);}
                    else {exitButton.setFillColor(normalColor);}
                    // Déplacement du bouton de volume si l'utilisateur est en train de le glisser
                    if (isDragging) {
                        float newVolume = (mousePos.x - (window.getSize().x - 250)) / 200.0f;
                        if (newVolume < 0)
                            newVolume = 0;
                        else if (newVolume > 1)
                            newVolume = 1;
                        volume = newVolume;
                        music.setVolume(volume * 100); // Réglez le volume sur une échelle de 0 à 100
                        volumeIndicator.setPosition(window.getSize().x - 250 + volume * 200, window.getSize().y - 45);
                    }
                }
            }
            window.clear();
            window.draw(title);
            window.draw(playButton);
            window.draw(exitButton);
            window.draw(volumeBar);
            window.draw(volumeIndicator);
            window.display();
        }
    return ActionMenu::Quitter;
    }

private:
    sf::RenderWindow& window;
    sf::Music& music;
    float volume = 0.5f; // Volume initial
};

class GameLauncher {
public:
    GameLauncher(sf::RenderWindow& window) : window(window) {}

void launch() {
    sf::RenderWindow window (sf::VideoMode(800,800), "Asteroid Game");
    Player joueur1(sf::Vector2f(400.f, 400.f));
    float speed = 0.5f; //vitesse du joueur
        std::vector<std::unique_ptr<Projectile>> projectiles;
        sf::Clock clock; // Horloge pour mesurer le temps écoulé

    // Boucle principale :
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type ==sf::Event::Closed) window.close();}
        sf::Time dt = clock.restart(); // Mesurer le temps écoulé depuis la dernière itération
        joueur1.update(dt, projectiles); // Mettre à jour le joueur avec le temps écoulé
        // On gère le déplacement droite/gauche/bas/haut avec les flèches directionnelles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && joueur1.getPosition().x > 20) {joueur1.move(sf::Vector2f(-speed, 0.f));}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && joueur1.getPosition().x < window.getSize().x - 20) {joueur1.move(sf::Vector2f(speed, 0.f));}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && joueur1.getPosition().y > 0) {joueur1.move(sf::Vector2f(0.f,-speed));}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && joueur1.getPosition().y < window.getSize().y - 40) {joueur1.move(sf::Vector2f(0.f,speed));}
        // Vérifie si la touche "espace" est enfoncée pour tirer un projectile
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            joueur1.update(dt, projectiles);
        }
        // Netoyyage de la fenetre
        window.clear();
        // Mettre à jour et dessiner les projectiles
        for (auto& projectile : projectiles) {
            projectile->update(dt); // Mettre à jour la position du projectile
            projectile->draw(window); // Dessiner le projectile mis à jour
        }
        joueur1.draw(window);
    // Supprimer les projectiles expirés
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const std::unique_ptr<Projectile>& p) { return p->isExpired(); }), projectiles.end());
        window.display();   
    }
}

private:
    sf::RenderWindow& window;
};


class TableauDesScores {
private:
    int score; // Variable de compteur de points

public:
    TableauDesScores() : score(0) {} // Initialiser le compteur de points à zéro

    void increaseScore(int points) {
        score += points; // Augmenter le compteur de points
    }

    void drawScore(sf::RenderWindow& window) {
        sf::Font font;
        if (!font.loadFromFile("../Ressources/police/arial/arial.ttf")) {
            // Gérer l'erreur de chargement de la police
            std::cerr << "Failed to load font file" << std::endl;
            return;
        }

        sf::Text scoreText("Score: " + std::to_string(score), font, 30);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        window.draw(scoreText); // Dessiner le compteur de points à l'écran
    }

    void resetScore(){
        score = 0;
    }
};

class GameOverScreen {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text retryText;
    sf::Text quitText;

public:
    GameOverScreen() {
        if (!font.loadFromFile("../Ressources/police/arial/arial.ttf")) {
        }

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("Game Over");
        gameOverText.setPosition(LargeurFenetre/2, HauteurFenetre/2);

        retryText.setFont(font);
        retryText.setCharacterSize(30);
        retryText.setFillColor(sf::Color::White);
        retryText.setString("Press R to Retry");
        retryText.setPosition(LargeurFenetre/2, HauteurFenetre/2 + 100);

        quitText.setFont(font);
        quitText.setCharacterSize(30);
        quitText.setFillColor(sf::Color::White);
        quitText.setString("Press Q to Quit");
        quitText.setPosition(LargeurFenetre/2, HauteurFenetre/2 + 200);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(gameOverText);
        window.draw(retryText);
        window.draw(quitText);
    }
};

int main() {
    
    sf::Music musicHub;
    if (!musicHub.openFromFile("../Ressources/audio/Dofus2.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
    musicHub.play();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroid Game");
    TableauDesScores LeScore;
    Menu menu(window, musicHub);
    Menu::ActionMenu action = menu.run();

    musicHub.stop();

    sf::SoundBuffer shootSoundBuffer;
    sf::Sound shootSound;
    if (!shootSoundBuffer.loadFromFile("../Ressources/audio/tir.wav")) {
    std::cerr << "Failed to load shoot sound file" << std::endl;}
    shootSound.setBuffer(shootSoundBuffer);
    int shootVolume = 3;
    shootSound.setVolume(shootVolume);

    
    sf::SoundBuffer DeathSoundBuffer;
    sf::Sound DeathSound;
    if (!DeathSoundBuffer.loadFromFile("../Ressources/audio/death.wav")) {
    std::cerr << "Failed to load death sound file" << std::endl;}
    DeathSound.setBuffer(DeathSoundBuffer);
    int DeathVolume = 100;
    DeathSound.setVolume(DeathVolume);


    if (action == Menu::ActionMenu::Jouer) {
        sf::Music musicGame;
        if (!musicGame.openFromFile("../Ressources/audio/Glory.wav")) {std::cerr << "Failed to load music file" << std::endl; return -1;}
        int musicVolume = 30;
        musicGame.setVolume(musicVolume);
        musicGame.play();
        
        srand(time(0));

        sf::RenderWindow app(sf::VideoMode(LargeurFenetre, HauteurFenetre), "Asteroides!");
        app.setFramerateLimit(60);

        sf::Texture t1,t2,t3,t4,t5,t6,t7;
        t1.loadFromFile("../Ressources/animation/spaceship.png");
        t2.loadFromFile("../Ressources/image/Fond.jpg");
        t3.loadFromFile("../Ressources/animation/explosions/type_C.png");
        t4.loadFromFile("../Ressources/animation/rock.png");
        t5.loadFromFile("../Ressources/animation/fire_red.png");
        t6.loadFromFile("../Ressources/animation/rock_small.png");
        t7.loadFromFile("../Ressources/animation/explosions/type_B.png");

        t1.setSmooth(true);
        t2.setSmooth(true);

        sf::Sprite background(t2);

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

                                LeScore.resetScore();
                                DeathSound.play();

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
        app.draw(background);
        for(auto i:entities) i->draw(app);
        LeScore.drawScore(app);
        app.display();
        }
    }
    
    return 0;
}
