#include "fonctions_bg.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "draw.hpp"
#include "vaisseau.hpp"
#include "collisions.hpp"
#include "powerup.hpp"
#include "score.hpp"
#include "structure.hpp"
#include "savemanager.hpp"
#include "animation.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ostream>
#include <string.h>
#include "menu.hpp"

#define NB_TEMPLATE_ENEMY 4

int main()
{
    srand(time(NULL));

    RenderWindow appMenu;
    RenderWindow fenetreVaisseau;
    RenderWindow fenetreOptions;

    // SPRITE BULLET

    Texture texture5;
    if (!texture5.loadFromFile("img/bullet/bullet_ally2.png"))
        printf("Erreur de chargement de img/bullet/bullet_ally2.png\n");
    Sprite sp_bullet_ally(texture5);

    Texture texture6;
    if (!texture6.loadFromFile("img/bullet/bullet_enemy.png"))
        printf("Erreur de chargement de img/bullet/bullet_enemy.png\n");
    Sprite sp_bullet_enemy(texture6);

    Texture laser;
    if (!laser.loadFromFile("img/bullet/laser.png"))
        printf("Erreur de chargement de img/bullet/laser.png\n");
    Sprite sp_laser(laser);

    // PERSONALISATION DE VAISSEAU

    Sprite sp_vaisseau;
    Sprite sp_bullet_vaisseau;
    BulletType vaisseau_bullet_type;
    Vector2f vaisseau_bullet_velocity;
    float vaisseau_cadence;
    bool veutJouer = false;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////// MENU ///////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    appMenu.create(VideoMode(TAILLE_FENETRE + 200, HAUTEUR_FENETRE + 50), "Menu");

    int i = 0;


    Text titre;

    Font font;
    Event event;

    //LES SONS

    sf::Music music[5];
    char *sourceMusic [4] = {"sound/MusicMenu.ogg", "sound/MusicJeu.ogg", "sound/MusicBoss.ogg", "sound/MusicTrash.ogg"};
    for(i=0; i<4; i++)
    {
        music[i].openFromFile(sourceMusic[i]);
    }

    SoundBuffer buffer[4];
    char *sourceBuffer [4] = {"sound/GameOver.ogg","sound/Tir.ogg","sound/Explosion.ogg"};
    for(i=0; i<3; i++)
    {
        buffer[i].loadFromFile(sourceBuffer[i]);
    }
    Sound tir[2];
    for(i=0; i<2; i++)
    {
        tir[i].setBuffer(buffer[1]);
    }
    Sound gameOver;
    gameOver.setBuffer(buffer[0]);
    Sound explosion;
    explosion.setBuffer(buffer[2]);

    if (!font.loadFromFile("font/retro_computer.ttf"))
    {
        printf("Erreur de lecture du fichier font/retro_computer\n");
        return 1;
    }

    Texture textureBgMenu;
    textureBgMenu.loadFromFile("img/background/bg_menu.jpg");
    Texture textureTitre;
    textureTitre.loadFromFile("img/background/titre.png");



    char *motsMenu [4]  = {"Jouer", "Vaisseau", "Options", "Quitter"};
    Text textMenu[4];
    for (i = 0; i< 4; i++) /////////1///////
    {
        textMenu[i].setFont(font);
        textMenu[i].setCharacterSize(32);
        textMenu[i].setString(motsMenu[i]);
    }


    Sprite sprite(textureBgMenu);
    Sprite spriteTitre(textureTitre);

    Menu menu;
    menu = addMenu(font, textMenu, sprite, spriteTitre, music);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////// VAISSEAU ///////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Texture textBgVaisseau;
    Texture TexSelect; //textures fenetre vaisseau

    Texture TexVaisseau [4];

    char *imagesVaisseau [4]  = {"img/vaisseau/vaisseau1.png", "img/vaisseau/vaisseau2.png", "img/vaisseau/vaisseau3.png", "img/vaisseau/vaisseau4.png"};

    TexSelect.loadFromFile("img/autres/triangleselect.png"); //triangle

    Sprite Spritevaisseau[4]; // Sprite vaisseaux

    Sprite SpriteTriangle(TexSelect); //Triangle selection vaisseau


    textBgVaisseau.loadFromFile("img/background/hangar.png");
    Sprite backgroundVaisseau(textBgVaisseau);

    /////////TEXTE////////////////////////////

    //Text armePrinci, retour, ok;//Text modif vaisseau
    Text textVaisseau[4];

    ////////////////DEF TEXTE + SPRITES////////////////////////
    char *motsVaisseau [3]  = {"Arme principale", "Ok", "Retour"};
    Sprite SpriteSelecArme [4];
    i = 0;
    for (i = 0; i<4; i++) ////2////// A METTRE DANS MEME FOR QUE MENU.
    {
        TexVaisseau[i].loadFromFile(imagesVaisseau [i]);
        Spritevaisseau[i].setTexture(TexVaisseau[i]);
        textVaisseau[i].setFont(font);
        textVaisseau[i].setCharacterSize(24);
        textVaisseau[i].setString(motsVaisseau[i]);
    }

    StructFenVaisseau vaisseauMenu;
    vaisseauMenu = imVaisseau(backgroundVaisseau, Spritevaisseau, SpriteTriangle, textVaisseau);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////// OPTIONS /////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Text textOptions[4];
    char *motsOptions [3] = {"Volume: ", "Configuration clavier: ", "Retour"};
    Texture imOptions;
    imOptions.loadFromFile("img/autres/clavier.png");
    Sprite spriteOption(imOptions);
    RectangleShape barreSon(Vector2f(300,10));
    RectangleShape curseurSon(Vector2f(10,40));

    int pointeur = 1;

    for (i = 0; i<3; i++)
    {
        textOptions[i].setFont(font);
        textOptions[i].setCharacterSize(20);
        textOptions[i].setString(motsOptions[i]);
        //imOptions[i].loadFromFile(imageOptions[i]);
        //spriteOptions[i].setTexture(imOptions[i]);
    }

    StructFenOptions OptionsMenu;
    OptionsMenu = imageOptions(spriteOption,textOptions, barreSon, curseurSon, font, pointeur);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////DEBUT BOUCLE APP OU FENETRE VAISSEAU ////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while(appMenu.isOpen() || fenetreVaisseau.isOpen() || fenetreOptions.isOpen())
    {
        while(appMenu.pollEvent(event) || fenetreVaisseau.pollEvent(event) || fenetreOptions.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                appMenu.close();
                fenetreVaisseau.close();
                fenetreOptions.close();
            }

            changementChoix(menu, event);
            selection(event,menu, &appMenu, &fenetreVaisseau, &fenetreOptions, music, &veutJouer);
            choixDuVaisseau(vaisseauMenu, event, &fenetreVaisseau, &appMenu);
            choixOptions(OptionsMenu,event, &fenetreOptions, &appMenu);

            // GESTION VOLUME SON
            gameOver.setVolume(OptionsMenu.indicateurVolume);
            explosion.setVolume(OptionsMenu.indicateurVolume);
            music[0].setVolume(OptionsMenu.indicateurVolume);
            music[1].setVolume(OptionsMenu.indicateurVolume);
            music[2].setVolume(OptionsMenu.indicateurVolume);
            music[3].setVolume(OptionsMenu.indicateurVolume);

            sp_vaisseau = vaisseauMenu.SpriteVaisseau[vaisseauMenu.pointeur];
            if (vaisseauMenu.pointeur == 0 || vaisseauMenu.pointeur == 1)
            {
                vaisseau_bullet_type = Normal;
                sp_bullet_vaisseau = sp_bullet_ally;
                vaisseau_bullet_velocity = Vector2f(0, -600);
                vaisseau_cadence = 10;
            }
            else
            {
                vaisseau_bullet_type = Laser;
                sp_bullet_vaisseau = sp_laser;
                vaisseau_bullet_velocity = Vector2f(0,0);
                vaisseau_cadence = 3;
            }
        }
        drawMenu(&appMenu, menu, event);
        appMenu.display();

        drawFenetreVaisseau(&fenetreVaisseau, vaisseauMenu, event);
        fenetreVaisseau.display();

        drawFenetreOptions(&fenetreOptions, OptionsMenu,event);
        fenetreOptions.display();
    }

    if (veutJouer)
    {
        int max_bullet = 0;
        int max_enemy = 0;

        // Initialisation des couches de l'arriere plan

        Background mes_bg[NB_BACKGROUND];
        initBackground(&mes_bg[0], "img/background/bg3.png", Vector2f(10, 30), 0);
        initBackground(&mes_bg[1], "img/background/nebuleuse2.png", Vector2f(15, 40), 3000);
        initBackground(&mes_bg[2], "img/background/planet1.png", Vector2f(20, 50), 4000);
        initBackground(&mes_bg[3], "img/background/asteroid.png", Vector2f(30, 80), 500);

        // CLOCK

        Clock main_clock;
        Clock enemy_clock;
        Clock unrestarted_clock;

        // TEMPLATE ENEMY

        Enemy enemy_templates[NB_TEMPLATE_ENEMY];
        resetAllEnemies(enemy_templates);

        // SPRITE POWERUP

        Sprite sp_powerup[4];
        Texture texture_powerup[4];
        initPowerupTexture(texture_powerup);
        initPowerupSprites(sp_powerup, texture_powerup);

        // SPRITE ENEMY

        Texture texture1;
        if (!texture1.loadFromFile("img/enemy/enemy1.png"))
            printf("Erreur de chargement de img/enemy/enemy1.png\n");
        enemy_templates[0].sprite = Sprite(texture1);

        Texture texture2;
        if (!texture2.loadFromFile("img/enemy/enemy2.png"))
            printf("Erreur de chargement de img/enemy/enemy2.png\n");
        enemy_templates[1].sprite = Sprite(texture2);

        Texture texture3;
        if (!texture3.loadFromFile("img/enemy/enemy3.png"))
            printf("Erreur de chargement de img/enemy/enemy3.png\n");
        enemy_templates[2].sprite = Sprite(texture3);

        Texture texture4;
        if (!texture4.loadFromFile("img/enemy/enemy4.png"))
            printf("Erreur de chargement de img/enemy/enemy4.png\n");
        enemy_templates[3].sprite = Sprite(texture4);

        // COMPORTEMENT TEMPLATE ENEMY

        enemy_templates[0].bullet.sprite = sp_bullet_enemy;
        enemy_templates[0].cadence = 4;
        enemy_templates[0].bullet.velocity = Vector2f(300,300);
        enemy_templates[0].damage = 15;
        enemy_templates[0].hp = 100;
        enemy_templates[0].score = 75;
        enemy_templates[0].bullet.isPlayerBullet = false;

        enemy_templates[1].bullet.sprite = sp_bullet_enemy;
        enemy_templates[1].cadence = 3;
        enemy_templates[1].bullet.velocity = Vector2f(350,350);
        enemy_templates[1].damage = 20;
        enemy_templates[1].hp = 80;
        enemy_templates[1].score = 125;
        enemy_templates[1].bullet.isPlayerBullet = false;

        enemy_templates[2].bullet.sprite = sp_bullet_enemy;
        enemy_templates[2].cadence = 1;
        enemy_templates[2].bullet.velocity = Vector2f(500,500);
        enemy_templates[2].damage = 30;
        enemy_templates[2].hp = 40;
        enemy_templates[2].score = 200;
        enemy_templates[2].bullet.isPlayerBullet = false;

        enemy_templates[3].bullet.sprite = sp_bullet_enemy;
        enemy_templates[3].cadence = 2;
        enemy_templates[3].bullet.velocity = Vector2f(400,400);
        enemy_templates[3].damage = 20;
        enemy_templates[3].hp = 90;
        enemy_templates[3].score = 150;
        enemy_templates[3].bullet.isPlayerBullet = false;

        //THRUSTERS

        Texture texture_thruster1;
        if(!texture_thruster1.loadFromFile("img/engine_exhaust/type1_0.png"))
            printf("ERREUR: LOADING FILE");
        Texture texture_thruster2;
        if(!texture_thruster2.loadFromFile("img/engine_exhaust/type1_1.png"))
            printf("ERREUR: LOADING FILE");
        Texture texture_thruster3;
        if(!texture_thruster3.loadFromFile("img/engine_exhaust/type1_2.png"))
            printf("ERREUR: LOADING FILE");

        Sprite sprites_thruster[3];
        sprites_thruster[0] = Sprite(texture_thruster1);
        sprites_thruster[1] = Sprite(texture_thruster2);
        sprites_thruster[2] = Sprite(texture_thruster3);

        //Explosion

        Texture texture_explosion;
        if(!texture_explosion.loadFromFile("img/explosions/explosions.png"))
            printf("ERREUR: EXPLOSION");
        Animation explosion_template;
        explosion_template = initAnimation(120, &unrestarted_clock);
        addTexture(explosion_template, texture_explosion);
        explosion_template.px = 80;
        explosion_template.py = 80;

        int const NB_EXPLOSION = 256;

        Animation all_explosions[NB_EXPLOSION];
        initExplosions(all_explosions, explosion_template, NB_EXPLOSION);

        // BULLETS

        Bullet all_bullets[NB_BULLETS];
        resetAllBullets(all_bullets);

        // VAISSEAU

        Bullet bullet_vaisseau = addBullet(sp_bullet_vaisseau, Vector2f(0,0), vaisseau_bullet_velocity, 20, vaisseau_bullet_type, true);
        Vaisseau vaisseau = addVaisseau(sp_vaisseau, Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT-100),Vector2f(350,350), 250, 20, bullet_vaisseau, vaisseau_cadence, &unrestarted_clock, sprites_thruster);

        // VIE DU VAISSEAU

        Vie vie = addBarreDeVie(Vector2f(100,20), vaisseau.hp);

        // ENEMIES

        Vector2f position1 = Vector2f(200,200);
        Vector2f velocity1 = Vector2f(0,0);
        Vector2f position2 = Vector2f(50,50);
        Vector2f velocity2 = Vector2f(50,20);

        Enemy all_enemies[NB_ENEMY];
        resetAllEnemies(all_enemies);

        // POWERUP

        PowerUp all_powerup[NB_POWERUP];
        resetAllPowerup(all_powerup);

        // SCORE

        int score = 0;
        Text text_score;
        char string_score[10];
        sprintf(string_score, "%d", score);
        text_score.setPosition(0,25);
        text_score.setFont(font);
        text_score.setString(string_score);
        text_score.setCharacterSize(30);

        Time elapsed;
        float taux_spawn = 1.2;
        int new_death = 0;
        int high_score;
        std::vector<std::string> all_score_string;
        std::vector<int> all_score_int;

        RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Super Fire Mega Lazer");

        while (app.isOpen())
        {
            if (vaisseau.hp > 0)
            {
                elapsed = main_clock.restart();
                while (app.pollEvent(event))
                {
                    // Evenements pendant la partie
                    if (event.type == Event::Closed)
                        app.close();
                    vaisseau.direction = deplacement(event);
                }

                // Apparition des ennemies
                spawnEnemy(all_enemies, &enemy_clock, taux_spawn, unrestarted_clock, &max_enemy, &max_bullet, enemy_templates);

                // Tir du joueur
                tirVaisseau(all_enemies, all_bullets, &vaisseau, &unrestarted_clock, &max_bullet);

                if(taux_spawn<=0.6 && music[3].getStatus() != Sound::Playing)
                {
                    music[1].stop();
                    music[3].play();
                    music[3].setLoop(true);
                }

                // Tir des ennemies
                shootEnemy(all_bullets, all_enemies, unrestarted_clock, vaisseau.position, max_enemy, &max_bullet);

                // Test de collisions et actualise le score

                int scoreTest;
                scoreTest=score;

                score += collisionBulletEnemyVaisseau(all_bullets, all_enemies, &vaisseau, max_enemy, max_bullet, all_powerup, sp_powerup, &vie, all_explosions);
                if(score>scoreTest)
                {
                    explosion.play();
                }

                checkScore(score, &taux_spawn);

                collisionVaisseauEnemy(all_enemies, &vaisseau, max_enemy);
                collisionVaisseauPowerup(all_powerup, &vaisseau);

                // Concertit le score en string (pour l'affiche)

                sprintf(string_score, "%d", score);
                text_score.setString(string_score);

                // Calcul et affichage

                app.clear();
                manage(&app, mes_bg, elapsed);
                manage(&app, all_enemies, elapsed, max_enemy);
                manage(&app, all_bullets, elapsed, max_bullet, &unrestarted_clock);
                manage(&app, &vaisseau, elapsed, mes_bg, gameOver);
                manage(&app, all_powerup, elapsed);
                manage(&app, all_explosions, &unrestarted_clock);
                app.draw(text_score);
                draw(&app, &vie);
                app.display();
            }
            else
            {
                if (new_death == 0)
                {
                    // Sauvegarde du score

                    enregistrerSauvegardeScore("save/score.txt", score);
                    all_score_string = lireSauvegardeScore("save/score.txt");
                    all_score_int = convertSauvegardeScore(all_score_string);
                    tri_bulles(all_score_int);
                    high_score = all_score_int[all_score_int.size()-1];
                    gameOver.play();
                    new_death = 1;

                }
                while (app.pollEvent(event))
                {
                    // Evenement sur l'ecran de fin
                    if (event.type == Event::KeyPressed)
                    {
                        switch (event.key.code)
                        {
                        case Keyboard::Escape:
                            app.close();
                            break;

                        case Keyboard::Return:
                            // Relancer le jeu et reset tout
                            score = 0;
                            taux_spawn = 1.2;
                            main_clock.restart();
                            enemy_clock.restart();
                            resetVaisseau(&vaisseau, main_clock);
                            changeBarreVie(&vaisseau, &vie);
                            unrestarted_clock.restart();
                            resetAllBullets(all_bullets);
                            resetAllEnemies(all_enemies);
                            resetAllPowerup(all_powerup);
                            resetAllAnimation(all_explosions);
                            max_bullet = 0;
                            max_enemy = 0;
                            new_death = 0;
                            if (music[3].getStatus() == Sound::Playing)
                            {
                                music[3].stop();
                                music[1].play();
                                music[1].setLoop(true);
                            }
                            break;
                        }
                    }

                    if (event.type == Event::Closed)
                        app.close();
                }

                // Creation des text affiche sur l'ecran de fin
                Text text[6];
                char string_end1[] = "SCORE FINAL";
                text[0].setFont(font);
                text[0].setString(string_end1);
                text[0].setCharacterSize(50);
                text[0].setPosition((WINDOW_WIDTH-text[0].getLocalBounds().width)/2, WINDOW_HEIGHT/2 - text[0].getLocalBounds().height - 200);

                text[1].setFont(font);
                text[1].setString(string_score);
                text[1].setCharacterSize(50);
                text[1].setColor(Color::Red);
                text[1].setPosition((WINDOW_WIDTH-text[1].getLocalBounds().width)/2, WINDOW_HEIGHT/2 - 150);

                text[2].setFont(font);
                text[2].setString("Appuyez sur :");
                text[2].setCharacterSize(40);
                text[2].setPosition((WINDOW_WIDTH-text[2].getGlobalBounds().width)/2, WINDOW_HEIGHT/2);

                text[3].setFont(font);
                text[3].setString("Entree pour rejouer");
                text[3].setCharacterSize(40);
                text[3].setColor(Color::Blue);
                text[3].setPosition((WINDOW_WIDTH-text[3].getGlobalBounds().width)/2, WINDOW_HEIGHT/2 + 100);

                text[4].setFont(font);
                text[4].setString("Echap pour quitter");
                text[4].setCharacterSize(40);
                text[4].setColor(Color::Blue);
                text[4].setPosition((WINDOW_WIDTH-text[4].getGlobalBounds().width)/2, WINDOW_HEIGHT/2 + 150);

                text[5].setFont(font);
                char string_highscore_text[30] = "Highscore : ";
                char string_highscore[10];
                sprintf(string_highscore, "%i", high_score);
                strcat(string_highscore_text, string_highscore);
                text[5].setString(string_highscore_text);
                text[5].setCharacterSize(40);
                text[5].setColor(Color::Red);
                text[5].setPosition((WINDOW_WIDTH-text[5].getGlobalBounds().width)/2, WINDOW_HEIGHT - 100);

                // Affichage des textes de l'ecran de fin

                app.clear();
                app.draw(text[0]);
                app.draw(text[1]);
                app.draw(text[2]);
                app.draw(text[3]);
                app.draw(text[4]);
                app.draw(text[5]);
                app.display();
            }
        }
    }
    return 0;
}
