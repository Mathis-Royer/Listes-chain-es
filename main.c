#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"
#include "tp3.c"


int main(){
    int menu = 0;
    int choixmat, ligne = 0, colonne = 0, valeur;
    matrice_creuse m1, m2;
    do{
        printf("1. Remplir une matrice creuse\n");
        printf("2. Afficher une matrice creuse sous forme de tableau\n");
        printf("3. Afficher une matrice creuse sous forme de listes\n");
        printf("4. Donner la valeur d un element d une matrice creuse\n");
        printf("5. Affecter une valeur a un element d une matrice creuse\n");
        printf("6. Additionner deux matrices creuses\n");
        printf("7. Calculer le gain en espace en utilisant cette repr�sentation pour une matrice donnee\n");
        printf("8. Quitter\n");
        printf("\n");
        do{
            scanf("%d",&menu);
        }while(menu < 1 && menu > 7);

        switch (menu){
            case 1:
                if (ligne == 0 && colonne == 0){
                    printf("Quelles sont les dimensions de votre matrice? (lignes puis colonnes)\n");
                    scanf("%d",&ligne);
                    scanf("%d",&colonne);
                }

                printf("Quelle matrice voulez vous remplir? (1 ou 2)\n");
                do{
                    scanf("%d",&choixmat);
                }while(choixmat != 1 && choixmat != 2);

                if(choixmat == 1) remplirMatrice(&m1, ligne, colonne);
                else remplirMatrice(&m2, ligne, colonne);

                printf("\n");
                break;


            case 2:
                printf("Quelle matrice voulez-vous afficher? (1 ou 2)\n");
                do{
                    scanf("%d",&choixmat);
                }while(choixmat != 1 && choixmat != 2);

                if(choixmat == 1) afficherMatrice(&m1);
                else afficherMatrice(&m2);

                printf("\n");
                break;


            case 3:
                printf("Quelle matrice voulez-vous afficher en listes? (1 ou 2)\n");
                do{
                    scanf("%d",&choixmat);
                }while(choixmat != 1 && choixmat != 2);

                if(choixmat == 1) afficherMatriceListes(&m1);
                else afficherMatriceListes(&m2);

                printf("\n");
                break;


            case 4:
                printf("Dans quelle matrice voulez-vous rechercher? (1 ou 2)\n");
                do{
                    scanf("%d",&choixmat);
                }while(choixmat != 1 && choixmat != 2);

                printf("Donnez les coordonnees de la valeur à rechercher (ligne puis colonne)\n");
                scanf("%d",&ligne);
                scanf("%d",&colonne);

                if(choixmat == 1) valeur = rechercherValeur(&m1, ligne, colonne);
                else valeur = rechercherValeur(&m2, ligne, colonne);

                printf("L element de la ligne %d et de la colonne %d a comme valeur %d", ligne, colonne, valeur);
                printf("\n\n");
                break;


            case 5:
                printf("Dans quelle matrice voulez-vous remplacer un element? (1 ou 2)\n");
                do{
                    scanf("%d",&choixmat);
                }while(choixmat != 1 && choixmat != 2);

                printf("Donnez l'element à remplacer (ligne puis colonne)\n");
                scanf("%d",&ligne);
                scanf("%d",&colonne);

                printf("Donnez la valeur a affecter\n");
                scanf("%d",&valeur);
                if(choixmat == 1) {
                    affecterValeur(&m1, ligne, colonne, valeur);
                    afficherMatriceListes(&m1);
                }
                else {
                    affecterValeur(&m2, ligne, colonne, valeur);
                    afficherMatriceListes(&m2);
                }
                printf("\n");
                break;


            case 6:
                additionerMatrices(&m1, &m2);
                afficherMatriceListes(&m1);

                printf("\n");
                break;


            case 7:
                printf("De quelle matrice voulez-vous calculer le nombre d octets gagnes? (1 ou 2)\n");
                do{
                    scanf("%d",&choixmat);
                }while(choixmat != 1 && choixmat != 2);

                if (choixmat == 1) valeur = nombreOctetsGagnes(&m1);
                else valeur = nombreOctetsGagnes(&m2);

                printf("%d octets ont ete gagnes grace � la representation de cette matrice creuse", valeur);
                printf("\n");
                break;
        }

    }while(menu != 8);
    free(m1.tab_lignes);
    free(m2.tab_lignes);
    return 0;
}
