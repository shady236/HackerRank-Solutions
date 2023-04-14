import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String s = scan.nextLine();
        // Write your code here.
        scan.close();
        
        
        
        String[] arrOfStr = s.split ("[!, ?._'@]+");
        
        int arrLen = arrOfStr.length;
        
        for (String a : arrOfStr)
        {
            if( a.equals("") )
            {
                arrLen--;
            }
        }
        
        System.out.println(arrLen);
        
        
        for (String a : arrOfStr)
        {
            if( !a.equals("") )
            {
                System.out.println(a);
            }
        }
        
    }
}

