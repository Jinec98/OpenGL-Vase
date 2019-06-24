#include "buildvase.h"
#include <fstream>

#define PI 3.14159265358979323846 

Vase::Vase(int v_levels, int h_levels)
{
	this->v_levels = v_levels;
	this->h_levels = h_levels;
}

Vase::~Vase(){}

void Vase::bulidVase()
{
	int mincal = 50, maxcal = 100;//最小口径和最大口径
	double height = 380;//花瓶的高度
	int index = 0;
	int temp_idx = -1;

	int step = height / v_levels;
	for (int i = -50; i < 330; i += step)
	{
		double r1 = mincal * sin(i / 180.0*PI) + maxcal;
		double r2 = mincal * sin((i + step) / 180.0*PI) + maxcal;

		for (int j = 0; j < h_levels; j++)
		{
			double angle1 = 360.0 / h_levels * j;
			double angle2 = 360.0 / h_levels * (j + 1);

			double v1_x = r1 * cos(angle1 / 180.0*PI);
			double v1_y = i;
			double v1_z = r1 * sin(angle1 / 180.0*PI);
			double v1_tx = (double)j / h_levels;
			double v1_ty = (double)(i + 50) / height;
			point_3d v1(v1_x, v1_y, v1_z, 0, v1_tx, v1_ty);
			temp_idx = isRepeat(v1);
			if (temp_idx == -1)
			{
				v1.idx = index;
				index++;
				vec_vertex.push_back(v1);
			}
			else
			{
				v1.idx = temp_idx;
			}

			double v2_x = r1 * cos(angle2 / 180.0*PI);
			double v2_y = i;
			double v2_z = r1 * sin(angle2 / 180.0*PI);
			double v2_tx = (double)(j + 1) / h_levels;
			double v2_ty = (double)(i + 50) / height;
			point_3d v2(v2_x, v2_y, v2_z, 0, v2_tx, v2_ty);
			temp_idx = isRepeat(v2);
			if (temp_idx == -1)
			{
				v2.idx = index;
				index++;
				vec_vertex.push_back(v2);
			}
			else
			{
				v2.idx = temp_idx;
			}

			double v3_x = r2 * cos(angle2 / 180.0*PI);
			double v3_y = i + step;
			double v3_z = r2 * sin(angle2 / 180.0*PI);
			double v3_tx = (double)(j + 1) / h_levels;
			double v3_ty = (double)(i + step + 50) / height;
			point_3d v3(v3_x, v3_y, v3_z, 0, v3_tx, v3_ty);
			temp_idx = isRepeat(v3);
			if (temp_idx == -1)
			{
				v3.idx = index;
				index++;
				vec_vertex.push_back(v3);
			}
			else
			{
				v3.idx = temp_idx;
			}

			double v4_x = r2 * cos(angle1 / 180.0*PI);
			double v4_y = i + step;
			double v4_z = r2 * sin(angle1 / 180.0*PI);
			double v4_tx = (double)j / h_levels;
			double v4_ty = (double)(i + step + 50) / height;
			point_3d v4(v4_x, v4_y, v4_z, 0, v4_tx, v4_ty);
			temp_idx = isRepeat(v4);
			if (temp_idx == -1)
			{
				v4.idx = index;
				index++;
				vec_vertex.push_back(v4);
			}
			else
			{
				v4.idx = temp_idx;
			}

			int* surface;
			surface = new int[4];
			surface[0] = v1.idx;
			surface[1] = v2.idx;
			surface[2] = v3.idx;
			surface[3] = v4.idx;

			vec_surface.push_back(surface);
		}
	}
}

int Vase::isRepeat(point_3d p)
{
	for (int i = 0; i < vec_vertex.size(); i++)
	{
		if (p.x == vec_vertex[i].x  && p.y == vec_vertex[i].y && p.z == vec_vertex[i].z)
			return vec_vertex[i].idx;
	}
	return -1;
}

void Vase::writeFile()
{
	int vertex_cnt = vec_vertex.size();
	int surface_cnt = vec_surface.size();
	ofstream file("vase.ply");
	file << "ply\n";
	file << "format ascii 1.0\n";
	file << "comment this is a vase\n";
	file << "element vertex " << vertex_cnt << "\n";
	file << "property double x\n";
	file << "property double y\n";
	file << "property double z\n";
	file << "element face " << surface_cnt << "\n";
	file << "property list uchar int vertex_index\n";
	file << "end_header\n";

	for (auto p : vec_vertex)
	{
		file << p.x << " " << p.z << " " << p.y << "\n";
	}
	for (auto s : vec_surface)
	{
		file << "4 " << s[0] << " " << s[1] << " " << s[2] << " " << s[3] << "\n";
	}
	file.close();
}