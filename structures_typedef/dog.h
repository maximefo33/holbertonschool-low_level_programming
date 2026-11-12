#ifndef dog_h
#define dog_h

/**
 * struct dog - Structure representing a dog
 * @name: The dog's name
 * @age: The dog's age
 * @owner: The dog's owner
 */

struct dog
{
	char *name;
	float age;
	char *owner;
};
typedef struct dog dog_t;
void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);
dog_t *new_dog(char *name, float age, char *owner);
void free_dog(dog_t *d);
#endif /* dog_h*/
