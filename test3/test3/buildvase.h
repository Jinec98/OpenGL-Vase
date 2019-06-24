#pragma once

#include <vector>

using namespace std;

struct point_3d
{
	double x;
	double y;
	double z;
	int idx;

	double tx;
	double ty;

	point_3d(double x, double y, double z, int idx, double tx, double ty)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->idx = idx;
		this->tx = tx;
		this->ty = ty;
	}
};


class Vase
{
public:
	Vase(int v_levels, int h_levels);
	~Vase();

	int v_levels;//ˮƽ����ķֿ����
	int h_levels;//��ֱ����ķֿ����
	vector<point_3d> vec_vertex;//���涥�������
	vector<int*> vec_surface;//������Ƭ������

	void bulidVase();//������ƿ
	int isRepeat(point_3d p);//�ж�ĳ�������Ƿ��Ѿ��ڶ���������
	void writeFile();//������ά�ļ�
};
