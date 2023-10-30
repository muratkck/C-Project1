#include <stdio.h>
#include <stdlib.h>
/*
Author: Murat Küçük
Student ID: 280201052
*/
typedef struct linked_list_node_t {
    void* data;
    struct linked_list_node_t* next;
}linked_list_node_t __attribute__((__packed__));

void create_array_of_linked_list_ptrs(linked_list_node_t*** destination, int size) {

    *destination = (linked_list_node_t**)malloc(size * sizeof(linked_list_node_t*));
    // destination is the address which holds the array of playlists and the type 
    // of the playlist is linked-list-node-t*.

    for(int i = 0; i < size; i++){
        (*destination)[i] = NULL;
    }
}

void get_element_of_array_of_linked_list_ptrs(linked_list_node_t** array, int index, linked_list_node_t** destination){

    linked_list_node_t* playlist = calloc(1, sizeof(linked_list_node_t));
    playlist = array[index];
    *destination = playlist;

}
void set_element_of_array_of_linked_list_ptrs(linked_list_node_t*** array, int index, linked_list_node_t** head) {
   
    (*array)[index] = *head;

}

void destroy_array_of_linked_list_ptrs(linked_list_node_t*** array) {
    
    *array = malloc(sizeof(linked_list_node_t*));
    *array = NULL;
    
}

void resize_array_of_linked_list_ptrs(linked_list_node_t*** destination, linked_list_node_t** array, int size, int new_size){

    for (int i = 0; i < size; i++){
        array[i] = (*destination)[i];
    }
    *destination = calloc(new_size, sizeof(linked_list_node_t*));

    for (int i = 0; i < new_size; i++){
        if(i<size){
            set_element_of_array_of_linked_list_ptrs(destination, i, &array[i]);
        }
        else{
            (*destination)[i] = NULL;
        }
    }

}

void create_link_list(linked_list_node_t** destination){

    linked_list_node_t* playlist = (linked_list_node_t*)calloc(1, sizeof(linked_list_node_t));
    playlist -> data = NULL;
    playlist -> next = NULL;
    *destination = playlist;

}

void destroy_linked_list(linked_list_node_t** head) {
    
    while ((*head) != NULL) {
        linked_list_node_t* temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }

}

void add_to_linked_list(linked_list_node_t** head, const void* data) {

    linked_list_node_t* temp = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    temp -> data = data;
    temp -> next = NULL;

    if((*head) -> data == NULL){
        *head = temp;
    } 
    else{
        linked_list_node_t* current = *head;
        while (current -> next != NULL){
            current = current ->next;
        }
        current -> next = temp;
    }
}

void remove_from_linked_list(linked_list_node_t** destination, linked_list_node_t** head, const void* data) {

    linked_list_node_t* current = (linked_list_node_t*)calloc(1, sizeof(linked_list_node_t));
    current = *head;
    linked_list_node_t* prev = NULL;

    while ((current)->data != NULL && (current)->data != data) {
        prev = (current);
        current = (current) -> next;
    }

    if ((current) == NULL) {
        // The target value was not found in the list
        return;
    }

    if (prev == NULL) {
        // The target is the head of the list
        *head = (current)->next;

    } else {
        prev->next = (current)->next;
    }
    *destination = *head;
    free(current);

}

typedef struct song_t {
    const char* name;
    float duration;
} song_t;
void create_song(song_t* destination, const char* name, float duration) {
    
   destination -> name = name;
   destination ->duration = duration;

}


linked_list_node_t** array_of_playlist_ptrs = NULL;
linked_list_node_t** array_of_five_new_playlist = NULL;

