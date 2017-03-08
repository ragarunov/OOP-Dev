/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */
 
import java.io.IOException;

// This class creates a shape of type Rectangle
public class Rectangle implements Shape {

	private String type; // Shape type (rectangle)
    private double width; // Rectangle width
	private double length; // Rectangle length
	
	/*
    Constructor accepts a string for the shape type and two doubles of length and width of the rectangle, throws exception if data is not valid
    */
	public Rectangle (String n, double w, double l) throws IOException {

		if (w <= 0 || l <= 0) throw new IOException();
		type = n;
		length = l;
		width = w;
	
	}
	
	// Return type of the shape
	public String getType() {
		 
		return type;
		 
	}
	 
	/*
    Getting the perimeter of the rectangle
	*/
	@Override
    public double getPerimeter() {
		
		double result = width + width + length + length;
        
		return result;
		
    }

	/*
    Returning a formatted string of the variables in the object
    */
    @Override
    public String toString(){
       
	   return "Rectangle{l=" + Double.toString(length) + " w=" + Double.toString(width) + "} has perimeter: " + String.format("%.2f", getPerimeter()) + '\n';
    }

    // Converts private data to hashCode by first converting to bits and then applying the hash formula.
    @Override
    public int hashCode(){
		
		int res = 1;
		long tmp;
		long anotherTmp;
		long bothTmp;
		
		tmp = Double.doubleToLongBits(length); // Convert to bits for bit shift
		anotherTmp = Double.doubleToLongBits(width); // Convert to bits for bit shift
		bothTmp = tmp + anotherTmp;
		
		res = 31 * res + (int) (bothTmp ^ (bothTmp >>> 32 )); // Hash formula
		return res;
       
    }

    /*
	A boolean function indicating whether the rectangles are equal
    */
    @Override
    public boolean equals(Object object){
		
		if (this == object) return true; // Check if equals
		if (object == null) return false; // Check if not null 
		if (this.hashCode() != object.hashCode()) return false; // Compare hash codes
		
		return true;
      
    }
}