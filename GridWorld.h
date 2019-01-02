	
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#define MAX_POPULATION 1000

#include <vector>
#include <iostream>

using namespace std; 
using std::vector;

/*

Grid-World 

Jhon Nunez
University of Illinois at Chicago

*/

class GridWorld {

  private:
	  
	  struct Node
	  {
		  int	data;
		  Node  *next;//Pointer to next node;
		  Node	*prev;//Pointer to previous node; 

		  Node() {
			  data = -999;
			  next = nullptr;
			  prev = nullptr;
		  }	  
		 // Node(int & d = int{}, Node * n = nullptr)
		 //	  : data{ d }, next{ n } { }

	  };

	  struct phoneBook {
		  
		  int id, row, column, alive;
		  Node* idLocation; //location of id

		  phoneBook() {
			  id = 0;
			  row = 0;
			  column = 0;
			  alive = 0;
			  idLocation = nullptr;
		  }

		};

	  struct district {
		  
		  Node * head; //head to members dll
		  Node * tail; //tail to  members dll
		  int row, column, districtPopulation;

		   district() { 
			  row = 0;
			  column = 0;
			  districtPopulation = 0;
		  }
	  };

	  // Data memmers of GridWorld
	  int rows;
	  int columns;
	  int totalPopulation = 0;
	  int range = 0;			//gives me range of data
	  int idCounter = -1;		//gives me next person id in world
	  int reUse = 0;			//signals when to re use an id from a previously dead person 

	  vector <vector <district> > dist;
	  vector <phoneBook> book; //declare phonebook vector
	
	  Node* dHead; //head to deadPool
	  Node* dTail; //tail to deadPool
	  //vector<int> deadPool;//deadPool
	  

  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
	  
