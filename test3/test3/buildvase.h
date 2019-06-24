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

	int v_levels;//水平方向的分块层数
	int h_levels;//竖直方向的分块层数
	vector<point_3d> vec_vertex;//保存顶点的向量
	vector<int*> vec_surface;//保存面片的向量

	void bulidVase();//构建花瓶
	int isRepeat(point_3d p);//判断某个顶点是否已经在顶点向量中
	void writeFile();//生成三维文件
};
