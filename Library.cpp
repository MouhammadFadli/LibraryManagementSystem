#include<iostream>
#include<cctype>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std; 

struct stBook {
	int BookID;
	string BookTitle;
	string BookAuthor;
	bool IsBoroowed = true;
	int BookCount = 0;
};

bool StringToBool(string result) {
	if (result == "Available")
		return true;
	else
		return false;
}

string BoolToString(bool result) {
		return result ? "Available" : "Borrowed";
		
}

int ReadNumber(string massage) {
	int num = 0;
	cout << massage << endl;
	while (!(cin >> num)) {
		cout << " INvalid number. Try again : ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return num;
}

int ReadNumberForMenu(string massage) {
	int num = 0;
	cout << massage << endl;
	while (!(cin >> num) && num <1 || num > 7) {
		cout << " INvalid number. Try again : ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return num;
}


void WordToVector(string word, vector<string>& words, char Sperator1 = '/') {
	string Nword = "";
	for (int i = 0; i < size(word); i++) {
		if (word[i] == Sperator1) {
			words.push_back(Nword);
			Nword = "";
		}
		else if (word[i] != Sperator1) {
			Nword += word[i];

		}


	}
	words.push_back(Nword);

}

stBook StringToStructByVector(string word, char Seperator) {
	vector<string> vBooks;
	stBook Book;
	WordToVector(word, vBooks, Seperator);
	if (vBooks.size() < 4) {
		Book.BookID = 0;
		Book.BookTitle = "";
		Book.BookAuthor = "";
		Book.IsBoroowed = false;
		return Book;
	}
	Book.BookID = stoi(vBooks[0]);
	Book.BookTitle = vBooks[1];
	Book.BookAuthor = vBooks[2];
	Book.IsBoroowed = StringToBool(vBooks[3]);
	return Book;
}

void SaveDataInFile(vector<stBook> vBooks) {
	fstream File;
	File.open("Books.txt", ios::out);
	if (File.is_open()) {
		for (stBook &B : vBooks) {
			File << B.BookID << '|' << B.BookTitle << '|' << B.BookAuthor << '|' << BoolToString(B.IsBoroowed) << "\n";
		}
		File.close();
	}

}

vector<stBook> ReadDataFromFile(int &counter) {
	vector<stBook> vBooks;
	fstream File;
	File.open("Books.txt", ios::in);
	if (File.is_open()) {
		string line;
		stBook Book;
		
		while (getline(File, line)) {
			
			Book = StringToStructByVector(line, '|');
			if (Book.BookTitle != "")
			{
				vBooks.push_back(Book);
				counter++;
			}
		}
		File.close();
	}
	return vBooks;
}

bool CheckID(vector<stBook> &vBooks,int ID) {
	for (stBook& B : vBooks) {
		if (ID == B.BookID)
			return false;
	}
	return true;
}

void Menu() {
	cout << "\n- - -   Library Mangement System   - - -\n" << endl;
	cout << "1.Add a new book" << endl;
	cout << "2.Display all books" << endl;
	cout << "3.Borrow a book" << endl;
	cout << "4.Return a book" << endl;
	cout << "5.Display available books" << endl;
	cout << "6.Display borrowed books" << endl;
	cout << "7.Exit" << endl;
	cout << "================================================\n";
	cout << "Choose an option : ";
}

void BorrowBook(vector<stBook> &vBooks) {
	int ID = ReadNumber("Enter Book ID to borrow : ");
	for (stBook &B:vBooks) {
		if (ID == B.BookID) {
			if (!B.IsBoroowed)
			{
				cout << "Book is alreay borrowed" << endl;
				return;
			}
			else {
				B.IsBoroowed = false;
				cout << "Book borrowed succesfully" << endl;
				SaveDataInFile(vBooks);
				return;
			}
		}
	}
	cout << "Book not found" << endl;
}

void ReturnBook(vector<stBook> &vBooks) {
	int ID = ReadNumber("Enter Book ID to return : ");

	for (stBook &B: vBooks) {
		if (ID == B.BookID) {
			if (B.IsBoroowed) {
				cout << "Book was not borrowed" << endl;
			}
			else {
				B.IsBoroowed = true;
				cout << "Book returned successfully" << endl;
				SaveDataInFile(vBooks);
			}
			return;
		}

	}
	cout << "Book not found" << endl;
}

void AddBook(vector<stBook> &vBooks) {
	stBook Books;
	do {
		Books.BookID = ReadNumber("Enter Book ID ((Number))");
		if (!CheckID(vBooks,Books.BookID)) {
			cout << "This ID already exists! Please enter a differnet ID" << endl;
		}
	} while (!CheckID(vBooks, Books.BookID));
	cin.ignore();
	cout << "Enter Book Title " << endl;
	getline(cin, Books.BookTitle);

	cout << "Enter Author Name" << endl;
	getline(cin, Books.BookAuthor);

	Books.IsBoroowed = true;
	Books.BookCount++;
	vBooks.push_back(Books);
	cout << "Book added successfully" << endl;
	cout << "\n************************\n";
	SaveDataInFile(vBooks);
}

void PrintBookRecord(stBook Book) {
	cout << "| " << setw(15) << left << Book.BookID;
	cout << "| " << setw(40) << left << Book.BookTitle;
	cout << "| " << setw(12) << left << Book.BookAuthor;
	
	string statusText = BoolToString(Book.IsBoroowed);
	if (statusText == "Available")
		cout << "| " << "\033[32m" << setw(12) << left << statusText << "\033[0m" << endl; // Green
	else
		cout << "| " << "\033[31m" << setw(12) << left << statusText << "\033[0m" << endl; // Red
}

void PrintTotalBooks() {
	int counter = 0;
	vector<stBook> vBooks = ReadDataFromFile(counter);
	cout << "\n========================================= All Books =========================================\n";
	cout << "\n_______________________________________________________";

	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Book ID";
	cout << "| " << left << setw(40) << "Book Title";
	cout << "| " << left << setw(12) << "Author Name";
	cout << "| " << left << setw(12) << "Is Browwed";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	int CountBook = 0;
	if (vBooks.size() == 0)
		cout << "\t\t\t\tNo Books Available In the System!";
	else
	{
		for (stBook B : vBooks) {
			PrintBookRecord(B);
			CountBook++;
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Books = " << CountBook;

}

vector<stBook> ReadBookAvailabelFromFile(int& counter) {
	vector<stBook> vBooks;
	fstream File;
	File.open("Books.txt", ios::in);
	if (File.is_open()) {
		string line;
		stBook Book;

		while (getline(File, line)) {

			Book = StringToStructByVector(line, '|');
			if (Book.IsBoroowed)
			{
				vBooks.push_back(Book);
				counter++;
			}
		}
		File.close();
	}
	return vBooks;
}

void PrintTotalAvailabelBooks() {
	int counter = 0;
	vector<stBook> vBooks = ReadBookAvailabelFromFile(counter);
	cout << "\n========================================= All Books =========================================\n";
	cout << "\n_______________________________________________________";

	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Book ID";
	cout << "| " << left << setw(40) << "Book Title";
	cout << "| " << left << setw(12) << "Author Name";
	cout << "| " << left << setw(12) << "Is Browwed";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	int CountBook = 0;
	if (vBooks.size() == 0)
		cout << "\t\t\t\tNo Books Available In the System!";
	else
	{
		for (stBook B : vBooks) {
			PrintBookRecord(B);
			CountBook++;
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Books = " << CountBook;

}

vector<stBook> ReadBookBorrowFromFile(int& counter) {
	vector<stBook> vBooks;
	fstream File;
	File.open("Books.txt", ios::in);
	if (File.is_open()) {
		string line;
		stBook Book;

		while (getline(File, line)) {

			Book = StringToStructByVector(line, '|');
			if (!Book.IsBoroowed)
			{
				vBooks.push_back(Book);
				counter++;
			}
		}
		File.close();
	}
	return vBooks;
}

void PrintTotalBorrowBooks() {
	int counter = 0;
	vector<stBook> vBooks = ReadBookBorrowFromFile(counter);
	cout << "\n========================================= All Books =========================================\n";
	cout << "\n_______________________________________________________";

	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Book ID";
	cout << "| " << left << setw(40) << "Book Title";
	cout << "| " << left << setw(12) << "Author Name";
	cout << "| " << left << setw(12) << "Is Browwed";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	int CountBook = 0;
	if (vBooks.size() == 0)
		cout << "\t\t\t\tNo Books Available In the System!";
	else
	{
		for (stBook B : vBooks) {
			PrintBookRecord(B);
			CountBook++;
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Books = " << CountBook;

}

void PrintMenu(vector<stBook> &vBooks) {
	int number = 0;
	do {
		system("cls");
		Menu();
		number = ReadNumberForMenu("((choose number))");
		switch (number) {
		case 1: 
		{
			system("cls");
			AddBook(vBooks);
			system("pause>0");
			break;
		}
		case 2: 
		{
			system("cls");
			PrintTotalBooks();
			system("pause>0");
			break;
		}
		case 3:
		{
			system("cls");
			BorrowBook(vBooks);
			system("pause>0");
			break;
		}
		case 4: 
		{
			system("cls");
			ReturnBook(vBooks);
			system("pause>0");
			break;
		}
		case 5:
		{
			system("cls");
			PrintTotalAvailabelBooks();
			system("pause>0");
			break;
		}
		case 6:
		{
			system("cls");
			PrintTotalBorrowBooks();
			system("pause>0");
			break;
		}
		case 7: cout << "Exiting...\a" << endl;
			break;
		default: cout << "Enter Error  ** You Enter : " << number << " **" << endl;
		}
	} while (number != 7);
}



int main() {
	int counter = 0;
	vector<stBook> vBooks = ReadDataFromFile(counter);
	PrintMenu(vBooks);
	return 0;
}