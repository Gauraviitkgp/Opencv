#include <iostream>

using namespace std;

int max=20;

class box{
public:
	int quantity;
	int value;
	int index;
};

int sum(box A,box B,int* total)
{
	*total=A.value+B.value;
	return A.quantity+B.quantity;
}

int sum(box A,box B,box C,int* total)		
{
	*total=A.value+B.value+C.value;
	return A.quantity+B.quantity+C.quantity;
}

int sum(box A,box B,box C,box D,int* total)		
{
	*total=A.value+B.value+C.value+D.value;
	return A.quantity+B.quantity+C.quantity+D.quantity;
}

int sum(box A,box B,box C,box D,box E,int* total)		
{
	
	*total=A.value+B.value+C.value+D.value+E.value;
	return A.quantity+B.quantity+C.quantity+D.quantity+E.quantity;
}

void calc(box gold[5])
{
	int i=1,j,k,l,m;
	int *total,sm=0,kase=-1;
	total=&sm;
	box *temp[5]={NULL,NULL,NULL,NULL,NULL};
	
	for(i=2;i<=5;i++)
	{
		switch(i)
		{
			case 2: 
				for(j=0;j<5;j++)
				{
					for(k=j+1;k<5;k++)
					{
						if(sum(gold[j],gold[k],total)<=20)
						{
							if(sm>kase)
							{
								kase=sm;
								temp[0]=&gold[j];
								temp[1]=&gold[k];
							}
						}
					}
				}
				break;
			case 3: 
				for(j=0;j<5;j++)
				{
					for(k=j+1;k<5;k++)
					{
						for(l=k+1;l<5;l++)
						{
							if(sum(gold[j],gold[k],gold[l],total)<=20)
							{
								if(sm>kase)
								{
									kase=sm;
									temp[0]=&gold[j];
									temp[1]=&gold[k];
									temp[2]=&gold[l];
								}
							}
						}
					}
				}
				break;
			case 4: 
				for(j=0;j<5;j++)
				{
					for(k=j+1;k<5;k++)
					{
						for(l=k+1;l<5;l++)
						{
							for(m=l+1;m<5;m++)
							{
								if(sum(gold[j],gold[k],gold[l],gold[m],total)<=20)
								{
									if(sm>kase)
									{
										kase=sm;
										temp[0]=&gold[j];
										temp[1]=&gold[k];
										temp[2]=&gold[l];
										temp[3]=&gold[m];
									}
								}
							}
						}
					}
				}
				break;
			case 5:
				if(sum(gold[0],gold[1],gold[2],gold[3],gold[4],total)<=20)
				{
					cout<<sum(gold[0],gold[1],gold[2],gold[3],gold[4],total)<<endl;
					if(sm>kase)
					{
						kase=sm;
						temp[0]=&gold[0];
						temp[1]=&gold[1];
						temp[2]=&gold[2];
						temp[3]=&gold[3];
						temp[4]=&gold[4];
					}
				}
		}
	}
	cout<<"Number of weights to be taken\n";
	for(i=0;i<5;i++)
	{
		if(temp[i]!=NULL)
			cout<<"Element "<<(*temp[i]).index<<" is included\n";
	}
	
}

int main()
{
	box gold[5];
	gold[0].quantity=5;gold[1].quantity=6;gold[2].quantity=5;gold[3].quantity=3;gold[4].quantity=4;
	gold[0].value=1;gold[1].value=8;gold[2].value=4;gold[3].value=6;gold[4].value=7;
	gold[0].index=1;gold[1].index=2;gold[2].index=3;gold[3].index=4;gold[4].index=5;
	calc(gold);
	
}
	