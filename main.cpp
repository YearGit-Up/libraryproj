#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Book {
	bool CheckIO;
	string
		Title,
		Author,
		Genre,
		ISBN;
	int Year;
	
};

struct Member {
	string Name, Code;
};
//PROTOTYPES///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void storeBook(ifstream &inFile, ifstream &, vector<Book> BookList, Book books[], int size, vector<Member>, Member member[], int);
void displayStoredBooks(vector<Book> BookList, vector<Member>);
void displayMembers(vector<Book> BookList, vector<Member> MemberList);
void displayMainMenu();
void mainMenu(int opt, vector<Book>, vector<Member>);
void regMem(vector<Book> BookList, vector<Member> &MemberList);
void removeMem(vector<Book> BookList, vector<Member> &MemberList);
void addBook(vector<Book> &BookList, vector<Member> MemberList);
void removeBook(vector<Book> &BookList, vector<Member> MemberList);
void searchCollectMethod(vector<Book> BookList, vector<Member> MemberList);
void searchByTitle(vector<Book> BookList, vector<Member> MemberList);
void searchByGenre(vector<Book> BookList, vector<Member> MemberList);
void checkOut(vector<Book> &BookList, vector<Member> MemberList);
string checkIOStat(vector<Book> BookList, vector<Member> MemberList, int index);

//PROGRAM STARTS HERE//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	//Variables for storing and handling books
	const int SIZE = 1000;
	ifstream inFile;
	vector<Book>BookList;
	Book BookFile[SIZE];
	inFile.open("booklist.txt");
	//Variables for storing and handling members
	const int MEM_COUNT = 1000;
	ifstream memFile;
	vector<Member> MemberList;
	Member members[MEM_COUNT];
	memFile.open("mems.txt");
	
	if (!inFile.is_open() || !memFile.is_open()) {
		cout << "ERROR" << endl;
		main();
	}
	else {
		storeBook(inFile, memFile, BookList, BookFile, SIZE, MemberList, members, MEM_COUNT);
	};

	system("pause");
}

//Function for storing data from a file//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void storeBook(ifstream &inFile, ifstream &memFile, vector<Book> BookList, Book books[], int size, vector<Member> MemberList, Member member[], int memCount) {
	int menuSelect;
	/*
	*The while loop states that it will push the contents
	*of an array into the vector up until there is nothing
	*more to read from the file. The while loop makes it so 
	*that it won't push junk values into vector. Only what can
	*be read will enter vector.*/

	//index variable i
	int i = 0;
		//Push data from file into array until you reach the end of file
		while (
			getline(inFile, books[i].Title),
			getline(inFile, books[i].Author),
			inFile >> books[i].Year,
			inFile.ignore(1000, '\n'),
			getline(inFile, books[i].Genre),
			getline(inFile, books[i].ISBN)) 
		{	
			//push each array elm into vector 1 by 1
			BookList.push_back(books[i]);
			i++;
			
		};
		//Loop for storing members of library
	int count = 0;
		while (
			getline(memFile, member[count].Name),
			getline(memFile, member[count].Code))
		{
			MemberList.push_back(member[count]);
			count++;
		}
	
		//After storing list enter program 
		displayMainMenu();
		cin >> menuSelect;
		mainMenu(menuSelect, BookList, MemberList);
}




//Function for displaying main menu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayMainMenu() {
	cout << "What would you like to do? " << endl; 
	cout << endl;
	cout << "[1] : Display Collection" << endl;
	cout << "[2] : Register With Library" << endl;
	cout << "[3] : Add Book To Collection" << endl;
	cout << "[4] : Check Out Book//FIX ME" << endl;
	cout << "[5] : Search Collection" << endl;
	cout << "[6] : Remove A Book From Collection" << endl;
	cout << "[7] : Remove A Member" << endl;
	cout << "[9] : Exit Program" << endl;
	cout << "[0] : Clear Screen" << endl;


}
//Function for controlling program flow////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainMenu(int opt, vector<Book> BookList, vector<Member> MemberList) {
	int menuSelect;

	switch (opt)
	{
	case 10: displayMembers(BookList, MemberList);
		break;
	case 0: system("CLS");
		displayMainMenu();
		cin >> menuSelect;
		mainMenu(menuSelect, BookList, MemberList);
		break;
	case 1: displayStoredBooks(BookList, MemberList);
		break;
	case 2: regMem(BookList, MemberList);
		break;
	case 3: addBook(BookList, MemberList);
		break;
	case 4: checkOut(BookList, MemberList);
		break;
	case 5: searchCollectMethod(BookList, MemberList);
		break;
	case 6: removeBook(BookList, MemberList);
		break;
	case 7: removeMem(BookList, MemberList);
		break;
	case 9: exit(0);
	default:
		break;
	}


}

