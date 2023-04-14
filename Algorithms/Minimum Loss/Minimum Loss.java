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
    
    static int seaech(List<Integer> arr, int target)
    {
        int st = 0;
        int ed = arr.size() - 1;
        
        while(st <= ed)
        {
            int mid = (st+ed)>>1;
            
            if(target == arr.get(mid)) 
                return mid;
            else if(target > arr.get(mid))
                st = mid + 1;
            else if(target < arr.get(mid))
                ed = mid - 1;
        }
        
        return -1;
    }
    
    /*
     * Complete the 'minimumLoss' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts LONG_INTEGER_ARRAY price as parameter.
     */

    public static long minimumLoss(List<Long> price) {
    // Write your code here
        
        // store original indeces 
        HashMap<Long, Integer> initIdx = new HashMap<>();
        for (int i = 0; i < price.size(); i++)
            initIdx.put(price.get(i), i);
        
        Collections.sort(price);
        
        long min = price.get(price.size() - 1);
        
        for(int i = 1; i < price.size(); i++)
        {
            long x = price.get(i) - price.get(i - 1);
            
            if(initIdx.get(price.get(i)) < initIdx.get(price.get(i - 1)))
                min = Math.min(min, x);
        }
        
        return min;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        List<Long> price = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
            .map(Long::parseLong)
            .collect(toList());

        long result = Result.minimumLoss(price);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
