#include "LIB_DDG.h"
#include "for_User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UserS 10
#define FILE_NAME "ranking.txt"

// ���� ����:
// 1. stage ��������
// 2. stage ������ time ��������
static int compare_User(const void* a, const void* b) {
    const User* u1 = (const User*)a;
    const User* u2 = (const User*)b;

    if (u1->stage != u2->stage) {
        return u2->stage - u1->stage;
    }
    return u1->time - u2->time;
}

User* init_User() {
    User* u = (User*)malloc(sizeof(User));
    if (u == NULL) return NULL;

    strcpy(u->name, "");
    u->stage = 0;
    u->time = 0;
    return u;
}

void destroy_User(User* u) {
    if (u == NULL) return;
    free(u);
}

//�̸� �Է����� ���� stage �߰��� ������ �� Ȥ�� stage 3 �� ���� �� User ���� �����ϴ� �Լ�
void set_User(User* u, char* name, int stage, int time) {
    printf("set_User called with name=%s, stage=%d, time=%d\n", name, stage, time);
    if (name == NULL) {
        printf("name is NULL\n");
    }
    else {
        strcpy(u->name, name);
    }
 
    u->stage = stage;
    u->time = time;
    printf("User set: name=%s, stage=%d, time=%d\n", u->name, u->stage, u->time);
}

// stage �߰��� ������ �� Ȥ�� stage 3 �� ���� �� User ���Ͽ� ����
void save_User(User* u) {
    User Users[MAX_UserS];
    int count = 0;

    // 1. ���� ���� read �ؼ� �迭�� �ֱ�
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp != NULL) {
        while (count < MAX_UserS &&
            fscanf(fp, "%49s %d %d", Users[count].name, &Users[count].stage, &Users[count].time) == 3) {
            count++;
        }
        fclose(fp);
    }

    // 2. ���� �̸��� �̹� ������ �������� Ȯ��
    // ���� ����:
    // - �� ���� stage�� ����
    // - ���� stage�� �� ���� time�� �� ����
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(Users[i].name, u->name) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        if (u->stage > Users[found].stage ||
            (u->stage == Users[found].stage && u->time < Users[found].time)) {
            Users[found] = *u;
        }
    }
    else {
        // 3. ���� ����
        if (count < MAX_UserS) {
            Users[count] = *u;
            count++;
        }
        else {
            // �迭�� ������ ���ĵ� ����
			//������ �� ���� ��� �� ������ ������ �� ��� ����
            //�׸��� ����
            if (compare_User(u, &Users[count - 1]) < 0) {
                Users[count - 1] = *u;
            }
        }
    }

    // 4. ����
    qsort(Users, count, sizeof(User), compare_User);

    // 5. ���Ͽ� �ٽ� ����
    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("���� ���� ����\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %d\n", Users[i].name, Users[i].stage, Users[i].time);
    }

    fclose(fp);
}


int load_top_Users(User * Users, int max_count) {
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        return 0;
    }

    int count = 0;
    while (count < max_count &&
        fscanf(fp, "%19s %d %d", Users[count].name, &Users[count].stage, &Users[count].time) == 3) {
        count++;
    }

    fclose(fp);
    return count;
}

void draw_top_Users(ALLEGRO_FONT* font) {
    User Users[MAX_UserS];
    int count = load_top_Users(Users, MAX_UserS);

    int start_x = 180;
    int start_y = 472;
    int line_gap = 37;

    if (font == NULL) return;


    for (int i = 0; i < count; i++) {
        char buf[128];
        int minute = Users[i].time / 60;
        int second = Users[i].time % 60;

        if (Users[i].time >= 60) {
            snprintf(buf, sizeof(buf), "%s  STAGE: %d  TIME: %dm %ds",
                Users[i].name,
                Users[i].stage,
                minute,
                second);
        }
        else {
            snprintf(buf, sizeof(buf), "%s  STAGE: %d  TIME: %ds",
                Users[i].name,
                Users[i].stage,
                Users[i].time);
        }

        al_draw_text(font, al_map_rgb(0, 0, 0),
            start_x,
            start_y + i * line_gap,
            0,
            buf);
    }
}

void print_all_Users(void) {
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("���� ���� ����\n");
        return;
    }

    User temp;
    int rank = 1;

    while (fscanf(fp, "%49s %d %d", temp.name, &temp.stage, &temp.time) == 3) {
        printf("%d��: �̸�=%s, stage=%d, time=%d\n",
            rank, temp.name, temp.stage, temp.time);
        rank++;
    }

    fclose(fp);
}