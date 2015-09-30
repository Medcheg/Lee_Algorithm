#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "cursor.h"

typedef struct tag_point
{
    int32_t x;
    int32_t y;
}point_t;

typedef struct tag_blackhole
{
    point_t a;
    point_t b;
    uint32_t speed;
}blackhole_t;

typedef struct tag_field
{
    uint8_t *field;
    uint32_t field_with;
    uint32_t field_height;

    point_t a;
    point_t b;

    blackhole_t  blackhole[10];
    uint32_t     blackhole_count;

    uint32_t itteration;
}space_t;

typedef struct tag_chain
{
    point_t *list;
    uint32_t  list_len;
    uint32_t  index;
}chain_t;

void init_space(space_t *space, uint32_t field_w, uint32_t field_h)
{
    // init field
    space->field_with   = field_w;
    space->field_height = field_h;
    space->field = (uint8_t*) calloc(1, space->field_with * space->field_height);

    space->field[space->a.y * space->field_with + space->a.x] = 0xFF; // A
    space->field[space->b.y * space->field_with + space->b.x] = 0xFE; // B

    uint32_t z;
    for ( z = 0;  z < space->blackhole_count; z++ )
    {
        space->field[space->blackhole[z].b.y * space->field_with + space->blackhole[z].b.x] = 0xF0; // Black hole in
        space->field[space->blackhole[z].a.y * space->field_with + space->blackhole[z].a.x] = 0xF1; // Black hole out
    }
}

void PUSH_STRING(char **buff, uint32_t *buff_size, uint32_t *buff_pos, char *m_char)
{
    uint32_t new_pos = *buff_pos + strlen(m_char) + 1;

    if ( new_pos >= *buff_size )
    {
        uint32_t new_size = (*buff_size) * 2;

        // initialization
        if ( *buff == NULL )
        {
            new_size = 1<<31;
            while ( (new_size & new_pos) == 0 ) {new_size >>= 1;}
            new_size <<= 1;

        }

        //realloc
        char* new_buff = (char*) realloc (*buff, new_size );
        if ( new_buff == NULL )
        {
            printf("Error allocation !!!\n");
            exit(1);
        }
        *buff = new_buff;
        *buff_size = new_size;
        //printf("new_size = %d\n", *buff_size);
    }

    // print character
    uint32_t printed_bytes = sprintf(&(*buff)[*buff_pos], "%s", (m_char));
    *buff_pos += printed_bytes;
    //printf("(m_buff_size) = %d \t (m_buff_pos) = %d \t sizeof(m_char) = %d\n", *buff_size, *buff_pos, (uint32_t)strlen(m_char));

}

void draw_space(space_t *space, uint8_t is_repaint)
{
    // ╔═╦═╗  ............
    // ║ ║ ║
    // ╠═╬═╣  |          |
    // ║ ║ ║
    // ╚═╩═╝  ''''''''''''
    // ╔═╗
    // ╚═╝

    uint32_t screen_w = 60;
    uint32_t screen_h = 20;
    float coef_x = (float)space->field_with / (float)screen_w ;
    float coef_y = (float)space->field_height / (float)screen_h;
    int32_t i, i1 = -1;
    int32_t k, k1 = -1;

    (void)i;
    (void)i1;
    (void)k;
    (void)k1;

    uint32_t buffer_size = 0;
    uint32_t buffer_pos  = 0;
    char *buffer = NULL;

    //(void)ptr;

    // header
    PUSH_STRING(&buffer, &buffer_size, &buffer_pos, "╔");
    for ( i = 0; i < screen_w; i++ ) PUSH_STRING(&buffer,&buffer_size, &buffer_pos, "═");
    PUSH_STRING(&buffer, &buffer_size, &buffer_pos, "╗\n");

    // space
    for ( k = 0; k < screen_h; k++)
    {
        PUSH_STRING(&buffer, &buffer_size, &buffer_pos, "║");

        for ( i = 0; i < screen_w; i++)
        {
            uint32_t field_pos_x = i * coef_x;
            uint32_t field_pos_y = k * coef_y;
            uint32_t next_field_pos_x = (i+1) * coef_x;
            uint32_t next_field_pos_y = (k+1) * coef_y;

            //printf ("field_pos_x = %d, field_pos_y = %d space->a.x / coef_x = %f\n", field_pos_x, field_pos_y, space->a.x / coef_x);
            char symbol[16] = {0};
            strcpy(symbol, " ");

            for ( k1 = field_pos_y; k1 < next_field_pos_y; k1++  )
            {
                for ( i1 = field_pos_x; i1 < next_field_pos_x; i1++  )
                {
                    //printf ("k1 = %d, i1 = %d, field_pos_x = %d, field_pos_y = %d  \n", k1, i1, field_pos_x, field_pos_y);

                    if ( space->field[k1*space->field_with + i1] == 0xFF ) strcpy(symbol, "A"); else
                    if ( space->field[k1*space->field_with + i1] == 0xFE ) strcpy(symbol, "B"); else
                    if ( space->field[k1*space->field_with + i1] == 0xF0 ) strcpy(symbol, "X"); else
                    if ( space->field[k1*space->field_with + i1] == 0xF1 ) strcpy(symbol, "*"); else
                    if ( space->field[k1*space->field_with + i1] != 0    ) strcpy(symbol, "~");
                }
            }
            PUSH_STRING(&buffer, &buffer_size, &buffer_pos, symbol);
        }
        PUSH_STRING(&buffer, &buffer_size, &buffer_pos, "║\n");
    }

    // footer
    PUSH_STRING(&buffer, &buffer_size, &buffer_pos, "╚");
    for ( i = 0; i < screen_w; i++ ) PUSH_STRING(&buffer,&buffer_size, &buffer_pos, "═");
    PUSH_STRING(&buffer, &buffer_size, &buffer_pos, "╝\n");

    // Print space
    printf("\n Itteration = %d\n\n", space->itteration);
    printf("%s", buffer);
    if ( is_repaint == 1 )
    {
        CURSOR_MOVE_UP(screen_h + 3 + 2);
    }

    if ( buffer != NULL )
    {
        free(buffer);
    }

}

