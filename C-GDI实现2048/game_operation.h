#pragma once
#define COLOR_TEXT			RGB(173,216,230)
int if_game_over = 0;
int if_game_win = 0;
void check_game_over(int a[4][4]);
int get_null_count(int a[4][4]);

/* 获取空位置数量 函数定义 */
int get_null_count(int a[4][4]) {
	int n = 0;
	int i;
	for (i = 0; i < 4; ++i) {
		int j;
		for (j = 0; j < 4; ++j) {
			a[i][j] == 0 ? ++n : 1;

		}
	}
	return n;
}
void check_game_over(int a[4][4]) {
	int i;
	for (i = 0; i < 4; ++i) {
		int j;
		for (j = 0; j < 3; ++j) {
			/* 横向和纵向比较挨着的两个元素是否相等，若有相等则游戏不结束 */
			if (a[i][j] == a[i][j + 1] || a[j][i] == a[j + 1][i]) {
				if_game_over = 0;
				return;
			}
		}
	}
	if_game_over = 1;
}
void check_game_win(int a[4][4]) {
	int i;
	for (i = 0; i < 4; ++i) {
		int j;
		for (j = 0; j < 3; ++j) {
			if (a[i][j] == 2048) {
				if_game_win = 1;
				return;
			}
		}
	}
}

