import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);
        
        int n = in.nextInt();
        List<Integer> list = new ArrayList<>(n);
        for(int i=0; i<n; i++)
            list.add(in.nextInt());
        
        int q = in.nextInt();
        for(int i=0; i<q; i++)
        {
            String op = in.next();
            if(op.compareTo("Insert") == 0)
                list.add(in.nextInt(), in.nextInt());
            else
                list.remove(in.nextInt());
        }
        
        in.close();
        
        for(int i : list)
            System.out.print(i + " ");
    }
}
