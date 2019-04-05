Created by: Jhon Nunez
University of Illinois at Chicago 
To run this program:

 1. run g++ driver.cpp
 2. run ./a.out 
 3. driver.cpp tests gridworld.h with a 5x5 grid

<h3> SUMMARY: </h3>

Welcome to GridWorld where everybody is a number and lives in a square (unless of course they are dead).                

The World:  The world is kind of boring.  It is an RxC grid (rows and columns).  
Each entry on the grid is called a district and is referred to by its row r and column c   
We’ll sometimes refer to such a district as Dr,c.

The People:  Then there are the people; each person is uniquely identified by an integer ID (like a social security number).   
Person IDs start at zero.  Each living person resides in one (and only one) of the districts.

Day Zero:  When a world is created, just two things determine its initial configuration:
	R:  the number of rows
	C:  the number of columns

When a world is created, there are no people at all:  every district is a wasteland with no population.  
However, once created there are a number of operations that can be performed on the world 
(you should be thinking "Abstract Data Type" about now).

Operations:  once a world is created, there are various operations that can be performed.  

  <h3> Birth </h3>
	by calling this function we are asking for a new person to be created and to place that person in district (row, col).
	If the given row/col corresponds to a valid district, this function does the following:
	creates a new person
	assigns a unique integer ID to the person and 
	places that person  in district (row, col).
	communicates the assigned ID to the caller via the reference parameter id.
	Returns true (for "success").

  <h3> Death </h3>
	If alive, person represented by id  is removed from its current district and the entire world.  
	Data structures updated accordingly.

  <h3> Move </h3>
	If given person is alive, and specified target-row
	and column are valid, person is moved to specified district and
     	data structures updated accordingly.
  
  <h3> Population </h3>
	Simply returns the  total number of (living) people in the entire world/grid.
	or
	simply returns the  total number of (living) people in district specified by (row,col).  
	If row/col does not correspond to a valid district, zero is returned.

   <h3> WhereIs </h3>
	If personID represents a currently living person, the row and column where that person currently 
	lives is reported via reference parameters row and col and true is returned.  

	If personID does not correspond to a currently living person, false is returned

  <h3> Members </h3>
	Creates and populates an integer vector with a snapshot of the current residents of district specified by (row, col).  
	The vector is returned as a pointer.

	If there is no such district (row,col), a vector is still returned, but it is empty.

  num_rows/num_cols
	Returns the number of row (or columns) in the world.  


