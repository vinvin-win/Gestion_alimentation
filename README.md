# Gestion alimentation

Les alimentations que l'on fait chez soi peu de composant nécessitent l'emploi d'un ou plusieur multimètre pour visualiser son bon fonctionnement.


=========

Les programmes sont basés sur un atmega328p de chez Atmel, monté avec un quartz 16 mhz.
Pour l'affichage j'emploie un écran LCD couleur, d'une taille 1.8" et de résolution 128x160: ST7735R.
L'avantage d'avoir un écran graphique est que cela évite d'avoir un menu où l'on sélectionne les informations que l'on veut afficher, ici elles sont toutes présentes sur une page.


=========
La programmation est faite sur l'IDE Arduino, je n'emploie pas directement l'arduino, car l'écran fonctionne en 3.3 V, puis il est plus simple de faire un PCB qui contient le circuit de l'alimentation et l'affichage.
J'ai employé une librairie qui ne m'appartient pas pour gérer l'affichage sur l'écran, voici le lien de cette librairie: https://github.com/adafruit/Adafruit-ST7735-Library 


=========

IMPORTANT !
Ce projet utilise d'autres projets sous la licence " GNU GENERAL PUBLIC LICENSE " qui n'appartiennent pas à vinvin-win.
Ce projet est lui-même distribué sous la licence " GNU GENERAL PUBLIC LICENSE " conformément aux clauses de la licence.
