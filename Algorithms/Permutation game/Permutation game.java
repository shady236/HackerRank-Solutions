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
    
    private static boolean isSorted(List<Integer> arr)
    {
        for(int i = 1; i < arr.size(); i++)
        {
            if(arr.get(i) < arr.get(i - 1))
                return false;
        }
        
        return true;
    }
    
    private static Boolean isWinning(List<Integer> arr, HashMap<List<Integer>, Boolean> isWinningDp)
    {
        boolean[] isNumFound = new boolean[16];
        List<Integer> key = new ArrayList<>();
        
        for(int e : arr)
        {
            key.add(e);
            isNumFound[e] = true;
        }
        
        int missingNum = arr.size();
        for (int i = 1; i < key.size(); i++) 
        {
            if(!isNumFound[i]) 
            {
                missingNum = i;
                break;
            }
        }
        
        for (int i = 0; i < key.size(); i++) 
        {
            if(key.get(i) > missingNum)
                key.set(i, key.get(i) - 1);
        }
        
        
        if(isWinningDp.containsKey(key))
            return isWinningDp.get(key);
        
        if(isSorted(arr))
        {
            isWinningDp.put(key, false);
            return false;
        }
        
        
        boolean res = false;
        for (int i = 0; i < key.size(); i++) 
        {
            int val = arr.get(i);
            arr.remove(i);
            
            boolean isNextWinnerPlayer = isWinning(arr, isWinningDp);
            
            arr.add(i, val);
            
            if(!isNextWinnerPlayer)
            {
                res = true;
                break;
            }
        }
        
        isWinningDp.put(key, res);
        return res;
    }

    /*
     * Complete the 'permutationGame' function below.
     *
     * The function is expected to return a STRING.
     * The function accepts INTEGER_ARRAY arr as parameter.
     */

    public static String permutationGame(List<Integer> arr) 
    {
        // Write your code here
        HashMap<List<Integer>, Boolean> isWinningDp = new HashMap<>();
        
        if(isWinning(arr, isWinningDp))
            return "Alice";
        return "Bob";
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

                String result = Result.permutationGame(arr);

                bufferedWriter.write(result);
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
