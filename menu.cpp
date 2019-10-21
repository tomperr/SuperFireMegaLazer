#include "menu.hpp"
#include "fonctions_bg.hpp"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////FONCTIONS + STRUCTURES MENU PRINCIPAL///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void changementChoix(Menu &menu, Event event)
{
    if (event.type==Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case (Keyboard::Down):
            menu.pointeur = (menu.pointeur + 1)%4;
            break;
        case (Keyboard::Up):
            menu.pointeur = (menu.pointeur - 1);
            if (menu.pointeur < 0)
                menu.pointeur = 3;
            break;
        }
    }
}

Menu addMenu(Font font, Text textMenu[], Sprite sprite, Sprite spriteTitre, Music music[])
{
    int i = 0;
    Menu nouveau;
    music[0].play();
    music[0].setLoop(true);
    nouveau.sprite = sprite;
    nouveau.spriteTitre = spriteTitre;
    nouveau.font = font;
    for (i = 0; i<4; i++)
    {
        nouveau.textMenu[i] = textMenu[i];
    }
    nouveau.wait = false;

    return nouveau;

}

void drawMenu(RenderWindow *appMenu, Menu menu, Event event)
{
    int i = 0, y;
    for(i = 0; i<4; i++)
    {
        if (i == menu.pointeur)
            menu.textMenu[i].setColor(Color::Red);
        else
            menu.textMenu[i].setColor(Color::White);
    }

    appMenu->draw(menu.sprite);
    menu.spriteTitre.setPosition(220, -10);
    appMenu->draw(menu.spriteTitre);
    i = 0, y = 100;
    for (i = 0; i<4; i++)
    {
        menu.textMenu[i].setPosition(50, y);
        appMenu->draw(menu.textMenu[i]);
        y += 100;
    }


}

void selection(Event event,Menu menu, RenderWindow *appMenu, RenderWindow *fenetreVaisseau, RenderWindow *fenetreOptions,Music music[], bool *veutJouer)
{
    if (appMenu->isOpen())
    {
        if (event.type == Event::KeyPressed)
        {
            switch(event.key.code)
            {
            case (Keyboard::Return):
                if (menu.pointeur == 0)
                {
                    appMenu->close();
                    music[0].stop();
                    music[1].play();
                    music[1].setLoop(true);
                    *veutJouer = true;
                }
                else if (menu.pointeur == 1) //Selection choix vaisseau
                {
                    appMenu->close();
                    fenetreVaisseau->create(VideoMode(TAILLE_FENETRE, HAUTEUR_FENETREVAISSEAU), "vaisseau");//750x500
                }
                else if (menu.pointeur == 2)
                {
                    appMenu->close();
                    fenetreOptions->create(VideoMode(TAILLE_FENETRE, HAUTEUR_FENETREVAISSEAU), "Options");
                }
                else if (menu.pointeur == 3)
                {
                    appMenu->close();
                }

            }
        }
    }
}










////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////FONCTIONS + STRUCTURES PARTIE VAISSEAU/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////RECUP DES DONNEES ENTREES DANS LE MAIN//////////////////////////////////////////////////////////////


StructFenVaisseau imVaisseau(Sprite background, Sprite vaisseau[], Sprite TexSelect, Text textVaisseau[])
{
    StructFenVaisseau fenVai;
    fenVai.background = background;

    int i = 0;
    for (i = 0; i<4; i++)
    {
        fenVai.SpriteVaisseau [i] = vaisseau[i];
        fenVai.textVaisseau[i] = textVaisseau[i];
    }

    fenVai.texSelect = TexSelect; //triangle
    return fenVai;
}


///////////////////////////////////////DEPLACEMENT CURSEUR VAISSEAU + SELECTEURS ARMES//////////////////////////////////////////////////////