//Function displays a list of all the books currently owned by The Last Bookstore. ///////////////////////////////////////////////////////////////////////////
void displayStoredBooks(vector<Book> BookList, vector<Member> MemberList) {
	int
		s1 = 10,
		s2 = 25,
		s3 = 40,
		menuSelect;
	cout << left;
	cout <<setw(s3) <<""<<"LIBRARY COLLECTION OF BOOKS" << endl;
	cout << endl;

	for (int i = 0; i < BookList.size(); i++) {
		cout <<setw(s2) << "" << setw(s1) << "Title: " << BookList[i].Title << endl;
		cout <<setw(s2) << "" << setw(s1) << "Author: " << BookList[i].Author << endl;
		cout <<setw(s2) << "" << setw(s1) << "Year: " << BookList[i].Year << endl;
		cout <<setw(s2) << "" << setw(s1) << "Genre: " << BookList[i].Genre << endl;
		cout <<setw(s2) << "" << setw(s1) << "ISBN: " << BookList[i].ISBN << endl;
		cout << endl;
	}

	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}

//Function for displaying members/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayMembers(vector<Book> BookList, vector<Member> MemberList) {
	int menuSelect, sW0 = 15, sW1 = 10, sW2 = 24;
	cout << left;
	cout << setw(sW1) << "" << "MEMBER" << setw(sW2) << "" << "MEMBER CODE" << endl;
	cout << endl;
	for (int i = 0; i < MemberList.size(); i++) {
		cout <<setw(sW1) << "" << "[" << (i + 1) << "] : " << setw(25) << MemberList[i].Name << MemberList[i].Code << endl;
	}
	cout << endl;
	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}

//Function for registering a member to library////////////////////////////////////////////////////////////////////////////////////////////////////////////
void regMem(vector<Book> BookList, vector<Member> &MemberList) {
	int menuSelect,
		addCnt = 1, 
		index;
	string memName, memCode;
	Member newMembers[1000];
	ofstream outFileMem;
	outFileMem.open("mems.txt", ios::app);
	
	for (index = 0; index < addCnt; index++) {
		//Get new member information
		cout << "Enter Your Name: " << endl;
		cin.ignore();
		getline(cin, memName);
		cout << "Enter A Member Code in the Format: XXX-XX-XXXX " << endl;
		cin>> memCode;
		
			//Add new members to new member array
			newMembers[index].Name = memName;
			newMembers[index].Code = memCode;
			//Push new members into larger system member list
			MemberList.push_back(newMembers[index]);
	}
	//Adjust system member file to reflect new members
	 
	outFileMem << MemberList[MemberList.size()-1].Name << endl;
	outFileMem << MemberList[MemberList.size()-1].Code << endl;
	outFileMem.close();

	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}

//This function removes a member from the library//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void removeMem(vector<Book> BookList, vector<Member> &MemberList) {
	int menuSelect;
	int choiceDel;
	ofstream outFileUpdate;
	

	for (int i = 0; i < MemberList.size(); i++) {
		cout << "[" << (i + 1) << "]" << " " << MemberList[i].Name << endl;
	}

	cout << "Enter the number of the member you want to remove: " << endl;
	cin >> choiceDel;
	if (choiceDel < 1 || choiceDel > MemberList.size()) {
		cout << "Invalid input. Try again." << endl;
		cout << endl;
		removeMem(BookList, MemberList);
	}
	else {
		MemberList.erase(MemberList.begin() + (choiceDel - 1));
		outFileUpdate.open("mems.txt");
		for (int up = 0; up < MemberList.size(); up++) {
			outFileUpdate << MemberList[up].Name << endl;
			outFileUpdate << MemberList[up].Code << endl;
		}
		outFileUpdate.close();
	}

	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}
