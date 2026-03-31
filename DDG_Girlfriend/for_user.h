#ifndef __FOR_User_H__
#define __FOR_User_H__
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char name[21];
	int stage; //깬 스테이지
	int time; //해당 스테이지를 깼을 때의 시간
}User;
User* init_User();
void set_User(User* u, char* name, int stage, int time);
void draw_top_Users(ALLEGRO_FONT* font);
void destroy_User(User* u);

#endif
