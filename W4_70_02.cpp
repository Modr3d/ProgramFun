#include<bits/stdc++.h>
using namespace std;

string sum(string a, string b){
	
    string result="";
    while(a.size() < b.size())
		a="0"+a;
    while(b.size() < a.size()) 
		b="0"+b;
		
    int left=0;
    
    for(int i=a.length()-1;i>=0;i--)
    {
        int temp=a[i]-48 + b[i]-48 + left;
        left=temp/10;
        temp=temp%10;
        result=(char)(temp+48)+result;
    }
    
    if(left>0) 
		result="1"+result;
		
    return result;
}

int main()
{
	string str;
	cout << "Enter Large Number : ";
	cin >> str;
	
	int pos = str.find(","),count=0;
	
	string a=str.substr(0,pos),b=str.substr(pos+1);
	
	cout << sum(a,b);
	
	
	return 0;
}
