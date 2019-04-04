#include<iostream>
#include<fstream>
#include<string>
#define MAX_SIZE 1000
#define INFINITY 99999
using namespace std;

struct Vertex//���� 
{
	int tag;//��Ǵ˶����Ƿ���� 
	string name,info;
};

struct ArcNode 
{
	int n;
	ArcNode *next;
};

struct VNode//�ڽӱ� 
{
	Vertex vex;
	ArcNode *next;
}AdjList[MAX_SIZE];

struct Graph//ͼ 
{
	int arc[MAX_SIZE][MAX_SIZE];
	int vexnum;
	int edgnum;
	int maxvexno; 
}G;

int created=0;//��ʾδ����ͼ 

void Menu()//�˵��� 
{
	printf("---------------��������ϵͳ���ܲ˵�---------------\n");
	printf("1-----����ͼ\n");
	printf("2-----��ѯ������Ϣ\n");
	printf("3-----���ξ��㵼��\n");
	printf("4-----�������·��\n");
	printf("5-----�����·�滮\n");
	printf("6-----�޸�ͼ\n"); 
	printf("7-----�˳����˵�\n"); 
	printf("�����빦�����ִ�й��ܣ�\n");
}

void CreatAdjList()//�����ڽӱ� 
{
	for(int i=0;i<=G.maxvexno;i++) 
		if(AdjList[i].vex.tag)
		{
			ArcNode *a;
			AdjList[i].next=NULL;
			for(int j=G.maxvexno;j>=0;j--)
				if(AdjList[j].vex.tag)
					if(G.arc[i][j]<INFINITY)
					{
						a=new ArcNode;
						a->n=j;
						a->next=AdjList[i].next;
						AdjList[i].next=a;
					}
		}
}

void CreatMap()//�����ļ����ݴ���ͼ��������ڽӱ� 
{
	int m,t,i,j;
	//��ȡVex.txt�ļ��ľ�����Ϣ 
	fstream f1("./Vex.txt",ios::in); 
	f1>>G.vexnum;
	t=0;//��¼�Ѷ�ȡ������Ϣ���� 
	for(i=0;t<G.vexnum;i++)
	{
		f1>>m;
		while(i!=m)
		{
			AdjList[i].vex.tag=0;//���Ϊi�ľ��㲻���ڣ����Ϊ0 
			i++;
		}
		AdjList[m].vex.tag=1; //������ڣ����Ϊ1 
		t++;
		f1>>AdjList[m].vex.name>>AdjList[m].vex.info;//��vex.txt�ļ��ж�ȡ������Ϣ 
	}
	G.maxvexno=m;//��¼���������� 
	f1.close();
	
	//��ʼ����·������ 
	for(i=0;i<=G.maxvexno;i++)
		if(AdjList[i].vex.tag)
			for(j=0;j<=G.maxvexno;j++)
				if(AdjList[j].vex.tag)
					G.arc[i][j]=INFINITY;//��ʼ������������ΪINFINITY 
	
	//��ȡEdge.txt��·����Ϣ 
	fstream f2("./Edge.txt",ios::in);
	G.edgnum=0;
	while(f2>>i>>j)
	{
		f2>>G.arc[i][j];
		G.arc[j][i]=G.arc[i][j];//��Edge.txt�ļ��ж�ȡ�������룬���ļ���δ���������������򱣳ֳ�ʼ��INFINITY 
		G.edgnum++;
	}
	f2.close();
	
	created=1;//��ʾ�Ѿ�����ͼ 
	
	//�����ڽӱ� 
	CreatAdjList(); 
	
	//չʾ�ڽӱ� 
	cout<<"�ڽӱ����£�"<<endl;//��ʽΪV1->V2->V3 
	for(i=0;i<=G.maxvexno;i++)
		if(AdjList[i].vex.tag)
		{
			cout<<'V'<<i;
			ArcNode *an=AdjList[i].next;
			while(an)
			{
				cout<<"->V"<<an->n;
				an=an->next;
			}
			cout<<endl;
		}
}

