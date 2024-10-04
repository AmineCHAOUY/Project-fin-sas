#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESERVATIONS 100
#define PASSWORD "123456"

typedef struct {
    int jour;
    int mois;
    int annee;
} date;


typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[15];
    int age;
    char statut[20];
    char reference[20];
    date date_reservation;
} personne;


personne reservations[MAX_RESERVATIONS];
int reservation_count = 0;

// Function prototypes
int password();
void clearBuffer();
void ajouter_reservation();
void modifier_reservation();
void supprimer_reservation();
void afficher_details();
void trier_reservations_par_nom();
void rechercher_reservation();
void statistiques();
void initialiser_reservations();
void mune();

int main() {
    mune(); 
    return 0;
}


void mune() {

    initialiser_reservations();
    int choice;

    do {
          //  system("cls");
        printf("\nMenu Principal : \n");
        printf("1. Ajouter une réservation\n");
        printf("2. Modifier une réservation\n");
        printf("3. Supprimer une réservation\n");
        printf("4. Afficher les détails d'une réservation\n");
        printf("5. Trier les réservations par Nom\n");
        printf("6. Rechercher une réservation\n");
        printf("7. Statistiques\n");
        printf("8. Exit\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: ajouter_reservation(); break;
            case 2: modifier_reservation(); break;
            case 3: supprimer_reservation(); break;
            case 4: afficher_details(); break;
            case 5: trier_reservations_par_nom(); break;
            case 6: rechercher_reservation(); break;
            case 7: statistiques(); break;
            case 8: printf("Merci et au revoir!\n"); break;
            default: printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 8);
}

int password() {
    char input_password[20];
    printf("Entrez le mot de passe : ");
    scanf("%s", input_password);

    if (strcmp(input_password, PASSWORD) == 0) {
        return 1;
    } else {
        printf("Mot de passe incorrect !\n");
        return 0;
    }
}
void initialiser_reservations() {

    for (int i = 0; i < 10; i++) {
        snprintf(reservations[i].nom, sizeof(reservations[i].nom), "Nom%d", i + 1);
        snprintf(reservations[i].prenom, sizeof(reservations[i].prenom), "Prenom%d", i + 1);
        reservations[i].age = 20 + (i % 10);

        snprintf(reservations[i].telephone, sizeof(reservations[i].telephone), "01234567%d", i);
        snprintf(reservations[i].statut, sizeof(reservations[i].statut), "validé");
        reservations[i].date_reservation.jour = 1 + (i % 28);
        reservations[i].date_reservation.mois = 1 + (i % 12);
        reservations[i].date_reservation.annee = 2024;

        snprintf(reservations[i].reference, sizeof(reservations[i].reference), "REF%d", i + 1);
    }
    reservation_count = 10;
}

void ajouter_reservation() {
    clearBuffer();
    if (reservation_count >= MAX_RESERVATIONS) {
        printf("Limite de réservations atteinte.\n");
        return;
    }

    personne new_reservation;
    int choice;

    do {
        printf("1. Déjà client\n");
        printf("2. Nouvelle client\n");
        printf("3. Retourner\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        if (choice == 1) {
            char reference[20];
            printf("Entrez votre référence : ");
            scanf("%s", reference);

            int found = 0;
            for (int i = 0; i < reservation_count; i++) {
                if (strcmp(reservations[i].reference, reference) == 0) {
                    found = 1;
                    printf("Informations trouvées :\n");
                    printf("Téléphone: %s, Âge: %d\n", reservations[i].telephone, reservations[i].age);
                    printf("Entrez la Date de réservation (jj mm aaaa): ");
                    scanf("%d %d %d", &new_reservation.date_reservation.jour,
                          &new_reservation.date_reservation.mois,
                          &new_reservation.date_reservation.annee);
                    new_reservation = reservations[i];
                    break;
                }
            }

            if (!found) {
                printf("Désolé, client non trouvé.\n");
            }
        }

        if (choice == 2) {
            printf("Entrez votre Nom: ");
            scanf("%s", new_reservation.nom);
            printf("Entrez votre Prénom: ");
            scanf("%s", new_reservation.prenom);
            printf("Entrez votre Âge: ");
            scanf("%d", &new_reservation.age);
            printf("Entrez votre Téléphone: ");
            scanf("%s", new_reservation.telephone);
            printf("Entrez le Statut (validé, reporté, annulé, traité): ");
            scanf("%s", new_reservation.statut);
            printf("Entrez la Date de réservation (jj mm aaaa): ");
            scanf("%d %d %d", &new_reservation.date_reservation.jour,
                  &new_reservation.date_reservation.mois,
                  &new_reservation.date_reservation.annee);

            snprintf(new_reservation.reference, sizeof(new_reservation.reference), "REF%d", reservation_count + 1);
            reservations[reservation_count] = new_reservation;
            reservation_count++;
            printf("Réservation ajoutée avec succès. Référence : %s\n", new_reservation.reference);
        }

    } while (choice != 3);

    printf("Au revoir!\n");
}

void modifier_reservation() {
    char reference[20];
    printf("Entrez la référence de la réservation à modifier : ");
    scanf("%s", reference);

    for (int i = 0; i < reservation_count; i++) {
        if (strcmp(reservations[i].reference, reference) == 0) {
            printf("Modifier les informations pour %s %s:\n", reservations[i].nom, reservations[i].prenom);
            printf("Entrez votre Nom: ");
            scanf("%s", reservations[i].nom);
            printf("Entrez votre Prénom: ");
            scanf("%s", reservations[i].prenom);
            printf("Entrez votre Âge: ");
            scanf("%d", &reservations[i].age);
            printf("Entrez votre Téléphone: ");
            scanf("%s", reservations[i].telephone);
            printf("Entrez le Statut (validé, reporté, annulé, traité): ");
            scanf("%s", reservations[i].statut);
            printf("Entrez la Date de réservation (jj mm aaaa): ");
            scanf("%d %d %d", &reservations[i].date_reservation.jour,
                  &reservations[i].date_reservation.mois,
                  &reservations[i].date_reservation.annee);
            printf("Réservation modifiée avec succès.\n");
            return;
        }
    }
    printf("Réservation non trouvée.\n");
}

void supprimer_reservation() {
    char reference[20];
    printf("Entrez la référence de la réservation à supprimer : ");
    scanf("%s", reference);

    for (int i = 0; i < reservation_count; i++) {
        if (strcmp(reservations[i].reference, reference) == 0) {
            for (int j = i; j < reservation_count - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            reservation_count--;
            printf("Réservation supprimée avec succès.\n");
            return;
        }
    }
    printf("Réservation non trouvée.\n");
}

void afficher_details() {
    char reference[20];
    printf("Entrez la référence de la réservation à afficher : ");
    scanf("%s", reference);

    for (int i = 0; i < reservation_count; i++) {
        if (strcmp(reservations[i].reference, reference) == 0) {
            printf("Détails de la réservation :\n");
            printf("Nom: %s\n", reservations[i].nom);
            printf("Prénom: %s\n", reservations[i].prenom);
            printf("Âge: %d\n", reservations[i].age);
            printf("Téléphone: %s\n", reservations[i].telephone);
            printf("Statut: %s\n", reservations[i].statut);
            printf("Date de réservation: %02d/%02d/%04d\n",
                   reservations[i].date_reservation.jour,
                   reservations[i].date_reservation.mois,
                   reservations[i].date_reservation.annee);
            return;
        }
    }
    printf("Réservation non trouvée.\n");
}

void trier_reservations_par_nom() {
    if (!password()) {
        return;
    }

    for (int i = 0; i < reservation_count - 1; i++) {
        for (int j = i + 1; j < reservation_count; j++) {
            if (strcmp(reservations[i].nom, reservations[j].nom) > 0) {
                personne temp = reservations[i];
                reservations[i] = reservations[j];
                reservations[j] = temp;
            }
        }
    }
    printf("Réservations triées par nom.\n");
}

void rechercher_reservation() {
    char nom[50];
    printf("Entrez le nom à rechercher : ");
    scanf("%s", nom);

    for (int i = 0; i < reservation_count; i++) {
        if (strcmp(reservations[i].nom, nom) == 0) {
            printf("Réservation trouvée :\n");
            printf("Nom: %s\n", reservations[i].nom);
            printf("Prénom: %s\n", reservations[i].prenom);
            printf("Téléphone: %s\n", reservations[i].telephone);
            printf("Âge: %d\n", reservations[i].age);
            printf("Statut: %s\n", reservations[i].statut);
            printf("Date de réservation: %02d/%02d/%04d\n",
                   reservations[i].date_reservation.jour,
                   reservations[i].date_reservation.mois,
                   reservations[i].date_reservation.annee);
            return;
        }
    }
    printf("Aucune réservation trouvée pour ce nom.\n");
}

void statistiques() {
    if (!password()) {
        return;
    }

    int total_age = 0;
    int count_0_18 = 0, count_19_35 = 0, count_36_plus = 0;

    for (int i = 0; i < reservation_count; i++) {
        total_age += reservations[i].age;

        if (reservations[i].age >= 0 && reservations[i].age <= 18) {
            count_0_18++;
        } else if (reservations[i].age >= 19 && reservations[i].age <= 35) {
            count_19_35++;
        } else {
            count_36_plus++;
        }
    }

    if (reservation_count > 0) {
        double moyenne_age = (double)total_age / reservation_count;
        printf("Moyenne d'âge des patients : %.2f\n", moyenne_age);
    } else {
        printf("Aucune réservation disponible pour le calcul des statistiques.\n");
    }

    printf("Nombre de patients par tranche d'âge :\n");
    printf("0-18 ans : %d\n", count_0_18);
    printf("19-35 ans : %d\n", count_19_35);
    printf("36 ans et plus : %d\n", count_36_plus);
}

void clearBuffer() {
    while (getchar() != '\n');
}