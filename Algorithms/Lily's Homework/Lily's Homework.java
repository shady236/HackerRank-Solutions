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
     * Complete the 'lilysHomework' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER_ARRAY arr as parameter.
     */

    public static int lilysHomework(List<Integer> arr)
    {
        List<Integer> arrCpy = new ArrayList<>();
        for(int i = 0; i < arr.size(); i++)
            arrCpy.add(arr.get(i));
        
        HashMap<Integer, Integer> map    = new HashMap<>();
        HashMap<Integer, Integer> mapCpy = new HashMap<>();
        for(int i = 0; i < arr.size(); i++)
        {
            map.put(arr.get(i), i);
            mapCpy.put(arr.get(i), i);
        }
        
        List<Integer> arrSorted = new ArrayList<>();
        for(int i = 0; i < arr.size(); i++)
            arrSorted.add(arr.get(i));
        
        Collections.sort(arrSorted);
        
        List<Integer> arrCpySorted = new ArrayList<>();
        for(int i = arr.size() - 1; i >= 0; i--)
            arrCpySorted.add(arrSorted.get(i));
        
        
        int swaps1 = 0; 
        int swaps2 = 0;
        
        for(int i = 0; i < arr.size(); i++)
        {
            if(arr.get(i) == arrSorted.get(i))
                continue;

            swaps1++;
            
            int orignalIdx = map.get(arrSorted.get(i));
            
            arr.set(orignalIdx, arr.get(i));
            arr.set(i, arrSorted.get(i));
            
            map.replace(arr.get(i), i);
            map.replace(arr.get(orignalIdx), orignalIdx);
        }
        
        for(int i = 0; i < arr.size(); i++)
        {
            if(arrCpy.get(i) == arrCpySorted.get(i))
                continue;

            swaps2++;
            
            int orignalIdx = mapCpy.get(arrCpySorted.get(i));
            
            arrCpy.set(orignalIdx, arrCpy.get(i));
            arrCpy.set(i, arrCpySorted.get(i));
            
            mapCpy.replace(arrCpy.get(i), i);
            mapCpy.replace(arrCpy.get(orignalIdx), orignalIdx);
        }
        
        return Math.min(swaps1, swaps2);
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

        int result = Result.lilysHomework(arr);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
