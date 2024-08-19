#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SpeciesNode {
    char class[50];
    char order[50];
    char family[50];
    char genus[50];
    char species[50];
    struct SpeciesNode* next;
} SpeciesNode;

void addSpecies(SpeciesNode** head);
void modifySpecies(SpeciesNode* head);
void deleteSpecies(SpeciesNode** head);
void sortSpecies(SpeciesNode** head, int criteria);
void printMenu(void);
int comparee(SpeciesNode* a, SpeciesNode* b, int criteria);
void printList(SpeciesNode* head);
int main(void) {
    SpeciesNode* head = NULL;
    int choice;
    int criteria;
    while (1) {
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addSpecies(&head);
                printList(head);
                break;
            case 2:
                modifySpecies(head);
                printList(head);
                break;
            case 3:
                deleteSpecies(&head);
                printList(head);
                break;
            case 4:
                
                printf("Sort by (1)Class, (2)Order, (3)Family, (4)Genus, (5)Species: ");
                scanf("%d", &criteria);
                sortSpecies(&head, criteria);
                printList(head);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void printList(SpeciesNode* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    
    SpeciesNode* current = head;
    while (current != NULL) {
        printf("Class: %s\nOrder: %s\nFamily: %s\nGenus: %s\nSpecies: %s\n",
               current->class, current->order, current->family, current->genus, current->species);
        current = current->next;
    }
}

void printMenu(void) {
    printf("\nMenu:\n");
    printf("1. Add Species\n");
    printf("2. Modify Species\n");
    printf("3. Delete Species\n");
    printf("4. Sort Species\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}
void addSpecies(SpeciesNode** head) {
    SpeciesNode* newNode = (SpeciesNode*)malloc(sizeof(SpeciesNode));
    printf("Enter Species information: \n");
    printf("Class: ");
    scanf("%s", newNode->class);
    printf("Order: ");
    scanf("%s", newNode->order);
    printf("Family: ");
    scanf("%s", newNode->family);
    printf("Genus: ");
    scanf("%s", newNode->genus);
    printf("Species: ");
    scanf("%s", newNode->species);
    
    newNode->next = *head;
    *head = newNode;
    
    printf("Species added successfully!\n");
}

void modifySpecies(SpeciesNode* head) {
    char speciesToModify[50];
    printf("Enter the species name to modify: ");
    scanf("%s", speciesToModify);
    
    SpeciesNode* current = head;
    while (current != NULL) {
        if (strcmp(current->species, speciesToModify) == 0) {
            printf("Enter new class: ");
            scanf("%s", current->class);
            printf("Enter new order: ");
            scanf("%s", current->order);
            printf("Enter new family: ");
            scanf("%s", current->family);
            printf("Enter new genus: ");
            scanf("%s", current->genus);
            printf("Enter new species: ");
            scanf("%s", current->species);
            printf("Species information modified successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Species not found!\n");
}

void deleteSpecies(SpeciesNode** head) {
    char speciesToDelete[50];
    printf("Enter the species name to delete: ");
    scanf("%s", speciesToDelete);
    
    SpeciesNode *temp = *head, *prev = NULL;
    
    while (temp != NULL && strcmp(temp->species, speciesToDelete) == 0) {
        *head = temp->next;
        free(temp);
        temp = *head;
    }
    
    while (temp != NULL) {
        while (temp != NULL && strcmp(temp->species, speciesToDelete) != 0) {
            prev = temp;
            temp = temp->next;
        }
        
        if (temp == NULL) return;
        
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
    printf("Species deleted successfully!\n");
}

void sortSpecies(SpeciesNode** head, int criteria) {
    if (*head == NULL || (*head)->next == NULL) return;
    
    SpeciesNode* sorted = NULL;
    SpeciesNode* current = *head;
    
    while (current != NULL) {
        SpeciesNode* next = current->next;
        if (sorted == NULL || comparee(current, sorted, criteria) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            SpeciesNode* temp = sorted;
            while (temp->next != NULL && comparee(current, temp->next, criteria) >= 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
    printf("Species sorted successfully!\n");
}

int comparee(SpeciesNode* a, SpeciesNode* b, int criteria) {
    switch (criteria) {
        case 1: return strcmp(a->class, b->class);
        case 2: return strcmp(a->order, b->order);
        case 3: return strcmp(a->family, b->family);
        case 4: return strcmp(a->genus, b->genus);
        case 5: return strcmp(a->species, b->species);
        default: return 0;
    }
}



