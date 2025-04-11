#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define TAILLE_TUILE 128

void chargeVache(ALLEGRO_BITMAP* vaches[4][4], char* nomFichier)
{
    ALLEGRO_BITMAP* master = al_load_bitmap(nomFichier);
    if (!master) {
        printf("Erreur: image %s introuvable\n", nomFichier);
        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // extraction des tuiles à partir du fichier maitre
            vaches[i][j] = al_create_bitmap( TAILLE_TUILE, TAILLE_TUILE);
            al_set_target_bitmap(vaches[i][j]);
            al_draw_bitmap_region(master,j*TAILLE_TUILE,i*TAILLE_TUILE, TAILLE_TUILE, TAILLE_TUILE,0,0,0);
        }
    }
    al_destroy_bitmap(master);
}

void libereVache(ALLEGRO_BITMAP* vaches[4][4])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            al_destroy_bitmap(vaches[i][j]);
            vaches[i][j] = NULL;
        }
    }
}

int main(void)
{
    // declarations
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_TIMER* animation = NULL;
    ALLEGRO_EVENT_QUEUE* file = NULL;
    ALLEGRO_EVENT event;
    bool fini = false;
    ALLEGRO_BITMAP* vaches[4][4];
    int frame = 0;

    // initialisation
    assert(al_init());
    al_init_image_addon();

    chargeVache(vaches,"../images/cow_eat.png" );

    // creation
    fenetre =al_create_display(128,4*128);
    timer = al_create_timer(1.0/60.0);     // frequence d'affichage generale
    animation = al_create_timer(1.0/6.0);  // frequence de l'animation
    file = al_create_event_queue();

    // sources
    al_register_event_source(file, al_get_display_event_source(fenetre));
    al_register_event_source(file, al_get_timer_event_source(timer));
    al_register_event_source(file, al_get_timer_event_source(animation));

    al_start_timer(timer);
    al_start_timer(animation);

    while (!fini)
    {
        al_wait_for_event(file, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            fini = true;
            break;
        case ALLEGRO_EVENT_TIMER:

            if ( event.timer.source == timer)
            {
                al_clear_to_color(al_map_rgb(0,255,0));
                // affichages de la vache suivant differentes perspectives.
                al_draw_bitmap(vaches[0][frame], 0,0,0);
                al_draw_bitmap(vaches[1][frame], 0,1*TAILLE_TUILE,0);
                al_draw_bitmap(vaches[2][frame], 0,2*TAILLE_TUILE,0);
                al_draw_bitmap(vaches[3][frame], 0,3*TAILLE_TUILE,0);
                al_flip_display();
            }

            if ( event.timer.source == animation)
            {
                frame = (frame + 1)%4;
            }


            break;
        }
    }


    al_destroy_display(fenetre);
    al_destroy_timer(timer);
    al_destroy_timer(animation);
    al_destroy_event_queue(file);
    libereVache(vaches);

    return 0;
}