#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct Patient
{
	int sno;
	char name[50];
	int age;
	char gender[10];
	char bloodgroup[10];
	char disease[50];
	char doctorassigned[50];
};
struct Doctor
{
	int sno;
	char name[50];
	char gender[10];
	char specialist[50];
	bool available;
};
struct Record
{
	Doctor doc[100];
	Patient pat[100];
	int dno;
	int pno;
};
void Display()
{
	cout << "\t\t\t############################################################" << endl;
	cout << "\t\t\t################ Hospital Management System ################" << endl;
	cout << "\t\t\t############################################################" << endl;
	cout << endl;
	cout << "\t\t\t                         Main Menu                         " << endl;
	cout << "\t\t\t1.Patient Menu" << endl;
	cout << "\t\t\t2.Doctor Menu" << endl;
	cout << "\t\t\t3.Exit" << endl;
}
Record readDRec(Record &r)
{
	int i = 0;
	char t[5];
	ifstream drec("Doctor Record.txt");
	if (drec.is_open())
	{
		while (drec.peek() != EOF)
		{
			drec.ignore(100, ':');
			drec.ignore(1);
			drec >> r.doc[i].sno;
			drec.ignore(100, ':');
			drec.ignore(1);
			drec.getline(r.doc[i].name, 51);
			drec.ignore(100, ':');
			drec.ignore(1);
			drec.getline(r.doc[i].gender, 11);
			drec.ignore(100, ':');
			drec.ignore(1);
			drec.getline(r.doc[i].specialist, 51);
			drec.ignore(100, ':');
			drec.ignore(1);
			drec.getline(t, 6);
			if (strcmp(t, "Yes") == 0)
			{
				r.doc[i].available = true;
			}
			else if (strcmp(t, "No") == 0)
			{
				r.doc[i].available = false;
			}
			else
			{
				cout << "Error in reading availablity info" << endl;
				throw 0;
			}
			drec.ignore(2);
			i++;
		}
		r.dno = i;
		drec.close();
	}
	else
	{
		cout << "Error Reading File" << endl;
		throw 0;
	}
	return r;
}
int sameSpecDis(Record &r, int num)
{
	readDRec(r);
	int i = 0;
	while (i < r.dno)
	{
		if (strcmp(r.pat[num].disease, r.doc[i].specialist) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}
void writeDoc(Record &r)
{
	char t[5];
	ofstream drec("Doctor Record.txt");
	if (drec.is_open())
	{
		for (int i = 0; i < r.dno; i++)
		{
			drec << "SNo.: ";
			drec << r.doc[i].sno << endl;
			drec << "Name: ";
			drec << r.doc[i].name << endl;
			drec << "Gender: ";
			drec << r.doc[i].gender << endl;
			drec << "Specialist: ";
			drec << r.doc[i].specialist << endl;
			drec << "Availablity: ";
			if (r.doc[i].available == 1)
			{
				strcpy_s(t, "Yes");
			}
			else if (r.doc[i].available == 0)
			{
				strcpy_s(t, "No");
			}
			else
			{
				cout << "Error in writing availablity info" << endl;
				throw 0;
			}
			drec << t << endl;
			drec << endl;
		}
		drec.close();
	}
	else
	{
		cout << "Error Writting File" << endl;
		throw 0;
	}
}
bool isDocinRec(Doctor &d, Record &r)
{
	readDRec(r);
	int i = 0;
	while (i < r.dno)
	{
		if (strcmp(d.name, r.doc[i].name) == 0)
		{
			return true;
		}
		i++;
	}
	return false;
}
void addDoc(Record &r)
{
	readDRec(r);
	char con;
	char t[5];
	int i = r.dno;
	while (1 == 1)
	{
		r.doc[i].sno = i + 1;
		cout << "\t\t\tEnter Doctor's name: ";
		cin.getline(r.doc[i].name, 51);
		cout << "\t\t\tEnter Doctor's gender: ";
		cin >> r.doc[i].gender;
		cin.ignore(1);
		cout << "\t\t\tEnter Doctor's specialist: ";
		cin.getline(r.doc[i].specialist, 51);
		cout << "\t\t\tEnter Doctor's availability: ";
		cin.getline(t, 6);
		if (strcmp(t, "Yes") == 0)
		{
			r.doc[i].available = true;
		}
		else if (strcmp(t, "No") == 0)
		{
			r.doc[i].available = false;
		}
		else
		{
			cout << "Error in reading availablity info" << endl;
			throw 0;
		}
		cout << "If you want to continue, Press c or C otherwise any otehr character: ";
		cin >> con;
		cin.ignore(1);
		if (con == 'c' || con == 'C')
		{
			i++;
		}
		else
		{
			system("cls");
			break;
		}
	}
	r.dno = i + 1;
	writeDoc(r);
}
Record delDoc(Doctor &d, Record &r)
{
	readDRec(r);
	int i = 0;
	bool f = 0;
	while (i < r.dno)
	{
		if (strcmp(d.name, r.doc[i].name) == 0)
		{
			f = 1;
			break;
		}
		i++;
	}
	if (f == 1)
	{
		r.dno--;
		int j = i + 1;
		while (i < r.dno)
		{
			r.doc[i].sno = r.doc[j].sno;
			strcpy_s(r.doc[i].name, r.doc[j].name);
			strcpy_s(r.doc[i].gender, r.doc[j].gender);
			strcpy_s(r.doc[i].specialist, r.doc[j].specialist);
			r.doc[i].available = r.doc[j].available;
			i++;
			j++;
		}
	}
	else
	{
		cout << "Doctor is already not available in the Record" << endl;
		system("pause");
	}
	system("cls");
	writeDoc(r);
	return r;
}
Record updateDoc(Doctor &d, char *available, Record &r)
{
	readDRec(r);
	int i = 0;
	while (i < r.dno)
	{
		strcpy_s(r.doc[i].gender, d.gender);
		strcpy_s(r.doc[i].specialist, d.specialist);
		if (strcmp(d.name, r.doc[i].name) == 0)
		{
			if (strcmp(available, "Yes") == 0)
			{
				r.doc[i].available = true;
			}
			else if (strcmp(available, "No") == 0)
			{
				r.doc[i].available = false;
			}
			else
			{
				cout << "Error in reading availablity info" << endl;
				throw 0;
			}
			break;
		}
		i++;
	}
	system("cls");
	writeDoc(r);
	return r;
}
Record readPRec(Record &r)
{
	int i = 0;
	ifstream prec("Patient Record.txt");
	if (prec.is_open())
	{
		while (prec.peek() != EOF)
		{
			prec.ignore(100, ':');
			prec.ignore(1);
			prec >> r.pat[i].sno;
			prec.ignore(100, ':');
			prec.ignore(1);
			prec.getline(r.pat[i].name, 51);
			prec.ignore(100, ':');
			prec.ignore(1);
			prec >> r.pat[i].age;
			prec.ignore(100, ':');
			prec.ignore(1);
			prec.getline(r.pat[i].gender, 11);
			prec.ignore(100, ':');
			prec.ignore(1);
			prec.getline(r.pat[i].bloodgroup, 11);
			prec.ignore(100, ':');
			prec.ignore(1);
			prec.getline(r.pat[i].disease, 51);
			prec.ignore(100, ':');
			prec.ignore(1);
			prec.getline(r.pat[i].doctorassigned, 51);
			prec.ignore(2);
			i++;
		}
		r.pno = i;
		prec.close();
	}
	else
	{
		cout << "Error Reading File" << endl;
		throw 0;
	}
	return r;
}
void writePat(Record &r)
{
	char t[5];
	ofstream prec("Patient Record.txt");
	if (prec.is_open())
	{
		for (int i = 0; i < r.pno; i++)
		{
			prec << "SNo.: ";
			prec << r.pat[i].sno << endl;
			prec << "Name: ";
			prec << r.pat[i].name << endl;
			prec << "Age: ";
			prec << r.pat[i].age << endl;
			prec << "Gender: ";
			prec << r.pat[i].gender << endl;
			prec << "Blood Group: ";
			prec << r.pat[i].bloodgroup << endl;
			prec << "Disease: ";
			prec << r.pat[i].disease << endl;
			prec << "Doctor Assigned: ";
			prec << r.pat[i].doctorassigned << endl;
			prec << endl;
		}
		prec.close();
	}
	else
	{
		cout << "Error Writting File" << endl;
		throw 0;
	}
}
bool isPatinRec(Patient &p, Record &r)
{
	readDRec(r);
	int i = 0;
	while (i < r.dno)
	{
		if (strcmp(p.name, r.doc[i].name) == 0)
		{
			return true;
		}
		i++;
	}
	return false;
}
void addPat(Record &r)
{
	readPRec(r);
	char con;
	int i = r.pno;
	while (1 == 1)
	{
		r.pat[i].sno = i + 1;
		cout << "\t\t\tEnter Patient's name: ";
		cin.getline(r.pat[i].name, 51);
		cout << "\t\t\tEnter Patient's age: ";
		cin >> r.pat[i].age;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			system("cls");
			cout << "Incorrect Input!" << endl;
			continue;
		}
		cout << "\t\t\tEnter Patient's gender: ";
		cin >> r.pat[i].gender;
		cin.ignore(1);
		cout << "\t\t\tEnter Patient's blood group: ";
		cin.getline(r.pat[i].bloodgroup, 11);
		cout << "\t\t\tEnter Patient's disease: ";
		cin.getline(r.pat[i].disease, 51);
		if (sameSpecDis(r, i) == -1)
		{
			cout << "This disease is not treated in this hospital!" << endl;
			continue;
		}
		else
		{
			strcpy_s(r.pat[i].doctorassigned, r.doc[sameSpecDis(r, i)].name);
			if (r.doc[sameSpecDis(r, i)].available == 0)
			{
				cout << "Doctor is not available for this moment!" << endl;
				continue;
			}
		}
		cout << "If you want to continue, Press c or C otherwise any otehr character: ";
		cin >> con;
		cin.ignore(1);
		if (con == 'c' || con == 'C')
		{
			i++;
		}
		else
		{
			system("cls");
			break;
		}
	}
	r.pno = i + 1;
	writePat(r);
}
Record delPat(Patient &p, Record &r)
{
	readPRec(r);
	int i = 0;
	bool f = 0;
	while (i < r.pno)
	{
		if (strcmp(p.name, r.pat[i].name) == 0)
		{
			f = 1;
			break;
		}
		i++;
	}
	if (f == 1)
	{
		r.pno--;
		int j = i + 1;
		while (i < r.pno)
		{
			r.pat[i].sno = r.pat[j].sno;
			strcpy_s(r.pat[i].name, r.pat[j].name);
			r.pat[i].age = r.pat[j].age;
			strcpy_s(r.pat[i].gender, r.pat[j].gender);
			strcpy_s(r.pat[i].bloodgroup, r.pat[j].bloodgroup);
			strcpy_s(r.pat[i].disease, r.pat[j].disease);
			strcpy_s(r.pat[i].doctorassigned, r.pat[j].doctorassigned);
			i++;
			j++;
		}
	}
	else
	{
		cout << "Patient is already not available in the Record" << endl;
		system("pause");
	}
	system("cls");
	writePat(r);
	return r;
}
Record updatePat(Patient &p, Record &r)
{
	readPRec(r);
	int i = 0;
	while (i < r.pno)
	{
		if (strcmp(p.name, r.pat[i].name) == 0)
		{
			r.pat[i].age = p.age;
			strcpy_s(r.pat[i].gender, p.gender);
			strcpy_s(r.pat[i].bloodgroup, p.bloodgroup);
			strcpy_s(r.pat[i].disease, p.disease);
			if (sameSpecDis(r, i) == -1)
			{
				cout << "This disease is not treated in this hospital!" << endl;
				continue;
			}
			else
			{
				strcpy_s(r.pat[i].doctorassigned, r.doc[sameSpecDis(r, i)].name);
				if (r.doc[sameSpecDis(r, i)].available == 0)
				{
					cout << "Doctor is not available for this moment!" << endl;
					continue;
				}
			}
			break;
		}
		i++;
	}
	system("cls");
	writePat(r);
	return r;
}
int main()
{
	Record rec;
	Patient pat;
	Doctor doc;
	char available[5];
	int op, opp;
	while (1 == 1)
	{
		Display();
		cout << "\t\t\tChoose your opnion: ";
		cin >> op;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			system("cls");
			cout << "Incorrect Input!" << endl;
			continue;
		}
		cin.ignore(1);
		system("cls");
		if (op == 1)
		{
			while (1 == 1)
			{
				cout << "\t\t\t1.Add Patient Record" << endl;
				cout << "\t\t\t2.Update Patient Record" << endl;
				cout << "\t\t\t3.Remove Patient Rceord" << endl;
				cout << "\t\t\tChoose your opinion: ";
				cin >> opp;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<int>::max(), '\n');
					system("cls");
					cout << "Incorrect Input!" << endl;
					continue;
				}
				cin.ignore(1);
				system("cls");
				if (opp == 1)
				{
					addPat(rec);
				}
				else if (opp == 2)
				{
					cout << "\t\t\tEnter Patient's name whose record is needed to update: ";
					cin.getline(pat.name, 51);
					if (isPatinRec(pat, rec) == 1)
					{
						cout << "\t\t\tEnter new Patient's age: ";
						cin >> pat.age;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(std::numeric_limits<int>::max(), '\n');
							system("cls");
							cout << "Invalid Input!" << endl;
							continue;
						}
						cout << "\t\t\tEnter new Patient's gender: ";
						cin >> pat.gender;
						cin.ignore(1);
						cout << "\t\t\tEnter new Patient's blood group: ";
						cin.getline(pat.bloodgroup, 11);
						cout << "\t\t\tEnter new Patient's disease: ";
						cin.getline(pat.disease, 51);
						updatePat(pat, rec);
					}
					else
					{
						cout << "Patient of this name is not in Record" << endl;
						system("pause");
					}
				}
				else if (opp == 3)
				{
					cout << "\t\t\tEnter Patient's name whose record is needed to remove: ";
					cin.getline(pat.name, 51);
					delPat(pat, rec);
				}
				else
				{
					cout << "Incorrect Input!" << endl;
					continue;
				}
				break;
			}
		}
		else if (op == 2)
		{
			while (1 == 1)
			{
				cout << "\t\t\t1.Add Doctor Record" << endl;
				cout << "\t\t\t2.Update Doctor Record" << endl;
				cout << "\t\t\t3.Remove Doctor Rceord" << endl;
				cout << "\t\t\tChoose your opinion: ";
				cin >> opp;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(std::numeric_limits<int>::max(), '\n');
					system("cls");
					cout << "Incorrect Input!" << endl;
					continue;
				}
				cin.ignore(1);
				system("cls");
				if (opp == 1)
				{
					addDoc(rec);
				}
				else if (opp == 2)
				{
					cout << "\t\t\tEnter Doctor's name whose record is needed to update: ";
					cin.getline(doc.name, 51);
					if (isDocinRec(doc, rec) == 1)
					{
						cout << "\t\t\tEnter new Doctor's gender: ";
						cin >> doc.gender;
						cin.ignore(1);
						cout << "\t\t\tEnter new Doctor's specialist: ";
						cin.getline(doc.specialist, 51);
						cout << "\t\t\tEnter new Doctor's availability: ";
						cin.getline(available, 6);
						updateDoc(doc, available, rec);
					}
					else
					{
						cout << "Doctor of this name is not in Record" << endl;
						system("pause");
					}
				}
				else if (opp == 3)
				{
					cout << "\t\t\tEnter Patient's name whose record is needed to remove: ";
					cin.getline(pat.name, 51);
					delDoc(doc, rec);
				}
				else
				{
					cout << "Incorrect Input!" << endl;
					continue;
				}
				break;
			}
		}
		else if (op == 3)
		{
			break;
		}
		else
		{
			cout << "Incorrect input!" << endl;
			continue;
		}
	}
}