void SearchVex(int n)//���ұ��Ϊn�ľ��� 
{
	if(created)//ͼ�ѱ����� 
	{ 
		if(n<0||n>G.maxvexno||AdjList[n].vex.tag==0)//���n�����ļ�����ı�ŷ�Χ�ڻ�����Ϊ0 
			cout<<"�þ��㲻���ڣ�"<<endl;
		else
		{//��������š����ƺ;�����Ϣ���Լ����ڵĸ��������š����ƺ������� 
			cout<<n<<"  "<<AdjList[n].vex.name<<"  "<<AdjList[n].vex.info<<endl;
			cout<<"���ھ��㣺"<<endl;
			for(int i=0;i<=G.maxvexno;i++)
				if(AdjList[i].vex.tag) 
					if(G.arc[i][n]<INFINITY)
						cout<<i<<"  "<<AdjList[i].vex.name<<"  "<<G.arc[i][n]<<endl; 
		}
	}
	else//ͼδ������ 
		cout<<"��δ��ȡ�ļ�����ͼ��"<<endl;
}

void DFS(int n,int count,int *a,int *no)//DFS����·�� 
{
	int *DVisited=new int[G.maxvexno+1];//������ 
	int *BVisited=new int[G.maxvexno+1];//������ 
	for(int i=0;i<=G.maxvexno;i++)
		if(AdjList[i].vex.tag)
		{
			DVisited[i]=a[i];//����ǰ�����������ı�� 
			BVisited[i]=0;//�����δ������ 
		}
	
	no[count++]=n;
	DVisited[n]=1;//�������ѷ��ʹ� 
	ArcNode *an=AdjList[n].next;
	while(an)//����������ö���������ÿ������ 
	{
		while(BVisited[an->n]||DVisited[an->n])//����������ѷ��ʹ�������һ������ 
		{
			an=an->next;
			if(an==NULL)break;
		}
		if(an)
		{
			DFS(an->n,count,DVisited,no);//�Դ˶������DFS���� 
			BVisited[an->n]=1;//��Ǵ˶�������ѷ��ʹ� 
			an=an->next;
		}
	}
	
	if(count==G.vexnum)//�����·���϶��������ܶ�������ͬ��˵����·���޻�· 
	{
		for(int i=0;i<count-1;i++)//���·�� 
			cout<<AdjList[no[i]].vex.name<<"-->";
		cout<<AdjList[count-1].vex.name<<endl;
	}
}

void Navigation_DFS(int n)//DFS�㷨�ӱ��Ϊn�ľ��㿪ʼ�޻�·����ȫͼ 
{
	if(created)//ͼ�ѱ����� 
	{ 
		if(n<0||n>G.maxvexno||AdjList[n].vex.tag==0)//���n�����ļ�����ı�ŷ�Χ�ڻ򶥵���Ϊ0 
			cout<<"�þ��㲻���ڣ�"<<endl;
		else
		{
			int count=1;//sum��¼�޻�··��������count��¼����·�����������Ķ��� 
			int *BVisited=new int[G.maxvexno+1];//������ 
			int *DVisited=new int[G.maxvexno+1];//������ 
			int *no=new int[G.vexnum];//��¼·���ϵĶ����� 
			
			for(int i=0;i<=G.maxvexno;i++)
				if(AdjList[i].vex.tag)
				{
					DVisited[i]=0;//����ǰ�����������ı�� 
					BVisited[i]=0;//�����δ������ 
				}
	
			no[0]=n;//��¼��� 
			DVisited[n]=1;//��������ѷ��ʹ� 
	
			ArcNode *an=AdjList[n].next;
			while(an)//����������ö���������ÿ������ 
			{
				while(BVisited[an->n])//����������ѷ��ʹ�������һ������ 
				{
					an=an->next;
					if(an=NULL)break;
				}
				if(an)
				{
					DFS(an->n,count,DVisited,no);//�Դ˶������DFS���� 
					BVisited[an->n]=1;//��Ǵ˶�������ѷ��ʹ� 
					an=an->next;
				}
			}
		}
	}
	else//ͼδ������ 
		cout<<"��δ��ȡ�ļ�����ͼ��"<<endl;
}

