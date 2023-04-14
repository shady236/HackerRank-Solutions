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
     * Complete the 'countPaths' function below.
     *
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. 2D_INTEGER_ARRAY edges
     */

    public static void countPaths(int n, List<List<Integer>> edges) {
        // Write your code here
        List<List<Integer>> graph  = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (List<Integer> e : edges) {
            int src = e.get(0) - 1;
            int dst = e.get(1) - 1;
            graph.get(src).add(dst);
        }
        
        boolean[] isVisited = new boolean[n];
        HashSet<Integer> path = new HashSet<>();
        boolean isThereCycle = dfs(graph, 0, isVisited, path);
        
        if (!isVisited[n - 1]) {
            System.out.println(0);
            return;
        }
        else if (isThereCycle) {
            System.out.println("INFINITE PATHS");
            return;
        }
        
        long[] paths = new long[n];
        Arrays.fill(isVisited, false);
        dfs(graph, 0, isVisited, paths);
        
        System.out.println(paths[0]);
    }
    
    static boolean dfs(List<List<Integer>> graph, int src, boolean[] isVisited, HashSet<Integer> path) {
        isVisited[src] = true;
        path.add(src);
        boolean isThereCysle = false;
        
        for (int adj : graph.get(src)) {
            if (isVisited[adj]) {
                isThereCysle = path.contains(adj);
            }
            else {
                isThereCysle |= dfs(graph, adj, isVisited, path);
            }
        }
        
        path.remove(src);
        return isThereCysle;
    }
    
    static void dfs(List<List<Integer>> graph, int src, boolean[] isVisited, long[] paths) {
        isVisited[src] = true;
        if (src == graph.size() - 1) {
            paths[src] = 1;
            return;
        }
        
        for (int adj : graph.get(src)) {
            if (!isVisited[adj]) {
                dfs(graph, adj, isVisited, paths);
            }
            
            paths[src] += paths[adj];
            paths[src] %= 1000000000;
        }
    }
    
}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int nodes = Integer.parseInt(firstMultipleInput[0]);

        int m = Integer.parseInt(firstMultipleInput[1]);

        List<List<Integer>> edges = new ArrayList<>();

        IntStream.range(0, m).forEach(i -> {
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

        Result.countPaths(nodes, edges);

        bufferedReader.close();
    }
}
