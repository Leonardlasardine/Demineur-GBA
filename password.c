#include <math.h>
#include "password.h"
#include "font.h"
#include "timers.h"
#include "menu.h"
#include "view.h"
#include "controls.h"
#include "videoModes.h"

unsigned long long concatenate(unsigned long long a, unsigned long long b) {
	unsigned long long pow = 10;
	while(b >= pow) {
		pow *= 10;
	}
	return a * pow + b;
}

//Inutile
unsigned long long concatenateArray(unsigned char *pseudo) {
	unsigned char i;
	unsigned long long number = pseudo[0];
	for(i = 1; i < 8; i++) {
		number = concatenate(number, pseudo[i]);
	}
	return number;
}

unsigned long long power(unsigned long long base, unsigned char exp) {
	unsigned char i;
	unsigned long long result = 1;
	for (i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

unsigned long long convertToBase10(unsigned char *base39) {
	unsigned long long number = 0;
	unsigned char i;
	
	for(i = 0; i < 8; i++) {
		number += base39[i] * power(39, (7-i));
	}

	return number;
}

//Convertir le nombre en base 10 en mot de passe utilisant tout le clavier (nombre en base 39 charactères)
//A l'envers ça serait mieux
unsigned char *convertToBase39(unsigned long long base10, unsigned char *newPseudo) {
	unsigned long long d;
	unsigned char r, n;

	d = base10;
	r = 0;
	n = 7;
	
	do {
		r = d % 39;
		d = d / 39;
		newPseudo[n] = r;
		n--;
	}
	while (d > 0);

	return newPseudo;
}

//Afficher le mot de passe
void writePassword() {
	/*endVideoMode3();
	setVideoMode0();

	unsigned int seed = getSeed();
	unsigned char d = getDifficulty();
	unsigned char m = getMines();
	unsigned char x = getX();
	unsigned char y = getY();
	
	ham_DrawText(1, 1, "%u", seed);
	ham_DrawText(1, 4, "%u", d);
	ham_DrawText(1, 7, "%u", m);
	ham_DrawText(1, 13, "X:%d  Y:%d", x, y);

	//while(1);*/

	drawScreenV(password_Bitmap);

	//Coller seed + Difficultée + Mines + Case de départ
	unsigned char password[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	unsigned long long base10 = concatenate(getSeed(), getDifficulty());
	unsigned char m = getMines();
	if (m < 10) {
		base10 = concatenate(base10, 0);
	}
	base10 = concatenate(base10, getMines());
	unsigned short fc = getFirstCase();
	if (fc < 10) {
		base10 = concatenate(base10, 0);
	}
	if (fc < 100) {
		base10 = concatenate(base10, 0);
	}
	base10 = concatenate(base10, getFirstCase());
	
	/*ham_DrawText(1, 7, "%u", fc);
	wait();
	setVideoMode3();*/

	convertToBase39(base10, password);

	unsigned char i;
	for (i = 0; i < 8; i++) {
		drawChar(105 + i*14, 40, password[i], getColor(0));
	}
}

//	XXXXXXX______
unsigned int getPasswordSeed(unsigned long long base10) {
	return base10 / 1000000; //Enlever 6 derniers chiffres
}

//	_______X_____
unsigned char getPasswordDifficulty(unsigned long long base10) {
	return (base10 / 100000) % 10;
}

//	________XX___
unsigned char getPasswordMines(unsigned long long base10) {
	return (base10/1000) % 100;
}

//	__________XXX
unsigned short getPasswordFirstCase(unsigned long long base10) {
	return base10 % 1000;
}
