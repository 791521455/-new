/*
*开发日志
*1.创建项目
*2.导入素材
*3.初始化场景
*4.顶部工具栏
*5.工具栏卡牌
* 
*/

#include <stdio.h>
#include <graphics.h>//easyx
#include "tools.h"

#define WIN_WIDTH   900
#define WIN_HEIGHT  600

enum {WAN_DOU, XIANG_RI_KUI, ZHI_WU_COUNT};

IMAGE imgBg;//背景图
IMAGE imgBar;//物品栏
IMAGE imgCards[ZHI_WU_COUNT];
IMAGE* imgZhiWu[ZHI_WU_COUNT][20];


int curX, curY;//选中植物位置，移动中

bool fileExist(const char* name) {
	FILE* fp = fopen(name, "r");//优化0wj01//if (fp) {fclose(fp);}
	if (fp==NULL){
		return false;
	}
	else {
		fclose(fp);
		return true;
	}//0wj02
}

void gameInit(){
	//加载背景图
	//改变项目属性
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar.png");

	memset(imgZhiWu, 0, sizeof(imgZhiWu));

	//初始化卡牌
	char name[64];
	for (int i = 0;i < ZHI_WU_COUNT;i++) {
		//生成植物卡牌文件名
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);

		for (int j = 0;j < 20;j++) {
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//先判断文件存在与否
			if (fileExist(name)) {
				loadimage(imgZhiWu[i][j], name);
			}
		}
	}

	//创建游戏窗口,initgraph(WIN_WIDTH, WIN_HEIGHT,1)控制台显示
	initgraph(WIN_WIDTH, WIN_HEIGHT);
}

void updateWindow() {
	BeginBatchDraw();//开始缓冲

	putimage(0, 0, &imgBg);
	//putimage(250, 0, &imgBar);
	putimagePNG(250, 0, &imgBar);

	for (int i = 0;i < ZHI_WU_COUNT; i++) {
		int x = 338 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}

	//渲染拖动中的植物


	EndBatchDraw();//结束双缓冲
}

void userClick() {
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 338 && msg.x < 338 + 65 * ZHI_WU_COUNT && msg.y < 96) {
				int index = (msg.x - 338) / 65;//printf("%d", index);调试
				status = 1;
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status ==1 ) {
			curX = msg.x;
			curY = msg.y;
		}
		else if (msg.message == WM_LBUTTONUP) {

		}
	}
}

int main(void) {
	gameInit();

	while (1) {
		userClick();

		updateWindow();
	}

	system("pause");
	return 0;
}
