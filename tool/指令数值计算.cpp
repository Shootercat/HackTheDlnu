//********************************************
//      hack the dlnu ָ�����
//          version 0.1
//              by Vic_
//      �����޸��㷨���뱣�����У��������˵��
//********************************************


#include <iostream>
#include <string>
using namespace std;


//������� ����ÿһ�������ֵ������Ȩֵ 26�����磬a     1*26^0
//                                                aa    1*26^1 + 1 *26^0
//                                                az    1*26^1 + 26*26^0
long long calculatecommand(string inputcommand)
{
	long long result = 0 ;
	long long power = 1;
	for(int i = inputcommand.length() -1 ; i >=0  ; i--)
	{
		result +=  power * (inputcommand[i] - 'a' + 1 );
		power *= 26;
	}
	return result;
}


void initprint()
{
    cout<<"���������\n    ΪHack The Dlnu ʹ��"<<endl
        <<"                 by Vic_"<<endl
        <<"----------------------------------"<<endl
        <<endl
        <<"������� ����ÿһ�������ֵ������Ȩֵ 26�����磬a     1*26^0"<<endl
        <<"                                                aa    1*26^1 + 1 *26^0"<<endl
        <<"                                                az    1*26^1 + 26*26^0"<<endl
        <<"֧��13λ����"<<endl
        <<"----------------------------------"<<endl;

}

int main ()
{
    initprint();
	while(1)
	{
	    string inputcommand;
	    cout<<"�������� ��";
        cin>>inputcommand;
        cout<<"\t\t\t\t����ֵΪ��"<<calculatecommand(inputcommand)<<endl;
	}
	return 0;
}
