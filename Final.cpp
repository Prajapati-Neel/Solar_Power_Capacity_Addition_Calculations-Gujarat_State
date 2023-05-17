#include<iostream>
#include<fstream>

using namespace std;

string_match_without_case_sensitivity(char vendor[],char c_vendor[])
{
	int i;
	for(i=0;i<61;i++)
	{
		if(vendor[i]!=c_vendor[i] && ((int)vendor[i])!=(((int)c_vendor[i])-32) && (((int)vendor[i])-32)!=((int)(c_vendor[i])))
		{
			return 0;
		}
	}
	return 1;
}

int character_to_integer(char input_char)
{
	switch (input_char)
	{
		case '0': return 0 ;break;
		case '1': return 1 ;break;
		case '2': return 2 ;break;
		case '3': return 3 ;break;
		case '4': return 4 ;break;
		case '5': return 5 ;break;
		case '6': return 6 ;break;
		case '7': return 7 ;break;
		case '8': return 8 ;break;
		case '9': return 9 ;break;
		case '-': return 0 ;break; 
	}
}

double string_to_float(char input_string[])
{
	int position_of_decimal_point;
	int position_of_last_digit;
	double output=0;
	int i,j,commas=0;
	float temp;
	for(i=0;i<61;i++)
	{
		if(input_string[i]==',')
		{
			commas++;
		}else if(commas>0)
		{
		input_string[i-commas]=input_string[i];
		input_string[i]='\0';	
		}
	}
	for(i=0;i<61;i++)
	{
		if(input_string[i]=='.')
		{
			position_of_decimal_point=i;
		}
		if(input_string[i]==' '||input_string[i]=='\0')
		{
			position_of_last_digit=i-1;
			break;
		}
	}

	for(i=position_of_decimal_point-1;i>=0;i--)
	{
		temp=character_to_integer(input_string[i]);
		for(j=0;j<position_of_decimal_point-1-i;j++)
		{
			temp*=10;
		}
		output+=temp;
	}	
	for(i=position_of_decimal_point+1;i<=position_of_last_digit;i++)
	{	
		temp=character_to_integer(input_string[i]);
		for(j=0;j<i-position_of_decimal_point;j++)
		{
			temp/=10;
		}
		output+=temp;
	}
	if(input_string[0]=='-')
	{
		return -output;	
	}
	else
	{
		return output;
	}
}


