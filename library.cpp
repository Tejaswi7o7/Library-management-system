#include <bits/stdc++.h>
#include <string>
using namespace std;

class Book{
    public:
    string title;
    string author;
    private:
    string isbn;
    int copiesAvailable;
    int totalCopies;

    public:
    Book(string t,string a,string i,int ca,int tc): title(t),author(a),isbn(i),copiesAvailable(ca),totalCopies(tc){}
    Book() : title("UnknownTitle"),author("UnknownAuthor"),isbn("ISBN"),copiesAvailable(0),totalCopies(5){}
    Book(const Book& other,string newIsbn): title(other.title),author(other.author),isbn(newIsbn),copiesAvailable(other.copiesAvailable),totalCopies(other.totalCopies){}

    int getTotalCopies()const{return totalCopies;}
    string getIsbn()const{return isbn;}
    int getCopiesAvailable()const{return copiesAvailable;}

    void updateCopies(int count){
    	if(copiesAvailable+count<0||totalCopies+count<0){
    		cout<<"Invalid request! Count becomes negative"<<endl;
    		return;
    	}
    	copiesAvailable+=count;
    	totalCopies+=count;
    }
    bool borrowBook(){
    	if(copiesAvailable>0){
    		copiesAvailable--;
    		return true;
    	}else{
    		cout<<"Invalid request! Copy of book not available"<<endl;
    		return false;
    	}
    }
    bool returnBook(){
    	if(copiesAvailable<totalCopies){
    		copiesAvailable++;
    		return true;
    	}else{
    		cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
    		return false;
    	}
    }
    void printDetails()const{
    	cout<<title<<" "<<author<<endl;
    }
};

class Member{
    public:
    string name;
    private:
    string memberID;
    map<string,int> borrowedBooks;
    int borrowLimit;

    public:
    Member(string id,string n,int bl=3)
    	: memberID(id),name(n),borrowLimit(bl){}

    string getMemberID()const{return memberID;}
    int getBorrowLimit()const{return borrowLimit;}
    bool borrowBook(string isbn){
    	if(borrowedBooks.size()>=borrowLimit){
    		cout<<"Invalid request! Borrow limit exceeded"<<endl;
    		return false;
    	}
    	borrowedBooks[isbn]++;
    	return true;
    }
    bool returnBook(string isbn){
    	if(borrowedBooks.find(isbn)==borrowedBooks.end()){
    		cout<<"Invalid request! Book not borrowed"<<endl;
    		return false;
    	}
    	borrowedBooks[isbn]--;
    	if(borrowedBooks[isbn]==0){
    		borrowedBooks.erase(isbn);
    	}
    	return true;
    }

    void printDetails()const{
    	for(const auto& pair:borrowedBooks){
    		cout<<memberID<<" "<<name<<" "<<pair.first<<" "<<pair.second<<endl;
    	}
    }
};

class Library{
    private:
    vector<Book> books;
    vector<Member> members;