void ShortestPath_DIJ(int m,int n)//Dijkstra�㷨����m���������n���������·�� 
{
	if(created)
	{
		if(m<0||m>G.maxvexno||AdjList[m].vex.tag==0||n<0||n>G.maxvexno||AdjList[n].vex.tag==0)
			cout<<"���㲻����"<<endl;
		else
		{
			int *Pre=new int[G.maxvexno+1];//��¼��ǰ�����ǰһ���� 
			int *Dis=new int[G.maxvexno+1];//��㵽��������ĵ�ǰ��̾��� 
			int *final=new int[G.maxvexno+1];// ��¼�Ƿ����ҵ���㵽������������·�� 
	
			for(int i=0;i<=G.maxvexno;i++)//��ʼ�� 
				if(AdjList[i].vex.tag)
				{
					final[i]=0;//��ʾ��㵽�����������̾����δ�ҵ� 
					Dis[i]=G.arc[m][i];//��ʼ����㵽�����������̾��룬����������ľ������ߵľ��룬�������INFINITY 
					if(Dis[i]<INFINITY)
						Pre[i]=m;//��̾���С��INFINITY���������������������ǰһ����Ϊ��� 
					else
						Pre[i]=-1;//������Ϊ-1����ʾ��ǰһ���� 
				}
			Dis[m]=0;//��㵽�������Ϊ0 
			final[m]=1;//��㵽������ҵ����·�� 
			
			for(int i=0;i<=G.maxvexno;i++)
				if(AdjList[i].vex.tag)
				{
					int min=INFINITY;//��¼���������ľ��� 
					int v=-1;//��¼���������ĵ� 
					for(int j=1;j<=G.maxvexno;j++)//��δ�ҵ����·���Ķ������ҵ����������Ķ��� 
						if(AdjList[j].vex.tag)
							if(!final[j]&&Dis[j]<min)
							{
								min=Dis[j];
								v=j; 
							} 
					final[v]=1;//��㵽�õ����ҵ���̾��� 
					for(int j=0;j<=G.maxvexno;j++)
						if(AdjList[j].vex.tag)
							if(!final[j]&&(min+G.arc[v][j]<Dis[j]))//������㵽�������̾��� 
							{
								Dis[j]=min+G.arc[v][j];
								Pre[j]=v;//��¼ǰһ���� 
							}
				}
			
			cout<<"��"<<AdjList[m].vex.name<<"��"<<AdjList[n].vex.name; 
			if(Dis[n]<INFINITY)//�������·�� 
			{
				cout<<"���·���ܳ���Ϊ"<<Dis[n]<<"  ���·��(����)���£�"<<endl; 
				cout<<AdjList[n].vex.name;
				int v=Pre[n];
				while(v!=m)
				{
					cout<<"<--"<<AdjList[v].vex.name;
					v=Pre[v];
				}
				cout<<"<--"<<AdjList[m].vex.name<<endl;
			}
			else
				cout<<"��ͨ��"<<endl;
		}
	}
	else//ͼδ������ 
		cout<<"��δ��ȡ�ļ�����ͼ��"<<endl;
}

