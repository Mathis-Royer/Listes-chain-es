#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


// Fonction qui permet de créer un élement d'une liste chaînée
// Params : indice de colonne (int), valeur de l'élement (int)
// Return : pointeur vers le nouvele élement créé
element* creerElement(int colonne, int valeur) {
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->col = colonne;
    nouvelElement->val = valeur;
    nouvelElement->suivant = NULL;
    return nouvelElement;
}


void remplirMatrice(matrice_creuse *m, int N, int M){
  m->Nlignes = N;
  m->Ncolonnes = M;
  m->tab_lignes = malloc(N*sizeof(liste_ligne));
  if(m->tab_lignes == NULL) printf("Erreur d'allocation du tab_lignes");

  for(int k=0; k<N; k++) m->tab_lignes[k] = NULL;

  element* element1 = NULL;
  element* elementPrecedent = NULL;

  int val = 0;
  int indiceDebutLigne = 0; //variable permettant de connaitre l'indice de la colonne du premier element d'une ligne

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      printf("valeur de l'élement de la colonne %d et de la ligne %d : ", j, i);
      scanf("%d", &val);
      
      if(val!=0){
        element1 = creerElement(j,val);
        if(j!=indiceDebutLigne) elementPrecedent->suivant = element1; //si ce n'est pas le premier element
        elementPrecedent = element1;
      }

      /*enregistrement du premier element*/
      if(j==indiceDebutLigne && val!=0){
        m->tab_lignes[i] = element1;
        indiceDebutLigne = -1;  //egale -1 pour signifier que le premier element a ete enregistre
      }
      else if(indiceDebutLigne!=-1) indiceDebutLigne++; //tant que le premier element n'est pas enregistre
    }
    indiceDebutLigne = 0;
  }
}


void afficherMatrice(matrice_creuse* m){
  printf("\n\n");

  liste_ligne listeLigne = NULL;

  for(int k=0; k<m->Nlignes; k++){
    listeLigne = m->tab_lignes[k];  //enregistre le premier element de la ligne k

    if(listeLigne->col>=0 && listeLigne->col<=m->Ncolonnes){
      for(int i=0; i<m->Ncolonnes; i++){

        if(listeLigne != NULL && listeLigne->col == i){
          printf("%d\t", listeLigne->val);  // affiche l'element si sa colonne correspond à l'indice i et s'il reste des valeurs à afficher
          listeLigne = listeLigne->suivant; // enregistrer l'element suivant
        }
        else printf("0\t"); //sinon afficher 0
      }
    }
    printf("\n");
  }
}

void afficherMatriceListes(matrice_creuse *m){
  liste_ligne colonne = NULL;
  printf("\n\n");

  for(int j=0; j<m->Nlignes; j++){
    colonne = m->tab_lignes[j];

    printf("[");

    if(colonne != NULL){

      for(int l=0; l<m->Ncolonnes; l++){

        printf("[col=%d ; val=%d]",colonne->col,colonne->val);
        if(colonne->suivant != NULL) colonne = colonne->suivant;
        else break;
      }
    }
    printf("]\n");
  }
}

int rechercherValeur(matrice_creuse* m, int i, int j){
  int val = 0;
  liste_ligne elementLigneI = m->tab_lignes[i];

  /*Parcours de chaque colonnes de la ligne i jusqu'à l'indice j*/
  for(int k=0; k<=j; k++){

    if(elementLigneI->col == j){
      val = elementLigneI->val;
      break;
    }
    else elementLigneI = elementLigneI->suivant;
  }
  return val; 
}

void affecterValeur(matrice_creuse* m, int i, int j, int val) {
  liste_ligne elementLigneI = m->tab_lignes[i];
  liste_ligne elementPrecedent = NULL;

  if(j>=m->Ncolonnes) printf("Error : l'indice de la colonne du nouvel element doit être inférieur à %d", m->Ncolonnes);
  if(val==0) return;

  for(int k=0; k<m->Ncolonnes; k++){
    /*Si l'on remplace une valeur deja existante*/
    if(elementLigneI != NULL && elementLigneI->col == j){
      elementLigneI->val = val;
      break;
    }

    /*Si l'on créée une nouvelle valeur en début de ligne non NULL*/
    else if(elementLigneI !=NULL && j<elementLigneI->col){
      element* nouvelElement = creerElement(j, val);
      nouvelElement->suivant = elementLigneI;
      m->tab_lignes[i] = nouvelElement;
      break;
    }

    /*Si l'on créé une nouvelle valeur en fin de ligne non NULL*/
    else if(elementLigneI != NULL && elementLigneI->suivant==NULL){
      element* nouvelElement = creerElement(j, val);
      elementLigneI->suivant = nouvelElement;
      break;
    }

    /*Si l'on créé une nouvelle valeur dans une ligne NULL*/
    else if(elementLigneI == NULL){
      element* nouvelElement = creerElement(j,val);
      m->tab_lignes[i] = nouvelElement;
      break;
    }

    elementPrecedent = elementLigneI;
    elementLigneI = elementLigneI->suivant;
  }
}

