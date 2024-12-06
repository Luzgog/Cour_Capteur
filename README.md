# EN326 : Capteurs pour l'embarqué

L'objectif est de s'initier au développement embarqué sous Mbed OS en communicant avec un capteur de CO2 sur une carte 6tron ZEST_CORE_FMLR-72 développée par le CATIE.

## Contributeurs

DELEGLISE Leonie
TABARDEL Bastien

## Guide d'installation et d'utilisation

Il faut tout d'abord cloner le dépôt.

```
git@github.com:Luzgog/Cour_Capteur.git
```

Il est nécessaire d'installer Mbed et ses outils. Pour cela il faudra suivre le guide suivant : https://6tron.io/ressources_logicielles/mbed/setup-tools

Il faut mettre rajouter la variable d'environnement MBDE_GCC_ARM_PATH dans le PATH. Cela indique à Mbed où se retrouve les outils de compilations.  
Sur les PC de l'école il se trouve dans /opt/gcc-arm-none-eabi/gcc-arm-none-eabi-10.3-2021-07/bin/. Il faudra donc rajouter dans le fichier .bashrc :

```
export MBED_GCC_ARM_PATH="/opt/gcc-arm-none-eabi/gcc-arm-none-eabi-10.3-2021-07/bin/"
export PATH=$MBED_GCC_ARM_PATH:$PATH
```

Il est nécessaire créer un environnement python virtuel, il est recommandé de le faire à l'extérieur du dossier cloné :

```
python -m venv <venv_name>
```

Il faudra ensuite l'activer :

```
source <venv_name>/bin/activate
```

Il faudra ensuite définir la cible et la toolchain :
```
mbed target ZEST_CORE_FMLR-72
mbed toolchain GCC_ARM
```

A la suite du clonage il faudra télécharger les dépendance du projet avec la commande
```
mbed deploy
```


Le projet pourra être compilé avec la commande `mbed compile` et la carte pourra être programmé avec la commande `sixtron_flash`.

La cible communiquera sur le port USB avec un baudrate de 9600. On pourra lire les communications avec des outils comme minicom ou mbed sterm de la manière suivante (remplacer x par le port correspondant) :
```
minicom -b 9600 -D /dev/ttyUSBx
mbed sterm --port /dev/ttyUSBx --baud 9600
```

## Travaux Pratiques

On peut retrouver le code correspondant aux exercices dans l'historique du depôt. Cependant, il faudra réaliser une commande supplémentaire :
```
cp mbed_zest-core-fmlr-72/custom_targets.json .
```

Pour l'exercice sur le **polling** :
```
git checkout 5dbc72d1416707ebee969c89a6031e48a81fb341
```

La carte affichera la valeur du boutton.

Pour l'exercice sur **l'interruption**:

```
git checkout a057de5a52a7f637613bb55a0ad90a4d7b5e59f5
```

La carte affichera le temps qu'aura passé le bouton à l'état pressé.

Pour l'exercice sur **le ticker** :

```
git checkout 0dbb1001cb92067828e2e7bf30662f26c3d56703
```

La carte va faire clignotter la led et incrémenter la fréquence de clignotement à chaque appuie du boutton.

Les travaux pratique sur **l'I2C**:

Le capteur à l'adresse I2C 0x62.

La mesure peut être lu dans le registre d'adresse 0xec05.

La donnée lu fait 9 octets dont 3 qui sont uniquement des CRC.

Nous avons réalisé une classe regroupant les interactions avec le capteur. On peut retrouver l'utilisation de cette classe sur le commit suivant. Attention cependant il n'est plus nécessaire de faire la copy du custom-target.json.

```
git checkout b39f0adb7c8915757cbc7bb542f9f2a394be5542
```

Pour les tp sur les **threads**:

```
git checkout b39f0adb7c8915757cbc7bb542f9f2a394be5542
```



Le projet lora se trouve sur le dernier commit 

```
git checkout main
```
