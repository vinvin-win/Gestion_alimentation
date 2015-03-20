# Gestion alimentation

Les alimentations que l'on fait chez soi avec peu de composants nécessitent l'emploi d'un ou plusieurs multimètres pour visualiser le bon fonctionnement de l'appareil. Grace à ce programme et quelques composants vous n'emploierez plus de multimètre.


=========

Les programmes sont basés sur un atmega328p de chez Atmel, monté avec un quartz 16 MHz.
Pour l'affichage j'emploie un écran LCD couleur, d'une taille 1.8" et de résolution 128x160: ST7735R.
L'avantage d'avoir un écran graphique est que cela évite d'avoir un menu où l'on sélectionne les informations que l'on veut afficher, ici elles sont toutes présentes sur une page.
Il y a une fonction qui permet de gérer un ventilateur de processeur grace à un PWM, variant en fonction de la température, qui doit être mesurée par une thermistance. La température en degrés Celsius est calculée grace à la relation de Steinhart-Hart.

=========
La programmation est faite avec l'IDE Arduino, je n'emploie pas directement l'arduino, car l'écran fonctionne en 3.3 V. Il est également plus simple de faire un PCB qui contient le circuit de l'alimentation et l'affichage.
J'ai employé une librairie qui ne m'appartient pas pour gérer l'affichage sur l'écran, voici le lien de cette librairie: ()[https://github.com/adafruit/Adafruit-ST7735-Library]


=========

IMPORTANT !
Ce projet utilise d'autres projets sous la licence " GNU GENERAL PUBLIC LICENSE " qui n'appartiennent pas à vinvin-win.
Ce projet est lui-même distribué sous la licence " GNU GENERAL PUBLIC LICENSE " conformément aux clauses de la licence.
