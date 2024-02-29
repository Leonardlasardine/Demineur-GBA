# Démineur-GBA

## Jeu de Démineur pour Nintendo GameBoy Advance

Ce projet est un jeu vidéo programmé en langage C et à l'aide du kit de développement [HAM](https://www.cameronjtinker.com/downloads/ham-all.zip).

### Fonctionalitées :

- Grille générée aléatoirement,
- 5 niveaux de difficultée disponibles,
- choix du nombre de mines,
- possiblilitée de sauvegarder et charger une partie dans la mémoire,
- utilisation d'un mot de passe pour regénérer une même grille,
- tableau des meilleurs scores,
- choix des couleurs.

### Structure du projet

À la racine se situent les fichiers C qui composent le programme. Les fichiers d'en-tête H se situent dans le dossier headers.   
Les images sont enregistrées sous la forme de tableau de pixels et se trouvent dans le dossier bitmaps.   
Les fichiers de son et musique sont des trakers au format s3m et se situent à la racine.

### Pour jouer

Pour tester, il suffit de télécharger le fichier [Demineur.gba](https://github.com/Leonardlasardine/Demineur-GBA/releases/download/v1.0.0/Demineur.gba) et de le lancer avec un émulateur ou une GameBoy Advance.   
Pour compiler le programme, il faut disposer d'un ordinateur avec Microsoft Windows **XP** et installer le kit de développement [HAM](https://www.cameronjtinker.com/downloads/ham-all.zip) puis lancer la commande build.bat.   
Pour générer des images pouvant être utilisé par le jeu, il faut convertir des images BMP d'une profondeur de couleur 8 bits avec la commande "gfx2gba -fsrc -c32k" du kit HAM.

### Captures d'écran

Example d'une partie et d'un tableau de scores   
![Partie](https://ams06pap001files.storage.live.com/y4mt3b-tV2TSgQj3lz8hcK8mAja0DVZsAbolkmIoKiRoEACE7pb7zSUcsHA7XUW0JFQZFGgjyf4oG_mslsKCjT6P6WxHxDvlf_X5-dDezT4med4urNmEOzCseFjJ_1aEJoe6-k-g4J1k2VGS9KNvSIKVlZjELyrc-3MC5azCw8IwvVkYKM_923Dhb3EddFgLotPvzuu9bjCDLOpGtA8quRzEQ?encodeFailures=1&width=240&height=160 "Partie") ![Tableau de scores](https://ams06pap001files.storage.live.com/y4mNI5QndNTPUUC7Q2R2piegJvnzgVE5t8gR3zrUkTxx32asWwJmmUyZE6Mbad1kXDJqNWXaT8Mq5K0dzbRk4rSnSEHf4rG-q03xh_sdy5ejLae8tdnaeYxIJ4MdyLqHokaIyKEYSHnCsC5PObV5MWk3Yrj6RfLUi20ZU4Z97vwR1pn-tg0dWcmSPu-8hBtr6Qo4DuTA8wG1z-1WgKQGewmlg?encodeFailures=1&width=240&height=160 "Tableau de scores")   
Génération de mot de passe   
![Mot de passe](https://ams06pap001files.storage.live.com/y4m1zsCTKNv32VnA9cjk_2GEgzeuVcUTIKJrsLsYuLx4dNZpOCwfssZwte9o9NwtHChsVJx_M1IfEXQRZhkgK1J5tPzUoYpDefF4Plvxn2aJLGEQ_0UNUklCs1GNTXvWTkef5Vp_qIEE-E2u-2-aN36jEpzXzz7Sz1RjBttE_Jdzu62yiHw09Tmjy1jJ99McO5kXa11OYAE1lGvFX8K4EIMhg?encodeFailures=1&width=240&height=160 "Mot de passe") ![Clavier](https://ams06pap001files.storage.live.com/y4mTb3GwWOMHvSkNt71Jcr-854YM46-cNu5QaOOGYoOSNhvnY-P2RcAl-6_OrHCLBacSqq0juYgoeYOtKc6tbElv72bXI0G8KQG-MsoqyhCMnQJ6Ue6ukczkXtAc8vHxQoJzXncUhn63sCjuk0CzzA2bTLZJuz7SlAudFpXveepB5kMkLnV6qJlvsgNu1fLGPSYNR2WmiMwE5JUdq1bqP5elw?encodeFailures=1&width=240&height=160 "Clavier")


Fonctionne sur GameBoy Advance après test.
