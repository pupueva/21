//21 ����

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define SIZE 5

// ����������� ��������� Cornice
typedef struct Cornice {
    int length;
    int ceilingWidth;
    int wallHeight;
    char material[20];
} cornice_t;

// ��������� �������
void fillCornicesArray(cornice_t* cornices, int size);
void print_cornice(cornice_t cornice);
void print_array(cornice_t* cornices, int size);
cornice_t* search_material(cornice_t* cornices, int size, char* material);
int compare(const void* a, const void* b);
void sort_array(cornice_t* cornices, int size);
int output_file(char* filename, cornice_t* cornices, int size);
int input_file(char* filename, cornice_t* cornices);

// ������� ��������� ���������� �����
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// ������������� ������� ���������� ����������
void fillCornicesArray(cornice_t* cornices, int size) {
    srand(time(NULL));
    const char* materials[] = { "Wood", "Aluminium", "Plastic", "Steel", "Metal" };
    for (int i = 0; i < size; i++) {
        cornices[i].length = getRandomNumber(1, 10);
        cornices[i].ceilingWidth = getRandomNumber(1, 5);
        cornices[i].wallHeight = getRandomNumber(2, 8);
        strcpy(cornices[i].material, materials[getRandomNumber(0, 4)]);
    }
}

// ����� ����� ������
void print_cornice(cornice_t cornice) {
    printf("| %d mm | %d mm | %d mm | %s |\n",
        cornice.length, cornice.ceilingWidth, cornice.wallHeight, cornice.material);
}

// ����� ������� �������
void print_array(cornice_t* cornices, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d. ", i + 1);
        print_cornice(cornices[i]);
    }
}

// ����� �� ���������
cornice_t* search_material(cornice_t* cornices, int size, char* material) {
    for (int i = 0; i < size; i++) {
        if (strcmp(cornices[i].material, material) == 0) {
            return &cornices[i];
        }
    }
    return NULL;
}

// ������� ��������� ��� qsort
int compare(const void* a, const void* b) {
    const cornice_t* corniceA = (const cornice_t*)a;
    const cornice_t* corniceB = (const cornice_t*)b;

    int areaA = corniceA->length * corniceA->ceilingWidth;
    int areaB = corniceB->length * corniceB->ceilingWidth;

    return (areaA - areaB);
}

// ���������� �������
void sort_array(cornice_t* cornices, int size) {
    qsort(cornices, size, sizeof(cornice_t), compare);
}

// ������ ������� � ����
int output_file(char* filename, cornice_t* cornices, int size) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("������ �������� ����� ��� ������");
        return -1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d %d %d %s\n",
            cornices[i].length,
            cornices[i].ceilingWidth,
            cornices[i].wallHeight,
            cornices[i].material);
    }
    fclose(file);
    return 0;
}

// ������ ������� �� �����
int input_file(char* filename, cornice_t* cornices) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("������ �������� ����� ��� ������");
        return -1;
    }
    int i = 0;
    while (fscanf(file, "%d %d %d %19s",
        &cornices[i].length,
        &cornices[i].ceilingWidth,
        &cornices[i].wallHeight,
        cornices[i].material) != EOF) {
        i++;
        if (i >= SIZE) break;
    }
    fclose(file);
    return i;
}

// ���� ������������
void menu() {
    printf("\n����:\n");
    printf("1. ��������� ������\n");
    printf("2. ������� ������\n");
    printf("3. ����� ������ �� ���������\n");
    printf("4. ������������� ������ �� �������\n");
    printf("5. ��������� ������ � ����\n");
    printf("6. ��������� ������ �� �����\n");
    printf("0. �����\n");
}

// ������� �������
int main() {

    setlocale(LC_CTYPE, "RUS");
    cornice_t cornices[SIZE];
    int choice;
    char material[20];
    char filename[50];

    do {
        menu();
        printf("�������� ��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            fillCornicesArray(cornices, SIZE);
            printf("������ ������� ��������!\n");
            break;
        case 2:
            print_array(cornices, SIZE);
            break;
        case 3:
            printf("������� �������� ��� ������: ");
            scanf("%19s", material);
            cornice_t* result = search_material(cornices, SIZE, material);
            if (result) {
                printf("��������� ������:\n");
                print_cornice(*result);
            }
            else {
                printf("������ �� �������.\n");
            }
            break;
        case 4:
            sort_array(cornices, SIZE);
            printf("������ ������������ �� �������.\n");
            break;
        case 5:
            printf("������� ��� ����� ��� ����������: ");
            scanf("%49s", filename);
            if (output_file(filename, cornices, SIZE) == 0) {
                printf("������ ������� �������� � ����.\n");
            }
            break;
        case 6:
            printf("������� ��� ����� ��� ��������: ");
            scanf("%49s", filename);
            if (input_file(filename, cornices) > 0) {
                printf("������ ������� �������� �� �����.\n");
            }
            break;
        case 0:
            printf("����� �� ���������.\n");
            break;
        default:
            printf("������������ ����, ���������� �����.\n");
        }
    } while (choice != 0);

    return 0;
}
