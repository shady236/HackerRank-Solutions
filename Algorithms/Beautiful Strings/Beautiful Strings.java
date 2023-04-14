import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Block {
    public char chr;
    public int  len;
    
    public Block(char ch, int l) {
        chr = ch;
        len = l;
    }
}

class Result {
    
    /*
     * Complete the 'beautifulStrings' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts STRING s as parameter.
     */

    public static long beautifulStrings(String s) {
        // Write your code here
        
        List<Block> blocks = new ArrayList<>();
        blocks.add(new Block(s.charAt(0), 1));
        
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) == s.charAt(i - 1)) 
                blocks.get(blocks.size() - 1).len++;
            else 
                blocks.add(new Block(s.charAt(i), 1));
        }
        
        long cnt = 0;
        
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks.get(i).len == 1) 
                cnt += blocks.size() - i - 1;
            else 
                cnt += blocks.size() - i;
        }
        
        for (int i = 1; i < blocks.size() - 1; i++) {
            if (blocks.get(i).len == 1 && blocks.get(i - 1).chr == blocks.get(i + 1).chr) 
                cnt--;
        }
        
        return cnt;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String s = bufferedReader.readLine();

        long result = Result.beautifulStrings(s);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