    public:
    bool addBook(Book& book){
    	for(const auto& b:books){
    		if(b.getIsbn()==book.getIsbn()){
    			cout<<"Invalid request! Book with same isbn already exists"<<endl;
    			return false;
    		}
    	}
    	books.push_back(book);
    	return true;
    }
    bool registerMember(Member& member){
    	for(const auto& m:members){
    		if(m.getMemberID()==member.getMemberID()){
    			cout<<"Invalid request! Member with same id already exists"<<endl;
    			return false;
    		}
    	}
    	members.push_back(member);
    	return true;
    }
    bool borrowBook(string memberID,string isbn){
    	Member* member=nullptr;
    	Book* book=nullptr;
    	for(auto& m:members){
    		if(m.getMemberID()==memberID){
    			member=&m;
    			break;
    		}
    	}
    	for(auto& b:books){
    		if(b.getIsbn()==isbn){
    			book=&b;
    			break;
    		}
    	}
    	if(!member||!book){
    		cout<<"Invalid request! Member or book not found"<<endl;
    		return false;
    	}
    	if(book->getCopiesAvailable()==0){
    		cout<<"Invalid request! Copy of book not available"<<endl;
    		return false;
    	}
    	if(!member->borrowBook(isbn)){
    		return false;
    	}
    	return book->borrowBook();
    }
    bool returnBook(string memberID,string isbn){
    	Member* member=nullptr;
    	Book* book=nullptr;
    	for(auto& m:members){
    		if(m.getMemberID()==memberID){
    			member=&m;
    			break;
    		}
    	}
    	for(auto& b:books){
    		if(b.getIsbn()==isbn){
    			book=&b;
    			break;
    		}
    	}
    	if(!member||!book){
    		cout<<"Invalid request! Member or book not found"<<endl;
    		return false;
    	}
		if(!book || book->getCopiesAvailable()>=book->getTotalCopies()){
    		cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
    		return false;
    	}
    	if(!member->returnBook(isbn)){
    		return false;
    	}
    	return book->returnBook();
    }
    void printLibraryDetails()const{
    	for(const auto& book:books){
    		cout<<book.title<<" "<<book.author<<" "<<book.getCopiesAvailable()<<endl;
    	}
    	for(const auto& member:members){
    		cout<<member.getMemberID()<<" "<<member.name<<endl;
    	}
    }
    void printBookDetails(string isbn)const{
    	for(const auto& book:books){
    		if(book.getIsbn()==isbn){
    			book.printDetails();
    		}
    	}
    }
    void printMemberDetails(string memberID)const{
    	for(const auto& member:members){
    		if(member.getMemberID()==memberID){
    			member.printDetails();
    		}
    	}
    }
    void updateCopiesCount(string isbn,int count){
    	for(auto& book:books){
    		if(book.getIsbn()==isbn){
    			book.updateCopies(count);
    		}
    	}
    }
    Book* findBookByIsbn(const string& isbn){
    	for(auto& book:books){
    		if(book.getIsbn()==isbn){
    			return &book;
    		}
    	}
    	return nullptr;
    }
};
int main(){
    Library library;
    string input;
    	while(cin>>input){
    		if(input=="Book"){
    			string subinput;
    			cin>>subinput;
    			if(subinput=="None"){
    				Book book;
    				library.addBook(book);
    			}
                else if(subinput=="ExistingBook"){
    				string oldIsbn,newIsbn;
    				cin>>oldIsbn>>newIsbn;
    				Book* existingBook=library.findBookByIsbn(oldIsbn);

    				if(existingBook){
    					Book newBook(*existingBook,newIsbn);
    					library.addBook(newBook);
    				}else{
    					cout<<"Invalid request! Book not found"<<endl;
    				}
    			}
				else{
    				string title,author,isbn;
    				int copiesAvailable,totalCopies;
    				title=subinput;
    				cin>>author>>isbn>>copiesAvailable>>totalCopies;
    				Book book(title,author,isbn,copiesAvailable,totalCopies);
    				library.addBook(book);
    			}
    		}
            else if(input=="Member"){
    			string subinput;
    			cin>>subinput;
    			if(subinput=="NoBorrowLimit"){
    				string memberID,name;
    				cin>>memberID>>name;
    				Member member(memberID,name);
    				library.registerMember(member);
    			}else{
    				string memberID,name;
    				int borrowLimit;
    				memberID=subinput;
    				cin>>name>>borrowLimit;
    				Member member(memberID,name,borrowLimit);
    				library.registerMember(member);
    			}
    		}
            else if(input=="Borrow"){
    			string memberID,isbn;
    			cin>>memberID>>isbn;
    			library.borrowBook(memberID,isbn);
    		}
            else if(input=="Return"){
    			string memberID,isbn;
    			cin>>memberID>>isbn;
    			library.returnBook(memberID,isbn);
    		}
            else if(input=="PrintBook"){
    			string isbn;
    			cin>>isbn;
    			library.printBookDetails(isbn);
    		}
            else if(input=="PrintMember"){
    			string memberID;
    			cin>>memberID;
    			library.printMemberDetails(memberID);
    		}
            else if(input=="PrintLibrary"){
    			library.printLibraryDetails();
    		}
            else if(input=="UpdateCopiesCount"){
    			string isbn;
    			int count;
    			cin>>isbn>>count;
    			library.updateCopiesCount(isbn,count);
    		}
            else if(input=="Done"){
    			break;
    		}


    	}



    }