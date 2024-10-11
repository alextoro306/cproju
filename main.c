#include <stdio.h>
#define MAX_SUBJECTS 100

// Määrittelee arvosanan pistemäärän perusteella
int calculateGrade(float score) {
    if (score >= 90) return 5;
    if (score >= 80) return 4;
    if (score >= 70) return 3;
    if (score >= 60) return 2;
    if (score >= 50) return 1;
    return 0;
}

// print ja tallennustoiminto
void printAndSave(FILE *file, const char *text) {
    printf("%s", text); // Tulostus konsoliin
    fprintf(file, "%s", text); // Kirjotus tiedostoon
}

int main() {
    char name[50]; // Opiskelijan nimi max 50 merkkiä
    int numSubjects; // Opiskelijan aineiden lukumäärä
    char subjects[MAX_SUBJECTS][50]; // Aineiden nimet max 50 merkkiä
    float scores[MAX_SUBJECTS]; // Pisteet ainetta kohden
    float totalScore = 0.0; // Kokonaispisteet
    int totalGrades = 0; // Arvosanojen summa

    printf("Welcome to the Student Grade Calculator!\n");

    // Kysyy oppilaan nime ja ottaa sen
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin); // stdin standardi syöttö näppäimistöl. size of kuinka monta merkkiä voidaan lukea. eli nimi voi olla mx 50 merkkiä.

    // Kysyy aineiden määrän
    printf("How many subjects do you want to calculate grades for? ");
    scanf("%d", &numSubjects); // %d lukee luvun integer. muuttuja eli numsubjects johon luettu kokonaisluku tallennetaan.
    while (getchar() != '\n'); // Tyhjentää turhat merkit ja väli

    // Tarkistaa aineiden määrän
    if (numSubjects < 1 || numSubjects > MAX_SUBJECTS) {
        printf("Invalid number of subjects! Please enter a number between 1 and %d.\n", MAX_SUBJECTS);
        return 1;
    }

    // Avaa tiedoston raportin kirjoittamiseen
    FILE *file = fopen("student_report.txt", "w"); //w avaa kirjotustilas tiedoston ja tallentaa sinne tiedot. ja poistaa aiemmat tiedot.
    if (file == NULL) { // null ei oo vielä alustettu
        return 1;
    }

    // Kysyy aineet ja pisteet
    for (int i = 0; i < numSubjects; i++) { //i = 0 alustetaan nollaks ja se toimii laskurina.
        printf("Enter subject %d name: ", i + 1);
        scanf(" %[^\n]", subjects[i]); // Lukee aineen nimen

        do { // suoritetaan vähintään kerran. eli jos vaik syöttö on virheellinen niin se kysyy niin pitkään kunnes se syöttö on oikea.
            printf("Enter your score for %s (0-100): ", subjects[i]); // pyytää käyttäjää syöttämään pisteet tietylle aineelle.
            scanf("%f", &scores[i]); // tallentaa pisteet muuttujaan.

            // Varmistaa, että pistemäärä on oikea
            if (scores[i] < 0 || scores[i] > 100) {
                printf("Invalid score! Please enter a score between 0 and 100.\n");
            }
        } while (scores[i] < 0 || scores[i] > 100);

        totalScore += scores[i]; // Kerää kokonaispisteet
        totalGrades += calculateGrade(scores[i]); // Laskee arvosanan
    }

    // Laskee keskiarvot pisteistä ja arvosanoista
    float averageScore = totalScore / numSubjects;
    float averageGrade = (float)totalGrades / numSubjects;

    // Tulostaa tiedot konsoliin ja fileen
    printAndSave(file, "------------------------------------------\n");
    printAndSave(file, "Student: ");
    printAndSave(file, name);
    printAndSave(file, "------------------------------------------\n");
    printAndSave(file, "Subject             Score   Grade\n");
    printAndSave(file, "------------------------------------------\n");

    // Tulostaa aineet, pisteet ja arvosanat tiedostoon ja konsoliin
    for (int i = 0; i < numSubjects; i++) { // käy läpi kaikki aineet
        int grade = calculateGrade(scores[i]); // Laskee jokase aineen arvosanan scores[i] perusteella käyttäen calculategrade funktioo.
        char buffer[100]; // Tallentaa aineen nimen, pisteet ja arvosanan taulukkoon.
        sprintf(buffer, "%-20s %.0f%%\t%d\n", subjects[i], scores[i], grade); // muotoilee aineen nimen, pisteet ja arvosanan yhteen merkkijonoon ja tallentaa buffer-taulukkoon.
        printAndSave(file, buffer); // tulostaa tiedot konsoliin ja tiedostoon.
    }

    // Tulostaa keskiarvot ja lisää tiedostoon
    printAndSave(file, "------------------------------------------\n");
    char averageBuffer[100]; // keskiarvojen tallentamiseen
    sprintf(averageBuffer, "Average Score: %.2f\n", averageScore);
    printAndSave(file, averageBuffer);
    sprintf(averageBuffer, "Average Grade: %.2f\n", averageGrade);
    printAndSave(file, averageBuffer);
    printAndSave(file, "------------------------------------------\n");
    return 0;
}