/* en-tete */
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <jerror.h>

/*class Point utiliser pour les Points du superCylindre */
class Point
{

public:
    float x;
    float y;
    float z;
};

float pi = atan(1) * 4; // valeur de pi
int view = 15;          // variable de vision dans l espace ortho

/*variables servant aux animations  */
bool sens = true, sens1 = true, enrou = true;
int intsens = 0, intsens1 = 0;

/*variable servant la texture pour les jambes*/
const int largim = 256;
const int hautim = 256;
unsigned char image[(hautim) * (largim)*3];
unsigned char texture[hautim][largim][3];

/*variable utiliser en cours*/
char presse;
int anglex, angley, x, y, xold, yold;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void SpecialInput(int key, int x, int y);
void loadJpegImage(char *fichier);
void superglutSolidCylinder(double radius, double height, int div, bool enroule);

/*fonction main permattant de creer la page*/
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("ProjetB");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    /*creation de la texture de peau aplliquée sur les jambes*/
    loadJpegImage("skin.jpg");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largim, hautim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glEnable(GL_TEXTURE_2D);

    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutSpecialFunc(SpecialInput);

    glutMainLoop();
    return 0;
}

/*fonction d affichage creer la tortue en 3D */
void affichage()
{
    // Variables de données construction 3D

    float Lpied = 3, Hpied = 1, Ipied = 2;               /*dimensions des pieds */
    float Lsourcil = 1, Hsourcil = 0.25, Isourcil = 0.5; /*dimensions des sourcils*/
    float Sx = 0.25, Sz = 0.35, Sy = 1.5;

    float Bcone = 0.5, Hcone = 1; /*dimensions des cones*/
    float Bconeg = Hpied / 2.0, Hconeg = Bconeg * 2;
    float Bconec = 0.6, Hconec = 2.5;

    float Lbras = 2, Rbras = 1;          /*dimensions des bras*/
    float DecalG = 2, DecalD = -2;       /*decalage droite et gauche*/
    float DecalYD = -2;                  /* decallage en y vers l'avant*/
    float Intorus = 0.2, Outtorus = 0.6; /**/
    float haut = Hpied;                  /*valeur par defaut de la hauteur cumulé*/
    float Rrotule = 1;                   /*radius des rotules */

    float div = 20, /* division des surface divisable modifiable entre 10 et 50 pour pas trop de probleme */

        /* debut code */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    /*mode Ortho*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((-1) * view, view, (-1) * view, view, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);

    /*  Lumière ambiante blanche */
    GLfloat position[] = {5.0, 5.0, 5.0, 10.0};
    GLfloat amb[] = {1.0, 1.0, 1.0, 100.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glEnable(GL_LIGHT0);

    /*-----------------------------*/
    /*                             */
    /*  debut partie geometrique   */
    /*                             */
    /*-----------------------------*/

    /* Sol */
    glPushMatrix();
    glColor3d(0.5, 0.5, 0.5);
    glScalef(10, 2, 10);
    glTranslatef(0, -haut / 2.0, 0);
    glutSolidCube(1);
    glPopMatrix();

    //-----------------------------------------Jambe Gauche

    // Push d animation + animation
    glPushMatrix();
    glRotatef(intsens1, 0, -1, 0);

    // cone - piqueG
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG + DecalG / 3.0, haut, -Lpied + Lpied / 4.0);
    glRotatef(170, -1, 0, 0);
    glutSolidCone(Bconeg, Hconeg, div, div);
    glPopMatrix();

    // cone - piqueC
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG, haut, -Lpied + Lpied / 4.0);
    glRotatef(170, -1, 0, 0);
    glutSolidCone(Bconeg, Hconeg, div, div);
    glPopMatrix();

    // cone - piqueD
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG - DecalG / 3.0, haut, -Lpied + Lpied / 4.0);
    glRotatef(170, -1, 0, 0);
    glutSolidCone(Bconeg, Hconeg, div, div);
    glPopMatrix();

    // cube - piedG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalG, haut, -Lpied / 4.0);
    glRotatef(90, 0, 0 - 1, 0);
    glScalef(Lpied, Hpied, Ipied);
    glutSolidCube(1);
    glPopMatrix();

    // sphere - chevilleG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    haut += Hpied / 2.0;
    glTranslatef(DecalG, haut, 0);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    // cylindre - tibiaG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalG, haut + Hpied, 0);
    superglutSolidCylinder(Rbras, Lbras, div, enrou);
    glPopMatrix();

    /*Push Pop d'aniamtion entre tibia et genou*/
    glPopMatrix();
    glPushMatrix();
    glRotatef(intsens1, 1, 0, 0);

    // sphere - genouG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    haut += Lbras;
    glTranslatef(DecalG, haut, -0.2);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    // cylindre - cuisseG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalG, haut + Hpied, 0);
    superglutSolidCylinder(Rbras, Lbras, div, enrou);
    glPopMatrix();

    // Pop d'animation
    glPopMatrix();

    //-----------------------------------------Jambe Droite

    // Push d animation + animation
    glPushMatrix();
    glRotatef(intsens1, 0, 1, 0);

    haut = Hpied; // reset de haut pour la deuxieme jambe

    // cone - piqueG
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD + DecalD / 3.0, haut, -Lpied + Lpied / 4.0);
    glRotatef(170, -1, 0, 0);
    glutSolidCone(Bconeg, Hconeg, div, div);
    glPopMatrix();

    // cone - piqueC
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD, haut, -Lpied + Lpied / 4.0);
    glRotatef(170, -1, 0, 0);
    glutSolidCone(Bconeg, Hconeg, div, div);
    glPopMatrix();

    // cone - piqueD
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD - DecalD / 3.0, haut, -Lpied + Lpied / 4.0);
    glRotatef(170, -1, 0, 0);
    glutSolidCone(Bconeg, Hconeg, div, div);
    glPopMatrix();

    // cube - piedD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalD, haut, -Lpied / 4.0);
    glRotatef(90, 0, -1, 0);
    glScalef(Lpied, Hpied, Ipied);
    glutSolidCube(1);
    glPopMatrix();

    // sphere - chevilleD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    haut += Hpied / 2.0;
    glTranslatef(DecalD, haut, 0);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    // cylindre - tibiaD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalD, haut + Hpied, 0);
    superglutSolidCylinder(Rbras, Lbras, div, enrou);
    glPopMatrix();

    /*Push Pop d'aniamtion entre tibia et genou*/
    glPopMatrix();
    glPushMatrix();
    glRotatef(intsens1, -1, 0, 0);

    // sphere - genouD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    haut += Lbras;
    glTranslatef(DecalD, haut, -0.2);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    // cylindre - cuisseD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalD, haut + Hpied, 0);
    superglutSolidCylinder(Rbras, Lbras, div, enrou);
    glPopMatrix();

    // Pop d'animation
    glPopMatrix();

    //-----------------------------------------Queue

    // Push d animation
    glPushMatrix();

    /*Code permetant de faire osciller queue de 5 degres*/
    glRotatef(intsens, 0, 1, 0);
    if (intsens == 5)
        sens = false;
    if (intsens == -5)
        sens = true;
    if (sens)
        intsens++;
    else
        intsens--;

    // cone - base queue
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(0, haut, 2);
    glRotatef(30, 1, 0, 0);
    glRotatef(intsens, 1, 0, 0);
    glutSolidCone(Bcone * 3, Hcone * 4, div, div);
    glPopMatrix();

    // cones - piques queue
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0, haut + 0.25, 3.5);
    glRotatef(40, -1, 0, 0);
    glutSolidCone(Bcone / 2, Hcone / 2, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0, haut - 0.75, 4.25);
    glRotatef(40, -1, 0, 0);
    glutSolidCone(Bcone / 2, Hcone / 2, div, div);
    glPopMatrix();

    // Pop d animation
    glPopMatrix();

    //-----------------------------------------Carapace

    // sphere - carapace
    glPushMatrix();
    glColor3f(0, 0.7, 0);
    haut += Lbras - Lbras / 10.0;
    glRotatef(30, -1, 0, 0);
    glTranslatef(0, haut, 4);
    glScalef(4, 4, 2);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    //-----------------------------------------Base plastron

    // cylindre - base plastron
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotatef(30, -1, 0, 0);
    glTranslatef(0, haut, 2.5);
    glScalef(4, 4, 0.5);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    //-----------------------------------------Corps

    // sphere - base corps
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glRotatef(30, -1, 0, 0);
    glTranslatef(0, haut + 1, 2.5);
    glScalef(3, 3, 2);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    //-----------------------------------------Contour carapace

    // tore - contour carapace
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(30, -1, 0, 0);
    glTranslatef(0, haut, 3);
    glutSolidTorus(0.8, 4, div, 100);
    glPopMatrix();

    //-----------------------------------------Pique sur la carapace

    // cone - pique
    // premier rang à partir du haut
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0, haut + 4.5, 0);
    glRotatef(65, -1, 0, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    // deuxième rangée

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0, haut + 3.5, 1.5);
    glRotatef(45, -1, 0, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD, haut + 3.5, 1);
    glRotatef(45, -1, 0, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG, haut + 3.5, 1);
    glRotatef(45, -1, 0, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    // troisième rangée

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0, haut + 2, 2.5);
    glRotatef(35, -1, 0, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD - 1, haut + 2, 1.75);
    glRotatef(35, -1, 0, 0);
    glRotatef(20, 0, -1, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG + 1, haut + 2, 1.75);
    glRotatef(35, -1, 0, 0);
    glRotatef(20, 0, 1, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    // quatrième rangée

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0, haut + 0.25, 3.25);
    glRotatef(25, -1, 0, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD, haut + 0.25, 3);
    glRotatef(25, -1, 0, 0);
    glRotatef(20, 0, -1, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG, haut + 0.25, 3);
    glRotatef(25, -1, 0, 0);
    glRotatef(20, 0, 1, 0);
    glutSolidCone(Bcone, Hcone, div, div);
    glPopMatrix();

    //-----------------------------------------BrasD

    // sphere - epauleD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalD, haut * 1.5, DecalYD);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    // cylindre - brasD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 1;
    glTranslatef(DecalD, haut + 0.5, DecalYD);
    glRotatef(70, -1, 0, 0);
    glutSolidCylinder(Rbras, Lbras, div, div);
    glPopMatrix();

    // sphere - coudeD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 0.25;
    glTranslatef(DecalD, haut, DecalYD);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    glPushMatrix();
    glRotatef(intsens1, 1, 0, 0);

    // cylindre - avantbrasD
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 0.25;
    glTranslatef(DecalD, haut, DecalYD);
    glRotatef(180, -1, 0, 0);
    glutSolidCylinder(Rbras, Lbras, div, div);
    glPopMatrix();

    // sphere - base main
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= Rbras + Rrotule * 1.5;
    glTranslatef(DecalD, haut, DecalYD);
    glRotatef(90, -1, 0, 0);
    glScalef(1, 1.5, 1);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // spheres - doigtsD

    // majeur
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 1;
    glTranslatef(DecalD, haut, DecalYD);
    glRotatef(180, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();
    // annulaire

    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalD - 0.5, haut, DecalYD);
    glRotatef(20, 0, 1, 0);
    glRotatef(180, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();
    // index

    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalD + 0.5, haut, DecalYD);
    glRotatef(20, 0, -1, 0);
    glRotatef(180, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();
    // pouce

    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD += 1;
    glTranslatef(DecalD + 0.5, haut, DecalYD);
    glRotatef(50, 0, -1, 0);
    glRotatef(30, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // cones - griffesD
    // majeur

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    DecalYD -= Sy + 0.75;
    glTranslatef(DecalD, haut, DecalYD);
    glRotatef(180, -1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();
    // annulaire

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD - 1, haut, DecalYD);
    glRotatef(20, 0, 1, 0);
    glRotatef(180, -1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();
    // index

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalD + 1, haut, DecalYD);
    glRotatef(20, 0, -1, 0);
    glRotatef(180, -1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();
    // pouce

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    DecalYD += 1.5;
    glTranslatef(DecalD + 1.5, haut - 0.75, DecalYD);
    glRotatef(130, 0, 1, 0);
    glRotatef(30, 1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();

    glPopMatrix();

    //--------------------------------------------BrasG

    DecalYD = -2;

    // sphere - epauleG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalG, haut * 1.5, DecalYD);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    // cylindre - brasG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 1;
    glTranslatef(DecalG, haut + 0.5, DecalYD);
    glRotatef(70, -1, 0, 0);
    glutSolidCylinder(Rbras, Lbras, div, div);
    glPopMatrix();

    // sphere - coudeG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 0.25;
    glTranslatef(DecalG, haut, DecalYD);
    glutSolidSphere(Rrotule, div, div);
    glPopMatrix();

    glPushMatrix();
    glRotatef(intsens1, -1, 0, 0);

    // cylindre - avantbrasG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 0.25;
    glTranslatef(DecalG, haut, DecalYD);
    glRotatef(180, -1, 0, 0);
    glutSolidCylinder(Rbras, Lbras, div, div);
    glPopMatrix();

    // sphere - base mainG
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= Rbras + Rrotule * 1.5;
    glTranslatef(DecalG, haut, DecalYD);
    glRotatef(90, -1, 0, 0);
    glScalef(1, 1.5, 1);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // spheres - doigtsG

    // majeur
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD -= 1;
    glTranslatef(DecalG, haut, DecalYD);
    glRotatef(180, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();
    // index

    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalG - 0.5, haut, DecalYD);
    glRotatef(20, 0, 1, 0);
    glRotatef(180, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();
    // annulaire

    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(DecalG + 0.5, haut, DecalYD);
    glRotatef(20, 0, -1, 0);
    glRotatef(180, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();
    // pouce

    glPushMatrix();
    glColor3f(1, 0.5, 0);
    DecalYD += 1;
    glTranslatef(DecalG - 0.5, haut, DecalYD);
    glRotatef(50, 0, 1, 0);
    glRotatef(30, -1, 0, 0);
    glScalef(Sx, Sz, Sy);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // cones - griffesG

    // majeur
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    DecalYD -= Sy + 0.75;
    glTranslatef(DecalG, haut, DecalYD);
    glRotatef(180, -1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();
    // index

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG + 1, haut, DecalYD);
    glRotatef(20, 0, -1, 0);
    glRotatef(180, -1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();
    // annulaire

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(DecalG - 1, haut, DecalYD);
    glRotatef(20, 0, 1, 0);
    glRotatef(180, -1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();
    // pouce

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    DecalYD += 1.5;
    glTranslatef(DecalG - 1.5, haut - 0.75, DecalYD);
    glRotatef(50, 0, 1, 0);
    glRotatef(180, 1, 0, 0);
    glutSolidCone(Bconeg / 2.5, Hconeg, div, div);
    glPopMatrix();

    glPopMatrix();

    //-----------------------------------------Tête

    // sphere - visage
    glPushMatrix();
    glColor3f(0, 0.4, 0);
    haut += 6;
    glRotatef(30, -1, 0, 0);
    glTranslatef(0, haut, 4);
    glScalef(2, 2, 2);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // sphere - boucheCentre
    glPushMatrix();
    glColor3f(1, 0.87, 0.68);
    glRotatef(30, -1, 0, 0);
    glTranslatef(0, haut, 3);
    glScalef(1.5, 1.5, 1.5);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // sphere - joueD
    glPushMatrix();
    glColor3f(1, 0.87, 0.68);
    glRotatef(30, -1, 0, 0);
    glTranslatef(-1, haut, 3);
    glScalef(1.5, 1.5, 1.5);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // sphere - joueG
    glPushMatrix();
    glColor3f(1, 0.87, 0.68);
    glRotatef(30, -1, 0, 0);
    glTranslatef(1, haut, 3);
    glScalef(1.5, 1.5, 1.5);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // sphere - oeilD
    glPushMatrix();
    glColor3f(1, 1, 1);
    haut += Rrotule * 1.5;
    glRotatef(30, -1, 0, 0);
    glTranslatef(0.75, haut, 3.5);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // sphere - oeilG
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(30, -1, 0, 0);
    glTranslatef(-0.75, haut, 3.5);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(1, div, div);
    glPopMatrix();

    // cube - sourcilG
    glPushMatrix();
    glColor3f(1, 0, 0);
    haut += Rrotule / 2.0;
    glTranslatef(0.5, haut, -Lsourcil * 3.5);
    glRotatef(30, 0, -1, 3);
    glScalef(Lsourcil, Hsourcil, Isourcil);
    glutSolidCube(1);
    glPopMatrix();

    // cube - sourcilD
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-0.5, haut, -Lsourcil * 3.5);
    glRotatef(-30, 0, -1, 3);
    glScalef(Lsourcil, Hsourcil, Isourcil);
    glutSolidCube(1);
    glPopMatrix();

    // tore - base corneG
    glPushMatrix();
    glColor3f(0.4, 0, 0);
    glTranslatef(1.25, haut, -2);
    glRotatef(90, 1, 0, 0);
    glRotatef(45, 0, -1, 0);
    glutSolidTorus(Intorus, Outtorus, div, 100);
    glPopMatrix();

    // tore - base corneD
    glPushMatrix();
    glColor3f(0.4, 0, 0);
    glTranslatef(-1.25, haut, -2);
    glRotatef(90, -1, 0, 0);
    glRotatef(45, 0, -1, 0);
    glutSolidTorus(Intorus, Outtorus, div, 100);
    glPopMatrix();

    // cone - corneG
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(1.25, haut, -2);
    glRotatef(90, -1, 0, 0);
    glRotatef(45, 0, 1, 0);
    glutSolidCone(Bconec, Hconec, div, div);
    glPopMatrix();

    // cone - corneD
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(-1.25, haut, -2);
    glRotatef(90, -1, 0, 0);
    glRotatef(45, 0, -1, 0);
    glutSolidCone(Bconec, Hconec, div, div);
    glPopMatrix();

    /*-----------------------------*/
    /*                             */
    /*    fin partie geometrique   */
    /*                             */
    /*-----------------------------*/

    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

/*fonction du cylindre avec texture ( fonction primitive ) */
void superglutSolidCylinder(double radius, double height, int div, bool enroule)
{
    Point tab[div][2]; // tableau de points du Cylindre

    int i = 0;   // indice du tableau
    float x = 0; // valeur de x pour faite le tour du cercle

    /*creation  du tableau de Point*/
    while (x < 2 * pi)
    {

        tab[i][0].x = (radius * cos(x));
        tab[i][0].y = (radius * sin(x));
        tab[i][0].z = -height / 2.0;
        tab[i][1].x = (radius * cos(x));
        tab[i][1].y = (radius * sin(x));
        tab[i][1].z = height / 2.0;

        x += (2.0 / div) * (pi);
        i++;
    }

    /*Si on souhaite enrouler la texture sur plusieurs faces*/
    if (enroule)

    {

        float start = 0;
        float step = ((((2.0 * pi) / div) * 100) / (2 * pi)) / 100; // transforme le nobre de division du cylindre en pourcentage de x sur la texture

        for (int j = 0; j < div - 1; j++)
        {

            /*creation des faces du cylindre avec une texture enroule*/
            glBegin(GL_POLYGON);
            glTexCoord2d(start, 1.0);
            glVertex3d(tab[j][0].x, tab[j][0].z, tab[j][0].y);
            glTexCoord2d(start + step, 1.0);
            glVertex3d(tab[j + 1][0].x, tab[j + 1][0].z, tab[j + 1][0].y);
            glTexCoord2d(start + step, 0.0);
            glVertex3d(tab[j + 1][1].x, tab[j + 1][1].z, tab[j + 1][1].y);
            glTexCoord2d(start, 0.0);
            glVertex3d(tab[j][1].x, tab[j][1].z, tab[j][1].y);
            glEnd();
            start += step;
        }

        /*fait la dernier face qui dois ce racrocher a la premiere */
        glBegin(GL_POLYGON);
        glTexCoord2d(start, 1.0);
        glVertex3d(tab[div - 1][0].x, tab[div - 1][0].z, tab[div - 1][0].y);
        glTexCoord2d(start + step, 1.0);
        glVertex3d(tab[0][0].x, tab[0][0].z, tab[0][0].y);
        glTexCoord2d(start + step, 0.0);
        glVertex3d(tab[0][1].x, tab[0][1].z, tab[0][1].y);
        glTexCoord2d(start, 0.0);
        glVertex3d(tab[div - 1][1].x, tab[div - 1][1].z, tab[div - 1][1].y);
        glEnd();
    }

    /*Si on ne souhaite pas enrouler la texture sur plusieurs faces*/
    else
    {
        for (int j = 0; j < div - 1; j++)
        {
            /*creation des faces du cylindre avec une texture par face*/
            glBegin(GL_POLYGON);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(tab[j][0].x, tab[j][0].z, tab[j][0].y);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(tab[j + 1][0].x, tab[j + 1][0].z, tab[j + 1][0].y);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(tab[j + 1][1].x, tab[j + 1][1].z, tab[j + 1][1].y);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(tab[j][1].x, tab[j][1].z, tab[j][1].y);
            glEnd();
        }

        /*fait la dernier face qui dois ce racrocher a la premiere */
        glBegin(GL_POLYGON);
        glTexCoord2d(1.0, 1.0);
        glVertex3d(tab[div - 1][0].x, tab[div - 1][0].z, tab[div - 1][0].y);
        glTexCoord2d(0.0, 1.0);
        glVertex3d(tab[0][0].x, tab[0][0].z, tab[0][0].y);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(tab[0][1].x, tab[0][1].z, tab[0][1].y);
        glTexCoord2d(1.0, 0.0);
        glVertex3d(tab[div - 1][1].x, tab[div - 1][1].z, tab[div - 1][1].y);
        glEnd();
    }
}

/* Fonction fournis pour transformer une image jpeg en tableau */
void loadJpegImage(char *fichier)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
#ifdef __WIN32
    if (fopen_s(&file, fichier, "rb") != 0)
    {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
#elif __GNUC__
    if ((file = fopen(fichier, "rb")) == 0)
    {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier \n");
        exit(1);
    }
#endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if ((cinfo.image_width != largim) || (cinfo.image_height != hautim))
    {
        fprintf(stdout, "Erreur : l'image doit etre de taille %d x %d\n", largim, hautim);
        exit(1);
    }
    if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
    {
        fprintf(stdout, "Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne = image;

    while (cinfo.output_scanline < cinfo.output_height)
    {
        ligne = image + 3 * largim * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, &ligne, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            texture[i][j][0] = image[i * 256 * 3 + j * 3];
            texture[i][j][1] = image[i * 256 * 3 + j * 3 + 1];
            texture[i][j][2] = image[i * 256 * 3 + j * 3 + 2];
        }
    }
}

/*fonction fournis pour les input du clavier */
void clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {

    case 'p': /*affiche en polygone */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;

    case 'f': /* affichage en fil de fer */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
        break;

    case 's': /* affichage en sommets seuls */
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutPostRedisplay();
        break;

    case 'd': /*met la profondeur */
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;

    case 'D': /* retire la profondeur */
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;

    case 'a': // Les faces à l'envers s'affichent en fil de fer
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_FRONT, GL_LINE);
        glutPostRedisplay();
        break;

    case 'b': /* choisi si on enroule ou pas les textures */
        enrou = !(enrou);
        break;

    case 'z': /* Dezoom */
        if (view < 20)
            view++;
        glutPostRedisplay();
        break;
    case 'Z': /* Zoom */
        if (view > 2)
            view--;
        glutPostRedisplay();
        break;

    case 'r': /* anime les pates et les jambes */
        if (intsens1 == 3)
            sens1 = false;
        if (intsens1 == -3)
            sens1 = true;
        if (sens1)
            intsens1++;
        else
            intsens1--;
        glutPostRedisplay();
        break;

    case 'q': /* quitte l'executable */
        exit(0);
    }
}

/*fonction fournis pour les input du clavier */
void SpecialInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: /* bouge la camera vers le bas */
        angley -= 2;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN: /* bouge la camera vers le haut */
        angley += 2;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT: /* bouge la camera vers le droite */
        anglex -= 2;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT: /* bouge la camera vers le gauche */
        anglex += 2;
        glutPostRedisplay();
        break;
    }
}

/*fonction fournis permettant le redimensionement de la fenetre */
void reshape(int x, int y)
{
    if (x < y)
        glViewport(0, (y - x) / 2, x, x);
    else
        glViewport((x - y) / 2, 0, y, y);
}

/*fonction fournis pour les boutons de la souris*/
void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presse = 1;
        xold = x;
        yold = y;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse = 0;
}

/* fonction fournis permetant une camera orbit */
void mousemotion(int x, int y)
{
    if (presse)
    {
        position sauvegardee
            anglex = anglex + (x - xold);
        angley = angley + (y - yold);
        glutPostRedisplay();
    }

    xold = x;
    yold = y;
}
