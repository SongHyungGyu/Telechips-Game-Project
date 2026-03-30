#include "for_flower.h"
#include "LIB_stage.h"



flower* init_flower(int x, int y){
	flower* f = (flower*)malloc(sizeof(flower));
	
	f->img = load_image(PATH "flower.png");
	f->x = x;
	f->y = y;
	f->w = al_get_bitmap_width(f->img);
	f->h = al_get_bitmap_height(f->img);
	f->used = 0;

	return f;
}

//1�� �� 2�� �δ���
bool collide(int x1, int y1, int w1, int h1,
	int x2, int y2, int w2, int h2) {

	//�� �߽� ��ǥ ���ϱ� ���� �߽���ǥ�� cx1, cy1, �δ����� �߽� ��ǥ�� cx2, cy2
	int cx1 = x1 + w1 / 2;
	int cy1 = y1 + h1 / 2;

	int cx2 = x2 + w2 / 2;
	int cy2 = y2 + h2 / 2;

	//�� ��ü �߽� �������� �Ÿ� ���� dx, dy
	int dx = cx1 - cx2;
	int dy = cy1 - cy2;

	//�� ��ä �߽� ���� �Ÿ��� 30(������)���� ������ �浹
	return (dx * dx + dy * dy) < 30 * 30; // ������ 30
}

void update_flower(flower* f, DDG* ddg, Stage* s) {
	// �̹� ���� ���̸� ��ȯ��
	if (f->used) return;

	//�̶����� �ȸԾ��� �� �� �浹�̸� f->used = 1�� ���� �� ������ �ϳ� ����
	if (collide(f->x, f->y, f->w, f->h,
		ddg->x, ddg->y, ddg_size, ddg_size)) {
		f->used = 1;   // �� ���� ó��
		s->flower_cnt--;
		printf("\nflower_current_cnt = %d\n", s->flower_cnt);
	}
}

void render_flower(flower* f) {
	if (f->used) return;
	al_draw_scaled_bitmap(f->img, 0, 0, f->w, f->h,
		f->x, f->y, FLOWER_SIZE, FLOWER_SIZE, 0);
}