/**
 * Last Name: Agarunov
 * First Name: Ronen
 * Student ID: 029-490-158
 * codeboard UserName: ragarunov
 */

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import java.util.*; // To use Arrays and Collections


public class Main {

	private static List<Shape> arr = new ArrayList<Shape>(); // Declaring ArrayList
	
    public static void main(String[] args) {
        
        System.out.println("-------> JAC 444 Assignment 1 by Ronen Agarunov <-------");
        
        System.out.println("\n------->Task 1 ... <-------");
		// Call the BuildFromFile function, passing the file name
		// returns an ArrayList of all the shapes
		arr = buildShapesFromFile("Shapes.txt");
		for (Shape b : arr) System.out.print(b); // Print out all shapes, unsorted
        
        System.out.println("\n------->Task 2 ... <-------");
		// Call deleteAt function, passing the ArrayList
		// This function will remove the lowest perimeters of Triangle and Circle shapes
		deleteAt(arr);

        System.out.println("\n------->Task 3 ... <-------");
		// Call calculate function, passing the ArrayList
		// Calculates perimeters of Parallelogram and Triangle shapes
		calculate(arr);
		
        System.out.println("\n------->Task 4 ... <-------");
		// Call sort function, passing the ArrayList
		// Sorts all the shapes in the ArrayList alphabetically and then numerically
		sort(arr);

    }

	// This function retrieves the data from the text file that is passed to it and organises it into an ArrayList
    public static List<Shape> buildShapesFromFile(String fileName) {

		// Default values - get path and set string
        String path = System.getProperty("user.dir");
        //Shape sp = null;
        String s;

        try (BufferedReader br = new BufferedReader(new FileReader(path + "/src/" + fileName))) {
        // if you run locally on your environment use: new FileReader(path + "/src/" + fileName)
		// Default file path: new FileReader("./Root/" + fileName)))
            while ((s = br.readLine()) != null) {
                String[] tok = s.split(","); // Create a String array and set it values of every line in the file, divided by ','
				
				/*
				If tok[0] -the name of the Shape- is == to the one we're looking for - 
				it will create a new object of specified shape, will assign its name type and value(s) to the constructor
				and add it to the ArrayList.
				
				This method repeats itself 5 times, for each Shape type we are interested in allocating.
				*/
				if (tok[0].equals("Circle")) {
					try{
						arr.add( new Circle(tok[0], Double.parseDouble(tok[1])) ); // Parses the string into a double
					} catch (IOException e) { }
				}
				
				else if (tok[0].equals("Triangle")) {
					try {
						arr.add( new Triangle(tok[0], Double.parseDouble(tok[1]), Double.parseDouble(tok[2]), Double.parseDouble(tok[3])) );
					}
					catch (IOException e) { }
				}
				
				else if (tok[0].equals("Square")) {
					try {
						arr.add( new Square(tok[0], Double.parseDouble(tok[1])) );
					}
					catch (IOException e) { }
				}
				
				else if (tok[0].equals("Parallelogram")) {
					try {
						arr.add( new Parallelogram(tok[0], Double.parseDouble(tok[1]), Double.parseDouble(tok[2])));
					} catch (IOException e) { }
					
				}
				
				else if (tok[0].equals("Rectangle")) {
					try {
						arr.add( new Rectangle(tok[0], Double.parseDouble(tok[1]), Double.parseDouble(tok[2])));
					} catch (IOException e) { }
				}
                
            }
			// if fails, catch an error message.
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

		// Return the arraylist back to class Main
        return arr;
	}
	
	public static void deleteAt(List<Shape> arr) {
		
		// Set minimum and maximum values.
		// T stands for Triangle, C stands for circle
		double minT = 999;
		double maxC = -999;

		/*
		Iterates through the arraylist-
		once finds a "Triangle" shape element, checks if the perimeter value is smaller than minT.
		If it is, minT gets assigned the new Perimeter value.
		
		once finds a "Circle" shape element, checks if the perimeter value is bigger than maxC.
		If it is, maxC gets assigned the new Perimeter value.
		*/
		for (Iterator<Shape> it = arr.iterator(); it.hasNext();) {
			
			Shape s = it.next();
			
			if (s.getType().equals("Triangle")) {
				
				if (s.getPerimeter() < minT) {
					
					minT = s.getPerimeter();
					
				}
				
			}
			
			if (s.getType().equals("Circle")) {
				
				if (s.getPerimeter() > maxC) {
					
					maxC = s.getPerimeter();
					
				}
				
			}
			
		}
		
		/*
		Iterates through the arraylist once again- 
		once finds a "Triangle" shape element, checks if the perimeter value is equal to minT.
		If it is, element gets removed.
		
		once finds a "Circle" shape element, checks if the perimeter value is equal to maxC.
		If it is, element gets removed.
		*/
		for (Iterator<Shape> it = arr.iterator(); it.hasNext();) {
			
			Shape s = it.next();
			
			if (s.getType().equals("Triangle")) {
				if (s.getPerimeter() == minT) it.remove();
			}
			
			if (s.getType().equals("Circle")) {
				if (s.getPerimeter() == maxC) it.remove();
			}
			
		}
		
		/*
		Prints out the new ArrayList, without the removed elements.
		Notifies the user of what values of what elements were removed on which shape type.
		*/
		for (Shape b : arr) System.out.print(b);
		System.out.printf("\nMinimum perimeter of all triangles: %.2f was DELETED.\n", minT);
		System.out.printf("Maximum perimeter of all circles: %.2f was DELETED.\n", maxC);

	}
	
	public static void calculate(List<Shape> arr) {
		
		// Set minimum and maximum values.
		// PrCal contains perimeters of all parallelograms.
		// PrTr contains perimeters of all triangles.
		double PrCal = 0;
		double PrTr = 0;
		
		/*
		Iterates through the ArrayList-
		once finds a "Parallelogram" shape element, adds its perimeter value to PrCal.
		once finds a "Triangle" shape element, adds its perimeter value to PrTr.
		*/
		for (Shape b : arr) {

			if (b.getType().equals("Parallelogram")) {
				
				PrCal += b.getPerimeter();
				
			}
			
			if (b.getType().equals("Triangle")) {
				
				PrTr += b.getPerimeter();
				
			}
			
		}
		
		// Prints out Perimeter of all Parallelograms and all Triangles
		System.out.printf("Perimeter of all Parallelogram: %.2f\n", PrCal);
		System.out.printf("Perimeter of all Triangles: %.2f\n", PrTr);
		
	}
	
	public static void sort(List<Shape> arr) {
		
		/*
		Uses built-in function of Collections.sort, passing the ArrayList and creating a new Comparator of Shape.
		A compare function, that gets the parameters of Shape object, compares between both names and sorts it.
		If both Shape type are equal, compares its perimeter and sorts them.
		*/
		Collections.sort(arr, new Comparator<Shape>() {
			@Override public int compare(Shape p1, Shape p2) {
				int i = p1.getType().compareTo(p2.getType());
				
				if (i == 0) {
					return Double.compare(p1.getPerimeter(), p2.getPerimeter());
				}
				
				return i;
				
			}
				
			});
		
		// Prints the sorted ArrayList
		for (Shape b : arr) System.out.print(b);
		
	}
}
