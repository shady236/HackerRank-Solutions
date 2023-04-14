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
     * Complete the 'sherlockAndMinimax' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER_ARRAY arr
     *  2. INTEGER p
     *  3. INTEGER q
     */

    public static int sherlockAndMinimax(List<Integer> arr, int p, int q)
    {
        Collections.sort(arr);
        
        if(arr.get(0) >= q)                  return p;
        if(arr.get(arr.size() - 1) <= p)     return q;
        
        int maxDiff = 0 , resultM = p;
        
        int i;
        if(arr.get(0) >= p)
        {
            maxDiff = arr.get(0) - p;
            resultM = p;
            i = 1;
        }
        else 
        {
            i=1;
            for(; arr.get(i) < p; i++);
            int midVal = (arr.get(i) + arr.get(i-1))>>1;
            if(midVal >= p)
            {
                maxDiff = Math.min(q, midVal) - arr.get(i-1);
                resultM = Math.min(q, midVal);
            }
            else
            {
                maxDiff = arr.get(i) - p;
                resultM = p;
            }
            i++;
        }
        
        for(; i<arr.size(); i++)
        {
            int midVal = (arr.get(i) + arr.get(i-1))>>1;
            int diff = Math.min(q, midVal) - arr.get(i-1);
            if(diff > maxDiff)
            {
                maxDiff = diff;
                resultM = Math.min(q, midVal);
            }
            
            if(arr.get(i) >= q)      break;
        }
        if(q > arr.get(arr.size() - 1))
        {
            if(q - arr.get(arr.size() - 1) > maxDiff)
            {
                maxDiff = q - arr.get(arr.size() - 1);
                resultM = q;
            }
        }
        
        return resultM;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> arr = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
            .map(Integer::parseInt)
            .collect(toList());

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int p = Integer.parseInt(firstMultipleInput[0]);

        int q = Integer.parseInt(firstMultipleInput[1]);

        int result = Result.sherlockAndMinimax(arr, p, q);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
