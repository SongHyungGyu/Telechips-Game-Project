#include "LIB_DDG.h"
#include "for_User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UserS 10
#define FILE_NAME "ranking.txt"

// 정렬 기준:
// 1. stage 내림차순
// 2. stage 같으면 time 오름차순
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

//이름 입력했을 떄나 stage 중간에 끝났을 때 혹은 stage 3 다 꺴을 떄 User 정보 세팅하는 함수
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

// stage 중간에 끝났을 때 혹은 stage 3 다 꺴을 떄 User 파일에 저장
void save_User(User* u) {
    User Users[MAX_UserS];
    int count = 0;

    // 1. 기존 파일 read 해서 배열에 넣기
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp != NULL) {
        while (count < MAX_UserS &&
            fscanf(fp, "%49s %d %d", Users[count].name, &Users[count].stage, &Users[count].time) == 3) {
            count++;
        }
        fclose(fp);
    }

    // 2. 같은 이름이 이미 있으면 갱신할지 확인
    // 갱신 기준:
    // - 더 높은 stage면 갱신
    // - 같은 stage면 더 작은 time일 때 갱신
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
        // 3. 끝에 저장
        if (count < MAX_UserS) {
            Users[count] = *u;
            count++;
        }
        else {
            // 배열은 무조건 정렬된 상태
			//마지막 꺼 보다 기록 이 좋으면 마지막 꺼 대신 저장
            //그리고 정렬
            if (compare_User(u, &Users[count - 1]) < 0) {
                Users[count - 1] = *u;
            }
        }
    }

    // 4. 정렬
    qsort(Users, count, sizeof(User), compare_User);

    // 5. 파일에 다시 저장
    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
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
            sprintf_s(buf, sizeof(buf), "%s  STAGE: %d  TIME: %dm %ds",
                Users[i].name,
                Users[i].stage,
                minute,
                second);
        }
        else {
            sprintf_s(buf, sizeof(buf), "%s  STAGE: %d  TIME: %ds",
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
        printf("파일 열기 실패\n");
        return;
    }

    User temp;
    int rank = 1;

    while (fscanf(fp, "%49s %d %d", temp.name, &temp.stage, &temp.time) == 3) {
        printf("%d등: 이름=%s, stage=%d, time=%d\n",
            rank, temp.name, temp.stage, temp.time);
        rank++;
    }

    fclose(fp);
}