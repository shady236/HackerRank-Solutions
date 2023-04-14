import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        
        int strLen = A.length();
        boolean isPalindrome = true;
        
        for(int i=0; i<strLen/2; i++)
        {
            if(A.charAt(i) != A.charAt(strLen-i-1))
            {
                isPalindrome = false;
                break;
            }
        }
        
        if(isPalindrome == true)
        {
            System.out.println("Yes");
        }
        else
        {
            System.out.println("No");
        }
        
    }
}