void choixDuVaisseau(StructFenVaisseau &vaisseau, Event event, RenderWindow *fenetreVaisseau, RenderWindow *appMenu)
{
    int i =0;

    if (fenetreVaisseau->isOpen())
    {

        if (event.type==Event::KeyPressed)
        {
            if ((vaisseau.choix%2) == 0)
            {
                vaisseau.choixArmes = false;
                switch (event.key.code)
                {
                case (Keyboard::Right):
                    vaisseau.pointeur = (vaisseau.pointeur + 1)%4;
                    break;
                case (Keyboard::Left):
                    vaisseau.pointeur = (vaisseau.pointeur - 1);
                    if (vaisseau.pointeur < 0)
                        vaisseau.pointeur = 3;
                    break;
                case (Keyboard::Up):
                    vaisseau.textVaisseau[2].setColor(Color::Red);
                    vaisseau.escape = true;
                    break;
                case (Keyboard::Down):
                    vaisseau.textVaisseau[2].setColor(Color::White);
                    vaisseau.escape = false;
                    break;
                }
            }
            if (event.key.code == Keyboard::A)
                vaisseau.choix++; //si choix%2 = 0 alors texte s'affiche pas
            else if (vaisseau.choix%2 == 1)
            {
                vaisseau.choixArmes = true;
                switch(event.key.code)
                {
                case (Keyboard::Up):
                    vaisseau.pointeurArmes = (vaisseau.pointeurArmes + 1)%2;
                    break;
                case(Keyboard::Down):
                    vaisseau.pointeurArmes = (vaisseau.pointeurArmes - 1)%2;
                    if (vaisseau.pointeurArmes < 0)
                        vaisseau.pointeurArmes = 1;
                    break;
                case(Keyboard::Return):

                    break;
                }
                for(i = 0; i<4; i++)
                {
                    if (i == vaisseau.pointeurArmes)
                        vaisseau.textVaisseau[i].setColor(Color::Red);
                    else
                        vaisseau.textVaisseau[i].setColor(Color::White);
                }

            }
            if (vaisseau.escape == true)
            {
                if (event.key.code == Keyboard::Return)
                {
                    fenetreVaisseau->close();
                    vaisseau.escape = false;
                    vaisseau.textVaisseau[2].setColor(Color::White);
                    appMenu->create(VideoMode(TAILLE_FENETRE + 200, HAUTEUR_FENETRE + 50), "Menu");
                }


            }


        }
    }

}

///////////////////////////////////////////////////////////////////DRAW SUR LA FENETRE////////////////////////////////////////////////////////////////////////

