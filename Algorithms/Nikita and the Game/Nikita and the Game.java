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
    
    public static int arraySplitting(List<Integer> arr, int strtIdx, int endIdx, HashMap<List<Integer>, Integer> maxPointsDp)
    {
        if(strtIdx >= endIdx)
            return 0;
        
        List<Integer> key = new ArrayList<>();
        key.add(strtIdx);
        key.add(endIdx);
        
        if(maxPointsDp.containsKey(key))
            return maxPointsDp.get(key);
        
        long sum = 0;
        for (int i = strtIdx; i <= endIdx; i++) 
        {
            sum += arr.get(i);
        } 
        
        if(sum == 0)    // all arr elements are 0
        {
            int maxPoint = endIdx - strtIdx;
            maxPointsDp.put(key, maxPoint);
            return maxPoint;
        }
        else if(sum % 2 == 1)   // array can't be divided
        {
            maxPointsDp.put(key, 0);
            return 0;
        }
        
        
        long partSum = sum>>1;  // sum / 2
        
        int  rightLastIdx = strtIdx;
        long rightSum = arr.get(strtIdx);
        while (rightSum < partSum && rightLastIdx < endIdx)
        {
            rightLastIdx++;
            rightSum += arr.get(rightLastIdx);
        }
        
        int  leftFirstIdx = endIdx;
        long leftSum = arr.get(endIdx);
        while (leftSum < partSum && leftFirstIdx > strtIdx)
        {
            leftFirstIdx--;
            leftSum += arr.get(leftFirstIdx);
        }
        
        
        if(rightLastIdx == endIdx || leftFirstIdx == strtIdx || rightLastIdx >= leftFirstIdx || rightSum > partSum || leftSum > partSum)
        {
            maxPointsDp.put(key, 0);
            return 0;
        }
        
        
        int maxPoint = 1 + Math.max(
            arraySplitting(arr, strtIdx, leftFirstIdx - 1, maxPointsDp),
            arraySplitting(arr, rightLastIdx + 1, endIdx, maxPointsDp)
        );
        
        maxPointsDp.put(key, maxPoint);
        return maxPoint;
    }
    /*
     * Complete the 'arraySplitting' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER_ARRAY arr as parameter.
     */

    public static int arraySplitting(List<Integer> arr) {
        // Write your code here
        HashMap<List<Integer>, Integer> maxPointsDp = new HashMap<>();
        
        return arraySplitting(arr, 0, arr.size() - 1, maxPointsDp);
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int t = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, t).forEach(tItr -> {
            try {
                int arrCount = Integer.parseInt(bufferedReader.readLine().trim());

                List<Integer> arr = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                    .map(Integer::parseInt)
                    .collect(toList());

                int result = Result.arraySplitting(arr);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
