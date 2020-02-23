#ifndef all_struct_h
#define all_struct_h




typedef struct
{
	uint8	Direction;		//类型
	uint8	Flag;			//会车区标志
	uint8	Start_Flag;		//开始判断会车区
	uint8	Mode;			//0 直道会车（不停车）  1弯道会车（停车）
}meeting_area;

typedef struct
{
	uint8	Flag;
	uint8	State;			//分为6段 0 1 3 5 6 为会车  2 4正常跑  3-中间会车 7-结束
	uint8   Track_Mode;		//0摄像头巡边  1电磁循迹
	uint8	Electric;		//0摄像头循迹	1电磁循迹
	uint8	End;			//结束会车标志位
	uint16 	Wait_Time;		//等待时间
	uint16  Distance;		//两车距离
	uint8	Find_Track;		//车辆巡线偏移
	uint8	Stop_Flag;		//停车标志
	uint8	Brake;			//刹车标志 1正在刹车 0刹车结束x
	uint8	Oder;			//车辆顺序
	uint8	Send_Flag;  //通讯标志位
}meeting;

extern uint8 Mode;
//void Running(void);

#endif