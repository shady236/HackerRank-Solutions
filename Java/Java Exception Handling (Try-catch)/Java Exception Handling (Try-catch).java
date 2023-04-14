import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        
        Scanner in = new Scanner(System.in);
        try {
            String line = in.next();
            int x = Integer.parseInt(line);
            line = in.next();
            int y = Integer.parseInt(line);
            System.out.println(x / y);
        }
        catch (ArithmeticException e) {
            System.out.println(e.toString());
        }
        catch (NumberFormatException e) {
            System.out.println("java.util.InputMismatchException");
        }
    }
}