void additionerMatrices(matrice_creuse* m1, matrice_creuse* m2){
  liste_ligne elementLigneKM1 = NULL;
  liste_ligne elementLigneKM1Precedent = NULL;
  liste_ligne elementLigneKM2 = NULL;

  for(int k=0; k<m1->Nlignes; k++){
    elementLigneKM1 = m1->tab_lignes[k];
    elementLigneKM1Precedent = NULL;
    elementLigneKM2 = m2->tab_lignes[k];

    for(int i=0; i<m1->Ncolonnes; i++){
      if(elementLigneKM2 != NULL){

        /*si l'on additionne deux valeurs non nulles*/
        if(elementLigneKM1 != NULL && elementLigneKM2 != NULL && elementLigneKM1->col == elementLigneKM2->col){
          elementLigneKM1->val = elementLigneKM1->val + elementLigneKM2->val;

          elementLigneKM1Precedent = elementLigneKM1;
          elementLigneKM1 = elementLigneKM1->suivant;
          elementLigneKM2 = elementLigneKM2->suivant;
        }

        /*Si l'on additionne une valeur de m1 nulle et une valeur de m2 non nulle*/
        /*En milieu et en fin de ligne NON NULL*/
        else if(elementLigneKM2 != NULL && (elementLigneKM1 == NULL || (elementLigneKM1 != NULL && elementLigneKM1->col > elementLigneKM2->col)) && elementLigneKM1Precedent != NULL){
          element* nouvelElement = creerElement(elementLigneKM2->col,elementLigneKM2->val);
          nouvelElement->suivant = elementLigneKM1;
          elementLigneKM1Precedent->suivant = nouvelElement;

          elementLigneKM2 = elementLigneKM2->suivant;
        }

        /*Si l'on additionne une valeur de m1 nulle et une valeur de m2 non nulle*/
        /*En début de ligne NON NULL*/
        else if(elementLigneKM1Precedent == NULL && elementLigneKM1 != NULL && elementLigneKM2 != NULL && elementLigneKM1->col > elementLigneKM2->col){
          element* nouvelElement = creerElement(elementLigneKM2->col,elementLigneKM2->val);
          nouvelElement->suivant = elementLigneKM1;
          m1->tab_lignes[k] = nouvelElement;

          elementLigneKM2 = elementLigneKM2->suivant;
        }

        /*Si l'on additionne une valeur de m1 nulle et une valeur de m2 non nulle*/
        /*En début de ligne NULL*/
        else if(elementLigneKM1Precedent == NULL && elementLigneKM1 == NULL && elementLigneKM2 != NULL){
          element* nouvelElement = creerElement(elementLigneKM2->col,elementLigneKM2->val);
          m1->tab_lignes[k] = nouvelElement;

          elementLigneKM1 = m1->tab_lignes[k];
          elementLigneKM2 = elementLigneKM2->suivant;
        }
      }
    }
  }
}

int nombreOctetsGagnes(matrice_creuse* m) {
  int espaceMatricePleine = m->Ncolonnes*m->Nlignes*(2*sizeof(int) + sizeof(element*));
  int nombreElements = 0;
  liste_ligne elementLigneK = NULL;

  for(int k=0; k<m->Nlignes; k++){
    elementLigneK = m->tab_lignes[k];

    for(int i=0; i<m->Ncolonnes; i++){
      if(elementLigneK == NULL) break;
      nombreElements++;
      elementLigneK = elementLigneK->suivant;
    }
  }
  int espaceMemoireEconomise = espaceMatricePleine - nombreElements*(2*sizeof(int) + sizeof(element*));

  return espaceMemoireEconomise;
}


/*void main(){
  matrice_creuse m;
  remplirMatrice(&m, 3, 4);
  printf("%d", nombreOctetsGagnes(&m));
  afficherMatrice(&m);
  afficherMatriceListes(&m);
  printf("%d", rechercherValeur(&m,1,2));
  affecterValeur(&m, 0, 1, 33);
  affecterValeur(&m, 2, 1, 55);
  affecterValeur(&m, 1, 0, 66);
  affecterValeur(&m, 1, 3, 44);
  afficherMatrice(&m);
  
  /*matrice_creuse m1;
  remplirMatrice(&m1, 3, 4);
  afficherMatriceListes(&m1);

  matrice_creuse m2;
  remplirMatrice(&m2, 3, 4);
  afficherMatriceListes(&m2);

  additionerMatrices(&m1, &m2);
  afficherMatrice(&m1);

  for(int k=0; k<m1.Nlignes;k++){
    free(m1.tab_lignes[k]);
    free(m2.tab_lignes[k]);
  }
}*/