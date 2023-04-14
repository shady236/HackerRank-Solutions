import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.security.*;
import javax.xml.bind.DatatypeConverter;

public class Solution 
{

    public static void main(String[] args)
    {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        
        Scanner scan = new Scanner(System.in);
        String password = scan.next();       
        scan.close();
        
        try
        {
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(password.getBytes());
            byte[] passwordDigest = md.digest();
            
            System.out.print(DatatypeConverter.printHexBinary(passwordDigest).toLowerCase());
        }
        catch(Exception e)
        {
            
        }
        
    }
}
