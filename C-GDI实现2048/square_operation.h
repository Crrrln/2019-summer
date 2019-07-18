#pragma once
int score = 0;
int  if_need_add_num = 0; /* ���趨��Ĭ����Ҫ�������������Ҫʱ���趨Ϊ1 */
void move_left(int a[4][4]);
void move_right(int a[4][4]);
void move_up(int a[4][4]);
void move_down(int a[4][4]);

void move_left(int a[4][4]){
	/* ����i��������������±꣬�������ƶ�ʱ�������໥����������Ӱ�� */
	int i;
	for (i = 0; i < 4; ++i) {
		/* ����jΪ���±꣬����kΪ���Ƚϣ��ϲ�������±꣬ѭ������ʱk<j */
		int j, k;
		for (j = 1, k = 0; j < 4; ++j) {
			if (a[i][j] > 0) /* �ҳ�k�����һ����Ϊ�յ���±�Ϊj��֮���������� */
			{
				if (a[i][k] == a[i][j]) {
					/* ���1��k���j����ȣ���ʱ�ϲ����鲢�Ʒ� */
					score += a[i][k++] *= 2;
					a[i][j] = 0;
					if_need_add_num = 1; /* ��Ҫ�����������ˢ�½��� */
				}
				else if (a[i][k] == 0) {
					/* ���2��k��Ϊ�գ����j�ֵ��k��൱��j�����ƶ���k���� */
					a[i][k] = a[i][j];
					a[i][j] = 0;
					if_need_add_num = 1;
				}
				else {
					/* ���3��k�Ϊ�գ��Һ�j���ȣ���ʱ��j�ֵ��k+1��൱���ƶ���k+1��λ�� */
					a[i][++k] = a[i][j];
					if (j != k) {
						/* �ж�j���k���Ƿ�ԭ�ȾͰ���һ�����������j�ֵΪ�գ�ֵΪ0�� */
						a[i][j] = 0;
						if_need_add_num = 1;
					}
				}
			}
		}
	}
}

/* ���� �������� */
void move_right(int a[4][4]) {
	/* �������Ʋ��������������j��k��������� */
	int i;
	for (i = 0; i < 4; ++i) {
		int j, k;
		for (j = 2, k = 3; j >= 0; --j) {
			if (a[i][j] > 0) {
				if (a[i][k] == a[i][j]) {
					score += a[i][k--] *= 2;
					a[i][j] = 0;
					if_need_add_num = 1;
				}
				else if (a[i][k] == 0) {
					a[i][k] = a[i][j];
					a[i][j] = 0;
					if_need_add_num = 1;
				}
				else {
					a[i][--k] = a[i][j];
					if (j != k) {
						a[i][j] = 0;
						if_need_add_num = 1;
					}
				}
			}
		}
	}
}

/* ���� �������� */
void move_up(int a[4][4]) {
	/* �������Ʋ�����������������л�������� */
	int i;
	for (i = 0; i < 4; ++i) {
		int j, k;
		for (j = 1, k = 0; j < 4; ++j) {
			if (a[j][i] > 0) {
				if (a[k][i] == a[j][i]) {
					score += a[k++][i] *= 2;
					a[j][i] = 0;
					if_need_add_num = 1;
				}
				else if (a[k][i] == 0) {
					a[k][i] = a[j][i];
					a[j][i] = 0;
					if_need_add_num = 1;
				}
				else {
					a[++k][i] = a[j][i];
					if (j != k) {
						a[j][i] = 0;
						if_need_add_num = 1;
					}
				}
			}
		}
	}
}

/* ���� �������� */
void move_down(int a[4][4]) {
	/* �������Ʋ�����������������л������������j��k��������� */
	int i;
	for (i = 0; i < 4; ++i) {
		int j, k;
		for (j = 2, k = 3; j >= 0; --j) {
			if (a[j][i] > 0) {
				if (a[k][i] == a[j][i]) {
					score += a[k--][i] *= 2;
					a[j][i] = 0;
					if_need_add_num = 1;
				}
				else if (a[k][i] == 0) {
					a[k][i] = a[j][i];
					a[j][i] = 0;
					if_need_add_num = 1;
				}
				else {
					a[--k][i] = a[j][i];
					if (j != k) {
						a[j][i] = 0;
						if_need_add_num = 1;
					}
				}
			}
		}
	}
}
