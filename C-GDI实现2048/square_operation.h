#pragma once
int score = 0;
int  if_need_add_num = 0; /* 先设定不默认需要生成随机数，需要时再设定为1 */
void move_left(int a[4][4]);
void move_right(int a[4][4]);
void move_up(int a[4][4]);
void move_down(int a[4][4]);

void move_left(int a[4][4]){
	/* 变量i用来遍历行项的下标，并且在移动时所有行相互独立，互不影响 */
	int i;
	for (i = 0; i < 4; ++i) {
		/* 变量j为列下标，变量k为待比较（合并）项的下标，循环进入时k<j */
		int j, k;
		for (j = 1, k = 0; j < 4; ++j) {
			if (a[i][j] > 0) /* 找出k后面第一个不为空的项，下标为j，之后分三种情况 */
			{
				if (a[i][k] == a[i][j]) {
					/* 情况1：k项和j项相等，此时合并方块并计分 */
					score += a[i][k++] *= 2;
					a[i][j] = 0;
					if_need_add_num = 1; /* 需要生成随机数和刷新界面 */
				}
				else if (a[i][k] == 0) {
					/* 情况2：k项为空，则把j项赋值给k项，相当于j方块移动到k方块 */
					a[i][k] = a[i][j];
					a[i][j] = 0;
					if_need_add_num = 1;
				}
				else {
					/* 情况3：k项不为空，且和j项不相等，此时把j项赋值给k+1项，相当于移动到k+1的位置 */
					a[i][++k] = a[i][j];
					if (j != k) {
						/* 判断j项和k项是否原先就挨在一起，若不是则把j项赋值为空（值为0） */
						a[i][j] = 0;
						if_need_add_num = 1;
					}
				}
			}
		}
	}
}

/* 右移 函数定义 */
void move_right(int a[4][4]) {
	/* 仿照左移操作，区别仅仅是j和k都反向遍历 */
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

/* 上移 函数定义 */
void move_up(int a[4][4]) {
	/* 仿照左移操作，区别仅仅是行列互换后遍历 */
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

/* 下移 函数定义 */
void move_down(int a[4][4]) {
	/* 仿照左移操作，区别仅仅是行列互换后遍历，且j和k都反向遍历 */
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
