#include<bits/stdc++.h> 
using namespace std;

int main()
{
	bool c;
	int sum;
	string str,s;
	cout << "Enter Large Number : ";
	cin >> str;
	
	int pos = str.find(",");
	
	string s1=str.substr(0,pos),s2=str.substr(pos+1);
	
	reverse(s1.begin(),s1.end());
	reverse(s2.begin(),s2.end());
	
	if(s1.size() > s2.size())
	{
		for(int i=0;i<s1.size();i++)
		{
			if(i >= s2.size())
			{
				if(c == 1)
				{
					s.push_back(s1[i]+1);
				}
				else
					s.push_back(s1[i]);
			}
			else
			{
				sum=(s1[i]-'0' + s2[i]-'0');
				if(c == 1)
				{
					s.push_back((sum%10)+'0'+1);
					c=false;
				}
				else
					s.push_back((sum%10)+'0');
				if(sum >= 10)
					c=1;
			}
		}
	}
	else // s2 > s1
	{
		for(int i=0;i<s2.size();i++)
		{
			if(i >= s1.size())
			{
				if(c == 1)
				{
					s.push_back(s2[i]+1);
				}
				else
					s.push_back(s2[i]);
			}
			else
			{
				sum=(s1[i]-'0' + s2[i]-'0');
				if(c == 1)
				{
					s.push_back((sum%10)+'0'+1);
					c=false;
				}
				else
					s.push_back((sum%10)+'0');
				if(sum >= 10)
					c=1;
			}
		}
	}	
	for(int i=s.size()-1;i>=0;i--)
		printf("%c",s[i]);
	
	return 0;
}
