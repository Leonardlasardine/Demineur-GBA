#include "score.h"
#include "font.h"
#include "view.h"
#include "menu.h"
#include "timers.h"
#include "save.h"
#include "keyboard.h"

unsigned char scoreMenu() {
	unsigned char i;
	//Rectangles
	for (i = 0; i < 5; i++) {
		drawLine(7, 54 + 18*i, 225, 16, RGB(0, 0, 0));
	}
	//Niveau
	drawLine(210, 5, 16, 16, RGB(20, 20, 0));
	drawChar(210, 5, getDifficulty(), RGB(130, 130, 0));

	unsigned short scoresColor = RGB(255, 138, 41);
	unsigned char score[8] = {39, 39, 39, 39, 39, 39, 39, 39};
	unsigned char d = getDifficulty();
	unsigned char timeH = 0;
	unsigned char timeM = 0;
	unsigned char timeS = 0;

	//Ecrire les scores
	for (i = 0; i < 5; i++) {
		drawChar(6, i*18 + 53, i, scoresColor);
		drawChar(16, i*18 + 53, 38, scoresColor); //tiret

		timeH = getScoreH(d, i);
		timeM = getScoreM(d, i);
		timeS = getScoreS(d, i);
		if (timeH*3600 + timeM*60 + timeS != 0) { //Si le score existe
			write(getScorePseudo(d, i, score),
				8, 30, i*18 + 53, -2, scoresColor);
			drawChar(160, i*18 + 53, numberToChar(timeH/10), scoresColor);//Dizaines
			drawChar(168, i*18 + 53, numberToChar(timeH%10), scoresColor);//Unités
			drawChar(176, i*18 + 53, 39, scoresColor);//Deux points
			drawChar(184, i*18 + 53, numberToChar(timeM/10), scoresColor);
			drawChar(192, i*18 + 53, numberToChar(timeM%10), scoresColor);
			drawChar(200, i*18 + 53, 39, scoresColor);
			drawChar(208, i*18 + 53, numberToChar(timeS/10), scoresColor);
			drawChar(216, i*18 + 53, numberToChar(timeS%10), scoresColor);
		}
	}

	//Controles
	//Touches
	unsigned char upScore = 0;
	unsigned char downScore = 0;
	unsigned char leftScore = 0;
	unsigned char rightScore = 0;
	unsigned char LScore = 0;
	unsigned char RScore = 0;
	unsigned char aScore = 0;
	unsigned char bScore = 0;
	unsigned char startScore = 0;

	unsigned char showScore = 1;

	while (showScore == 1) {
		if(F_CTRLINPUT_UP_PRESSED) {
		   upScore = 1;
	   } else {
		   if (upScore) {
			   //Comme le bouton gauche
			   leftScore = 1;
			   upScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_DOWN_PRESSED) {
		   downScore = 1;
	   } else {
		   if (downScore) {
			   //Comme le bouton droite
			   rightScore = 1;
			   downScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_LEFT_PRESSED) {
		   leftScore = 1;
	   } else {
		   if (leftScore && d > 0) {
			   setDifficulty(d-1);
			   showScore = 2;
			   leftScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_RIGHT_PRESSED) {
		   rightScore = 1;
	   } else {
		   if (rightScore && d < 4) {
			   setDifficulty(d+1);
			   showScore = 2;
			   rightScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_L_PRESSED) {
		   LScore = 1;
		   //Quitter Score
		   if (F_CTRLINPUT_R_PRESSED) {
			   showScore = 0;
		   }
	   } else {
		   if (LScore) {
			   //Comme le bouton gauche
			   leftScore = 1;
			   LScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_R_PRESSED) {
		   RScore = 1;
	   } else {
		   if (RScore) {
			   //Comme le bouton droite
			   rightScore = 1;
			   RScore = 0;
		   }
	   }
	   
	   if (F_CTRLINPUT_A_PRESSED) {
		   aScore = 1;
	   } else {
		   if (aScore) {//Quitter
			   showScore = 0;
			   aScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_B_PRESSED) {
		   bScore = 1;
	   } else {
		   if (bScore) {
			   showScore = 0;
			   bScore = 0;
		   }
	   }

	   if (F_CTRLINPUT_START_PRESSED) {
		   startScore = 1;
	   } else {
		   if (startScore) {
			   //Comme le bouton B
			   bScore = 1;
			   startScore = 0;
		   }
	   }
	}

	//Changer de page ou quitter
	return showScore;
}
//rajouter deux points clavier

void drawScoreBackground() {
	//Fond
	fillColor(RGB(20, 20, 0));
	
	//Titres
	unsigned short titleColor = RGB(130, 130, 0);
	unsigned char title[6] = {28, 12, 24, 27, 14, 28};
	unsigned char level[6] = {23, 18, 31, 14, 10, 30};
	unsigned short headerColor = RGB(255, 255, 255);
	unsigned char headerPseudo[6] = {25, 28, 14, 30, 13, 24};
	unsigned char headerTime[5] = {29, 14, 22, 25, 28};

	write(title, 6, 5, 5, 0, titleColor);
	drawChar(105, 5, 38, titleColor);//tiret

	write(level, 6, 130, 5, -4, titleColor);

	write(headerPseudo, 6, 30, 38, -4, headerColor);
	write(headerTime, 5, 160, 38, -4, headerColor);
}

//Demander pseudo si meilleur score
void newScore() {
	unsigned char d = getDifficulty();
	unsigned char h = getHours();
	unsigned char m = getMinutes();
	unsigned char s = getSeconds();
	unsigned char pseudo[8] = {39, 39, 39, 39, 39, 39, 39, 39};
	unsigned char i, old_h, old_m, old_s;
	unsigned char bestLine = 5;

	for (i = 5; i > 0; i--) {
		old_h = getScoreH(d, i-1);
		old_m = getScoreM(d , i-1);
		old_s = getScoreS(d, i-1);
		if(h*3600 + m*60 + s < old_h*3600 + old_m*60 + old_s //Meilleur que le score sur cette ligne
			|| old_h*3600 + old_m*60 + old_s == 0) { //Ou si score vide (=0)
			bestLine--;
		} else {
			i = 1;//Quitter la boucle
		}
	}

	//Si meilleur que la 5ème ligne
	if (bestLine < 5) {
		//Deplacer les scores vers le bas
		for (i = 4; i > bestLine; i--) {
			getScorePseudo(d, i-1, pseudo);
			old_h = getScoreH(d, i-1);
			old_m = getScoreM(d , i-1);
			old_s = getScoreS(d, i-1);

			setScorePseudo(d , i, pseudo);
			setScoreH(d, i, old_h);
			setScoreM(d, i, old_m);
			setScoreS(d, i, old_s);
		}

		for (i = 0; i < 8; i++) {
			pseudo[i] = 39;
		}
		setScorePseudo(d , bestLine, keyboard(pseudo));
		setScoreH(d, bestLine, h);
		setScoreM(d, bestLine, m);
		setScoreS(d, bestLine, s);
	}
	//AFAIRE afficher le score pendant 3 secondes
}
