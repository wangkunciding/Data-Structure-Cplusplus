#include<iostream>
#include<cstring>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 6; //������
bool visit[N];   //���ʾ���
int lowcost[N] = { 0 };//��С��
int map[N][N] = {   
	{INF,  7,  4,INF,INF,INF},
	{  7,INF,  6,  2,INF,  4},
	{  4,  6,INF,INF,  9,  8},
	{INF,  2,INF,INF,INF,  7},
	{INF,INF,  9,INF,INF,  1},
	{INF,  4,  8,  7,  1,INF}
};

 
/*�ߵĶ���*/
struct edge
{
       int u, v;                                //�ߵ������˵���
       int cost;                                //��Ȩ
       edge(int x,int y, int c):u(x),v(y),cost(c){}
};
 
/*�ߵıȽϺ���*/
bool cmp(edge a, edge b)
{
       return a.cost < b.cost;
}
 
/*���鼯��ѯ����������x���ڼ��ϵĸ����*/
int findFather(vector<int> father, int x)
{
       int a = x;
       while (x != father[x])
              x = father[x];
       while (a != father[a]) {
              int z = a;
              a = father[a];
              father[z] = x;
       }
       return x;
}
 
/*Kruskal�㷨������ͼ����С������*/
int Kruskal(int n, int m, vector<edge>& E)
{
       /*
       param
       n:                         ͼ�Ķ������
       m:                         ͼ�бߵĸ���
       E:                         �ߵļ���
       */
       vector<int> father(n);                                 //���鼯����
       int ans = 0;                                           //�����Ȩ֮��
       int NumEdge = 0;                                       //��¼��С����������
       for (int i = 0; i < n; i++)                            //��ʼ�����鼯
              father[i] = i;
       sort(E.begin(), E.end(), cmp);                         //���б߰���Ȩ��С��������
       for (int i = 0; i < m; ++i)                            //ö�����б�
       {
              int faU = findFather(father, E[i].u);           //��ѯ�˵�u���ڼ��ϵĸ����
              int faV = findFather(father, E[i].v);           //��ѯ�˵�v���ڼ��ϵĸ����
              if (faU != faV) {                               //�������һ��������
                     father[faU] = faV;                       //�ϲ����ϣ��൱�ڰѲ��Ա߼��뵽��С��������
                     ans += E[i].cost;
					 cout<<E[i].u<<"-��"<<E[i].v<<endl;
                     NumEdge++;                               //��ǰ������������1
                     if (NumEdge == n - 1)                    //�������ڶ�������1���㷨����
                           break;
              }
       }
       if (NumEdge != n - 1)                                  //�޷���ͨʱ����-1
              return -1;
       else
              return ans;                                     //������С��������Ȩ֮��
}
 



int prim(int cur)
{
	int index = cur;
	int sum = 0;       //���·���� 
	int i = 0 , j = 0;
	cout << index << "->";
	memset(visit,false, sizeof(visit));  //��ĳһ���ڴ��е�����ȫ������Ϊָ����ֵ�� �������ͨ��Ϊ��������ڴ�����ʼ������
	visit[cur] = true;
	for(i = 0; i < N; i++)
		lowcost[i] = map[cur][i];//��ʼ������cur������������ı߷��� 

	for(i = 1; i < N; i++)//����forѭ�� ����ÿһ�����
	{
		int min= INF;   //����һ������min��ʼ��Ϊһ������ֵ 
		//��һ��forѭ��  δ���ʵĵ�����������index�ıȽ�
		for(j = 0; j < N; j++)
		{
			if(!visit[j] && lowcost[j] < min)//�ҵ�δ���ʵĵ��У����뵱ǰ��С������������С�ĵ�
			{
				min = lowcost[j];  //���ϸ������cur�����������̾��룬��lowcost[j]Ȩֵ�������ݵ�min�� ����Ȩֵ 
				index = j;//��j�����±���µ�index�У���cur�����½�� 
			}
		}
		visit[index] = true;//��Ǿ�����̵Ľ���Ѿ������ʹ�
		cout << index << "->";//����½�� 
		sum += min;//Ȩֵ�ۼ� 
		//�ڶ���forѭ��  ��index��㿪ʼ������ͼ�е��½��map[index][j]����С��������lowcost[j]�ɽ��֮���Ȩֵ�����Ƚ� ����lowcost
		for(j = 0; j < N; j++) 
		{
			if(!visit[j] && lowcost[j]>map[index][j])     
			{
				lowcost[j] = map[index][j];
			}
		}
	}
	cout << endl;
	return sum;               //������С����������·��ֵ
}
int main()
{
	cout<<"===============================prim==============================="<<endl;
	cout << prim(0) << endl;//��0��ʼ
	cout << prim(1) << endl;//��1��ʼ
	cout << prim(2) << endl;//��2��ʼ
	cout << prim(3) << endl;//��3��ʼ
	cout << prim(4) << endl;//��4��ʼ
	cout << prim(5) << endl;//��5��ʼ
	

	cout<<"===============================kurskal==============================="<<endl;
	edge medge[10] = {edge(0,1,4),edge(1,2,1),edge(2,3,6),edge(3,4,5),edge(0,4,1),edge(0,5,2),edge(1,5,3),edge(2,5,5),edge(3,5,4),edge(4,5,3)};
	vector<edge> E(medge, medge+10);
	int n = 6;
	int m = 10;
	int res = Kruskal(n, m, E);
	cout << res << endl;

	return 0;
}

