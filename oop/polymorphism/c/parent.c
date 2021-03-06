#include "parent.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


static struct parent_vtable vtable;


inline void parent_setup(void)
{
    static bool initialized = false;

    if(!(initialized))
    {
        vtable.say_hello = NULL;
        initialized      = true;
    }
}


void parent_init(struct parent *this, const char *str)
{
    size_t length;

    parent_setup();
    this->vtable = &vtable;
    length       = strlen(str);
    this->str    = malloc(length + 1);
    strcpy(this->str, str);
}


void parent_destroy(struct parent *this)
{
    free(this->str);
}


void parent_say_hello(struct parent *this)
{
    void (*say_hello)(struct parent *);

    say_hello = this->vtable->say_hello;

    if(say_hello == NULL)
    {
        exit(EXIT_FAILURE);
    }

    say_hello(this);
}
