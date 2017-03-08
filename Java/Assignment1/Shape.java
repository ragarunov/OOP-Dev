/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */
 
public interface Shape {

	public String getType(); // Holds the type of the Shape
	public double getPerimeter(); // Holds the perimeter of the Shape
	public String toString(); // Prints out the view and the members of the Shape
	public boolean equals(Object object); // Tests if object passed is equal to existing object
	public int hashCode(); // Converts private data to hashCode by first converting to bits and then applying the hash formula.
	
}