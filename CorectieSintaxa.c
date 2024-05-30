#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < c) return b;
    return c;
}

int levenshtein_distance(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int **d = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        d[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++) d[i][0] = i;
    for (int j = 0; j <= len2; j++) d[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            d[i][j] = min(d[i - 1][j] + 1,         // ștergere
                          d[i][j - 1] + 1,         // inserare
                          d[i - 1][j - 1] + cost); // substituire
        }
    }

    int distance = d[len1][len2];

    for (int i = 0; i <= len1; i++) {
        free(d[i]);
    }
    free(d);

    return distance;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Nu s-a putut deschide fisierul input.txt\n");
        return 1;
    }

    char rule[100];
    char fragment[100];

    if (fgets(rule, sizeof(rule), file) == NULL) {
        fprintf(stderr, "Eroare la citirea regulii din fisier\n");
        fclose(file);
        return 1;
    }
    
    // Eliminăm caracterele de newline la sfârșitul liniei citite
    rule[strcspn(rule, "\n")] = '\0';

    if (fgets(fragment, sizeof(fragment), file) == NULL) {
        fprintf(stderr, "Eroare la citirea fragmentului de cod din fisier\n");
        fclose(file);
        return 1;
    }

    // Eliminăm caracterele de newline la sfârșitul liniei citite
    fragment[strcspn(fragment, "\n")] = '\0';

    fclose(file);

    int distance = levenshtein_distance(fragment, rule);
    printf("Numarul minim de operatii necesare pentru a corecta fragmentul de cod: %d\n", distance);

    return 0;
}