void WirePath_Prim()//Prim�㷨��������̵�· 
{
	struct
	{
		int vexno;
		int lowcost;
	}closedge[MAX_SIZE];//��¼��ǰ�Ѿ�ȷ���ĵ㼯��ĳ����i����̾��뼰��Ӧ������ 
	
	int sum=0;//�ܳ���
	int t;//��¼һ�������ţ��Դ˶���Ϊ��� 
	
	for(int i=0;i<=G.maxvexno;i++)//��t 
		if(AdjList[i].vex.tag)
		{
			t=i;
			break;
		}
	
	for(int i=0;i<=G.maxvexno;i++)//��ʼ����ȷ���㼯����t 
		if(AdjList[i].vex.tag)
		{
			closedge[i].vexno=t;
			closedge[i].lowcost=G.arc[t][i];
		}
	closedge[t].lowcost=0;//��ʾ�ö���������ȷ���㼯 
	
	for(int i=1;i<=G.vexnum;i++)//������G.vexnum-1�����㲢����ȷ���㼯�� 
	{
		int vex2=-1,vex1=-1,min=INFINITY;
		for(int j=0;j<=G.maxvexno;j++)//������ȷ���㼯��������Ķ��� 
			if(AdjList[j].vex.tag)
				if(closedge[j].lowcost>0&&closedge[j].lowcost<INFINITY)
					if(closedge[j].lowcost<min)
					{
						min=closedge[j].lowcost;
						vex2=j;
						vex1=closedge[j].vexno;//��ö�����������ȷ���㼯�е�ĳһ���� 
					}
		
		if(vex1==-1&&vex2==-1)//�������� 
			break;
		
		cout<<AdjList[vex1].vex.name<<"-->"<<AdjList[vex2].vex.name<<"  "<<min<<endl;//�����̾��뼰���ӵ����� 
		closedge[vex2].lowcost=0;//���ö��㲢����ȷ���㼯 
		
		sum+=min;//�ܳ��ȸ��� 
		for(int j=0;j<=G.maxvexno;j++)//������ȷ���㼯�����������̾��� 
			if(G.arc[vex2][j]<closedge[j].lowcost)
			{
				closedge[j].vexno=vex2;
				closedge[j].lowcost=G.arc[vex2][j];
			}
	}
	cout<<"��·�ܳ���"<<sum<<endl;//�����·�ܳ� 
}

void ShowVexTxt()
{
	int n,no;
	string name,info;
	fstream f9("./Vex.txt",ios::in);
	f9>>n;
	cout<<n<<endl;
	for(int i=0;i<n;i++)
	{
		f9>>no>>name>>info;
		cout<<no<<' '<<name<<' '<<info<<endl;
	}
}

void ShowEdgeTxt()
{
	int start,end,dis;
	fstream f10("./Edge.txt",ios::in);
	for(int i=0;i<G.edgnum;i++)
	{
		f10>>start>>end>>dis;
		cout<<start<<' '<<end<<' '<<dis<<endl;
	}
}

int count;//��¼�ѷ��ʶ����� 

void Connect_DFS(int i,int *Visited)
{
	ArcNode *an=AdjList[i].next;
	Visited[i]=1;//����ѷ��ʹ� 
	count++;//�����ѷ��ʹ��ĵ㼯 
	while(an)//������ö���������ÿ������ 
	{
		while(Visited[an->n]||AdjList[an->n].vex.tag==0)//�ѷ��ʹ�������һ������ 
		{
			an=an->next;
			if(an==NULL)break;
		}
		if(an)
		{
			Connect_DFS(an->n,Visited);//�Դ˶������DFS����  
			an=an->next;
		}
	}
}

int IsConnected()
{
	count=0;
	int *Visited=new int[G.maxvexno+1]; //����Ƿ��ѷ��ʹ� 
	for(int i=0;i<=G.maxvexno;i++)
		if(AdjList[i].vex.tag)
			Visited[i]=0;//��ʼ�� 
	for(int i=0;i<=G.maxvexno;i++) 
		if(AdjList[i].vex.tag)
		{
			Connect_DFS(i,Visited);
			break;
		}
		
	if(count==G.vexnum)
		return 1;
	else
		return 0; 
}

