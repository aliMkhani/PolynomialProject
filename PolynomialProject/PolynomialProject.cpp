#include "Polynomial.h"

int main()
{












	Polynomial polynomial = Polynomial();
	ofstream writeFile;
	ifstream readFile;
	string polyString;
	Polynomial* polynomial2;
	bool con1 = true;
	bool con2 = true;
	string skipClosing;
	while (con1)
	{
		int item = 0;
		system("CLS");
		cout << "1- New Polynomial\n"
			<< "2- Load frop text file\n"
			<< "3- Load frop binary file\n"
			<< "4- Quit";
		cout << endl;
		cin >> item;
		switch (item)
		{
		case 1:
			con2 = true;
			while (con2)
			{
				item = 0;
				system("CLS");
				cout << "current polynomial: " << polynomial << endl;
				cout << "1- Add\n"
					<< "2- Subtract\n"
					<< "3- Multiply\n"
					<< "4- Derivative\n"
					<< "5- Find Degree\n"
					<< "6- Find Value for specific X\n"
					<< "7- Compare\n"
					<< "8- Save to a text file\n"
					<< "9- Save to a binary file\n"
					<< "10- Quit";
				cout << endl;
				cin >> item;
				switch (item)
				{
				case 1:
				{
					system("CLS");
					cout << "Add:   this:" << polynomial << endl;
					polynomial2 = new Polynomial();
					cout << "enter polynomial:" << endl;
					cin >> polynomial2;
					cout << "this + " << *polynomial2 << endl;
					cout << "result: " << endl;
					polynomial = *polynomial2 + polynomial;
					cout << polynomial << endl;
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 2:
				{
					system("CLS");
					cout << "Subtract:   this:" << polynomial << endl;
					polynomial2 = new Polynomial();
					cout << "enter polynomial:" << endl;
					cin >> polynomial2;
					cout << "this - " << *polynomial2 << endl;
					cout << "result: " << endl;
					polynomial = polynomial - *polynomial2;
					cout << polynomial << endl;
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 3:
				{
					system("CLS");
					cout << "Multiply:   this:" << polynomial << endl;
					polynomial2 = new Polynomial();
					cout << "enter polynomial:" << endl;
					cin >> polynomial2;
					cout << "this * " << *polynomial2 << endl;
					cout << "result: " << endl;
					polynomial = *polynomial2 * polynomial;
					cout << polynomial << endl;
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 4:
				{
					system("CLS");
					cout << "Derivative:   this:" << polynomial << endl;
					polynomial = ~polynomial;
					cout << "Derivative of this : " << polynomial << endl;
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 5:
				{
					system("CLS");
					cout << "Find Degree:   this:" << polynomial << endl;
					cout << "Degree of this: " << polynomial.Degree() << endl;
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 6:
				{
					system("CLS");
					cout << "Find Value for specific X:   this:" << polynomial << endl;
					cout << "enter x" << endl;
					int x;
					cin >> x;
					cout << "result: " << polynomial(x) << endl;
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 7:
				{
					system("CLS");
					cout << "Compare:   this:" << polynomial << endl;
					polynomial2 = new Polynomial();
					cout << "enter polynomial:" << endl;
					cin >> polynomial2;
					cout << endl;
					if (polynomial.Degree() > polynomial2->Degree())
					{
						cout << polynomial << " is large degree" << endl;
					}
					else
					{
						if (polynomial.Degree() == polynomial2->Degree())
						{
							cout << "degrees are equal" << endl;
						}
						else
						{
							cout << *polynomial2 << " is large degree" << endl;
						}
					}
					cout << "Done. enter somthing to exit." << endl;
					cin >> skipClosing;
				}
				break;
				case 8:
				{
					writeFile.open("polyText.txt");
					writeFile << polynomial.Tostring();
					writeFile.close();
				}
				break;
				case 9:
				{
					writeFile.open("polyBinary.dat", ios::out | ios::binary);
					if (!writeFile) {
						cout << "Cannot open file!" << endl;
					}
					writeFile.write((char*)&polynomial, sizeof(Polynomial));
					writeFile.close();
					if (!writeFile.good()) {
						cout << "Error occurred at writing time!" << endl;
					}
				}
				break;
				case 10:
					con2 = false;
					break;
				default:
					con2 = false;
					break;
				}
			}
			break;
		case 2:
		{
			readFile.open("polyText.txt");
			if (!readFile) {
				cout << "Cannot open file!" << endl;
				return 1;
			}
			getline(readFile, polyString);
			polynomial.FillByString(polyString);
			readFile.close();
		}
		break;
		case 3:
		{
			readFile.open("polyBinary.dat", ios::out | ios::binary);
			if (!readFile) {
				cout << "Cannot open file!" << endl;
				return 1;
			}
			readFile.read((char*)&polynomial, sizeof(Polynomial));
			readFile.close();
			if (!readFile.good()) {
				cout << "Error occurred at reading time!" << endl;
				return 0;
			}
		}
		break;
		case 4:
			con1 = false;
			break;
		default:
			con1 = false;
			break;
		}
		getchar();
	}
}

