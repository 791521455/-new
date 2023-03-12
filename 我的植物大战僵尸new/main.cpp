/*
*������־
*1.������Ŀ
*2.�����ز�
*3.��ʼ������
*4.����������
*5.����������
* 
*/

#include <stdio.h>
#include <graphics.h>//easyx
#include "tools.h"

#define WIN_WIDTH   900
#define WIN_HEIGHT  600

enum {WAN_DOU, XIANG_RI_KUI, ZHI_WU_COUNT};

IMAGE imgBg;//����ͼ
IMAGE imgBar;//��Ʒ��
IMAGE imgCards[ZHI_WU_COUNT];
IMAGE* imgZhiWu[ZHI_WU_COUNT][20];


int curX, curY;//ѡ��ֲ��λ�ã��ƶ���

bool fileExist(const char* name) {
	FILE* fp = fopen(name, "r");//�Ż�0wj01//if (fp) {fclose(fp);}
	if (fp==NULL){
		return false;
	}
	else {
		fclose(fp);
		return true;
	}//0wj02
}

void gameInit(){
	//���ر���ͼ
	//�ı���Ŀ����
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar.png");

	memset(imgZhiWu, 0, sizeof(imgZhiWu));

	//��ʼ������
	char name[64];
	for (int i = 0;i < ZHI_WU_COUNT;i++) {
		//����ֲ�￨���ļ���
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);

		for (int j = 0;j < 20;j++) {
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//���ж��ļ��������
			if (fileExist(name)) {
				loadimage(imgZhiWu[i][j], name);
			}
		}
	}

	//������Ϸ����,initgraph(WIN_WIDTH, WIN_HEIGHT,1)����̨��ʾ
	initgraph(WIN_WIDTH, WIN_HEIGHT);
}

void updateWindow() {
	BeginBatchDraw();//��ʼ����

	putimage(0, 0, &imgBg);
	//putimage(250, 0, &imgBar);
	putimagePNG(250, 0, &imgBar);

	for (int i = 0;i < ZHI_WU_COUNT; i++) {
		int x = 338 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}

	//��Ⱦ�϶��е�ֲ��


	EndBatchDraw();//����˫����
}

void userClick() {
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 338 && msg.x < 338 + 65 * ZHI_WU_COUNT && msg.y < 96) {
				int index = (msg.x - 338) / 65;//printf("%d", index);����
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