void chain_add_node( space_t *space, chain_t *chain, point_t coord, uint32_t chain_index )
{
//    if ( space->field[coord.x][coord.y] == 0 )
//    {
//        space->field[coord.x][coord.y] = chain_index;

//        chain->list_len++;
//        chain->list = (point_t * ) realloc (chain->list, sizeof(point_t) * (chain->list_len));

//        chain->list[chain->list_len-1].x = coord.x;
//        chain->list[chain->list_len-1].y = coord.y;
//    } else
//    {
//        if ( space->field[coord.x][coord.y] > chain_index )
//        {
//            space->field[coord.x][coord.y] = chain_index;

//            chain->list_len++;
//            chain->list = (point_t * ) realloc (chain->list, sizeof(point_t) * (chain->list_len));

//            chain->list[chain->list_len-1].x = coord.x;
//            chain->list[chain->list_len-1].y = coord.y;
//        }
//    }

//    chain->index = chain_index;
}

void chain_create(chain_t **chain, uint32_t *count )
{
//    *count =  *count + 1;
//    *chain = (chain_t * ) realloc (*chain, sizeof(chain_t) * (*count));
}

void chain_free(chain_t *chain, uint32_t *count )
{
//    uint32_t i;

//    for ( i = 0; i < *count; i++ )
//    {
//        if ( chain[i].list != NULL )
//        {
//            free (chain[i].list);
//            chain[i].list = NULL;
//            chain[i].list_len = 0;
//        }

//    }
//    free (chain);
//    *count = 0;
}

void check_limitation(uint32_t w, uint32_t h, point_t *p)
{
    if ( p->x  < 0   ) p->x = 0;
    if ( p->x >= w-1 ) p->x = w-1;

    if ( p->y  < 0   ) p->y = 0;
    if ( p->y >= h-1 ) p->y = h-1;

    //printf("y = %d\n", p->y);
}

int main()
{
    space_t space;
    chain_t *chain = NULL;
    uint32_t chain_count = 0;

    memset (&space, 0, sizeof(space_t));

    uint32_t w = 120;
    uint32_t h = 40;
    //uint32_t w = 20;
    //uint32_t h = 10;

    space.a.x = 10, space.a.y = 5;
    space.b.x = 90, space.b.y = 35;

    space.blackhole_count = 2;

    space.blackhole[0].speed = 10;
    space.blackhole[0].a.x = 80; space.blackhole[0].a.y = 30;
    space.blackhole[0].b.x = 80; space.blackhole[0].b.y = 7;

    space.blackhole[1].speed = 5;
    space.blackhole[1].a.x = 7;  space.blackhole[1].a.y = 7;
    space.blackhole[1].b.x = 70; space.blackhole[1].b.y = 31;

    init_space(&space, w, h);

    uint32_t i, z;
    (void)i;
    (void)z;
    (void)w;
    (void)h;

    chain_create(&chain, &chain_count);

    chain_add_node(&space, &chain[0], space.a, space.itteration);
    do
    {
        chain_create(&chain, &chain_count);

//        chain_t *curr_chain = &chain[space.itteration];
//        chain_t *new_chain = &chain[chain_count - 1];

//        //printf("curr_chain->list_len = %d chain_count = %d\n", curr_chain->list_len, chain_count);

//        for ( z = 0; z < curr_chain->list_len; z++)
//        {
//            point_t p;

//            p.x = curr_chain->list[z].x - 1;
//            p.y = curr_chain->list[z].y;
//            check_limitation(w, h, &p);
//            chain_add_node(&space, new_chain, p, space.itteration);

//            p.x = curr_chain->list[z].x + 1;
//            p.y = curr_chain->list[z].y;
//            check_limitation(w, h, &p);
//            chain_add_node(&space, new_chain, p, space.itteration);

//            p.x = curr_chain->list[z].x;
//            p.y = curr_chain->list[z].y - 1;
//            check_limitation(w, h, &p);
//            chain_add_node(&space, new_chain, p, space.itteration);

//            p.x = curr_chain->list[z].x;
//            p.y = curr_chain->list[z].y + 1;
//            check_limitation(w, h, &p);
//            chain_add_node(&space, new_chain, p, space.itteration);
//        }

        space.itteration++;
        draw_space(&space, 1); usleep(2000);
        break;
    } while(  space.itteration  < 218);

    draw_space(&space, 0);

    //chain_free(chain, &chain_count);

    printf("\nDone !!! \n\n");

    return 0;
}
