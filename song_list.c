#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dynamic_array {
int capacity;
int size;
void** elements;
} dynamic_array;

void init_array(dynamic_array* array) {
/*You must use the dynamic_array data structure for storing songs. The initial capacity of
the dynamic_array must be 2, and you must allocate 2 void* in the heap by using
malloc() and assign NULL value to them. elements pointer must store the returned
address from malloc(). Implement these operations in the init_array function*/

array -> capacity = 2;
array -> size = 0;
array->elements = (void**)malloc(array->capacity * sizeof(void*));
for (int i=0; i<2; i++){
    array -> elements[i] = NULL;
}
}

void put_element(dynamic_array* array, void* element) {
/* When the user chooses to add a new song you must create that song in the heap by
using malloc(). You must put this song address into the songs by using the put_element
function. In the put_element function you must increase the size of the elements array
and put the newly added element’s address into the elements array. Emplace it to the
first available position. */
/*Everytime the size of the dynamic_array reaches capacity/2 you must increase the
capacity to 2 times the old one, and copy the elements of the elements array into the
new allocated elements array. You must assign NULL value for elements array elements
that haven’t pointed to any valid songs yet. All these operations must be implemented in
the put_element function*/
    if (array->size == array->capacity) {
        array->capacity *= 2;
        void** temp = (void**)malloc(array->capacity * sizeof(void*));
        memcpy(temp, array->elements, array->size * sizeof(void*));
        free(array->elements);
        array->elements = temp;
    }
    array->elements[array->size++] = element;
}

void remove_element(dynamic_array* array, int position) {
/*When the user chooses to delete the song, you must find it by using get_element
function, and use free() function to deallocate them from the heap. And use
remove_element to remove its address from the songs*/
/*Everytime the size of the dynamic_array drops down to capacity/2, reduce capacity by
factor of 2 and allocate space for that capacity, copy the values of the elements array to
the newly allocated elements array and deallocate the old elements array by using free()
function. All these operations must be implemented in the remove_element function.*/
    if (array->size == array->capacity / 2) {
        array->capacity /= 2;
        void** temp = (void**)malloc(array->capacity * sizeof(void*));
        memcpy(temp, array->elements, array->size * sizeof(void*));
        free(array->elements);
        array->elements = temp;
    }
    free(array->elements[position]);
    for (int j = position; j < array->size - 1; j++) {
        array->elements[j] = array->elements[j + 1];
    }
    array->elements[array->size - 1] = NULL;
    array->size--;
}
void* get_element(dynamic_array* array, int position) {
/*While you list the songs you must use the get_element function to get the song address
at that position. Note that get_element returns void*, so you can cast the type of void* to
song*, and then access the song fields.*/
return array -> elements[position];
}

typedef struct song {
char* name;
float duration;
} song;

int main() {
    dynamic_array songs;
    init_array(&songs);
    while(1){
        printf("Write 1 for Adding Song\n");
        printf("Write 2 for Deleting Song\n");
        printf("Write 3 for Listing Songs\n");
        printf("Write 4 to Exit\n");
        int num;
        scanf("%d",&num);
        
        if(num == 1){
            song* add = (song*)malloc(sizeof(song));
            add->name = (char*)malloc(100 * sizeof(char));
            printf("Song Name: ");
            scanf("%s",add->name);
            printf("Song Duration: ");
            scanf("%f",&add->duration);
            put_element(&songs, add);
        }
        else if(num == 2){
            char* name = (char*)malloc(100 * sizeof(char));
            printf("Song Name: ");
            scanf("%s",name);
            for (int i = 0; i < songs.size; i++){
                song* s = (song*)get_element(&songs,i);
                if(strcmp(s->name, name)==0){
                    remove_element(&songs,i);
                    break;
                }
            }
            free(name);
        }
        else if(num == 3) {
            for(int i = 0; i < songs.size; i++){
                song* s = (song*)get_element(&songs,i);
                printf("Song: %s   Duration: %f \n",s -> name, s -> duration);
            }
        }
        else if(num == 4){
            break;
        }
    }
    return 0;
}



