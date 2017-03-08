/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */
 
import java.io.IOException;

// This class creates a shape of type Parallelogram
public class Parallelogram implements Shape {

	private String type; // Shape type (parallelogram)
    private double width; // Parallelogram width
	private double height; // Parallelogram height

	/*
    Constructor accepts a string for the shape type and two doubles of width and height of the parallelogram, throws exception if data is not valid
    */
	public Parallelogram (String n, double w, double h) throws IOException {
	
		if (w <= 0 || h <= 0) throw new IOException();
		type = n;
		height = h;
		width = w;
	
	}
	
	// Return type of the shape
	public String getType() {
	
		return type;
	
	}
	 
	/*
    Getting the perimeter of the parallelogram
	*/
	@Override
    public double getPerimeter() {
		
		double result = 2*(height + width);
        
		return result;
		
    }

	/*
    Returning a formatted string of the variables in the object
    */
    @Override
    public String toString(){
     
	   return "Parallelogram{w=" + String.format("%.1f", width) + " h=" + String.format("%.1f", height) + "} has perimeter: " + String.format("%.2f", getPerimeter()) + '\n';
	   
    }

    // Converts private data to hashCode by first converting to bits and then applying the hash formula.
    @Override
    public int hashCode(){
		
		int res = 1;
		long tmp;
		long anotherTmp;
		long bothTmp;
		
		tmp = Double.doubleToLongBits(height); // Convert to bits for bit shift
		anotherTmp = Double.doubleToLongBits(width); // Convert to bits for bit shift
		bothTmp = tmp + anotherTmp;
		
		res = 31 * res + (int) (bothTmp ^ (bothTmp >>> 32 )); // Hash formula
		return res;
       
    }

	/*
	A boolean function indicating whether the parallelograms are equal
    */
    @Override
    public boolean equals(Object object){
		
		if (this == object) return true; // Check if equals
		if (object == null) return false; // Check if not null 
		if (this.hashCode() != object.hashCode()) return false; // Compare hash codes
		
		return true;
		
    }
}