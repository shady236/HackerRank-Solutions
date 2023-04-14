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
     * Complete the 'boardCutting' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER_ARRAY cost_y
     *  2. INTEGER_ARRAY cost_x
     */
    
    public static final long mod = 1000000007;
    
    public static int boardCutting(List<Integer> cost_y, List<Integer> cost_x)
    {
        Collections.sort(cost_y, Comparator.reverseOrder());
        Collections.sort(cost_x, Comparator.reverseOrder());
        
        long cost = 0;
        int yIdx=0 , xIdx=0;
        
        while(yIdx < cost_y.size() && xIdx < cost_x.size())
        {
            if(cost_x.get(xIdx) < cost_y.get(yIdx))
            {
                cost += cost_y.get(yIdx) * (xIdx + 1l);
                yIdx++;
            }
            else 
            {
                cost += cost_x.get(xIdx) * (yIdx + 1l);
                xIdx++;
            }
            cost %= mod;
        }
        
        if(yIdx < cost_y.size())
        {
            long sum = 0;
            while(yIdx < cost_y.size())
            {
                sum += cost_y.get(yIdx);
                yIdx++;
            }            
            cost += (sum * (xIdx + 1)) % mod;
        }
        else 
        {
            long sum = 0;
            while(xIdx < cost_x.size())
            {
                sum += cost_x.get(xIdx);
                xIdx++;
            }
            cost += (sum * (yIdx + 1)) % mod;
        }
        
        cost %= mod;
        
        return (int)cost;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int m = Integer.parseInt(firstMultipleInput[0]);

                int n = Integer.parseInt(firstMultipleInput[1]);

                List<Integer> cost_y = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                    .map(Integer::parseInt)
                    .collect(toList());

                List<Integer> cost_x = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                    .map(Integer::parseInt)
                    .collect(toList());

                int result = Result.boardCutting(cost_y, cost_x);

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