void AddVex()//��Ӿ�����Ϣ 
{
	int no,start,end,dis,maxno;
	string name,info;
	

	if(G.vexnum<MAX_SIZE)
	{
		cout<<"��������ӵľ��㼰·��������һ�У������� ���� ��Ϣ �ڶ��У������� ������ ���룩"<<endl;
		cin>>no>>name>>info;
		cin>>start>>end>>dis; 
		if(no<0)
			cout<<"�����Ų��Ϸ������ʧ�ܣ�"<<endl;
		else
		{	
			if(no>G.maxvexno||AdjList[no].vex.tag==0)
			{//��ʼ���þ��������Ϣ 
				AdjList[no].vex.tag=1; 
				AdjList[no].vex.name=name;
				AdjList[no].vex.info=info;
				G.vexnum++;
				maxno=G.maxvexno;
				if(no>G.maxvexno)//��������ţ����������ڵĶ����� 
				{
					for(int i=G.maxvexno+1;i<no;i++)
						AdjList[i].vex.tag=0;
					G.maxvexno=no;
				}	
				for(int i=0;i<=G.maxvexno;i++)//��ʼ��no����������ľ��� 
					if(AdjList[i].vex.tag)
					{
						G.arc[i][no]=INFINITY;
						G.arc[no][i]=INFINITY;
					}
				//���·�� 
				if(start<0||start>G.maxvexno||AdjList[start].vex.tag==0||end<0||end>G.maxvexno||AdjList[end].vex.tag==0)
					cout<<"���㲻���ڣ����ʧ�ܣ�"<<endl;
				else if(dis<=0||dis>=INFINITY)
					cout<<"��·�����볬�ޣ����ʧ�ܣ�"<<endl;
				else if(G.arc[start][end]<INFINITY)
					cout<<"��·���Ѽ�¼�����ʧ�ܣ�"<<endl;
				else
				{
					G.arc[start][end]=dis;
					G.arc[end][start]=dis;
					G.edgnum++;
					CreatAdjList();//�ؽ��ڽӱ� 
					if(IsConnected())//��Ӻ�������ͨͼ 
					{
						fstream f3("./Vex.txt",ios::out); 
						fstream f4("./Edge.txt",ios::out);
						//����Vex�ļ� 
						f3<<G.vexnum<<endl; 
						for(int i=0;i<=G.maxvexno;i++)
							if(AdjList[i].vex.tag)
								f3<<i<<' '<<AdjList[i].vex.name<<' '<<AdjList[i].vex.info<<endl;
						f3.close();
						//����Edge�ļ�
						for(int i=0;i<=G.maxvexno;i++) 
							if(AdjList[i].vex.tag)
								for(int j=i;j<=G.maxvexno;j++)
									if(AdjList[j].vex.tag)
										if(G.arc[i][j]<INFINITY)
											f4<<i<<' '<<j<<' '<<G.arc[i][j]<<endl;;
						f4.close(); 
						cout<<"��Ӿ���ɹ���"<<endl;
						
					}
					else//�������ʧ�� 
					{//����Ϊ���ǰ��ֵ 
						AdjList[no].vex.tag=0; 
						G.vexnum--;
						G.maxvexno=maxno;
						G.arc[start][end]=INFINITY;
						G.arc[end][start]=INFINITY;
						G.edgnum--;
						cout<<"��Ӻ�Ϊ����ͨͼ�����ʧ�ܣ�"<<endl;
					}
					//���´���ͼ 
					CreatMap();	 
				}
			}
			else
				cout<<"�þ����Ѵ��ڣ����ʧ�ܣ�"<<endl;
		}
	}
	else
		cout<<"����洢�����Ѵ����ޣ��޷�����ӣ�"<<endl;
}

void AddEdge()
{
	int start,end,dis; 
	
	//���·�� 
	cout<<"��������ӵ�·������������ ������ ���룩"<<endl;
	cin>>start>>end>>dis; 
	if(start<0||start>G.maxvexno||AdjList[start].vex.tag==0||end<0||end>G.maxvexno||AdjList[end].vex.tag==0)
		cout<<"���㲻���ڣ����ʧ�ܣ�"<<endl;
	else if(dis<=0||dis>=INFINITY)
		cout<<"��·�����볬�ޣ����ʧ�ܣ�"<<endl;
	else if(G.arc[start][end]<INFINITY)
		cout<<"��·���Ѽ�¼�����ʧ�ܣ�"<<endl;
	else
	{
		G.arc[start][end]=dis;
		G.arc[end][start]=dis;
		G.edgnum++;
		CreatAdjList();//�ؽ��ڽӱ� 
		if(IsConnected())//��Ӻ�������ͨͼ 
		{
			fstream f5("./Edge.txt",ios::out);
			//����Edge�ļ�
			for(int i=0;i<=G.maxvexno;i++) 
				if(AdjList[i].vex.tag)
					for(int j=i;j<=G.maxvexno;j++)
						if(AdjList[j].vex.tag)
							if(G.arc[i][j]<INFINITY)
								f5<<i<<' '<<j<<' '<<G.arc[i][j]<<endl;
			f5.close();
			cout<<"���·���ɹ���"<<endl;
		}
		else
		{
			G.arc[start][end]=INFINITY;
			G.arc[end][start]=INFINITY;
			G.edgnum--;
			cout<<"��Ӻ�Ϊ����ͨͼ�����ʧ�ܣ�"<<endl;
		}
		CreatMap();//���´���ͼ 
	}
}