int main(void){

    create_array_of_linked_list_ptrs(&array_of_playlist_ptrs, 5);

    // The playlists are stored into array_of_playlist_ptrs
    int index = 0;
    while (!array_of_playlist_ptrs[index]){

        linked_list_node_t* playlist;
        create_link_list(&playlist);
        set_element_of_array_of_linked_list_ptrs(&array_of_playlist_ptrs, index, &playlist);
        index++;
    }


    // The array_of_playlist_ptrs is resized to 10.
    create_array_of_linked_list_ptrs(&array_of_five_new_playlist, 5);
    resize_array_of_linked_list_ptrs(&array_of_playlist_ptrs, array_of_five_new_playlist, 5, 10);

    // The array_of_playlist_ptrs is refilled.
    for (int i = 5; i < 10; i++){
        linked_list_node_t* playlist;
        create_link_list(&playlist);
        set_element_of_array_of_linked_list_ptrs(&array_of_playlist_ptrs, i, &playlist);
    }

    const char* songNames[] = {
        "Eternal Serenity", "Midnight Melodies", "Summer Breeze", "Lost in the Echo",
        "Rainy Day Reflections", "Ocean Waves", "Electric Dreams", "Under the Stars",
        "A Moment of Solitude", "Urban Groove", "Whispers in the Wind", "Sunset Serenade",
        "Chasing Shadows", "Dance of the Fireflies", "Golden Memories", "Soothing Strings",
        "Celestial Voyage", "Mystic Rhythms", "Velvet Nightfall", "Echoes of Eternity",
        "Samba Delight", "Into the Unknown", "Jazzed Up", "Gentle Harmonies",
        "Enchanted Forest", "Rhythm of the Rain", "Acoustic Reverie", "City Lights",
        "Tranquil Waters", "Moonlit Sonata", "Serenade in G Minor", "Desert Sands",
        "Distant Horizons", "Whimsical Waltz", "Soulful Serenade", "Piano Nocturne",
        "Hidden Treasures", "Whirling Dervish", "Mystical Journey", "Harbor Dreams"
    };


    // Creates songs and adds to the playlists.
    int index1 = 0;
    while(array_of_playlist_ptrs[index1]){

        for (int i = 0; i < 4; i++){
            
            song_t* song_ptr = calloc(1, sizeof(song_t));
            const char* song_name = songNames[4*index1 + i];
            float song_duration = 10 * (rand() / (float)RAND_MAX);
            create_song(song_ptr, song_name, song_duration);
            add_to_linked_list(&array_of_playlist_ptrs[index1], (const void*)song_ptr);
            
        }
        index1++;
    }      

    // Remove the second song of each playlist
    int index2 = 0;
    while (array_of_playlist_ptrs[index2]){

        song_t* removed_song = calloc(1, sizeof(song_t));
        linked_list_node_t* current_playlist = array_of_playlist_ptrs[index2];
        current_playlist = current_playlist -> next;
        removed_song =(song_t*)current_playlist -> data;
        remove_from_linked_list(&array_of_playlist_ptrs[index2], &array_of_playlist_ptrs[index2], (const void*)removed_song);
        index2++;
    }
    
    // Print all songs by get_element_of_array_of_linked_list_ptrs() function
    int index3 = 0;
    while (array_of_playlist_ptrs[index3]){

        linked_list_node_t* playlist_required;
        get_element_of_array_of_linked_list_ptrs(array_of_playlist_ptrs, index3, &playlist_required);

        printf("%s%d\n", "Playlist #", index3);
        
        while (playlist_required != NULL){

            printf("    Name: %s, Duration: %f\n", ((song_t*)(playlist_required -> data)) -> name, ((song_t*)(playlist_required -> data)) -> duration);
            playlist_required = playlist_required -> next;
        }

        index3++;

    }

    // Each playlist is destroyed
    int index4 = 0;
    while (array_of_playlist_ptrs[index4]){
        destroy_linked_list(&array_of_playlist_ptrs[index4]);
        index4++;
    }

    // The array_of_playlist_ptrs is destroyed
    destroy_array_of_linked_list_ptrs(&array_of_playlist_ptrs);

    return 0;

}