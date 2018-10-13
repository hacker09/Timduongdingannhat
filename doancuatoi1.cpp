#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define maxN 100
#define maxC 10000

int d[maxN],c[maxN][maxN], trace[maxN], n, m, s, f,Cmax;
bool Free[maxN];
ifstream input;
ofstream output;


// n: so dinh; m: so canh; s: dinh dau; f: dinh cuoi
// d[i]: duong di ngan nhat tu s den i
// mang c[][]: do thi 
int input_so()
{
	int check , a;
	tiep:
	check = scanf("%d" , &a);
	fflush(stdin);
	if( check == 0 ){
		cout << "Ban nhap sai, nhap lai dinh! : ";
		goto tiep;
		
	}else{
		return a;
	}
	
}
/* int input_file()
{
	input.open("E:\\filevao.txt");
	FILE *input;
	//khai bao
	tiep:
		if(!input){
			cout << " File khong ton tai,tao file moi ! \n";
			output.open("E:\\filevao2.txt");
			return 0;
			}
				
					cout << "File hop le, bat dau ! \n";
					return 0;
					
     } */
   
int readData()
{
	
	input.open("D:\\filevao.txt");
		if ( input.fail() ) {
    			cout <<"      ------  File khong ton tai!  --------\n ";
		        //cout <<"      ------    Ban kiem tra lai file! --------\n";
		        return 0;
		        
		
                            } else {
                            	
                            	 cout <<"    --> Bat dau doc file -->   \n";
	
                            	  }
							  

	
	//	cout << "doc n, m, s, f tu file" << endl;

	
	input >> n >> m ;


	
	cout <<"\n";
	do{
		cout <<"\n    Nhap dinh dau : "; 
	    s = input_so();
	}while( s > n || s < 1);
	
	do{
		cout <<"\n    Nhap dinh cuoi : ";
		
	f = input_so();
	cout <<endl;
	}while( f > n || f < 1 );
	
	
	
	//khoi tao mang 2 chieu c[u][v]
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i == j) c[i][j] = 0; else c[i][j] = maxC;
			
	// m dong chua 3 so u, v, c[u][v];
		cout << "x/y";
	for (int i = 0; i < n; i++) cout << setw(7) << i+1;
	cout << endl;
	
	for (int i = 1; i <= m; i ++)
	{
		int u, v, x;
		input >> u >> v >> x;
		c[u][v] = c[v][u] = x;// do thi 2 vo huong
	}
		for ( int i = 1; i <= n; i++){
			
	    for ( int j = 1; j <= n; j++){

	   	cout << c[i][j] << " ";
	   }
	   cout << "\n";
	}
	
	input.close();
	return 1;
}

void init()
{	//Tinh gia tri vo cung Cmax
	for(int i=1; i <= n; i++)
		for(int j=1; j<=n; j++)
		{
			Cmax+=c[i][j];
		}
	
	//dat gia tri vo cung vao cac cap dinh khong noi nhau
	for(int i=1;i <= n; i++)
		for(int j=0; j<=n; j++)
		{
			if (( i != j ) &&( c[i][j] == 0 )) c[i][j]=Cmax;
		 } 
	for(int i=1; i<=n;i++) 
	{
	   d[i]=Cmax;
	   Free[i]=true;
	}
	d[s]=0; Free[s]=false;
}

void Dijkstra()
{
	int i,v,w,min;
   
   for (i=1; i<=n; i++) 

   {
      d[i]=c[s][i]; 
	  trace[i]=s;
   }
    for (int j=1; j<n; j++)//dem buoc
    {   
	 	min=Cmax; w=0;
	 	for(i=1; i<=n;i++) 
		    if ((Free[i]==true)&&(d[i]<min)) 
		    {
		      min=d[i];	
		      w=i;
		    }
  			if(w==0) break;
        //co dinh nhan w da chon
	    Free[w]=false; 
	    //Dung w de toi uu nhung dinh ke voi w
	    for (v=1; v<=n; v++)
	     {
		   if (( Free[v] == true) && ( d[v] > d[w] + c[w][v] ))
	         { 	
			    d[v] = d[w] + c[w][v];
	      	    trace[v] = w;
	         }
	     }
    }
}

void Ford_Bellman()
{
	bool stop;
	for (int i = 1; i <= n - 1; i ++)
	{
		stop = true;
		for (int u = 1; u <= n; u ++)
			for (int v = 1; v <= n; v ++)
				if (d[v] > (d[u] + c[u][v]))
				{
					d[v] = d[u] + c[u][v];
					trace[v] = u;// luu vet cua duong di
					stop = false;
				}
		if (stop) break;
	}
	
}
		

void printResult()
{
	int i;
	output.open("E:\\filera.txt");
	
	if (d[f] == maxC)
	 { 
	            
				output << "khong co duong di tu "<< s <<" den "<< f << endl;
				cout << endl;
	            cout << "khong co duong di tu "<< s <<" den "<< f << endl;
	 }
	else
	{
		
		output << "  duong di tu "<< s <<" den "<< f <<" la : " << d[f] << endl;
		cout << endl;
		cout << "  duong di tu "<< s <<" den "<< f <<" la : " << d[f] << endl;
		
		// truy vet
		i = f;
		int b[100], dem =0;
		
		while (i != s)
		{
			b[dem] = i ;
			i = trace[i];
			dem ++;
		}
		b[dem]=s;
		for(int k = dem; k > 0; k--)
		{	
		    cout << "  " << b[k] <<"-->" ;
			output << "  " << b[k] << "-->" ;
			
			
			
		}
		
		    cout << f;
			output << f;
	}
	output.close();
}
void Menu(int &select)
{
	cout << endl << "   Moi ban chon thuat toan :\n"<< endl;
	cout << "        1: Thuat toan Dijkstra\n"<< endl;
	cout << "        2: Thuat toan Bellman_Ford\n"<< endl;
	cout << "        3: Thoat !\n\n"<< endl;
	cin  >> select;
}

int main(){
		cout << "==================DO AN TIM DUONG DI NGAN NHAT===================\n";
	    cout << "* Bui Duc Lam     \t     Lop 15T1 \n";
	    cout << "* Nguyen Cong Trung\t     Lop 15T1\n ";
	    cout << "==============================================================\n";
	    cout << "Ban co ma tran ban dau la : \n";
	
	int select=1;
	
	while (select)
	{
		Menu(select);
		switch (select)
		{
			case 1:
			{
				cout << "\n    Tim duong di ngan nhat bang thuat toan Dijkstra !\n";
				if(readData() == 0)
					break;
        		init();
	    		Dijkstra();
	    		printResult();
	    		cout << "\n   Xem ket qua tai filera.txt!!!\n";
				break;
			} 
			case 2:
			{
				cout << "\n    Tim duong di ngan nhat bang thuat toan Bellman_Ford !\n";
				readData();
	    		init();
        		Ford_Bellman();
	    		printResult();
	    		cout<<"\n   Xem ket qua tai filera.txt!!!\n";
				break;
			}
		}
		if (select == 3) break;
	}
	
	return 0;
}