void Add()//��Ӳ��� 
{
	int n,tag;
	while(1)
	{
		tag=0;
		cout<<"Vex.txt���ݶ�ȡ��"<<endl;
		ShowVexTxt();
		cout<<"Edge.txt���ݶ�ȡ��"<<endl;
		ShowEdgeTxt();
		cout<<"--------���ѡ��------"<<endl;
		cout<<"-----<1>����-----" <<endl;
		cout<<"-----<2>·��-----"<<endl;
		cout<<"-----<3>�˳���ǰ�˵�-----"<<endl; 
		cout<<"���빦�����ִ����Ӧ���ܣ�"<<endl;
		cin>>n;
		switch(n)
		{
			case 1:AddVex();break;
			case 2:AddEdge();break;
			case 3:tag=1;break;
			default:cout<<"���๦�����ڿ����������ڴ�����"<<endl;
		}
		if(tag)
			break;
	}
}

void ReviseEdge()
{
	//�޸�·����Ϣ 
	int m,n,start,end,dis;
	cout<<"������Ҫ�޸�·�������·�������������ó���"<<G.edgnum<<"����"<<endl; 
	cin>>n;
	while(n<0||n>G.edgnum)
	{
		cout<<"�ѳ����Ѵ���·�����������������룺"<<endl;
		cin>>n;
	}
	m=n;
	cout<<"����������·������Ϣ������ʽ�������� ������ ���룩"<<endl;
	while(n)
	{
		cin>>start>>end>>dis;
		if(start<0||start>G.maxvexno||AdjList[start].vex.tag==0||end<0||end>G.maxvexno||AdjList[end].vex.tag==0)
			cout<<"���㲻���ڣ������������޸���Ϣ��"<<endl;
		else if(dis<=0||dis>=INFINITY)
			cout<<"��·�����볬�ޣ������������޸���Ϣ��"<<endl;
		else if(G.arc[start][end]==INFINITY)
			cout<<"��·�������ڣ������������޸���Ϣ��"<<endl;
		else
		{
			G.arc[start][end]=dis;
			G.arc[end][start]=dis; 
			n--;
		}
	}
	
	fstream f7("./Edge.txt",ios::out);
	//�����ļ� 
	for(int i=0;i<=G.maxvexno;i++)
		if(AdjList[i].vex.tag)
			for(int j=i;j<=G.maxvexno;j++)
				if(AdjList[j].vex.tag)
					if(G.arc[i][j]<INFINITY)
						f7<<i<<' '<<j<<' '<<G.arc[i][j]<<endl;
	f7.close();
	cout<<m<<"��·����Ϣ�ѳɹ��޸ģ�"<<endl;
	
	CreatMap();//���´���ͼ 
}

void ReviseVex()
{
	int m,n,no;
	string name,info;
	//�޸ľ�����Ϣ 
	cout<<"������Ҫ�޸ĵľ�����Ϣ�ľ�������������ó���"<<G.vexnum<<"����"<<endl;
	cin>>n;
	while(n<0||n>G.vexnum)
	{
		cout<<"�ѳ���Ŀǰ�Ѵ��ھ�����������������룺"<<endl;
		cin>>n;
	}
	m=n;
	cout<<"���������뾰������Ϣ������ʽ����� ������ ���ܣ�"<<endl;
	while(n)
	{
		cin>>no>>name>>info;
		if(no>=0&&no<G.maxvexno&&AdjList[no].vex.tag)
		{
			AdjList[no].vex.name=name;
			AdjList[no].vex.info=info;
			n--;
		}
		else
			cout<<"�þ��㲻���ڣ��������޸���Ϣ��"<<endl;
	}
	
	//�����ļ� 
	fstream f6("./Vex.txt",ios::out); 
	f6<<G.vexnum<<endl;
	for(int i=0;i<=G.maxvexno;i++)
		if(AdjList[i].vex.tag)
			f6<<i<<' '<<AdjList[i].vex.name<<' '<<AdjList[i].vex.info<<endl;
	f6.close();
	cout<<m<<"��������Ϣ�ѳɹ��޸ģ�"<<endl;
	
	CreatMap();//���´���ͼ 
}

