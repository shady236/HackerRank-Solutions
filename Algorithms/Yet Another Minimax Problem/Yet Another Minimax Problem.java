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
    
    private static int getMsb(int a)
    {
        for (int i = 31; i >= 0; i--) 
        {
            if(((a>>i) & 1) == 1)
                return i;
        }
        
        return -1;
    }
    
    /*
     * Complete the 'anotherMinimaxProblem' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER_ARRAY a as parameter.
     */

    public static int anotherMinimaxProblem(List<Integer> a) {
        // Write your code here
        
        // sort a in non-increasing order
        Collections.sort(a, Collections.reverseOrder());
        
        // repeat while there are nonzero elements
        while(a.get(0) > 0)
        {
            // get position of msb for biggest element
            int highestMsb = getMsb(a.get(0));
            
            /* 
            * get index of first element with msb position 
            * lower msb of biggest number
            */
            int seprationIdx = -1;
            for (int i = 1; i < a.size(); i++) 
            {
                if(getMsb(a.get(i)) < highestMsb)
                {
                    seprationIdx = i;
                    break;
                }
            }
            
            // if all elemnts has the same msb, clear this bit
            if(seprationIdx == -1)
            {
                for (int i = 0; i < a.size(); i++) 
                {
                    int val = a.get(i);
                    val &= ~(1<<highestMsb);
                    a.set(i, val);
                }
            }
            else 
            {
                /* 
                 * get min combination between elements 
                 * having the same msb as biggest element
                 * with elements smaller than this msb
                 */
                int minScore = Integer.MAX_VALUE;
                
                for (int i = 0; i < seprationIdx; i++) 
                {
                    for (int j = seprationIdx; j < a.size(); j++) 
                    {
                        int score = a.get(i) ^ a.get(j);
                        if(score < minScore)
                            minScore = score;
                    }
                }
                
                return minScore;
            }
        }
        
        return 0;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> a = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
            .map(Integer::parseInt)
            .collect(toList());

        int result = Result.anotherMinimaxProblem(a);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
