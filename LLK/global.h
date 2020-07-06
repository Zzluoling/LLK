#pragma once

typedef struct  tagVertex
{
	int row;
	int col;
	int info;
}Vertex;

#define BLANK           -1
#define MAX_VERTEX_NUM  160      //������
#define MAX_ROW         10       //����
#define MAX_COL         16       //����
#define MAP_TOP         20       //���Ͻ�������
#define MAP_LEFT        20       //���ϽǺ�����
#define PIC_WIDTH       40       //ͼƬ���
#define PIC_HEIGHT      40       //ͼƬ�߶�
#define MAX_PIC_NUM     16       //ͼƬ��ɫ
#define REPEAT_NUM      10       //ÿ�ֻ�ɫͼƬ����
#define PLAY_TIMER_ID   1        //��ʱ�����
#define GAME_LOSE       -1
#define GAME_SUCESS     0   
#define GAME_PLAY       1