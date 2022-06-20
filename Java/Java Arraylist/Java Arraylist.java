import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();

        List<List<Integer>> list = new ArrayList<List<Integer>>(n);
        
        for(int i=0; i<n; i++)
        {
            int d = in.nextInt();
            
            List<Integer> l = new ArrayList<>(d);
            for(int j=0; j<d; j++)
            {
                l.add(in.nextInt());
            }
            list.add(l);
        }
        
        int q = in.nextInt();
        for(int i=0; i<q; i++)
        {
            try
            {
                System.out.println(list.get(in.nextInt() - 1).get(in.nextInt() - 1));
            }
            catch(Exception e)
            {
                System.out.println("ERROR!");
            }
        }
        
        in.close();
    }
    
}