void drawFenetreVaisseau(RenderWindow *fenetreVaisseau, StructFenVaisseau vaisseau, Event event)
{

    switch (vaisseau.pointeur)
    {
    case 0:
        vaisseau.texSelect.setPosition(188,((HAUTEUR_FENETREVAISSEAU)/2)-(vaisseau.texSelect.getGlobalBounds().height)-50); //positionnement triangle
        break;
    case 1:
        vaisseau.texSelect.setPosition(316, ((HAUTEUR_FENETREVAISSEAU)/2)-(vaisseau.texSelect.getGlobalBounds().height)-50);
        break;
    case 2:
        vaisseau.texSelect.setPosition(444, ((HAUTEUR_FENETREVAISSEAU)/2)-(vaisseau.texSelect.getGlobalBounds().height)-50);
        break;
    case 3:
        vaisseau.texSelect.setPosition(573, ((HAUTEUR_FENETREVAISSEAU)/2)-(vaisseau.texSelect.getGlobalBounds().height)-50);
        break;
    }

    fenetreVaisseau->clear();

    vaisseau.background.setPosition(-150,0);

    vaisseau.texSelect.setRotation(180);

    vaisseau.textVaisseau[0].setPosition(100,320); // Peut-être à mettre dans une boucle
    vaisseau.textVaisseau[1].setPosition(350,450);
    fenetreVaisseau->draw(vaisseau.background); //Image background;
    fenetreVaisseau->draw(vaisseau.textVaisseau[2]);

    fenetreVaisseau->draw(vaisseau.texSelect);
    int i = 0;
    int x = 150, y = ((HAUTEUR_FENETREVAISSEAU)/2)-((vaisseau.SpriteVaisseau[0].getGlobalBounds().width)/2)-50;
    for (i = 0; i < 4; i++)
    {
        vaisseau.SpriteVaisseau[i].setPosition(x,y);
        fenetreVaisseau->draw(vaisseau.SpriteVaisseau[i]);
        if (vaisseau.choix%2 == 1) //affichage texte armes
        {
            fenetreVaisseau->draw(vaisseau.textVaisseau[0]);
            fenetreVaisseau->draw(vaisseau.textVaisseau[1]);

        }
        x += 128;

    }

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////// OPTIONS ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





StructFenOptions imageOptions(Sprite spriteOptions, Text textOptions[], RectangleShape barreSon, RectangleShape curseurSon, Font font, int pointeur)
{
    StructFenOptions fenOptions;
    fenOptions.pointeur = pointeur;
    fenOptions.font = font;
    fenOptions.spriteOptions = spriteOptions;
    fenOptions.barreSon = barreSon;
    fenOptions.curseurSon = curseurSon;
    int i = 0;
    for (i = 0; i<4; i++)
    {
        fenOptions.textOptions[i] = textOptions[i];
    }

    return fenOptions;
}

void choixOptions(StructFenOptions &fenOptions, Event event, RenderWindow *fenetreOptions, RenderWindow *appMenu)
{
    if(fenetreOptions->isOpen())
    {
        if (event.type==Event::KeyPressed)
        {
            if (fenOptions.choixVolume%2 == 0)
            {
                fenOptions.curseurSon.setFillColor(Color::White);
                switch (event.key.code)
                {
                case (Keyboard::Down):
                    fenOptions.pointeur = (fenOptions.pointeur + 1)%3;
                    break;
                case (Keyboard::Up):
                    fenOptions.pointeur = (fenOptions.pointeur - 1);
                    if (fenOptions.pointeur < 0)
                        fenOptions.pointeur = 2;
                    break;
                }
            }
            if (event.key.code == Keyboard::Return)
            {
                if (fenOptions.pointeur == 0)
                {
                    fenOptions.choixVolume++;
                    fenOptions.curseurSon.setFillColor(Color::Red);
                }
                if (fenOptions.pointeur == 2)
                {
                    fenetreOptions->close();
                    fenOptions.pointeur = 0;
                    appMenu->create(VideoMode(TAILLE_FENETRE + 200, HAUTEUR_FENETRE + 50), "Menu");

                }
            }
            else if (fenOptions.choixVolume%2 == 1)
            {
                switch(event.key.code)
                {
                case (Keyboard::Right):
                    if (fenOptions.curseurX <= 630)
                    {
                        fenOptions.curseurX += 15;
                        fenOptions.indicateurVolume += 5;
                    }
                    break;
                case (Keyboard::Left):
                    if (fenOptions.curseurX>= 360)
                    {
                        fenOptions.curseurX -=15;
                        fenOptions.indicateurVolume -= 5;
                    }
                    break;

                }
            }

        }
    }

}









void drawFenetreOptions(RenderWindow *fenetreOptions, StructFenOptions options, Event event)
{
    int i = 0, y = 100;

    for(i = 0; i<4; i++)
    {
        if (i == options.pointeur)
            options.textOptions[i].setColor(Color::Red);
        else
            options.textOptions[i].setColor(Color::White);
    }



    fenetreOptions->clear();

    for (i = 0; i<4; i++)
    {
        options.textOptions[i].setPosition(10, y);
        if (i == 0)
        {
            options.barreSon.setPosition(350, y +10);

        }
        if (i == 2)
            options.textOptions[i].setPosition(TAILLE_FENETRE -130, HAUTEUR_FENETREVAISSEAU - 40);
        fenetreOptions->draw(options.textOptions[i]);
        y +=150;
    }

    options.curseurSon.setPosition(options.curseurX,options.curseurY);
    options.spriteOptions.setPosition(100,300);
    fenetreOptions->draw(options.spriteOptions);
    fenetreOptions->draw(options.barreSon);
    fenetreOptions->draw(options.curseurSon);


}
