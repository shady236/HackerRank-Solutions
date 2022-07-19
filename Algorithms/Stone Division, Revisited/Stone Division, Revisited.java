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
    
    public static long solve(long n, List<Long> s, HashMap<Long, Long> dp)
    {
        if(dp.containsKey(n))
            return dp.get(n);
        
        long max = 0;
        for(int i=0; i<s.size(); i++)
        {
            if(n % s.get(i) == 0 && n != s.get(i))
            {
                long cnt = 1 + n / s.get(i) * solve(s.get(i), s, dp);
                if(cnt > max)
                    max = cnt;
            }
        }
        
        dp.put(n, max);
        return max;
    }
    
    /*
     * Complete the 'stoneDivision' function below.
     *
     * The function is expected to return a LONG_INTEGER.
     * The function accepts following parameters:
     *  1. LONG_INTEGER n
     *  2. LONG_INTEGER_ARRAY s
     */

    public static long stoneDivision(long n, List<Long> s)
    {
        HashMap<Long, Long> dp = new HashMap<>();
        
        return solve(n, s, dp);
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

                long n = Long.parseLong(firstMultipleInput[0]);

                int m = Integer.parseInt(firstMultipleInput[1]);

                List<Long> s = Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                    .map(Long::parseLong)
                    .collect(toList());
                
                long result = Result.stoneDivision(n, s);

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
