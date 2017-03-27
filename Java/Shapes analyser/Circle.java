/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */
 
import java.io.IOException;

// This class creates a shape of type Circle
public class Circle implements Shape {

	private String type; // Shape type (circle)
    private double radius; // Circle radius
	double pi = 3.14159; // Value of PI

    /*
    Constructor accepts a string for the shape type and a double for the radius, throws exception if data is not valid
    */
	public Circle (String n, double r) throws IOException {
		
		if (r <= 0) throw new IOException();
		type = n;
		radius = r;
	}
	 
	// Return type of the shape
	public String getType() {
		 
		return type;
		 
	}
	 
    /*
    Getting the perimeter of the circle
	*/
    public double getPerimeter() {
       return 2 * pi * radius;
    }

    /*
    Returning a formatted string of the variables in the object
    */
    @Override
    public String toString(){
       
	   return "Circle{r=" + Double.toString(radius) + "} has perimeter: " + String.format("%.2f", getPerimeter()) + '\n';
	   
    }

    // Converts private data to hashCode by first converting to bits and then applying the hash formula.
    @Override
    public int hashCode(){
		
		int res = 1;
		long tmp = Double.doubleToLongBits(radius); // Convert to bits for bit shift
		res = 31 * res + (int)(tmp ^ (tmp >>> 32 )); // Hash formula
		return res;
       
    }

    /*
	A boolean function indicating whether the circles are equal
    */
    @Override
    public boolean equals(Object object){
		
		if (this == object) return true; // Check if equals
		if (object == null) return false; // Check if not null 
		if (this.hashCode() != object.hashCode()) return false; // Compare hash codes
		
		return true;
      
    }
}