//This function adds a book to the larger system of collected books //////////////////////////////////////////////////////////////////////////////////////////////
void addBook(vector<Book> &BookList, vector<Member> MemberList) {
	int menuSelect, newYear, index;
	ofstream outFileBook;
	outFileBook.open("booklist.txt", ios::app);
	string newTitle, newAuth, newGenre, newISBN;
	Book addBook[1000];
	//Get Book Information
	for (index = 0; index < 1; index++) {
		cin.ignore();
		cout << "What is the title of the book?" << endl;
		getline(cin, newTitle);
		cout << "Who is the author of the book?" << endl;
		getline(cin, newAuth);
		cout << "What year was the book published?" << endl;
		cin >> newYear;
		cout << "What genre is the book?" << endl;
		cin >> newGenre;
		cin.ignore();
		cout << "Give the book an ISBN# in the format XXXX-X-XX-XXX " << endl;
		getline(cin, newISBN);
		//Add book to an array for holding
		addBook[index].Title = newTitle;
		addBook[index].Author = newAuth;
		addBook[index].Year = newYear;
		addBook[index].Genre = newGenre;
		addBook[index].ISBN = newISBN;
		//Append contents of holding array to the end of larger system book list
		BookList.push_back(addBook[index]);
	}
	//Adjust system file that holds list of books to add new book
	
	outFileBook << BookList[BookList.size() - 1].Title << endl;
	outFileBook << BookList[BookList.size() - 1].Author << endl;
	outFileBook << BookList[BookList.size() - 1].Year << endl;
	outFileBook << BookList[BookList.size() - 1].Genre << endl;
	outFileBook << BookList[BookList.size() - 1].ISBN << endl;
	outFileBook.close();

	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}

//This Function Removes a book from the system
void removeBook(vector<Book> &BookList, vector<Member> MemberList) {
	int menuSelect, choiceDel;
	ofstream outFileBkUpdate;
	outFileBkUpdate.open("booklist.txt");
	
	
	for (int i = 0; i < BookList.size(); i++) {
		cout << "[" << (i + 1) << "]" << " " << BookList[i].Title << endl;
	}
	cout << "Enter the number of the book you wish to remove: " << endl;
	cin >> choiceDel;

	if (choiceDel < 1 || choiceDel > BookList.size()) {
		cout << "Invalid input. Try again." << endl;
		removeBook(BookList, MemberList);
	}
	else {
		BookList.erase(BookList.begin() + (choiceDel - 1));
		//This loop updates the larger system book file with the changes made in this function
		for (int up = 0; up < BookList.size(); up++) {
			outFileBkUpdate << BookList[up].Title << endl;
			outFileBkUpdate << BookList[up].Author << endl;
			outFileBkUpdate << BookList[up].Year << endl;
			outFileBkUpdate << BookList[up].Genre << endl;
			outFileBkUpdate << BookList[up].ISBN << endl;
		}
	}
	outFileBkUpdate.close();
	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}

