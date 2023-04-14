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
     * Complete the 'crabGraphs' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. INTEGER t
     *  3. 2D_INTEGER_ARRAY graph
     */

    public static int crabGraphs(int n, int t, List<List<Integer>> edges) {
        // Write your code here
        
        int[] degree = new int[n];
        for (List<Integer> e : edges) {
            int u = e.get(0) - 1;
            int v = e.get(1) - 1;
            degree[u]++;
            degree[v]++;
        }
        
        int newN = n * 2 + 2;
        int[][] maxFlowGraph = new int[newN][newN];
        for (List<Integer> e : edges) {
            int u = e.get(0) - 1;
            int v = e.get(1) - 1;
            
            int uAsHead = 2 * u;
            int uAsTail = 2 * u + 1;
            int vAsHead = 2 * v;
            int vAsTail = 2 * v + 1;
            
            maxFlowGraph[uAsHead][vAsTail] = 1;
            maxFlowGraph[vAsHead][uAsTail] = 1;
        }
        
        int src = n * 2;
        int dst = n * 2 + 1;
        
        for (int u = 0; u < n; u++) {
            int uAsHead = u * 2;
            maxFlowGraph[src][uAsHead] = Math.min(t, degree[u]);
            
            int uAsTail = u * 2 + 1;
            maxFlowGraph[uAsTail][dst] = 1;
        }
        
        int maxFlow = 0;
        
        while (true) {
            List<Integer> path = getPath(maxFlowGraph, src, dst);
            if (path.isEmpty()) {
                break;
            }
            
            int flow = Integer.MAX_VALUE;
            for (int i = 1; i < path.size(); i++) {
                int u = path.get(i - 1);
                int v = path.get(i);
                flow = Math.min(flow, maxFlowGraph[u][v]);
            }
            
            maxFlow += flow;
            for (int i = 1; i < path.size(); i++) {
                int u = path.get(i - 1);
                int v = path.get(i);
                maxFlowGraph[u][v] -= flow;
                maxFlowGraph[v][u] += flow;
            }
        }
        
        return maxFlow;
    }
    
    static List<Integer> getPath(int[][] graph, int src, int dst) {
        boolean[] isVisited = new boolean[graph.length];
        return getPath(graph, src, dst, isVisited);
    }
    
    static List<Integer> getPath(int[][] graph, int src, int dst, boolean[] isVisited) {
        List<Integer> path = new ArrayList<>();
        if (src == dst) {
            path.add(src);
            return path;
        }
        
        isVisited[src] = true;
        for (int next = 0; next < graph.length; next++) {
            if (graph[src][next] > 0 && !isVisited[next]) {
                List<Integer> remPath = getPath(graph, next, dst, isVisited);
                if (!remPath.isEmpty()) {
                    path.add(src);
                    path.addAll(remPath);
                    return path;
                }
            }
        }
        
        return path;
    }    
}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int c = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, c).forEach(cItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int n = Integer.parseInt(firstMultipleInput[0]);

                int t = Integer.parseInt(firstMultipleInput[1]);

                int m = Integer.parseInt(firstMultipleInput[2]);

                List<List<Integer>> graph = new ArrayList<>();

                IntStream.range(0, m).forEach(i -> {
                    try {
                        graph.add(
                            Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                                .map(Integer::parseInt)
                                .collect(toList())
                        );
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                });

                int result = Result.crabGraphs(n, t, graph);

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
