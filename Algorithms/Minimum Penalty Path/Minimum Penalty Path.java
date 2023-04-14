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


class Edge {
    public int dst;
    public int cost;
    
    public Edge(int dest, int cst) {
        dst  = dest;
        cost = cst;
    }
}


class Result {
    
    private static final int INFTY = (1 << 15) - 1;

    /*
     * Complete the 'beautifulPath' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. 2D_INTEGER_ARRAY edges
     *  2. INTEGER A
     *  3. INTEGER B
     */

    public static int beautifulPath(int n,List<List<Integer>> edges, int A, int B) {
        // Write your code here
        
        List<List<Edge>> graph = new ArrayList<>();
        
        for (int u = 0; u < n; u++) {
            graph.add(new ArrayList<>());
        }
        
        for (List<Integer> edge : edges) {
            int u = edge.get(0) - 1;
            int v = edge.get(1) - 1;
            int c = edge.get(2);
            
            if (u == v) {
                continue;
            }
            
            graph.get(u).add(new Edge(v, c));
            graph.get(v).add(new Edge(u, c));
        }
        
        A--;
        B--;
        
        int[][] minCost = new int[n][1024];
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 1024; c++) {
                minCost[i][c] = INFTY;
            }
        }
        
        for (int c = 1023; c >= 0; c--) {
            Queue<Integer> queue = new LinkedList<>();
            minCost[B][c] = c;
            queue.add(B);
            
            while (!queue.isEmpty()) {
                int node = queue.poll();
                List<Edge> nodeEdges = graph.get(node);
                
                for (Edge edge : nodeEdges) {
                    int dst = edge.dst;
                    int cst = edge.cost | c;
                    int newCost = cst | minCost[node][cst];
                    if (minCost[dst][c] > newCost) {
                        minCost[dst][c] = newCost;
                        queue.add(dst);
                    }
                }
            }
        }
        
        if (minCost[A][0] == INFTY) {
            return -1;
        }
        return minCost[A][0];
    }
}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(firstMultipleInput[0]);

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

        String[] secondMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int A = Integer.parseInt(secondMultipleInput[0]);

        int B = Integer.parseInt(secondMultipleInput[1]);

        int result = Result.beautifulPath(n, edges, A, B);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
