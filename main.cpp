#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

float rad = 0.8, range = 90;
float stable = 0.8;
float maxx = 95;
float maxy = 95;
float maxz = 95;
float minx = 5;
float miny = 5;
float minz = 5;
float sBox = 1;
float eBox = 80;
float coe = 2;
// int SK = 2;
// int step = 5;
void main()
{
	char filename[] = "C:/Users/Zhihan Hu/Documents/lab/2023/seungsu/frozen/0percentoverlay50eV.xyz";
	char firstFrame[] = "C:/Users/Zhihan Hu/Documents/lab/2023/seungsu/frozen/overlayreference.xyz";
	char savefilename[] = "C:/Users/Zhihan Hu/Documents/lab/2023/seungsu/frozen/0percentZrC50.seg";
	char savefilename2[] = "C:/Users/Zhihan Hu/Documents/lab/2023/seungsu/frozen/0percentZrC50.txt";

	char NumString[20];
	char keyword[256];
	int Num, temp, n = 0, count = 0;
	float posx, posy, posz;
	float posxx, posyy, poszz;
	float nposx, nposy, nposz;
	float dis, dis1, dis2, dis3;
	float min, max;
	vector<float> px, py, pz;
	vector<float> tx, ty, tz;
	vector<float> cx, cy, cz;
	vector<int> sphereStat;
	vector<int> atomStat;
	ifstream is(filename, ios::in);
	ifstream sds(firstFrame, ios::in);
	ofstream ofs(savefilename, ios::out);
	ofstream ofs2(savefilename2, ios::out);
	ofs << "from pymol.cgo import *" << endl;
	ofs << "from pymol import cmd" << endl;
	ofs << "box = [" << endl;
	ofs << "LINEWIDTH, 1.0," << endl;

	ofs << "BEGIN, LINES," << endl;
	ofs << "COLOR, 0.8, 0.8, 0.8," << endl;
	ofs << "VERTEX," << eBox << "," << eBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << eBox << "," << sBox << "," << eBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << eBox << "," << eBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << eBox << "," << eBox << "," << sBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << eBox << "," << eBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << eBox << "," << eBox << "," << endl;
	ofs << endl;
	ofs << "COLOR, 0.5, 1.0, 0.5," << endl;
	ofs << "VERTEX," << sBox << "," << sBox << "," << sBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << eBox << "," << sBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << sBox << "," << sBox << "," << sBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << sBox << "," << eBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << sBox << "," << sBox << "," << sBox << "," << endl;
	ofs << "VERTEX," << eBox << "," << sBox << "," << sBox << "," << endl;
	ofs << endl;

	ofs << "COLOR, 0.8, 0.8, 0.8," << endl;
	ofs << "VERTEX," << eBox << "," << sBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << sBox << "," << eBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << eBox << "," << sBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << eBox << "," << sBox << "," << sBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << eBox << "," << eBox << "," << sBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << eBox << "," << sBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << eBox << "," << eBox << "," << sBox << "," << endl;
	ofs << "VERTEX," << eBox << "," << sBox << "," << sBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << sBox << "," << eBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << eBox << "," << sBox << "," << endl;
	ofs << endl;
	ofs << "VERTEX," << sBox << "," << eBox << "," << eBox << "," << endl;
	ofs << "VERTEX," << sBox << "," << sBox << "," << eBox << "," << endl;
	ofs << endl;
	ofs << "END" << endl;
	ofs << "]" << endl;

	char str[1024];
	char str2[1024];
	is.getline(str, 1024);
	sscanf(str, "%d", &Num);
	to_string(Num);

	is.getline(str, 1024);

	sds.getline(str2, 1024);
	sds.getline(str2, 1024);

	for (int i = 0; i < Num; i++)
	{
		is.getline(str, 1024);
		sds.getline(str2, 1024);
		sscanf(str, "%d %f %f %f", &temp, &posx, &posy, &posz);

		tx.push_back(posx);
		ty.push_back(posy);
		tz.push_back(posz);
		sphereStat.push_back(0);
		atomStat.push_back(0);
	}

	cx.resize(Num);
	cy.resize(Num);
	cz.resize(Num);
	px.resize(Num);
	py.resize(Num);
	pz.resize(Num);
	// count++;
	ofs << "# FRAME     " << count + 1 << endl;
	ofs << "atoms = [" << endl;
	ofs << "    ]" << endl;
	ofs << endl;
	ofs << "obj = box + atoms" << endl;
	ofs << endl;
	ofs << "cmd.load_cgo(obj,'segment',  " << count + 1 << ")" << endl;
	ofs << endl;

	int test_count = 0;
	while (!is.eof())
	{
		is.getline(str, 1024);
		sds.getline(str2, 1024);
		if (strcmp(str, NumString) == 0)
		{
			test_count++;
			cout << test_count << endl;
			is.getline(str, 1024);
			sds.getline(str2, 1024);
			count++;
			if (count < 0)
				continue;
			n++;
			ofs << "# FRAME     " << count << endl;
			ofs << "atoms = [" << endl;
			cout << "start processing frame " << count << "!" << endl;
			for (int i = 0; i < Num; i++)
			{
				atomStat[i] = 1;
				sphereStat[i] = 1;
			}

			for (int i = 0; i < Num; i++)
			{
				is.getline(str, 1024);
				sds.getline(str2, 1024);
				sscanf(str, "%d %f %f %f", &temp, &nposx, &nposy, &nposz);
				sscanf(str2, "%d %f %f %f", &temp, &posxx, &posyy, &poszz);
				cx[i] = nposx;
				cy[i] = nposy;
				cz[i] = nposz;
				px[i] = posxx;
				py[i] = posyy;
				pz[i] = poszz;
				dis = sqrt((nposx - px[i]) * (nposx - px[i]) + (nposy - py[i]) * (nposy - py[i]) + (nposz - pz[i]) * (nposz - pz[i]));

				if (dis > stable && dis < range)
				{

					/*if(atomStat[i]==0)
					{
						for(int j=0;j<Num;j++)
						{
							dis1 = sqrt((tx[i]-px[j])*(tx[i]-px[j])+(ty[i]-py[j])*(ty[i]-py[j])+(tz[i]-pz[j])*(tz[i]-pz[j]));
							if(dis1<=rad)
							{
								dis2=sqrt((nposx-px[j])*(nposx-px[j])+(nposy-py[j])*(nposy-py[j])+(nposz-pz[j])*(nposz-pz[j]));
								if(dis2>rad)
								{
									sphereStat[j] = 1;
									min = 1000;
									for(int k=0;k<Num;k++)
									{
										dis3=sqrt((nposx-px[k])*(nposx-px[k])+(nposy-py[k])*(nposy-py[k])+(nposz-pz[k])*(nposz-pz[k]));
										if(dis3<min)
										{
											min = dis3;
											temp = k;
										}
									}
									if(min>rad)
										atomStat[i] = 1;
									else
										sphereStat[temp] = 0;
								}
								break;
							}
						}
					}
					else
					{
						for(int j=0;j<Num;j++)
						{
							dis2=sqrt((nposx-px[j])*(nposx-px[j])+(nposy-py[j])*(nposy-py[j])+(nposz-pz[j])*(nposz-pz[j]));
							if(dis2<rad)
							{
								atomStat[i] = 0;
								sphereStat[j] = 0;
								break;
							}
						}
					}*/
					for (int j = 0; j < Num; j++)
					{
						dis2 = sqrt((nposx - px[j]) * (nposx - px[j]) + (nposy - py[j]) * (nposy - py[j]) + (nposz - pz[j]) * (nposz - pz[j]));
						if (dis2 < rad)
						{
							atomStat[i] = 0;
							sphereStat[j] = 0;
							break;
						}
					}
				}
				else
				{
					atomStat[i] = 0;
					sphereStat[i] = 0;
				}
			}
			ofs << "COLOR,1.000,0.000,0.000," << endl;
			int c1 = 0, c2 = 0;
			for (int i = 0; i < Num; i++)
			{

				if (atomStat[i] == 1)
				{
					if (cx[i] <= maxx && cy[i] <= maxy && cz[i] <= maxz && cx[i] >= minx && cy[i] >= miny && cz[i] >= minz)
					{
						c1++;
						ofs << "SPHERE," << cx[i] << "," << cy[i] << "," << cz[i] << "," << 0.6 << "," << endl;
					}
				}
			}
			ofs << "COLOR,0.750,0.750,1.900," << endl;
			for (int i = 0; i < Num; i++)
			{

				if (sphereStat[i] == 1)
				{
					if (px[i] <= maxx && py[i] <= maxy && pz[i] <= maxz && px[i] >= minx && py[i] >= miny && pz[i] >= minz)
					{
						ofs << "SPHERE," << px[i] << "," << py[i] << "," << pz[i] << "," << 0.5 << "," << endl;
						c2++;
					}
				}
			}
			ofs2 << count << " " << c1 << " " << c2 << endl;
			ofs << "    ]" << endl;
			ofs << endl;
			ofs << "obj = box + atoms" << endl;
			ofs << endl;
			ofs << "cmd.load_cgo(obj,'segment',  " << count + 1 << ")" << endl;
			ofs << endl;
			for (int i = 0; i < Num; i++)
			{
				tx[i] = cx[i];
				ty[i] = cy[i];
				tz[i] = cz[i];
			}
		}
	}
	cout << count << " records" << endl;
	sds.close();
	is.close();
	ofs.close();
	ofs2.close();
	cout << "done!" << endl;
	return;
}
