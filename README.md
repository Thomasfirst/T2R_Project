# TicketToRide-Polytech

Ce repository contient les fichiers nécessaire au tournoi Polytech Sorbonne des *Aventuriers du rail* (Ticket to Ride).

Pour lancer le programme, télécharger le repository, puis le décompresser. Ensuite lancer le terminal dans le fichier API.
Faire la commande “make” qui exécutera le makefile. Enfin lancer dans le terminal l'exécutable T2R_lExe.out avec la commande “ ./T2R_lExe.out ”.  
  ( C'est bien un l pas un 1 ./T2R_lExe.out)

Le programme fonctionne de la manière suivante:
  On peut choisir entre trois algorithmes:
 
  (Dans les trois cas on initialise 2 objectifs de départ qui valent le moins .On prend le moins de risque possible avec l'aléatoire.)
 
  - On a premièrement un algorithme qui permet de jouer manuellement.
  Il contient les fonctions de base pour choisir des mouvements à faire, et remplir les structures de données.
  Par exemple il remplie la structure qui contient le nombre de cartes et de wagons à chaque fois qu'on y touche.
  On a aussi des fonctions pour voir ce qu'il se passe chez l'adversaire ou voir l'état du terrain(look.c)
 
  - Le deuxième algorithme est totalement automatique, on le lance et on attend.
  Il reprend ce que l'on a vu sur le pdf (Dijkstra ...)
  On prend le premier objectif sur tous ceux que l’on a choisi. 
  Par la suite, il fait un tableau avec les routes que l’on veut. 
  De ce tableau on extrait la route que l’on a besoin(celle que l’on a pas et que l’ennemie n’a pas, cela et fait de la première route jusqu'à la dernière), 
  bien sur on recalcule l'itinéraire à chaque tour pour voir si l’ennemie n’a pas pris une route que l’on veut, si il l'a pris on contourne/on s’adapte. 
  Si on peut poser la route on le fait, sinon on pioche une carte de la couleur de la route. 
  Si dans les cartes visibles il n’y a pas la couleur de la route souhaitée, on regarde les autres routes que l’on a à placer et on prend une des couleurs que l’on a besoin.
  Si il n’y a toujours pas de carte que l’on veut on pioche aléatoirement ( pour les chances d’avoir une locomotive ou une carte que l'on veut ).
  Si la route et multicolor on pose les cartes que l'on a le plus et d’on on pas besoin. 
  Bien sûr, on optimise les cartes qu’il nous faut pour les prochaines prises de routes.(Même si on ne regarde pas tous les objectifs en même temps.)
  Les locomotives sont utilisées dès que possible, ça serait bête de perdre en en gardant toujours sous le coude.
  
    Pour les prochain objectif on suit le meme raisonnement.
    
    Il y a des sécurités si l'ennemi avance trop vite( il a peu de wagons restant...) on pose toutes nos cartes le plus vite possible pour ne pas perdre de points.
    Quand on a fini nos objectifs, on utilise le second morceau de l'algorithme.
    Il permet de placer les routes qui valent le plus de points.
    Évidemment on regarde si ces routes sont prises ou pas pour piocher les bonnes couleurs.
    On essaye d’en prendre le plus possible jusqu'à la fin(quand on a plus de wagon).
  
  On a plus de 70% de chance de gagner contre nice_bot normalement.


  - Le troisième algorithme
  
  Il utilise la seconde partie de l’algorithme deux, mais est légèrement différent pour être optimiser. 
  En effet, il essaye de placer le plus de points possibles en un minimum de temps possibles. 
  Pour ce faire, il essaye de placer le maximum de route de 6 (celle qui rapportera le plus), en un minimum de tour. 
  On ne tient pas compte des objectifs( c’est pour ca que l’on prend ceux qui valent le moins pour perdre le moins de points possibles). 
  Le bot essaye d’optimiser la pioche le plus possible, pour qu'à la fin il ne lui reste aucun wagon et très peu de cartes
  (normalement moins de 10, enfin c’est ce qu'on voudrait), pendant que l’adversaire perd des point a cause de ses objectif non accomplie et de plus 
  l’ennemie a un nombre de wagon important qui sont non placé. L'objectif est de finir vite avec le plus de points possible.
 
  On a plus de 90% de chance de gagner contre nice_bot normalement.





