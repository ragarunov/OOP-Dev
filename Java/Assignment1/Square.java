/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */
import java.io.IOException;

// This class creates a shape of type Square
public class Square  implements Shape {

	private String type; // Shape type (square)
    private double side; // Square side size

	
	/*
    Constructor accepts a string for the shape type and a double for the side size, throws exception if data is not valid
    */
	 public Square (String n, double s) throws IOException {
		 
		if (s <= 0) throw new IOException();
		type = n;
		side = s;
		 
	}
	
	// Return type of the shape
    public String getType() {
		 
		return type;
		 
	}

    /*
    Getting the perimeter of the square
	*/
	@Override
    public double getPerimeter() {
       return side * 4;
    }

    /*
    Returning a formatted string of the variables in the object
    */
    @Override
    public String toString(){
       
	   return "Square{s=" + String.format("%.5f", side) + "} has perimeter: " + String.format("%.5f", getPerimeter()) + '\n';

    }

    // Converts private data to hashCode by first converting to bits and then applying the hash formula.
    @Override
    public int hashCode(){
		
		int res = 1;
		long tmp = Double.doubleToLongBits(side); // Convert to bits for bit shift
		res = 31 * res + (int) (tmp ^ (tmp >>> 32 )); // Hash formula
		return res;
       
    }

    /*
	A boolean function indicating whether the squares are equal
    */
    @Override
    public boolean equals(Object object){
		
		if (this == object) return true; // Check if equals
		if (object == null) return false; // Check if not null 
		if (this.hashCode() != object.hashCode()) return false; // Compare hash codes
		
		return true;
      
    }
}