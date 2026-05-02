#ifndef __FOR_User_H__
#define __FOR_User_H__
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char name[21];
	int stage; //�� ��������
	int time; //�ش� ���������� ���� ���� �ð�
}User;
User* init_User();
void set_User(User* u, char* name, int stage, int time);
void draw_top_Users(ALLEGRO_FONT* font);
void destroy_User(User* u);
void save_User(User* u);
#endif