int main()
{
	ifstream ifile;
	char read_string[1100];
	char vendor[61];
	double proj_cost,reg_cap,subsidy;
	double total_reg_cap_of_vendor,total_pv_cap_of_vendor,total_inv_cap_of_vendor,total_proj_cost_of_vendor;
	double avg_reg_cap_of_vendor,avg_pv_cap_of_vendor,avg_inv_cap_of_vendor,avg_proj_cost_of_vendor;
	double total_reg_cap=0,total_pv_cap=0,total_inv_cap=0,total_proj_cost=0;
	double avg_reg_cap=0,avg_pv_cap=0,avg_inv_cap=0,avg_proj_cost=0;
	int same_vendor=2,total_no_of_vendors=0,total_no_of_projects_by_vendor=0,total_no_of_projects=0;
	int lines_processed=0,first_line=1;
	int no_of_projects_in_1KW_to_1_99KW=0,no_of_projects_in_2KW_to_2_99KW=0,no_of_projects_in_3KW_to_3_99KW=0,no_of_projects_in_4KW_to_4_99KW=0,no_of_projects_in_5KW_to_6_99KW=0,no_of_projects_in_7KW_to_9_99KW=0,no_of_projects_in_10KW_to_15KW=0,no_of_projects_in_15_01KW_to_30KW=0,no_of_projects_in_more_than_30KW=0;
	double total_cost_of_projects_in_1KW_to_1_99KW=0,total_cost_of_projects_in_2KW_to_2_99KW=0,total_cost_of_projects_in_3KW_to_3_99KW=0,total_cost_of_projects_in_4KW_to_4_99KW=0,total_cost_of_projects_in_5KW_to_6_99KW=0,total_cost_of_projects_in_7KW_to_9_99KW=0,total_cost_of_projects_in_10KW_to_15KW=0,total_cost_of_projects_in_15_01KW_to_30KW=0,total_cost_of_projects_in_more_than_30KW=0;
	double total_reg_cap_of_projects_in_1KW_to_1_99KW=0,total_reg_cap_of_projects_in_2KW_to_2_99KW=0,total_reg_cap_of_projects_in_3KW_to_3_99KW=0,total_reg_cap_of_projects_in_4KW_to_4_99KW=0,total_reg_cap_of_projects_in_5KW_to_6_99KW=0,total_reg_cap_of_projects_in_7KW_to_9_99KW=0,total_reg_cap_of_projects_in_10KW_to_15KW=0,total_reg_cap_of_projects_in_15_01KW_to_30KW=0,total_reg_cap_of_projects_in_more_than_30KW=0;
	double total_subsidy_of_projects_in_1KW_to_1_99KW=0,total_subsidy_of_projects_in_2KW_to_2_99KW=0,total_subsidy_of_projects_in_3KW_to_3_99KW=0,total_subsidy_of_projects_in_4KW_to_4_99KW=0,total_subsidy_of_projects_in_5KW_to_6_99KW=0,total_subsidy_of_projects_in_7KW_to_9_99KW=0,total_subsidy_of_projects_in_10KW_to_15KW=0,total_subsidy_of_projects_in_15_01KW_to_30KW=0,total_subsidy_of_projects_in_more_than_30KW=0;
	
	int i,i_vendor,i_reg_cap,i_pv_cap,i_inv_cap,i_proj_cost,i_subsidy;
	
	printf("%-61s","Vendor");
	printf(" %-12s","Reg cap");
	printf("%-12s","PV cap");
	printf("%-12s","Inv cap");
	printf("%-15s","Cost of Proj");
	printf("%-6s","Proj");
	printf("%-12s","Avg Reg.cap");
	printf("%-12s","Avg PV.cap");
	printf("%-12s","Avg Inv.cap");
	printf("%-18s","Avg Cost of Proj");
	printf("\n");
	for(i=0;i<168;i++)
	{
		printf("=");
	}
	printf("\n");
		
	ifile.open("Step-1 Master file with 60 characters in each column.text");
	ifile.getline(read_string,1100);
	while(!ifile.eof() )//&& lines_processed<715)
	{
		char c_vendor[61],c_reg_cap[61],c_pv_cap[61],c_inv_cap[61],c_proj_cost[61],c_subsidy[61];
		
		ifile.getline(read_string,1100);
		
		for(i=0,i_vendor=244,i_reg_cap=366,i_pv_cap=427,i_inv_cap=488,i_proj_cost=549,i_subsidy=610;i<61;i++)
		{
			c_vendor[i]=read_string[i_vendor++];
			c_reg_cap[i]=read_string[i_reg_cap++];
			c_pv_cap[i]=read_string[i_pv_cap++];
			c_inv_cap[i]=read_string[i_inv_cap++];
			c_proj_cost[i]=read_string[i_proj_cost++];
			c_subsidy[i]=read_string[i_subsidy++];
		}
		reg_cap=string_to_float(c_reg_cap);
		proj_cost=string_to_float(c_proj_cost);
		subsidy=string_to_float(c_subsidy);

		if(1<=reg_cap && reg_cap<=1.99999)		{ no_of_projects_in_1KW_to_1_99KW++; total_cost_of_projects_in_1KW_to_1_99KW+=proj_cost; total_reg_cap_of_projects_in_1KW_to_1_99KW+=reg_cap; total_subsidy_of_projects_in_1KW_to_1_99KW+=subsidy; }
		else if(2<=reg_cap && reg_cap<=2.99999)	{ no_of_projects_in_2KW_to_2_99KW++; total_cost_of_projects_in_2KW_to_2_99KW+=proj_cost; total_reg_cap_of_projects_in_2KW_to_2_99KW+=reg_cap; total_subsidy_of_projects_in_2KW_to_2_99KW+=subsidy; }
		else if(3<=reg_cap && reg_cap<=3.99999)	{ no_of_projects_in_3KW_to_3_99KW++; total_cost_of_projects_in_3KW_to_3_99KW+=proj_cost; total_reg_cap_of_projects_in_3KW_to_3_99KW+=reg_cap; total_subsidy_of_projects_in_3KW_to_3_99KW+=subsidy; }
		else if(4<=reg_cap && reg_cap<=4.99999)	{ no_of_projects_in_4KW_to_4_99KW++; total_cost_of_projects_in_4KW_to_4_99KW+=proj_cost; total_reg_cap_of_projects_in_4KW_to_4_99KW+=reg_cap; total_subsidy_of_projects_in_4KW_to_4_99KW+=subsidy; }
		else if(5<=reg_cap && reg_cap<=6.99999)	{ no_of_projects_in_5KW_to_6_99KW++; total_cost_of_projects_in_5KW_to_6_99KW+=proj_cost; total_reg_cap_of_projects_in_5KW_to_6_99KW+=reg_cap; total_subsidy_of_projects_in_5KW_to_6_99KW+=subsidy; }
		else if(7<=reg_cap && reg_cap<=9.99999)	{ no_of_projects_in_7KW_to_9_99KW++; total_cost_of_projects_in_7KW_to_9_99KW+=proj_cost; total_reg_cap_of_projects_in_7KW_to_9_99KW+=reg_cap; total_subsidy_of_projects_in_7KW_to_9_99KW+=subsidy; }
		else if(10<=reg_cap && reg_cap<=15)		{ no_of_projects_in_10KW_to_15KW++; total_cost_of_projects_in_10KW_to_15KW+=proj_cost; total_reg_cap_of_projects_in_10KW_to_15KW+=reg_cap; total_subsidy_of_projects_in_10KW_to_15KW+=subsidy; }
		else if(15<reg_cap && reg_cap<=30)		{ no_of_projects_in_15_01KW_to_30KW++; total_cost_of_projects_in_15_01KW_to_30KW+=proj_cost; total_reg_cap_of_projects_in_15_01KW_to_30KW+=reg_cap; total_subsidy_of_projects_in_15_01KW_to_30KW+=subsidy; }
		else if(30<reg_cap)						{ no_of_projects_in_more_than_30KW++; total_cost_of_projects_in_more_than_30KW+=proj_cost; total_reg_cap_of_projects_in_more_than_30KW+=reg_cap; total_subsidy_of_projects_in_more_than_30KW+=subsidy; }

		same_vendor=string_match_without_case_sensitivity(vendor,c_vendor);
		if(same_vendor==1)
		{
			total_no_of_projects_by_vendor++;
			total_reg_cap_of_vendor+=reg_cap;
			total_pv_cap_of_vendor+=string_to_float(c_pv_cap);
			total_inv_cap_of_vendor+=string_to_float(c_inv_cap);
			total_proj_cost_of_vendor+=proj_cost;
			
			total_proj_cost+=proj_cost;
			
			if(ifile.eof())
			{
				for(i=0;i<61;i++)
				{
					if(vendor[i]==' '&&(vendor[i-1]==' '||vendor[i+1]==' '))
					{
						if(i%4!=0)
						{
							cout<<vendor[i];	
						}
						else
						{
							cout<<"_";
						}						
					}
					else
					{
						cout<<vendor[i];	
					}
				}
				total_reg_cap+=total_reg_cap_of_vendor;
				total_pv_cap+=total_pv_cap_of_vendor;
				total_inv_cap+=total_inv_cap_of_vendor;
				total_no_of_projects+=total_no_of_projects_by_vendor;

				avg_reg_cap_of_vendor=total_reg_cap_of_vendor/total_no_of_projects_by_vendor;
				avg_pv_cap_of_vendor=total_pv_cap_of_vendor/total_no_of_projects_by_vendor;
				avg_inv_cap_of_vendor=total_inv_cap_of_vendor/total_no_of_projects_by_vendor;
				avg_proj_cost_of_vendor=total_proj_cost_of_vendor/total_no_of_projects_by_vendor;

				printf(" %-12.3f",total_reg_cap_of_vendor);
				printf("%-12.3f",total_pv_cap_of_vendor);
				printf("%-12.3f",total_inv_cap_of_vendor);
				printf("%-15.2f",total_proj_cost_of_vendor);
				printf("%-6d",total_no_of_projects_by_vendor);
				printf("%-12.3f",avg_reg_cap_of_vendor);
				printf("%-12.3f",avg_pv_cap_of_vendor);
				printf("%-12.3f",avg_inv_cap_of_vendor);
				printf("%-18.2f\n",avg_proj_cost_of_vendor);

			}
		}
		else
		{
			if(first_line==1)
			{
				first_line=0;
			}
			else
			{
				for(i=0;i<61;i++)
				{
					if(vendor[i]==' '&&(vendor[i-1]==' '||vendor[i+1]==' '))
					{
						if(i%4!=0)
						{
							cout<<vendor[i];	
						}
						else
						{
							cout<<"_";
						}						
					}
					else
					{
						cout<<vendor[i];	
					}
				}
				total_reg_cap+=total_reg_cap_of_vendor;
				total_pv_cap+=total_pv_cap_of_vendor;
				total_inv_cap+=total_inv_cap_of_vendor;
				total_no_of_projects+=total_no_of_projects_by_vendor;
				
				avg_reg_cap_of_vendor=total_reg_cap_of_vendor/total_no_of_projects_by_vendor;
				avg_pv_cap_of_vendor=total_pv_cap_of_vendor/total_no_of_projects_by_vendor;
				avg_inv_cap_of_vendor=total_inv_cap_of_vendor/total_no_of_projects_by_vendor;
				avg_proj_cost_of_vendor=total_proj_cost_of_vendor/total_no_of_projects_by_vendor;

				printf(" %-12.3f",total_reg_cap_of_vendor);
				printf("%-12.3f",total_pv_cap_of_vendor);
				printf("%-12.3f",total_inv_cap_of_vendor);
				printf("%-15.2f",total_proj_cost_of_vendor);
				printf("%-6d",total_no_of_projects_by_vendor);
				printf("%-12.3f",avg_reg_cap_of_vendor);
				printf("%-12.3f",avg_pv_cap_of_vendor);
				printf("%-12.3f",avg_inv_cap_of_vendor);
				printf("%-18.2f\n",avg_proj_cost_of_vendor);
			}
			for(i=0,i_vendor=244;i<61;i++,i_vendor++)
			{
				vendor[i]=read_string[i_vendor];
			}
			total_no_of_projects_by_vendor=1;
			total_no_of_vendors++;
			total_reg_cap_of_vendor=reg_cap;
			total_pv_cap_of_vendor=string_to_float(c_pv_cap);
			total_inv_cap_of_vendor=string_to_float(c_inv_cap);
			total_proj_cost_of_vendor=proj_cost;
			
			total_proj_cost+=proj_cost;
			
		}
		lines_processed++;
	}
	printf("%15s%5d%15s","Total Vendors -",total_no_of_vendors,"");
	printf("%26s ","Total");
	printf("%-12.3f",total_reg_cap);
	printf("%-12.3f",total_pv_cap);
	printf("%-12.3f",total_inv_cap);
	printf("%-15.2f",total_proj_cost);
	printf("%-d\n",total_no_of_projects);
	printf("%61s ","Average");
	printf("%-12.3f",total_reg_cap/total_no_of_projects);
	printf("%-12.3f",total_pv_cap/total_no_of_projects);
	printf("%-12.3f",total_inv_cap/total_no_of_projects);
	printf("%-15.2f\n\n",total_proj_cost/total_no_of_projects);

	printf("%-20s%-12s%-15s%-15s%-17s%-17s%-12s%-23s%-15s%-15s\n", "Range", "No of proj", "Average Cost", "Avg Subsidy", "Avg Cost per KW", "Avg Sub per KW", "Subsidy %","Cost/KW after Subsidy", "Total Reg cap","Avg Reg cap");//Cost per KW after Subsidy,Avg Reg capacity
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "1KW to 1.999KW", no_of_projects_in_1KW_to_1_99KW, total_cost_of_projects_in_1KW_to_1_99KW/no_of_projects_in_1KW_to_1_99KW, total_subsidy_of_projects_in_1KW_to_1_99KW/no_of_projects_in_1KW_to_1_99KW, total_cost_of_projects_in_1KW_to_1_99KW/total_reg_cap_of_projects_in_1KW_to_1_99KW, total_subsidy_of_projects_in_1KW_to_1_99KW/total_reg_cap_of_projects_in_1KW_to_1_99KW, total_subsidy_of_projects_in_1KW_to_1_99KW/total_cost_of_projects_in_1KW_to_1_99KW*100, (total_cost_of_projects_in_1KW_to_1_99KW-total_subsidy_of_projects_in_1KW_to_1_99KW)/total_reg_cap_of_projects_in_1KW_to_1_99KW, total_reg_cap_of_projects_in_1KW_to_1_99KW, total_reg_cap_of_projects_in_1KW_to_1_99KW/no_of_projects_in_1KW_to_1_99KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "2KW to 2.999KW", no_of_projects_in_2KW_to_2_99KW, total_cost_of_projects_in_2KW_to_2_99KW/no_of_projects_in_2KW_to_2_99KW, total_subsidy_of_projects_in_2KW_to_2_99KW/no_of_projects_in_2KW_to_2_99KW, total_cost_of_projects_in_2KW_to_2_99KW/total_reg_cap_of_projects_in_2KW_to_2_99KW, total_subsidy_of_projects_in_2KW_to_2_99KW/total_reg_cap_of_projects_in_2KW_to_2_99KW, total_subsidy_of_projects_in_2KW_to_2_99KW/total_cost_of_projects_in_2KW_to_2_99KW*100, (total_cost_of_projects_in_2KW_to_2_99KW-total_subsidy_of_projects_in_2KW_to_2_99KW)/total_reg_cap_of_projects_in_2KW_to_2_99KW, total_reg_cap_of_projects_in_2KW_to_2_99KW, total_reg_cap_of_projects_in_2KW_to_2_99KW/no_of_projects_in_2KW_to_2_99KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "3KW to 3.999KW", no_of_projects_in_3KW_to_3_99KW, total_cost_of_projects_in_3KW_to_3_99KW/no_of_projects_in_3KW_to_3_99KW, total_subsidy_of_projects_in_3KW_to_3_99KW/no_of_projects_in_3KW_to_3_99KW, total_cost_of_projects_in_3KW_to_3_99KW/total_reg_cap_of_projects_in_3KW_to_3_99KW, total_subsidy_of_projects_in_3KW_to_3_99KW/total_reg_cap_of_projects_in_3KW_to_3_99KW, total_subsidy_of_projects_in_3KW_to_3_99KW/total_cost_of_projects_in_3KW_to_3_99KW*100, (total_cost_of_projects_in_3KW_to_3_99KW-total_subsidy_of_projects_in_3KW_to_3_99KW)/total_reg_cap_of_projects_in_3KW_to_3_99KW, total_reg_cap_of_projects_in_3KW_to_3_99KW, total_reg_cap_of_projects_in_3KW_to_3_99KW/no_of_projects_in_3KW_to_3_99KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "4KW to 4.999KW", no_of_projects_in_4KW_to_4_99KW, total_cost_of_projects_in_4KW_to_4_99KW/no_of_projects_in_4KW_to_4_99KW, total_subsidy_of_projects_in_4KW_to_4_99KW/no_of_projects_in_4KW_to_4_99KW, total_cost_of_projects_in_4KW_to_4_99KW/total_reg_cap_of_projects_in_4KW_to_4_99KW, total_subsidy_of_projects_in_4KW_to_4_99KW/total_reg_cap_of_projects_in_4KW_to_4_99KW, total_subsidy_of_projects_in_4KW_to_4_99KW/total_cost_of_projects_in_4KW_to_4_99KW*100, (total_cost_of_projects_in_4KW_to_4_99KW-total_subsidy_of_projects_in_4KW_to_4_99KW)/total_reg_cap_of_projects_in_4KW_to_4_99KW, total_reg_cap_of_projects_in_4KW_to_4_99KW, total_reg_cap_of_projects_in_4KW_to_4_99KW/no_of_projects_in_4KW_to_4_99KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "5KW to 6.999KW", no_of_projects_in_5KW_to_6_99KW, total_cost_of_projects_in_5KW_to_6_99KW/no_of_projects_in_5KW_to_6_99KW, total_subsidy_of_projects_in_5KW_to_6_99KW/no_of_projects_in_5KW_to_6_99KW, total_cost_of_projects_in_5KW_to_6_99KW/total_reg_cap_of_projects_in_5KW_to_6_99KW, total_subsidy_of_projects_in_5KW_to_6_99KW/total_reg_cap_of_projects_in_5KW_to_6_99KW, total_subsidy_of_projects_in_5KW_to_6_99KW/total_cost_of_projects_in_5KW_to_6_99KW*100, (total_cost_of_projects_in_5KW_to_6_99KW-total_subsidy_of_projects_in_5KW_to_6_99KW)/total_reg_cap_of_projects_in_5KW_to_6_99KW, total_reg_cap_of_projects_in_5KW_to_6_99KW, total_reg_cap_of_projects_in_5KW_to_6_99KW/no_of_projects_in_5KW_to_6_99KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "7KW to 9.999KW", no_of_projects_in_7KW_to_9_99KW, total_cost_of_projects_in_7KW_to_9_99KW/no_of_projects_in_7KW_to_9_99KW, total_subsidy_of_projects_in_7KW_to_9_99KW/no_of_projects_in_7KW_to_9_99KW, total_cost_of_projects_in_7KW_to_9_99KW/total_reg_cap_of_projects_in_7KW_to_9_99KW, total_subsidy_of_projects_in_7KW_to_9_99KW/total_reg_cap_of_projects_in_7KW_to_9_99KW, total_subsidy_of_projects_in_7KW_to_9_99KW/total_cost_of_projects_in_7KW_to_9_99KW*100, (total_cost_of_projects_in_7KW_to_9_99KW-total_subsidy_of_projects_in_7KW_to_9_99KW)/total_reg_cap_of_projects_in_7KW_to_9_99KW, total_reg_cap_of_projects_in_7KW_to_9_99KW, total_reg_cap_of_projects_in_7KW_to_9_99KW/no_of_projects_in_7KW_to_9_99KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "10KW to 15KW", no_of_projects_in_10KW_to_15KW, total_cost_of_projects_in_10KW_to_15KW/no_of_projects_in_10KW_to_15KW, total_subsidy_of_projects_in_10KW_to_15KW/no_of_projects_in_10KW_to_15KW, total_cost_of_projects_in_10KW_to_15KW/total_reg_cap_of_projects_in_10KW_to_15KW, total_subsidy_of_projects_in_10KW_to_15KW/total_reg_cap_of_projects_in_10KW_to_15KW, total_subsidy_of_projects_in_10KW_to_15KW/total_cost_of_projects_in_10KW_to_15KW*100, (total_cost_of_projects_in_10KW_to_15KW-total_subsidy_of_projects_in_10KW_to_15KW)/total_reg_cap_of_projects_in_10KW_to_15KW, total_reg_cap_of_projects_in_10KW_to_15KW, total_reg_cap_of_projects_in_10KW_to_15KW/no_of_projects_in_10KW_to_15KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "15KW to 30KW", no_of_projects_in_15_01KW_to_30KW, total_cost_of_projects_in_15_01KW_to_30KW/no_of_projects_in_15_01KW_to_30KW, total_subsidy_of_projects_in_15_01KW_to_30KW/no_of_projects_in_15_01KW_to_30KW, total_cost_of_projects_in_15_01KW_to_30KW/total_reg_cap_of_projects_in_15_01KW_to_30KW, total_subsidy_of_projects_in_15_01KW_to_30KW/total_reg_cap_of_projects_in_15_01KW_to_30KW, total_subsidy_of_projects_in_15_01KW_to_30KW/total_cost_of_projects_in_15_01KW_to_30KW*100, (total_cost_of_projects_in_15_01KW_to_30KW-total_subsidy_of_projects_in_15_01KW_to_30KW)/total_reg_cap_of_projects_in_15_01KW_to_30KW, total_reg_cap_of_projects_in_15_01KW_to_30KW, total_reg_cap_of_projects_in_15_01KW_to_30KW/no_of_projects_in_15_01KW_to_30KW);
	printf("%-20s%-12d%-15.2f%-15.2f%-17.2f%-17.2f%-12.2f%-23.2f%-15.3f%-15.3f\n", "More than 30", no_of_projects_in_more_than_30KW, total_cost_of_projects_in_more_than_30KW/no_of_projects_in_more_than_30KW, total_subsidy_of_projects_in_more_than_30KW/no_of_projects_in_more_than_30KW, total_cost_of_projects_in_more_than_30KW/total_reg_cap_of_projects_in_more_than_30KW, total_subsidy_of_projects_in_more_than_30KW/total_reg_cap_of_projects_in_more_than_30KW, total_subsidy_of_projects_in_more_than_30KW/total_cost_of_projects_in_more_than_30KW*100, (total_cost_of_projects_in_more_than_30KW-total_subsidy_of_projects_in_more_than_30KW)/total_reg_cap_of_projects_in_more_than_30KW, total_reg_cap_of_projects_in_more_than_30KW, total_reg_cap_of_projects_in_more_than_30KW/no_of_projects_in_more_than_30KW);
	
}
	
