import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);
        
        int n = in.nextInt();
        List<Integer> list = new ArrayList<>(n);
        for(int i=0; i<n; i++)
            list.add(in.nextInt());
        in.close();
        
        int count = 0;
        for(int i=0; i<n; i++)
        {
            int sum = 0;
            for(int j=i; j<n; j++)
            {
                sum += list.get(j);
                if(sum < 0)     count++;
            }
        }
        System.out.println(count);
    }
}
