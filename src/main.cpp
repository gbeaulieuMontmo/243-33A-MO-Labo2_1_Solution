#include <Arduino.h>
#include <bits_manip.h> //ajout de la bibliothèque bits_manip.h

// Définition des broches de la DEL1 RVB
#define DEL1R PG2
#define DEL1V PG1
#define DEL1B PG0
// Broches Arduino pour la DEL1 RVB
#define DEL1RA 39
#define DEL1VA 40
#define DEL1BA 41

// Définition des broches de la DEL2 RVB
#define DEL2R PL7
#define DEL2V PL6
#define DEL2B PL5
// Broches Arduino pour la DEL2 RVB
#define DEL2RA 42
#define DEL2VA 43
#define DEL2BA 44

// Définition des broches de la DEL3 RVB
#define DEL3R PL4
#define DEL3V PL3
#define DEL3B PL2
// Broches Arduino pour la DEL3 RVB
#define DEL3RA 45
#define DEL3VA 46
#define DEL3BA 47

// Définition des broches des boutons-poussoirs
#define BTNA PC6 
#define BTNB PC4
#define BTNC PC5  

//Permet d'allumer la DEL 1 de la couleur choisie.
//Param:  rouge = valeur de rouge entre 0 et 255.
//        vert = valeur de vert entre 0 et 255.
//        bleu = valeur de bleu entre 0 et 255.
void allume_del1(int rouge, int vert, int bleu)
{
  analogWrite(DEL1RA, rouge);
  analogWrite(DEL1VA, vert);
  analogWrite(DEL1BA, bleu);
}

//Permet d'allumer la DEL 2 de la couleur choisie.
//Param:  rouge = valeur de rouge entre 0 et 255.
//        vert = valeur de vert entre 0 et 255.
//        bleu = valeur de bleu entre 0 et 255.
void allume_del2(int rouge, int vert, int bleu)
{
  analogWrite(DEL2RA, rouge);
  analogWrite(DEL2VA, vert);
  analogWrite(DEL2BA, bleu);
}

//Permet d'allumer la DEL 3 de la couleur choisie.
//Param:  rouge = valeur de rouge entre 0 et 255.
//        vert = valeur de vert entre 0 et 255.
//        bleu = valeur de bleu entre 0 et 255.
void allume_del3(int rouge, int vert, int bleu)
{
  analogWrite(DEL3RA, rouge);
  analogWrite(DEL3VA, vert);
  analogWrite(DEL3BA, bleu);
}

void jeuxLumiere1()
{
  allume_del1(255, 0, 0); // Rouge
  allume_del2(0, 255, 0); // Vert
  allume_del3(0, 0, 255); // Bleu
  delay(1000);
  allume_del1(0, 255, 0); // Vert
  allume_del2(0, 0, 255); // Bleu
  allume_del3(255, 0, 0); // Rouge
  delay(1000);
  allume_del1(0, 0, 255); // Bleu
  allume_del2(255, 0, 0); // Rouge
  allume_del3(0, 255, 0); // Vert
  delay(1000);
  // Éteindre les DELs
  allume_del1(0, 0, 0);
  allume_del2(0, 0, 0);
  allume_del3(0, 0, 0);
  delay(1000);
}

void jeuxLumiere2()
{
  //Faire allumer les DELs en blanc
  allume_del1(255, 255, 255); // Blanc
  allume_del2(255, 255, 255); // Blanc
  allume_del3(255, 255, 255); // Blanc
  delay(1000);
  //Faire allumer les DELs une à la suite de l'autre avec des couleurs
  //au hasard
  allume_del1(random(0, 256), random(0, 256), random(0, 256));
  delay(500);
  allume_del2(random(0, 256), random(0, 256), random(0, 256));
  delay(500);
  allume_del3(random(0, 256), random(0, 256), random(0, 256));
  delay(1000);
  //Éteindre les DELs
  allume_del1(0, 0, 0);
  allume_del2(0, 0, 0);
  allume_del3(0, 0, 0);
  delay(1000);
} 

void jeuxLumiere3()
{
  //Faire allumer les DELs en rouge si on appuie sur le bouton B
  //en vert si on appuie sur le bouton A
  //et en bleu si on appuie sur le bouton C
  if (isBitSet(PINC, BTNA) == 0) // Bouton A appuyé
  {
    //Allumer les DELs en vert
    allume_del1(0, 255, 0); 
    allume_del2(0, 255, 0); 
    allume_del3(0, 255, 0); 
  }
  else if (isBitSet(PINC, BTNB) == 0) // Bouton B appuyé
  {
    //Allumer les DELs en rouge
    allume_del1(255, 0, 0); 
    allume_del2(255, 0, 0); 
    allume_del3(255, 0, 0); 
  }
  else if (isBitSet(PINC, BTNC) == 0) // Bouton C appuyé
  {
    //Allumer les DELs en bleu
    allume_del1(0, 0, 255); 
    allume_del2(0, 0, 255); 
    allume_del3(0, 0, 255); 
  }
  else // Aucun bouton appuyé
  {
    //Éteindre les DELs
    allume_del1(0, 0, 0); 
    allume_del2(0, 0, 0); 
    allume_del3(0, 0, 0); 
  }
}


void setup() {
  DDRG = setBitM(DDRG, B00000111); // Configure les broches de la DEL1 RVB comme sorties
  DDRL = setBitM(DDRL, B11111100); // Configure les broches de la DEL2 et DEL3 RVB comme sorties
  DDRC = clearBitM(DDRC, B01110000); // Configure les broches des boutons-poussoirs comme entrées
  PORTC = setBitM(PORTC, B01110000); // Active les résistances pullup internes pour les boutons-poussoirs
  randomSeed(analogRead(0)); // Initialisation du générateur de nombres aléatoires
}

void loop() {
  //jeuxLumiere1();
  //jeuxLumiere2();
  jeuxLumiere3();
}

