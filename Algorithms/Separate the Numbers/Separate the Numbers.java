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

class Result {

    /*
     * Complete the 'separateNumbers' function below.
     *
     * The function accepts STRING s as parameter.
     */

    public static void separateNumbers(String s)
    {
        // Write your code here
        int sLen = s.length();
        BigInteger startNum = BigInteger.ZERO;
        boolean isStartNumValid = false;
        
        if(s.charAt(0) != '0')
        {
            for(int firstNumLen = 1; firstNumLen <= (sLen>>1); firstNumLen++)
            {
                int numLen = firstNumLen;
                startNum = new BigInteger(s.substring(0, firstNumLen));
                BigInteger prevNum = new BigInteger(startNum.toString());
                
                for(int i = firstNumLen; i != sLen; i += numLen)
                {
                    if(prevNum.add(BigInteger.ONE).equals(new BigInteger(Integer.toString((int)(Math.pow(10, numLen) + 0.002)))))
                        numLen++;
                    
                    if(i + numLen > sLen)
                    {
                        isStartNumValid = false;
                        break;
                    }
                    
                    BigInteger currNum = new BigInteger(s.substring(i, i + numLen));
                    
                    if(!currNum.equals(prevNum.add(BigInteger.ONE)))
                    {
                        isStartNumValid = false;
                        break;
                    }
                    else
                    {
                        prevNum = new BigInteger(currNum.toString());
                        isStartNumValid = true; 
                    }
                }
                if(isStartNumValid)     break;
            }
        }
        
        if(isStartNumValid)
        {
            System.out.println("YES " + startNum.toString());
        }
        else
        {
            System.out.println("NO");
        }
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                String s = bufferedReader.readLine();

                Result.separateNumbers(s);
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
    }
}