//This function determines how a user searches for a book/////////////////////////////////////////////////////////////////////////////////////////////////////////
void searchCollectMethod(vector<Book> BookList, vector<Member> MemberList) {
	int userChoice;

	cout << "How would you like to search for a book?" << endl;
	cout << endl;
	cout << "[1] : Search By Title" << endl;
	cout << "[2] : Search By Genre" << endl;
	cin >> userChoice;

	switch (userChoice)
	{
	case 1:searchByTitle(BookList, MemberList);
		break;
	case 2:searchByGenre(BookList,MemberList);
		break;
	default: searchCollectMethod(BookList, MemberList);
		break;
	}
}
//This function searches for a book based of its title(partial search friendly)////////////////////////////////////////////////////////////////////////////////
void searchByTitle(vector<Book> BookList, vector<Member> MemberList) {
	int menuSelect;
	const int SIZE = 351;
	char titleSearch[SIZE];//Char array used for holding user input

	cout << "Enter the title for the book: ";
	cin.ignore(1000, '\n');
	cin.getline(titleSearch, SIZE);
	for (int index = 0; index < BookList.size(); index++) {

		if (strstr(BookList[index].Title.c_str(), titleSearch)){//if user input is found inside of book list, output the book(s) info
			
			cout << "Title: " << BookList[index].Title << endl;
			cout << "Author: " << BookList[index].Author << endl;
			cout << "Year: " << BookList[index].Year << endl;
			cout << "Genre: " << BookList[index].Genre << endl;
			cout << "ISBN: " << BookList[index].ISBN << endl;
			cout << endl;
		}
	}
		displayMainMenu();
		cin >> menuSelect;
		mainMenu(menuSelect, BookList, MemberList);

}
//This Function searches for a book based off its genre(Partial search friendly)//////////////////////////////////////////////////////////////////////////////
void searchByGenre(vector<Book> BookList, vector<Member> MemberList) {
	int menuSelect;
	const int SIZE = 351;
	char genreSelect[SIZE];
	vector<char> books;
	cout << "Enter which genre of books you would like to read: " << endl;
	cin.ignore(1000, '\n');
	cin.getline(genreSelect, SIZE);

	for (int index = 0; index < BookList.size(); index++) {
		if (strstr(BookList[index].Genre.c_str(), genreSelect)) {
			cout << "Title: " << BookList[index].Title << endl;
			cout << "Author: " << BookList[index].Author << endl;
			cout << "Year: " << BookList[index].Year << endl;
			cout << "Genre: " << BookList[index].Genre << endl;
			cout << "ISBN: " << BookList[index].ISBN << endl;
			cout << endl;
		}
	}
		displayMainMenu();
		cin >> menuSelect;
		mainMenu(menuSelect, BookList, MemberList);
	
}

//FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME |/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/|/////////////
void checkOut(vector<Book> &BookList, vector<Member> MemberList) {
	const int CHARS = 1000;
	char bookChoice[CHARS];
	bool *boolPTR = nullptr;
	int
		s1 = 10,
		s2 = 25,
		s3 = 40,
		menuSelect,
		bookSelect;
	cout << left;
	cout << setw(s3) << "" << "LIBRARY COLLECTION OF BOOKS" << endl;
	cout << endl;
	for (int i = 0; i < BookList.size(); i++) {
		cout << setw(s2) << "" << setw(s1) << "Title: " << BookList[i].Title << setw(s1) <<":"<< checkIOStat(BookList, MemberList, i) << endl;
		cout << setw(s2) << "" << setw(s1) << "Author: " << BookList[i].Author << endl;
		cout << setw(s2) << "" << setw(s1) << "Year: " << BookList[i].Year << endl;
		cout << setw(s2) << "" << setw(s1) << "Genre: " << BookList[i].Genre << endl;
		cout << setw(s2) << "" << setw(s1) << "ISBN: " << BookList[i].ISBN << endl;
		cout << endl;
	
	}

	cout << "Which book will you be checking out?" << endl;
	cin.ignore();
	cin.getline(bookChoice, CHARS);
	for (int i = 0; i < BookList.size(); i++) {
		if (strstr(BookList[i].Title.c_str(), bookChoice) && BookList[i].CheckIO == false){
			BookList[i].CheckIO = true;
			boolPTR = &BookList[i].CheckIO;
			*boolPTR = true;
			cout << "The book has now been checked out." << endl;

		}
	}
	cout << endl;
	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
	
}

string checkIOStat(vector<Book> BookList, vector<Member> MemberList, int index) {
	int
		s1 = 10,
		s2 = 25,
		s3 = 40, 
		menuSelect;

	for (int i = 0; i < BookList.size(); i++) {
		if (BookList[index].CheckIO == true) {
			return "[UNAVAILABLE]";
		}
		else
			return "[AVAILABLE]";
	}

	cout << endl;
	displayMainMenu();
	cin >> menuSelect;
	mainMenu(menuSelect, BookList, MemberList);
}
