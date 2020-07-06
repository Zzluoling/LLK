#pragma once

typedef struct  tagVertex
{
	int row;
	int col;
	int info;
}Vertex;

#define BLANK           -1
#define MAX_VERTEX_NUM  160      //顶点数
#define MAX_ROW         10       //行数
#define MAX_COL         16       //列数
#define MAP_TOP         20       //左上角纵坐标
#define MAP_LEFT        20       //左上角横坐标
#define PIC_WIDTH       40       //图片宽度
#define PIC_HEIGHT      40       //图片高度
#define MAX_PIC_NUM     16       //图片花色
#define REPEAT_NUM      10       //每种花色图片个数
#define PLAY_TIMER_ID   1        //计时器编号
#define GAME_LOSE       -1
#define GAME_SUCESS     0   
#define GAME_PLAY       1