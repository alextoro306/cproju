#include <stdio.h>

#define MAX_SUBJECTS 100

//määrittelee arvosanan pistemäärän perusteella
int calculateGrade(float score) {
    if (score >= 90) return 5;
    if (score >= 80) return 4;
    if (score >= 70) return 3;
    if (score >= 60) return 2;
    if (score >= 50) return 1;
    return 0;
}

int main() {
    char name[50];
    int numSubjects;
    char subjects[MAX_SUBJECTS][50]; //taulukko aiheiden nimien tallentamiseen
    float scores[MAX_SUBJECTS]; //tallentaa tulokset
    float totalScore = 0.0;
    int totalGrades = 0; //laskee arvosanojen keskiarvon

    printf("Welcome to the Student Grade Calculator!\n");

    //kysyy oppilaan nimen ja ottaa sen
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);

    //kysyy aiheiden määrän
    printf("How many subjects do you want to calculate grades for? ");
    scanf("%d", &numSubjects);
    while (getchar() != '\n'); //tyhjä

    //määrittelee aiheiden määrän
    if (numSubjects < 1 || numSubjects > MAX_SUBJECTS) {
        printf("Invalid number of subjects! Please enter a number between 1 and %d.\n", MAX_SUBJECTS);
        return 1;
    }

    //tässä kysytään aiheet ja pisteet
    for (int i = 0; i < numSubjects; i++) {
        printf("Enter subject %d name: ", i + 1);
        scanf(" %[^\n]", subjects[i]); //lukee aiheen nime

        printf("Enter your score for %s (0-100): ", subjects[i]);
        scanf("%f", &scores[i]);

        //määrittelee pisteet
        if (scores[i] < 0 || scores[i] > 100) {
            printf("Invalid score! Please enter a score between 0 and 100.\n");
            return 1;
        }

        totalScore += scores[i]; //kerää kokonaispisteet
        totalGrades += calculateGrade(scores[i]); //laskee arvosanan
    }

    //Laskee keskimääräsen pistemäärän ja arvosanan
    float averageScore = totalScore / numSubjects;
    float averageGrade = (float)totalGrades / numSubjects; //Keskiarvo asteikolla 0-5

    //avaa tiedoston raportin kirjottamiseen
    FILE *file = fopen("student_report.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }

    //printtaa tiedot konsoliin
    printf("------------------------------------------\n");
    printf("Student: %s", name);
    printf("------------------------------------------\n");
    printf("Subject             Score   Grade\n");
    printf("------------------------------------------\n");

    //Tulostaa aiheen pisteet ja arvosanat
    for (int i = 0; i < numSubjects; i++) {
        int grade = calculateGrade(scores[i]);
        // leveyden säätö konsoliin
        printf("%-20s %.0f%%\t%d\n", subjects[i], scores[i], grade); //aiheen, pisteiden ja arvosanan tulostaminen konsoliin
        fprintf(file, "%-20s %.0f%%\t%d\n", subjects[i], scores[i], grade); //kirjoittaa tiedostoon
    }

    //Tulostaa keskimääräisen pistemäärän ja arvosanan
    printf("------------------------------------------\n");
    printf("Average Score: %.2f\n", averageScore);
    printf("Average Grade: %.2f\n", averageGrade);

    //kirjoittaa tiedostoon keskimääräisen pistemäärän ja arvosanan
    fprintf(file, "------------------------------------------\n");
    fprintf(file, "Average Score: %.2f\n", averageScore);
    fprintf(file, "Average Grade: %.2f\n", averageGrade);
    return 0;
}
