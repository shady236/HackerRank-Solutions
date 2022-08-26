//Complete this code or write your own from scratch
import java.util.*;
import java.io.*;

class Solution{
	public static void main(String []argh)
	{
		Scanner in = new Scanner(System.in);
		int n=in.nextInt();
		in.nextLine();
		HashMap<String, Integer> book = new HashMap<>();
        for(int i=0;i<n;i++)
		{
			String name=in.nextLine();
			int phone=in.nextInt();
			book.put(name, phone);
            in.nextLine();
		}
		while(in.hasNext())
		{
			String s=in.nextLine();
            if(book.get(s) == null)
                System.out.println("Not found");
            else
                System.out.println(s + "=" + book.get(s));
		}
	}
}


