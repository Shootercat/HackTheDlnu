#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;

struct node_filesystem                      //�ļ�ϵͳ  ���
{
    string name;                            //�˽������

    string document[1000];                  //�ļ���㣬�����������ļ���
    int    document_length;
    node_filesystem *filedir[1000];         //
    int              filedir_length;

    node_filesystem *pri_dir;

    node_filesystem()
    {
        document_length = 0;
        filedir_length = 0;
    }
};

node_filesystem *rootdir = new node_filesystem();                    //��Ŀ¼


node_filesystem *workpoint ;                //����ָ��

int filesystem_read(string filename)        //�ļ�ϵͳ
{
    rootdir->pri_dir = NULL;
    rootdir->name = "/";
    workpoint = rootdir;
    filename = "FileSystem\\" + filename;

    ifstream infile(filename.c_str());

	if(!infile)
	{
		cerr << "��ʼ�ļ���ȡ����" <<filename<<"\n";
		return 1;
	}

	string fileinput;
	string fileflag = "-";
    while(infile>>fileinput)
	{
	    int flag = 0;
	    for(int i = fileflag.length() - 1; i >= 0  ; i --)       //�ļ��жϱ�־���жϵ�ǰ¼������ļ������ļ���
        {
            if(fileinput[i] != fileflag[i])
            {
                if(fileinput[i] == '+')
                {
                    flag = 1;
                    break;
                }
                else
                {
                    workpoint = workpoint->pri_dir;
                    fileflag = fileflag.substr(0,fileflag.length()-1);
                }
            }
        }
        if (flag)
        {
            node_filesystem *newfilepoint = new node_filesystem();
            newfilepoint->name = fileinput.substr(fileflag.length(),fileinput.length());
            newfilepoint->pri_dir = workpoint;
            workpoint->filedir[workpoint->filedir_length++] = newfilepoint;
            workpoint = workpoint->filedir[workpoint->filedir_length - 1];
            fileflag += "-";
        }
        else
        {
            workpoint->document[workpoint->document_length++] = fileinput.substr(fileflag.length(),fileinput.length());
        }
	}
	infile.close();
	workpoint = rootdir;
}

void command_ls()
{
    cout<<endl;
    for(int i = 0; i < workpoint->filedir_length ; i++)
    {
        cout<<workpoint->filedir[i]->name<<" <dir>"<<endl;
    }
    for(int i = 0; i < workpoint->document_length ; i++)
    {
        cout<<workpoint->document[i]<<endl;
    }
    cout<<endl
        <<workpoint->document_length<<"  file(s)"<<endl
        <<workpoint->filedir_length<<"  folder(s)"<<endl<<endl;
}

void command_cd(string inputdir)
{
    if(inputdir == "")
    {
        cout<<endl
            <<"Syntax error! Correct syntax : cd foldername"<<endl<<endl;
        return ;
    }
    if(inputdir == "..")
    {
        if(workpoint->pri_dir != NULL)
        {
           workpoint = workpoint->pri_dir;
        }
        return ;
    }
    for(int i = 0 ; i < workpoint->filedir_length ; i++)
    {
        if(inputdir == workpoint->filedir[i]->name)
        {
            workpoint = workpoint->filedir[i];
            return ;
        }
    }
    cout<<endl<< "cannot find the folder "<<inputdir<<endl<<endl;
}

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


int command(string inputcommand)            //����ϵͳ
{
	istringstream inputcommand_stream(inputcommand);

	while(inputcommand_stream>>inputcommand)
	{
		int temp = calculatecommand(inputcommand);

		switch (temp)
		{
		case 104358:			//exit   ��ֵ210�����Լ�����
			{
				exit(0);
				break;
			}
        case 1585264:           //clear ����
            {
                system("cls");
                return 0;
            }
        case 82:            //cd
            {
                string inputdir;
                inputcommand_stream>>inputdir;
                command_cd(inputdir);
                return 0;
            }
        case 331:            //ls
            {
                command_ls();
                return 0;
            }
        case 2956:           //dir
            {
                return 0;
            }
        case 144316:           //help
            {
                return 0;
            }
		default :
			{
			    return 1;
			}
		}
	}
}


void welcomeinformation()                  //��ӭ��Ϣ
{
    cout<<"Hack The Dlnu -Console Command"<<endl
        <<"         -version 0.1"<<endl
        <<"         By  Vic_"<<endl                                //�Լ������ֲ���
        <<endl
        <<"---------------------------------------"<<endl
        <<"Input \"help\" get help;"<<endl
        <<endl;
}


int main ()
{
    welcomeinformation();
    // filesystem_read
    filesystem_read("default.htd");
	while(1)
	{
		string inputcommand = "";
		cout<<"[Vic@"<<workpoint->name<<"]#";
		getline(cin,inputcommand);
		if(command(inputcommand))
        {
            cout<<endl<<"   Unknown  command"<<endl<<endl;
        }
	}
	return 0;
}
