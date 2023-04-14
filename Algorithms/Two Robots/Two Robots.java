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
    
    public static int minDistance(List<List<Integer>> queries, int queriesIdx, int r1Pos, int r2Pos, HashMap<Integer, Integer> dp)
    {
        if(queriesIdx == queries.size())
            return 0;
        
        int key1 = (r1Pos * 10000) + (r2Pos * 10000) + queriesIdx;
        int key2 = (r2Pos * 10000) + (r1Pos * 10000) + queriesIdx;
        
        if(dp.containsKey(key1))
            return dp.get(key1);
        
        if(dp.containsKey(key2))
            return dp.get(key2);
        
        int src = queries.get(queriesIdx).get(0);
        int dis = queries.get(queriesIdx).get(1);
        
        int dstnce = Math.abs(src - dis);
        
        int res;
        
        if(r1Pos == -1)
            res = dstnce + minDistance(
                queries, queriesIdx + 1, dis, r2Pos, dp
            );
        
        else if(r2Pos == -1)
            res = dstnce + Math.min(
                Math.abs(src - r1Pos) + 
                minDistance(
                    queries, queriesIdx + 1, dis, r2Pos, dp
                ),
                minDistance(
                    queries, queriesIdx + 1, r1Pos, dis, dp
                )
            );
        
        else 
            res = dstnce + Math.min(
                Math.abs(src - r1Pos) + 
                minDistance(
                    queries, queriesIdx + 1, dis, r2Pos, dp
                ),
                Math.abs(src - r2Pos) + 
                minDistance(
                    queries, queriesIdx + 1, r1Pos, dis, dp
                )
            );
        
        
        dp.put(key1, res);
        return res;
    }
    
    
    /*
     * Complete the 'twoRobots' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER m
     *  2. 2D_INTEGER_ARRAY queries
     */

    public static int twoRobots(int m, List<List<Integer>> queries) {
    // Write your code here
        HashMap<Integer, Integer> dp = new HashMap<>();
        
        return minDistance(queries, 0, -1, -1, dp);
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int t = Integer.parseInt(bufferedReader.readLine().trim());
        
        for (int tItr = 0; tItr < t; tItr++) {
        
            String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

            int m = Integer.parseInt(firstMultipleInput[0]);

            int n = Integer.parseInt(firstMultipleInput[1]);

            List<List<Integer>> queries = new ArrayList<>();

            IntStream.range(0, n).forEach(i -> {
                try {
                    queries.add(
                        Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                            .map(Integer::parseInt)
                            .collect(toList())
                    );
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            });

            int result = Result.twoRobots(m, queries);

            bufferedWriter.write(String.valueOf(result));
            bufferedWriter.newLine();
        }

        bufferedReader.close();
        bufferedWriter.close();
    }
}