	  GridWorld(unsigned nrows, unsigned ncols)   {
      // your constructor code here!
		rows = nrows;
		columns = ncols;		
/*
		vector < vector <district> > dist(rows); //declare district vector
		for (i = 0; i < rows; i++) {
			dist[i] = vector <district> (columns);
			//dist[i] = columnV(columns);
			for (j = 0; j < columns; j++) {
				//dist[i][j].row = i;
				//dist[i][j].column = j;
				dist[i][j].row = i;
				dist[i][j].column = j;
			}
		}
		*/
		//resize matrix based on user input 
		dist.resize(columns, vector<district>(rows));

		//label each row and column in gridWorld
		int i,j;
		for (i = 0; i < rows; i++) {
			for (j = 0; j < columns; j++) {			
				//initilize dll in district
				dist[i][j].head = nullptr;
				dist[i][j].tail = nullptr;		
				dist[i][j].row = i;
				dist[i][j].column = j;
			}
		}
		//initialize deadPool
		dHead = nullptr;
		dTail = nullptr; 

		/*
		//print vector of GridWorld
		for (i = 0; i < rows; i++) {
			for (j = 0; j < columns; j++) {
				cout << dist[i][j].row << dist[i][j].column << " ";
			}
			cout << endl;
		}
		*/

    }
    ~GridWorld(){
      // your destructor code here.
		int i, j;
		dist.clear(); //wipe gridWorld vectors 
		book.clear();//wipe phone book
		clearDeath();//wipe deadPool

		/*
		for (i = 0; i < rows; i++) {//remove distric members 
			for (j = 0; j < columns; j++) {
				clear(i, j);
			}
		}
		*/

    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
	
	//--------------------------------------------------------------------------------
	//DLL functions
	void addDead(int val) {
	
		Node* p = new Node();
		if (dHead == nullptr) {//empty list
			p->data = val;
			p->next = nullptr;
			p->prev = nullptr; 
			dHead = p;
			dTail = p;
		}
		else {
				
			p->data = val;
			p->next = nullptr; 
			dTail->next = p;
			p->prev = dTail;
			dTail = p;

		}
		//cout << "dHead " << dHead->data << endl; //testing
		//cout << "dTail " << dTail->data << endl; //testing
	}
	bool removeDead() {//deadPool popFront
		Node *p;
		p = dHead; 

		if (p == nullptr) {//list is already empty 
			dTail = nullptr; 
			return false;
		}
		if (p->next == nullptr) {//only one member of list
			dHead = nullptr;
			dTail = nullptr;
			//delete p;
			return true;
		}

		p = dHead->next;
		p->prev = nullptr;
		dHead = p;
		//delete p;
		return true;

		//cout << "dHead " << dHead->data << endl; //testing
		//cout << "dTail " << dTail->data << endl; //testing
	}

	void clearDeath() {//Wipe dead pool
		Node *p = dHead;
		Node *tmp;

		while (p != nullptr) {
			tmp = p->next;
			free(p);
			p = tmp;
		}

		dHead = nullptr; 
		dTail = nullptr; 
	}

	void pushFront(int val, int row, int col) {
		Node* p = new Node();
		if (dist[row][col].head == nullptr) {//empty list

			p->data = val;
			dist[row][col].head = p;
			dist[row][col].tail = p;
		}
		else {
			p->data = val;
			p->next = dist[row][col].head;
			dist[row][col].head = p;
		}
		//cout << dist[row][col].head->data << endl; //testing
		//cout << dist[row][col].tail->data << endl; //testing
	}

	void pushBack(int val, int row, int col) {	
		
		Node* p = new Node();
		if (dist[row][col].head == nullptr) {//empty list
			
			p->data = val;
			p->next = nullptr;
			p->prev = nullptr; 
			dist[row][col].head = p;
			dist[row][col].tail = p;

		}
		else {// push back
			p->data = val;
			p->prev = dist[row][col].tail;
			dist[row][col].tail->next = p;
			p->next = nullptr; 
			dist[row][col].tail = p;
		}

		//cout << dist[row][col].head->data << endl; //testing
		//cout << dist[row][col].tail->data << endl; //testing
		
	}

	bool popFront(int row, int col) {

		Node *p;

		if (dist[row][col].head == nullptr) {//list is already empty 
			return false; 
		}
		if (dist[row][col].head->next == nullptr) {//only one member of list
			p = dist[row][col].head;
			p->next = nullptr;
			delete p;
			return true; 
		}

		p = dist[row][col].head->next;
		dist[row][col].head = p;
		dist[row][col].head->prev = nullptr;
		p = p->prev;
		delete p;
		return true; 

		//cout << dist[row][col].head->data << endl; //testing
		//cout << dist[row][col].tail->data << endl; //testing

	}

	bool popBack(int & val, int row, int col) {

		Node *p;

		if (dist[row][col].head == nullptr) {//list is already empty 
			return false;
		}
		if (dist[row][col].head->next == nullptr) {//only one member of list
			p = dist[row][col].head;
			p->next = nullptr;
			delete p;
			return true;
		}

		p = dist[row][col].head->next;
		dist[row][col].head = p;
		dist[row][col].head->prev = nullptr;
		p = p->prev;
		delete p;
		return true;

		//cout << dist[row][col].head->data << endl; //testing
		//cout << dist[row][col].tail->data << endl; //testing

	}

	bool remove(Node* p, int row, int col) {//O(1)

		//cout << "Pointer val before" << p->data << endl;
		if (p == nullptr) {//person is already dead
			return false; 
		}
		if (p->next == nullptr && p->prev == nullptr) {//last person on list	
			dist[row][col].head = nullptr;
			dist[row][col].tail = nullptr;
			delete p;
			return true; 
		}
		if (p->prev == nullptr) {//remove first person
			dist[row][col].head = p->next;
			dist[row][col].head->prev = nullptr; 
			delete p;
			return true;
		}
		if (p->next == nullptr) {//remove last person
			dist[row][col].tail = p->prev;
			dist[row][col].tail->next = nullptr;
			delete p;
			return true;
		}
		else {//its in between two nodes
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			return true;
		}
		//cout << "Pointer val after" << p->data << endl;
	}



	void clear(int row, int col) {
		Node *p = dist[row][col].head;
		Node *tmp;

		while (p != nullptr) {
			tmp = p->next;
			free(p);
			p = tmp;
		}

		dist[row][col].head = nullptr;
		dist[row][col].tail = nullptr;
	}


	void printMems(int row, int col){
		Node *p = dist[row][col].head;

		cout << "[ ";
		while (p != nullptr) {
			cout << p->data << " ";
			
			p = p->next;

		}
		cout << "]\n";
	}
	
	//--------------------------------------------------------------------------------
	int getTotalPopulation() {
		return totalPopulation; //retrieves the world's population 
	}

	int getRange() {
		return range;//retrieves range
	}

	int getID() {

		//deadPool numbers
		Node *p = dHead;
		int deadNum;

		if (p != nullptr) {//death pool members

			deadNum = p->data;
			removeDead(); //remove head
			reUse++; //signals that a ID must be reused 
			return deadNum; 
		}
		idCounter++; //increase counter 
		return idCounter;
	}
	//--------------------------------------------------------------------------------

    bool birth(int row, int col, int &id){
		
		if (rows <= row || columns <= col) {//return false when input is out of bound 
			return false;
		}
		int N;

		N = getID();
		pushBack(N, row, col);
		id = N;
		//populate phoneBook

		//reuse id number 
		if (reUse == 1) {
			book[N].alive = 1;
			book[N].row = row;
			book[N].column = col;
			book[N].idLocation = dist[row][col].tail;
			reUse = 0; //signals re use has been completed 
		}
		else {

			//create new entry
			phoneBook A;
			A.id = N;
			A.row = row;
			A.column = col;
			A.alive = 1;
			A.idLocation = dist[row][col].tail;
			book.push_back(A);
		}

		dist[row][col].districtPopulation++; //increase district's population 
		totalPopulation++; //increase world's population 
		range++;//increase range

		
		return true; 
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){

		int row, col;
 
		if ( idCounter < personID) {
			//cout << "range " << endl; //testing
			return false; //invalid id "Out of range" 
		}
		
		if (book[personID].alive == 0) {
			//cout << "book dead" << endl; //testing
			return false;//person is dead
		}
	  
		//locate person
		row = book[personID].row;
		col =  book[personID].column;
		book[personID].alive = 0; //mark death in phoneBook 
		
		Node *location = book[personID].idLocation;
		remove(location, row, col);
		addDead(personID);//add ID to dead pool 
		dist[row][col].districtPopulation--; //decrease district population 
		totalPopulation--; //decrease population by 1

		return true;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{


		if ( range <= id) {
			return false;//out of range
	    }
		if (book[id].alive == 0) {
			return false;//person is dead
		}

		row = book[id].row;
		col = book[id].column;

		return true;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){

		int row, col;
		if (idCounter < id) {
			return false;//out of range
		}
		if (book[id].alive == 0) {
			return false;//person is dead
		}		
		if (rows <= targetRow || columns <= targetCol) {//return false when input is out of bound 
			return false;
		}
		row = book[id].row;
		col = book[id].column;
		dist[row][col].districtPopulation--; //decrease old district population
		dist[targetRow][targetCol].districtPopulation++; //increase new district population
											 
		Node *location = book[id].idLocation;
		remove(location, row, col);
		pushBack(id, targetRow, targetCol);//add to new district; 
		
		book[id].row = targetRow; //update phoneBook
		book[id].column = targetCol; //update phoneBook

		return true;
    }

    std::vector<int> * members(int row, int col)const{
	
	  vector<int>* v = new vector<int>;

	  if (rows <= row || columns <= col) {//Input is out of bound 
			return v;
	  }

	  Node *p = dist[row][col].head;

	  if (p == nullptr) {
		  return v; 
	  }

	  while (p != nullptr) {//populate new vector 
		  v->push_back(p->data);
		  p = p->next;
	  }

	  return v;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return totalPopulation;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return dist[row][col].districtPopulation;
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return rows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return columns;
    }


};

#endif
