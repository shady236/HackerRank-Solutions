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
     * Complete the 'angryChildren' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER k
     *  2. INTEGER_ARRAY packets
     */

    public static long angryChildren(int k, List<Integer> packets) {
        // Write your code here
        Collections.sort(packets);
        
        /*
         * After sorting elements, minimum unfairness can be calculated without 
         * using any abs() functions, abs(ai - aj) = ai - aj  if i > j
         *
         * Choosing k elemennts from the packets array and calculating unfairness 
         * after that is unefficient, it takes O(k^2) time
         * 
         * Unfairness of choosing k elemnts can be calculated in linear time, it 
         * just requires us to keep track of running sum and size of elements.
         * We start with empty set; i.e. no choosen elements; so:
         *     - sum = 0
         *     - size = 0
         *     - unfairness = 0
         * When we add an elements say a, unfairness would increase by an amount of
         * diffrence between element a and all previously chosen elements.
         * 
         * By traversing elements from start to end, curent element must be >= all 
         * previously chosen elements, so diffrence between a and all previously 
         * chosen elements would be:
         *  (a - e0) + (a - e1) + (a - e2) + ...  = a * size - sum
         * 
         * 
         * NOTE: min unfairness can be gotten only from subarrays, no need to try all
         * subsequences, thats why if currently we have chosen some elements, next
         * element to be chosen will increase unfairness by --> a * size - sum
         * so, a' value must be chosen to be min which is surely the next element
         * to the last chosen element.
         */
        
        
        /*
         * get unfairness of first subarray which is packets[0 ... k - 1] inclusive 
         */
        long sum = 0;
        long unfairness = 0;
        
        for (int i = 0; i < k; i++) 
        {
            unfairness += packets.get(i) * (long)i - sum;
            sum += packets.get(i);
        }
        
        long minUnfairness = unfairness;
        
        /*
         * try other subarrays which will start from index > 0
         */
        int strtIdx = 1;
        int endIdx = strtIdx + k - 1;
        while (endIdx < packets.size())
        {
            /*
             * now subarray is packets[strtIdx ... endIdx]
             * previous subarray was packets[strtIdx - 1 ... endIdx - 1]
             * 
             * first, remove element at strtIdx - 1 from subarray, this will affect
             * both sum and unfairness
             * 
             * sum would decrese by the value of packets[strtIdx - 1]
             * 
             * unfairness would decrease by an amount of diffrence between element
             * packets[strtIdx - 1] and elements of packets[strtIdx ... endIdx - 1]
             * 
             * As array in sorted, rhis diffrence would be the sum of these terms:
             *   - packets[strtIdx]     -  packets[strtIdx - 1]
             *   - packets[strtIdx + 1] -  packets[strtIdx - 1]
             *   - packets[strtIdx + 2] -  packets[strtIdx - 1]
             *   - ...
             *   - packets[endIdx]      -  packets[strtIdx - 1]
             * 
             * as terms count are k - 1, it can be simplyfied to 
             *     sum - packets[strtIdx - 1] * (k - 1)
             */
            sum  -= packets.get(strtIdx - 1);
            unfairness -= sum - packets.get(strtIdx - 1) * (k - 1L);
            
            
            /*
             * add element at endIdx to subarray
             */
            unfairness += packets.get(endIdx) * (k - 1L) - sum;
            sum  += packets.get(endIdx);
            
            minUnfairness = Math.min(minUnfairness, unfairness);
            
            strtIdx++;
            endIdx++;
        }
        
        return minUnfairness;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        int k = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> packets = IntStream.range(0, n).mapToObj(i -> {
            try {
                return bufferedReader.readLine().replaceAll("\\s+$", "");
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        })
            .map(String::trim)
            .map(Integer::parseInt)
            .collect(toList());

        long result = Result.angryChildren(k, packets);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
