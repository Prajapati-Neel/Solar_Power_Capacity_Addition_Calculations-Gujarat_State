#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream ifile;
	ofstream ofile;
	char temp_string[400];
	char Final_string[1100];
	int c_counter;
	int t_counter=0;
	ifile.open("Master File.txt");
	ofile.open("Step-1 Master file with 60 characters in each column.text");
	while(ifile)
	{
		ifile.getline(temp_string,400);
		c_counter=0;
		t_counter=0;
		for(int i=0;temp_string[i]!='\0';i++)
		{
			if(temp_string[i]!='\t')
			{
				Final_string[c_counter]=temp_string[i];
				c_counter++;
				t_counter++;
			}
			else
			{
				while(t_counter<=60)
				{
					Final_string[c_counter]=' ';
					c_counter++;
					t_counter++;	
				}
				t_counter=0;
			}
		}
		ofile.write(Final_string,c_counter);
		if(!ifile.eof())
		{
				ofile.write("\n",1);
		}
		
	}
	/*{//block of code for finding unique charcters in the file 
		while(ifile)
		{
			char charcters[100];
			int c_top=0;
			ifile.getline(temp_string,400);
	
			for(int i=0;temp_string[i]!='\0';i++)
			{
				for(int j=0;j<=c_top;j++)
				{
					if(temp_string[i]==charcters[j])
					{
						break;
					}else if(j==c_top){
						
						charcters[c_top]=temp_string[i];
						c_top++;
						break;					
					}
				}
			}		
			lines_processed++;
		}
		cout<<"total="<<it<<"   charcters"<<c_top<<"\n";
		for(int i=0;i<c_top;i++)
		{
			cout<<"\'"<<charcters[i]<<"\'-"<<(int)charcters[i]<<",";
			
		}
		ofile.write(charcters,c_top);	
	}*/
	
	
}
	
