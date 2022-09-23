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
    
    private static int[][] getMinPairsDistance(int n, List<List<Integer>> graph)
    {
        int[][][] minPrefixDistane = new int[n + 1][n][n];
        
        
        // base case, no brefix set of vertices
        for(int u = 0; u < n; u++)
        {
            for(int v = 0; v < n; v++)
            {
                if(u == v)
                {
                    minPrefixDistane[0][u][v] = 0;
                }
                else if(graph.get(u).contains(v))
                {
                    minPrefixDistane[0][u][v] = 1;
                    minPrefixDistane[0][v][u] = 1;
                }
                else 
                {
                    minPrefixDistane[0][u][v] = n;
                }
            }
        }
        
        
        // recursive case 
        for(int i = 1; i <= n; i++)
        {
            for(int u = 0; u < n; u++)
            {
                for(int v = 0; v < n; v++)
                {
                    int pathIncludeI = (
                        minPrefixDistane[i - 1][u][i - 1] + 
                        minPrefixDistane[i - 1][i - 1][v]
                    );
                    
                    minPrefixDistane[i][u][v] = Math.min(
                        minPrefixDistane[i - 1][u][v],
                        pathIncludeI
                    );
                    
                    minPrefixDistane[i][v][u] = minPrefixDistane[i][u][v];
                }
            }
        }
        
        
        return minPrefixDistane[n];
    }
    
    /*
     * Complete the 'farVertices' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. INTEGER k
     *  3. 2D_INTEGER_ARRAY edges
     */

    public static int farVertices(int n, int k, List<List<Integer>> edges) {
        // Write your code here
        
        List<List<Integer>> graph = new ArrayList<>();
        for(int i = 0; i < n; i++)
            graph.add(new ArrayList<>());
        
        for(List<Integer> edge : edges)
        {
            int u = edge.get(0) - 1;
            int v = edge.get(1) - 1;
            
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        
        int[][] minPairsDistance = getMinPairsDistance(n, graph);
        
        
        int marked = 0;
        boolean[] isMarked = new boolean[n];
        boolean isThereMore = true;
        
        while(isThereMore)
        {
            int[] farVerticesCnt = new int[n];
            int maxVertexHasFar = -1;
            
            for(int u = 0; u < n; u++)
            {
                for(int v = 0; v < n; v++)
                {
                    if(minPairsDistance[u][v] > k && !isMarked[v] && !isMarked[u])
                    {
                        farVerticesCnt[u]++;
                        
                        if(maxVertexHasFar == -1 || farVerticesCnt[u] > farVerticesCnt[maxVertexHasFar])
                            maxVertexHasFar = u;
                    }
                }
            }
            
            
            if(maxVertexHasFar == -1)
            {
                isThereMore = false;
            }
            else 
            {
                isThereMore = true;
                isMarked[maxVertexHasFar] = true;
                marked++;
            }
        }
        
        return marked;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(firstMultipleInput[0]);

        int k = Integer.parseInt(firstMultipleInput[1]);

        List<List<Integer>> edges = new ArrayList<>();

        IntStream.range(0, n - 1).forEach(i -> {
            try {
                edges.add(
                    Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                        .map(Integer::parseInt)
                        .collect(toList())
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        int result = Result.farVertices(n, k, edges);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
