First Dual Project

Gestion de la memoire
- tout les elements qui sont destine aux structures doivent
etre allouer avec ft_malloc.
- Les elements qui sont allouer de maniere ephemere sont allouer
avec malloc et free dans la meme fonction.
- Si un element est allouer avec une fonction externe il doit etre free dans la meme fonction ou etre ajouter au garbage colector avec memory_add.

- le garbage colector est free a chaque commande entre et executer.
- Dans le cas d un 'control C' le garbage_collector est free et des signaux d arret sont envoyer a tout les processus enfant.
- Dans le cas d un 'control D' ou dun exit le garbage_collectot est free et on exit le programme.