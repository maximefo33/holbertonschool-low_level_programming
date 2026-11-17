void print_name(char *name, void (*f)(char *))
{
    /* f est le pointeur vers la fonction.
     * name contient la chaîne à transmettre à cette fonction.
     */
    f(name);
}