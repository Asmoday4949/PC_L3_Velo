# Fonctionnement

## Algorithme

1. Habitant initialisé à un site aléatoire
2. Maintenance initialisée au dépôt

3. Les habitants se déplacent à un site aléatoire en prenant un velo
4. Une fois arrivé, ils déposent leur vélo

5. S'il n'y a plus de vélo
	5.1 Ils vont entrer dans la queue en attendant qu'un vélo soit disponible (conservation de la priorité d'arrivée).

6. S'il n'y a plus de borne libre
	6.1 Ils vont entrer dans une autre queue en attendant qu'une borne se libère (conservation de la priorité d'arrivée).


Les habitants sont représentés par la classe "Habitant".

La maintenance est représentée par la classe "Maintenance".

Les sites sont représentés par une structure "Site" qui se trouve dans le fichier header : algothread.h
Pour plus d'information concernant cette structure, veuillez consulter le fichier mentionner.

La queue est représentée par une "QQueue", il y a 2 conditions pour réveiller seulement les habitants concernés.
-> Si on rajoute des vélos, on réveille seulement ceux qui attendent pour un vélo.

La maintenance et les habitants sont dans une boucle infinie comme précisé dans le PDF.

## Interface Graphique

Un widget a été créé pour demander à l'utilisateur les divers arguments, voire fichier : initwidget.h
Tout ce qui était dans MainWindow à la base a été déplacé dans CityWidget.
MainWindow n'est plus qu'un QWidget avec un stacklayout qui va gérer la transition des données de InitWidget à CityWidget.

## Tests

Le programme a été testé en affichant toutes les modifications dans les sites, en vérifiant que le total de vélos à chaque site soit correct et que les déplacement 
des habitants de site à site soient également justes.
Nous avons également vérifié que les queues fonctionnement correctement. C'est-à-dire que les personnes "sortent" de l'attente dans l'ordre de leur arrivée.

Il est possible d'afficher les logs du programme les déplacement et modifications du total de vélos à chaque site en modifiant le booléen "displayQDebug" 
qui est initialisé dans le constructeur de la classe "AlgoThread".
