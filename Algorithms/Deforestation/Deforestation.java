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
    
    private static int hackenbush(List<List<Integer>> graph, int root, int prnt) 
    {
        int res = 0;
        
        for (int child : graph.get(root))
        {
            if (child != prnt)
                res ^= hackenbush(graph, child, root) + 1;
        }
        
        return res;
    }
    
    /*
     * Complete the 'deforestation' function below.
     *
     * The function is expected to return a STRING.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. 2D_INTEGER_ARRAY tree
     */

    public static String deforestation(int n, List<List<Integer>> tree) {
        // Write your code here
        
        List<List<Integer>> graph = new ArrayList<>();
        for(int i = 0; i < n; i++)
            graph.add(new ArrayList<>());
        
        for(List<Integer> edge : tree)
        {
            int u = edge.get(0) - 1;
            int v = edge.get(1) - 1;
            
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        
        if (hackenbush(graph, 0, -1) == 0)
            return "Bob";
        return "Alice";
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int t = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, t).forEach(tItr -> {
            try {
                int n = Integer.parseInt(bufferedReader.readLine().trim());

                List<List<Integer>> tree = new ArrayList<>();

                IntStream.range(0, n - 1).forEach(i -> {
                    try {
                        tree.add(
                            Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                                .map(Integer::parseInt)
                                .collect(toList())
                        );
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                });

                String result = Result.deforestation(n, tree);

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
