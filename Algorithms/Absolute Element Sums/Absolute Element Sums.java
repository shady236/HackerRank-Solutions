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
    
    private static int searchAbove(List<Integer> arr, long target)
    {
        if(arr.get(arr.size() - 1) < target)
            return -1;
        
        int left  = 0;
        int right = arr.size() - 1;
        int mid = 0;
        int res = arr.size();
        
        while(left <= right)
        {
            mid = (left + right) >> 1;
            
            if(arr.get(mid) == target)
                return mid;
            else if(arr.get(mid) > target)
            {
                res = mid;
                right = mid - 1;
            }
            else 
                left = mid + 1;
        }
        
        return res;
    }
    
    
    private static int searchBelow(List<Integer> arr, long target)
    {
        if(arr.get(0) > target)
            return -1;
        
        int left  = 0;
        int right = arr.size() - 1;
        int mid = 0;
        int res = -1;
        
        while(left <= right)
        {
            mid = (left + right) >> 1;
            
            if(arr.get(mid) == target)
                return mid;
            else if(arr.get(mid) < target)
            {
                res = Math.max(res, mid);
                left = mid + 1;
            }
            else 
                right = mid - 1;
        }
        
        return res;
    }
    
    
    private static long absoluteSum(List<Integer> arr, List<Integer> prefixSum, long x)
    {
        if(x == 0)
            return prefixSum.get(prefixSum.size() - 1);
        
        int seg1EndIdx, seg2EndIdx;
        if(x > 0)
        {
            seg1EndIdx = searchBelow(arr, -x);
            seg2EndIdx = searchBelow(arr,  0);
            
            long seg1Sum = 0;
            if(seg1EndIdx != -1) 
                seg1Sum = (
                    prefixSum.get(seg1EndIdx) - 
                    x * (seg1EndIdx + 1)
                );
            
            long seg2Sum = 0;
            if(seg2EndIdx != -1 && seg2EndIdx > seg1EndIdx)
            {
                if(seg1EndIdx != -1) 
                    seg2Sum = (
                        (seg2EndIdx - seg1EndIdx) * x - 
                        prefixSum.get(seg2EndIdx) + 
                        prefixSum.get(seg1EndIdx)
                    );
                else 
                    seg2Sum = (
                        (seg2EndIdx + 1) * x - 
                        prefixSum.get(seg2EndIdx) 
                    );
            }
            
            long seg3Sum = 0;
            if(seg2EndIdx != arr.size() - 1)
            {
                if(seg2EndIdx != -1) 
                    seg3Sum = (
                        (arr.size() - 1 - seg2EndIdx) * x +
                        prefixSum.get(arr.size() - 1) -
                        prefixSum.get(seg2EndIdx)
                    );
                else 
                    seg3Sum = (
                        arr.size() * x + 
                        prefixSum.get(arr.get(arr.size() - 1)) 
                    );
            }
            
            return seg1Sum + seg2Sum + seg3Sum;
        }
        else 
        {
            seg1EndIdx = searchBelow(arr,  0);
            seg2EndIdx = searchBelow(arr, -x);
            
            long seg1Sum = 0;
            if(seg1EndIdx != -1) 
                seg1Sum = (
                    prefixSum.get(seg1EndIdx) - 
                    x * (seg1EndIdx + 1)
                );
            
            long seg2Sum = 0;
            if(seg2EndIdx != -1 && seg2EndIdx > seg1EndIdx)
            {
                if(seg1EndIdx != -1) 
                    seg2Sum = (
                        (seg2EndIdx - seg1EndIdx) * -x -
                        prefixSum.get(seg2EndIdx) + 
                        prefixSum.get(seg1EndIdx)
                    );
                else 
                    seg2Sum = (
                        (seg2EndIdx + 1) * -x -
                        prefixSum.get(seg2EndIdx) 
                    );
            }
            
            long seg3Sum = 0;
            if(seg2EndIdx != arr.size() - 1)
            {
                if(seg2EndIdx != -1) 
                    seg3Sum = (
                        prefixSum.get(arr.size() - 1) - 
                        prefixSum.get(seg2EndIdx) +
                        (arr.size() - 1 - seg2EndIdx) * x
                    );
                else 
                    seg3Sum = (
                        arr.size() * x +
                        prefixSum.get(arr.get(arr.size() - 1)) 
                    );
            }
            
            return seg1Sum + seg2Sum + seg3Sum;
        }
    }
    
    /*
     * Complete the 'playingWithNumbers' function below.
     *
     * The function is expected to return an INTEGER_ARRAY.
     * The function accepts following parameters:
     *  1. INTEGER_ARRAY arr
     *  2. INTEGER_ARRAY queries
     */

    public static List<Long> playingWithNumbers(List<Integer> arr, List<Integer> queries) {
        // Write your code here
        Collections.sort(arr);
        
        List<Integer> prefixSum = new ArrayList<>();
        prefixSum.add(Math.abs(arr.get(0)));
        
        for (int i = 1; i < arr.size(); i++) {
            prefixSum.add(
                Math.abs(arr.get(i)) + prefixSum.get(i - 1)
            );
        }
        
        long x = 0;
        List<Long> res = new ArrayList<>();
        for (int q : queries) {
            x += q;
            res.add(absoluteSum(arr, prefixSum, x));
        }
        
        return res;
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

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> queries = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
            .map(Integer::parseInt)
            .collect(toList());

        List<Long> result = Result.playingWithNumbers(arr, queries);

        bufferedWriter.write(
            result.stream()
                .map(Object::toString)
                .collect(joining("\n"))
            + "\n"
        );

        bufferedReader.close();
        bufferedWriter.close();
    }
}
