/*
Program: University Student & Event Management System
Subject: Structured Programming and Defensive Technologies (SPDT)
Language: C
*/

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_EVENTS 5

/* Enum for event type */
enum EventType { CULTURAL, SPORTS, TECHNICAL };

/* Union for score (only one score per event) */
union Score {
    int sports_score;
    float cultural_score;
};

/* Structure for Event */
struct Event {
    char event_name[30];
    enum EventType type;
    int max_marks;
    union Score score;
};

/* Structure for Student */
struct Student {
    int roll;
    char name[30];
    int age;
    char phone[15];
    char email[30];
    struct Event events[MAX_EVENTS];
    int event_count;
    float total_marks;
    float average;
    char grade;
};

/* Function prototypes */
void addStudent(struct Student students[], int *count);
void calculateResult(struct Student *s);
void displayLeaderboard(struct Student students[], int count);
void searchStudent(struct Student students[], int count, int roll);
int isRollDuplicate(struct Student students[], int count, int roll);
void sortByTotalMarks(struct Student students[], int count);

/* Main function */
int main(void) {
    struct Student students[MAX_STUDENTS];
    int student_count = 0;
    int choice, roll;

    do {
        printf("\n--- University Student & Event Management ---\n");
        printf("1. Add Student\n");
        printf("2. Display Leaderboard\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addStudent(students, &student_count);
                break;
            case 2:
                displayLeaderboard(students, student_count);
                break;
            case 3:
                printf("Enter roll number to search: ");
                if (scanf("%d", &roll) != 1) {
                    printf("Invalid roll number.\n");
                    // clear input buffer in a simple way
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                    break;
                }
                searchStudent(students, student_count, roll);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

/* Check for duplicate roll number */
int isRollDuplicate(struct Student students[], int count, int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            return 1;
        }
    }
    return 0;
}

/* Add student and event details */
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Limit reached.\n");
        return;
    }

    struct Student *s = &students[*count];
    int i;

    printf("Enter roll number: ");
    if (scanf("%d", &s->roll) != 1) {
        printf("Invalid roll number.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return;
    }

    if (isRollDuplicate(students, *count, s->roll)) {
        printf("Roll number already exists. Student not added.\n");
        return;
    }

    printf("Enter name: ");
    // limit to 29 chars, allow spaces
    scanf(" %29[^\n]", s->name);

    printf("Enter age: ");
    if (scanf("%d", &s->age) != 1 || s->age <= 0) {
        printf("Invalid age.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return;
    }

    printf("Enter phone: ");
    scanf("%14s", s->phone);  // 14 + '\0'

    printf("Enter email: ");
    scanf("%29s", s->email);  // 29 + '\0'

    printf("Enter number of events (max %d): ", MAX_EVENTS);
    if (scanf("%d", &s->event_count) != 1 ||
        s->event_count <= 0 || s->event_count > MAX_EVENTS) {
        printf("Invalid number of events.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return;
    }

    s->total_marks = 0.0f;

    for (i = 0; i < s->event_count; i++) {
        int type;
        float temp_score_f;
        int temp_score_i;

        printf("\nEvent %d name: ", i + 1);
        scanf(" %29[^\n]", s->events[i].event_name);

        /* Read and validate event type */
        printf("Event type (0-Cultural, 1-Sports, 2-Technical): ");
        if (scanf("%d", &type) != 1 ||
            type < CULTURAL || type > TECHNICAL) {
            printf("Invalid event type. Re-enter this event.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            i--;    // repeat this event
            continue;
        }
        s->events[i].type = (enum EventType)type;

        /* Read and validate max marks */
        printf("Maximum marks: ");
        if (scanf("%d", &s->events[i].max_marks) != 1 ||
            s->events[i].max_marks <= 0) {
            printf("Invalid maximum marks. Re-enter this event.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            i--;
            continue;
        }

        if (s->events[i].type == SPORTS) {
            printf("Enter sports score: ");
            if (scanf("%d", &temp_score_i) != 1 ||
                temp_score_i < 0 || temp_score_i > s->events[i].max_marks) {
                printf("Invalid score. Re-enter this event.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                i--;
                continue;
            }
            s->events[i].score.sports_score = temp_score_i;
            s->total_marks += (float)temp_score_i;
        } else {
            printf("Enter score: ");
            if (scanf("%f", &temp_score_f) != 1 ||
                temp_score_f < 0 || temp_score_f > s->events[i].max_marks) {
                printf("Invalid score. Re-enter this event.\n");
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                i--;
                continue;
            }
            s->events[i].score.cultural_score = temp_score_f;
            s->total_marks += temp_score_f;
        }
    }

    calculateResult(s);
    (*count)++;

    printf("Student added successfully.\n");
}

/* Calculate total, average and grade */
void calculateResult(struct Student *s) {
    if (s->event_count <= 0) {
        s->average = 0.0f;
        s->grade = 'D';
        return;
    }

    s->average = s->total_marks / s->event_count;

    if (s->average >= 80.0f)
        s->grade = 'A';
    else if (s->average >= 60.0f)
        s->grade = 'B';
    else if (s->average >= 40.0f)
        s->grade = 'C';
    else
        s->grade = 'D';
}

/* Sort students in descending order of total marks (simple bubble sort) */
void sortByTotalMarks(struct Student students[], int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (students[j].total_marks < students[j + 1].total_marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/* Display leaderboard */
void displayLeaderboard(struct Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    /* Sort a copy if you want to preserve original order; here sort in-place */
    sortByTotalMarks(students, count);

    printf("\n--- Leaderboard ---\n");
    printf("Name\t\tTotal Marks\tGrade\n");

    for (int i = 0; i < count; i++) {
        printf("%s\t\t%.2f\t\t%c\n",
               students[i].name,
               students[i].total_marks,
               students[i].grade);
    }
}

/* Search student by roll number */
void searchStudent(struct Student students[], int count, int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("\nStudent Found:\n");
            printf("Roll: %d\n", students[i].roll);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Phone: %s\n", students[i].phone);
            printf("Email: %s\n", students[i].email);
            printf("Total Marks: %.2f\n", students[i].total_marks);
            printf("Average: %.2f\n", students[i].average);
            printf("Grade: %c\n", students[i].grade);

            printf("\nEvents:\n");
            for (int j = 0; j < students[i].event_count; j++) {
                printf("  Event %d: %s\n", j + 1, students[i].events[j].event_name);
                printf("    Type: ");
                switch (students[i].events[j].type) {
                    case CULTURAL:  printf("Cultural\n");  break;
                    case SPORTS:    printf("Sports\n");    break;
                    case TECHNICAL: printf("Technical\n"); break;
                    default:        printf("Unknown\n");   break;
                }
                printf("    Max Marks: %d\n", students[i].events[j].max_marks);
                if (students[i].events[j].type == SPORTS) {
                    printf("    Score: %d\n",
                           students[i].events[j].score.sports_score);
                } else {
                    printf("    Score: %.2f\n",
                           students[i].events[j].score.cultural_score);
                }
            }
            return;
        }
    }
    printf("Student not found.\n");
}
