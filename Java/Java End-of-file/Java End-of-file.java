import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        
        
        Scanner scaner = new Scanner(System.in);
        int i = 1;
        while(scaner.hasNext())
        {
            System.out.println(i + " " + scaner.nextLine());
            i++;
        }
        scaner.close();
        
    }
}
