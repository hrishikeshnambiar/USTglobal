#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
#include<conio.h>
class clinic        //This program is a reminder system
{                   //for a clinic.

private:            //It can Create, Modify ,Add,Delete and View Remiders.

	int patientno;
	int age;
	char name[100];
public:
	int findpatientno()
	{
		return patientno;
	}

void input()
{
	cout<<"Enter the Patient’s name :";
	cin>>name;
	cout<<"Enter patient Number and then age :" ;
	cin>>patientno>>age;
}
void output()
{
	cout<<"Patientno==> "<<patientno<<endl;
	cout<<"Name==> "<<name<<endl;
	cout<<"Age ==> "<<age<<endl;

}
}fileobj,object;
void Create()
{
	char ch='y';
	fstream fil;
	fil.open("first.dat",ios::out| ios::binary);
	while(ch=='y' || ch =='Y')
	{
		fileobj.input();
		fil.write((char*)&fileobj, sizeof(fileobj));
		cout<<"Want to Continue.....(y/n)";
		cin>>ch;
	}
	fil.close();
}

void Add()
{
	char ch='y';
	fstream fil;
	fil.open("first.dat",ios::app| ios::binary);
	while(ch=='y' || ch =='Y')
	{
		fileobj.input();
		fil.write((char*)&fileobj, sizeof(fileobj));
		cout<<"Want to Continue.(y/n)";
		cin>>ch;
	}
	fil.close();
}

void Display()
{
	fstream fil;
	fil.open("first.dat",ios::in| ios::binary);
	cout<<"The reminders are\n";
	if(!fil)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		while(!fil.eof())
		{
			fil.read((char*)&fileobj, sizeof(fileobj));
			if(fil.eof())
			break;
			fileobj.output();
		}
	}
	fil.close();
}

void Modify()
{
	int n;
	long pos;
	char found='f';
	cout<<"Enter Patient number that should be searched to modify:";
	cin>>n;
	fstream fil;
	fil.open("first.dat",ios::in|ios::out|ios::binary);

	while(!fil.eof())
	{
	pos=fil.tellg();
	fil.read((char*)&fileobj, sizeof(fileobj));
	if(fileobj.findpatientno()==n)
	{
	fileobj.input();
	fil.seekp(pos);
	fil.write((char*)&fileobj, sizeof(fileobj));
	found='t';
	break;
	} }
	if(found=='f')
	cout<<"reminder not found\n";
	fil.seekg(0);
	cout<<"now the file contains\n";
	while(!fil.eof())
		{
			fil.read((char*)&object, sizeof(object));
			if(fil.eof())
			break;
			object.output();
		}



	fil.close();
}

void Delete()
{
	int n;
	char confirm='n', found='f';
	cout<<"Enter Patient number that should be searched to delete:";
	cin>>n;
	ofstream off;
	ifstream iff;
	off.open("second.dat",ios::out|ios::binary);
	iff.open("first.dat",ios::in| ios::binary);

	while(!iff.eof())
	{
		iff.read((char*)&fileobj, sizeof(fileobj));
		if(fileobj.findpatientno()==n)
		{
		fileobj.output();
		found='t';
		cout<<"are you sure, you want to delete this reminder?(y/n)";
		cin>>confirm;
		if(confirm=='n')
		off.write((char*)&fileobj, sizeof(fileobj));
		else
		continue;
		}
		else
		off.write((char*)&fileobj, sizeof(fileobj));
	}
		if(found=='f')
		cout<<"reminder not found\n";
		iff.close();
		off.close();
		remove("first.dat");
		rename("second.dat", "first.dat");
		iff.open("first.dat",ios::in| ios::binary);
		cout<<"now the file contains\n";
		while(!iff.eof())
		{
			iff.read((char*)&object,sizeof(object));
			if(iff.eof())
			break;
			object.output();
		}
	iff.close();

}
int main()
{
	int opt=0;
	while(1)
	{
		clrscr();
		cout<<"1.Create New Data Base"<<endl;
		cout<<"2.Add New Reminder in Data Base"<<endl;
		cout<<"3.Display Reminder From Data Base"<<endl;
		cout<<"4.Modify Reminder From Data Base"<<endl;
		cout<<"5.Delete Reminder From Data Base"<<endl;
		cout<<"6.Exit From the Program"<<endl;
		cout<<"Enter your Option : "<<endl;
		cin>>opt;
		switch(opt)
		{
			case 1:
			{
				Create();
				cout<<"Press any key to Display Main Menu"<<endl;
				getch();
				break;
			}
			case 2:
			{
				Add();
				cout<<"Press any key to Display Main Menu"<<endl;
				getch();
				break;
			}
			case 3:
			{
				Display();
				cout<<"Press any key to Display Main Menu"<<endl;
				getch();
				break;
			}

			case 4:
			{
				Modify();
				cout<<"Press any key to Display Main Menu"<<endl;
				getch();
				break;
			}
			case 5:
			{
				Delete();
				cout<<"Press any key to Display Main Menu"<<endl;
				getch();
				break;
			}
			case 6:
			{
				exit(0);
			}
			default:
			{
				cout<<"Wrong Choice.Press any Key to View the Main Menu";
				getch();

			}
		}
	}

}