void Revise()//�޸Ĳ��� 
{
	int n,tag;
	while(1)
	{
		tag=0;
		cout<<"Vex.txt���ݶ�ȡ��"<<endl;
		ShowVexTxt();
		cout<<"Edge.txt���ݶ�ȡ��"<<endl;
		ShowEdgeTxt();
		cout<<"--------�޸�ѡ��------"<<endl;
		cout<<"-----<1>����-----" <<endl;
		cout<<"-----<2>·��-----"<<endl;
		cout<<"-----<3>�˳���ǰ�˵�-----"<<endl; 
		cout<<"�����빦�����ִ����Ӧ���ܣ�"<<endl; 
		cin>>n;
		switch(n)
		{
			case 1:ReviseVex();break;
			case 2:ReviseEdge();break;
			case 3:tag=1;break;
			default:cout<<"���๦�����ڿ����������ڴ�����"<<endl;
		}
		if(tag)
			break;
	}	
}

void DeleteVex()
{
	int no,maxno;
	
	cout<<"������Ҫɾ���ı�ţ�"<<endl;
	cin>>no;
	if(no<0||no>G.maxvexno||AdjList[no].vex.tag==0)
		cout<<"���㲻���ڣ�ɾ��ʧ�ܣ�"<<endl;
	else
	{
		G.vexnum--;
		AdjList[no].vex.tag=0;//�޸ı�� 
		maxno=G.maxvexno;
		if(no==G.maxvexno)//��������� 
			for(int i=G.maxvexno-1;i>=0;i--)
				if(AdjList[i].vex.tag)
				{
					G.maxvexno=i;
					break;
				}
		CreatAdjList();//�ؽ��ڽӱ� 
		if(IsConnected())
		{
			fstream f8("./Vex.txt",ios::out);
			//����Vex�ļ� 
			f8<<G.vexnum<<endl; 
				for(int i=0;i<=G.maxvexno;i++)
					if(AdjList[i].vex.tag)
						f8<<i<<' '<<AdjList[i].vex.name<<' '<<AdjList[i].vex.info<<endl;
			f8.close();
			
			fstream f9("./Edge.txt",ios::out);
			//����ɾ��������·��������Edge�ļ� 
			G.edgnum=0;
			for(int i=0;i<=G.maxvexno;i++)
				if(AdjList[i].vex.tag)
					for(int j=i;j<=G.maxvexno;j++)
						if(AdjList[j].vex.tag)
							if(G.arc[i][j]<INFINITY)
							{
								f9<<i<<' '<<j<<' '<<G.arc[i][j]<<endl;
								G.edgnum++;
							}
			f9.close();
			cout<<"�ɹ�ɾ�����㣡"<<endl;

		}
		else
		{
			G.vexnum++;
			AdjList[no].vex.tag=1;//�޸ı�� 
			G.maxvexno=maxno;
			cout<<"ɾ����Ϊ����ͨͼ��ɾ��ʧ�ܣ�"<<endl; 
		}
				
		CreatMap();//���´���ͼ 
	}
} 

