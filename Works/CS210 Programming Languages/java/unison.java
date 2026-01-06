/* unison.java
 * 
 * Miguel Villlanueva
 * CS 210
 */

import java.io.*;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;

class unison
{
    public static void main(String[] args) throws FileNotFoundException
    {
	// File output
	PrintStream o = new PrintStream(new File("uniuml.json"));
	// Console output
	PrintStream console = System.out;
	// Assign o to output stream
	System.setOut(o);

        int a = args.length;    // Number of files to read
	int c = 0;              // Starting point

	while(c < a)
	{
	    File f = new File(args[c]);
	    try(BufferedReader br = new BufferedReader(new FileReader(f)))
	    {
		int supers = 0;      // Number of super classes
	        int rBrackets = 0;   // Number of right brackets
		int moreParams = 0;  // Signal for field continuation
	        String delims1 = "[  \t\n]+";
		String delims2 = "[ ,]+";
	        String line;
	        while((line = br.readLine()) != null)
	        {
		    // Parse line in file
		    String[] tok = line.split(delims1);
		    for(int i = 0; i < tok.length; i++)
		    {
			// Skip comments
			if(tok[i].equals("#"))
			    break;

			// If class fields are found on mult. lines
                        if(moreParams == 1)
                        {
			    /*
			      For some reason there are random
	                      "" strings contained in tok[0]

			      Confusing stuff lies below and
			      is the result of trial and error

			      But in my testing it works!
			    */

			    // End of field continuation
                            if(tok[1].equals(")"))
                                moreParams = 0;
			    // Checks if param contains a comma
                            else if(line.indexOf(",") != -1)
                            {
                                String s = "";
                                s = tok[1].substring(0, tok[1].indexOf(","));
                                System.out.print("\"");
                                System.out.print(s);
                                System.out.print("\", ");
				break;
                            }
			    // Last param
                            else
                            {
                                System.out.print("\"");
                                System.out.print(tok[1]);
                                System.out.print("\"]\n");
				System.out.println("  \"methods\" : {");
				rBrackets++;
				break;
                            }
                        }

			// class found
		        if(tok[i].equals("class"))
		        {
			    System.out.print("{ \"class\": \"");
			    String p = "";
			    if(line.indexOf("(") != -1)
			    {
			        p = line.substring(line.indexOf("(") + 1);
			        if(line.indexOf(")") != -1)
		  		    p = p.substring(0, p.indexOf(")"));
				else
				   moreParams = 1;    // field continues 
			    }
			    // Count the number of super classes
			    for(int j = 0; j < line.length(); j++)
			    {
				if(line.charAt(j) == ':')
				    supers++;
			    }
			    // Create a substring of the last class
			    String last = "";
			    last = tok[i + (2*supers) + 1];
			    last = last.substring(0, last.indexOf("("));
			    // If there are no super classes
			    if(supers == 0)
			    {
				System.out.print(last);
				System.out.print("\",\n");
			    }
			    else
			    {
				System.out.print(tok[i + 1]);
				i = i + 3;    // Skips colon
				System.out.print("\",\n");
				System.out.print("  \"super\": [");
				while(supers > 1)
				{
				    System.out.print("\"");
				    System.out.print(tok[i]);
				    System.out.print("\",");
				    supers--;
				    i = i + 2;
				}
				System.out.print("\"");
				System.out.print(last);
				System.out.print("\"]\n");
			    }

			    // Parse inbetween parenthesis
			    String[] params = p.split(delims2);
			    // If class contains no fields
			    if(line.indexOf("()") == -1)
			        System.out.print("\"fields\": [");
			    else
			    {
				System.out.println("  \"methods\" : {");
				rBrackets = rBrackets + 2;
				break;
			    }
			    // If everything needed is on one line
			    if(moreParams != 1)
			    {
				if(p.equals(""))
				    System.out.print("]\n");
				else
				{
				    // Print class fields
			            for(int k = 0; k < (params.length - 1); k++)
				    {
				        System.out.print("\"");
				        System.out.print(params[k]);
				        System.out.print("\", ");
				    }
				    System.out.print("\"");
				    System.out.print(params[params.length - 1]);
				    System.out.print("\"]\n");
				}
				System.out.println("  \"methods\" : {");
				rBrackets++;
			    }
			    // Increments number of rBrackets
			    rBrackets++;    // Printed at the end of file
		        }

			// method found
			if(tok[i].equals("method"))
			{
			    String m = ""; 
			    m = tok[i+1].substring(0, tok[i+1].indexOf("("));
			    System.out.print("\"");
			    System.out.print(m);
			    System.out.print("\": [");
			    
			    String p1 = "";
			    p1 = line.substring(line.indexOf("(") + 1);
			    p1 = p1.substring(0, p1.indexOf(")"));
			    
			    String[] params1 = p1.split(delims2);
			    if(p1.equals(""))
				System.out.print("]\n");
			    else
			    {
				// Print the method parameters
				for(int n = 0; n < (params1.length - 1); n++)
				{
				    System.out.print("\"");
				    System.out.print(params1[n]);
				    System.out.print("\", ");
				}
				System.out.print("\"");
				System.out.print(params1[params1.length - 1]);
				System.out.print("\"]\n");
			    }
			}
		    }
	        }
		// Print rBrackets
		while(rBrackets > 0)
		{
		    System.out.println("}");
		    rBrackets--;
		}
		System.out.println("");    // End of file
	    }
	    catch(IOException e)
	    {
	        e.printStackTrace();
	    }
	    c++;    // I chose the variable c because I thought it was funny
	}
	// Assign console to output stream
	System.setOut(console);
	System.out.println("uniuml.json created!");
    }
}
