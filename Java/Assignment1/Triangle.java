/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */
 
import java.io.IOException;

// This class creates a shape of type Triangle
public class Triangle implements Shape {

	private String type; // Shape type (triangle)
    private double A; // Side A of triangle
	private double B; // Side B of triangle
	private double C; // Side C of triangle

	/*
    Constructor accepts a string for the shape type and three doubles each side of the triangle, throws exception if data is not valid
    */
	public Triangle (String n, double a, double b, double c) throws IOException {
	
		if (a <= 0 || b <= 0 || c <= 0) throw new IOException();
		type = n;
		A = a;
		B = b;
		C = c;
	
	}
	
	// Return type of the shape
	public String getType() {
	
		return type;
	
	}

	/*
    Getting the perimeter of the triangle
	*/
	@Override
    public double getPerimeter() {
		
		double result = A + B + C;
        
		return result;
		
    }

	/*
    Returning a formatted string of the variables in the object
    */
    @Override
    public String toString(){
       
	   return "Triangle{A=" + Double.toString(A) + " B=" + Double.toString(B) + " C=" + Double.toString(C) + "} has perimeter: " + String.format("%.2f", getPerimeter()) + '\n';
    
	}

    // Converts private data to hashCode by first converting to bits and then applying the hash formula.
    @Override
    public int hashCode(){
		
		int res = 1;
		long tmpA;
		long tmpB;
		long tmpC;
		long allTmp;
		
		tmpA = Double.doubleToLongBits(A); // Convert to bits for bit shift
		tmpB = Double.doubleToLongBits(B); // Convert to bits for bit shift
		tmpC = Double.doubleToLongBits(C); // Convert to bits for bit shift
		allTmp = tmpA + tmpB + tmpC;
		
		res = 31 * res + (int) (allTmp ^ (allTmp >>> 32 )); // Hash formula
		return res;
       
    }

    /*
	A boolean function indicating whether the triangles are equal
    */
    @Override
    public boolean equals(Object object){
		
		if (this == object) return true; // Check if equals
		if (object == null) return false; // Check if not null 
		if (this.hashCode() != object.hashCode()) return false; // Compare hash codes
		
		return true;
      
    }
}