void DeleteEdge()
{ 
	int n,m,dis,start,end;
	

	//ɾ��·����Ϣ
	cout<<"������Ҫɾ����·�������������ó���"<<G.edgnum-G.vexnum+1<<"����"<<endl;
	cin>>n;
	while(n<0||n>G.edgnum-G.vexnum+1)
	{
		cout<<"�ѳ�����ɾ��·�������ƣ����������룺"<<endl;
		cin>>n;
	}
	m=n;
	cout<<"����������·�����ӵ������㣺����ʽ�������� �����ţ�"<<endl;
	while(n)
	{
		cin>>start>>end;
		if(start<0||start>G.maxvexno||AdjList[start].vex.tag==0||end<0||end>G.maxvexno||AdjList[end].vex.tag==0)
			cout<<"���㲻���ڣ�����������ɾ����Ϣ��"<<endl;
		else if(G.arc[start][end]==INFINITY)
			cout<<"��·�������ڣ�����������ɾ����Ϣ��"<<endl;
		else
		{
			dis=G.arc[start][end];
			G.arc[start][end]=INFINITY;
			G.arc[end][start]=INFINITY;
			G.edgnum--;
			n--;
			CreatAdjList();//�ؽ��ڽӱ� 
			if(IsConnected())
			{
				fstream f10("./Edge.txt",ios::out); 
				//�����ļ� 
				for(int i=0;i<=G.maxvexno;i++)
					if(AdjList[i].vex.tag)
						for(int j=i;j<=G.maxvexno;j++)
							if(AdjList[j].vex.tag)
								if(G.arc[i][j]<INFINITY)
									f10<<i<<' '<<j<<' '<<G.arc[i][j]<<endl;
				f10.close();
				cout<<"�ɹ�ɾ��·����"<<endl;
			} 
			else
			{
				G.arc[start][end]=dis;
				G.arc[end][start]=dis;
				G.edgnum++;
				cout<<"ɾ����Ϊ����ͨͼ��ɾ��ʧ�ܣ�"<<endl;
			}
		}
	}
	cout<<m<<"��·��ɾ����ϣ�"<<endl;
	
	CreatMap();//���´���ͼ 	
}

void Delete()//ɾ������
{
	int n,tag;
	while(1)
	{
		tag=0;
		cout<<"Vex.txt���ݶ�ȡ��"<<endl;
		ShowVexTxt();
		cout<<"Edge.txt���ݶ�ȡ��"<<endl;
		ShowEdgeTxt();
		cout<<"--------ɾ��ѡ��------"<<endl;
		cout<<"-----<1>����-----" <<endl;
		cout<<"-----<2>·��-----"<<endl;
		cout<<"-----<3>�˳���ǰ�˵�-----"<<endl; 
		cout<<"���빦�����ִ����Ӧ���ܣ�"<<endl; 
		cin>>n;
		switch(n)
		{
			case 1:DeleteVex();break;
			case 2:DeleteEdge();break;
			case 3:tag=1;break;
			default:cout<<"���๦�����ڿ����������ڴ�����"<<endl;
		}
		if(tag)
			break;
	}
}

void Edit()
{
	int m;
	if(created)
	{
		while(1)
		{
			int tag=0;
			cout<<"-----�༭�����˵�-----"<<endl; 
			cout<<"-----<1>���-----"<<endl;
			cout<<"-----<2>ɾ��-----"<<endl;
			cout<<"-----<3>�޸�-----"<<endl;
			cout<<"-----<4>�˳����˵�-----";
			cout<<"������ִ����Ӧ������"<<endl;
			cin>>m;
			switch(m)
			{
				case 1:Add();break;
				case 2:Delete();break;
				case 3:Revise();break;	
				case 4:tag=1;break;
				default:cout<<"���๦�����ڿ����У������ڴ�����" <<endl;
			} 
			if(tag)
				break;
		}
	}
	else
		cout<<"��δ��ȡ�ļ�����ͼ��"<<endl;
}

int main()
{
	int tag,m,n;
	while(1)
	{
		tag=0;
		Menu();
		cin>>n;
		switch(n)
		{
			case 1:CreatMap();break;
			case 2:{cout<<"�����뾰����ţ�"<<endl;cin>>n;SearchVex(n);}break;
			case 3:{cout<<"�����뾰����ţ�"<<endl;cin>>n;Navigation_DFS(n);}break;
			case 4:{cout<<"��������ֹ������ţ�"<<endl;cin>>m>>n;ShortestPath_DIJ(m,n);}break;
			case 5:WirePath_Prim();break;
			case 6:Edit();break;
			case 7:tag=1;break;
			default:cout<<"���๦�����ڿ����������ڴ�����"<<endl;
		}
		if(tag)
		break;
	}
	return 0;
 } 
