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
    public int dest;
    public int weight;
    
    public Edge(int dest, int weight)
    {
        this.dest = dest;
        this.weight = weight;
    }
}

class Result {
    
    private static boolean find(List<Integer> lst, int trgt)
    {
        for (int e : lst) {
            if(trgt == e)
                return true;
        }
        return false;
    }
    
    
    /*
     * Complete the 'prims' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. 2D_INTEGER_ARRAY edges
     *  3. INTEGER start
     */

    public static int prims(int n, List<List<Integer>> edges, int start) {
        // Write your code here
        
        List<List<Edge>> nodeEdges = new ArrayList<>();
        for(int i = 0; i < n; i++)
            nodeEdges.add(new ArrayList<>());
        
        for(List<Integer> e : edges)
        {
            int u = e.get(0) - 1;
            int v = e.get(1) - 1;
            int w = e.get(2);
            
            nodeEdges.get(u).add(new Edge(v, w));
            nodeEdges.get(v).add(new Edge(u, w));
        }
        
        
        for(List<Edge> l : nodeEdges)
        {
            Collections.sort(l, new Comparator<Edge>() {
                @Override
                public int compare(Edge o1, Edge o2) {
                    return o1.weight - o2.weight;
                }
            });
        }
        
        
        int sum = 0;
        List<Integer> coveredNodes = new ArrayList<>();
        coveredNodes.add(start - 1);
        
        while (coveredNodes.size() < n) 
        {
            Edge minEdge = null;
            
            for (int node : coveredNodes) {
                Edge nodeMinEdge = null;
                
                for (Edge e : nodeEdges.get(node)) {
                    if(!find(coveredNodes, e.dest)) {
                        nodeMinEdge = e;
                        break;
                    }
                }
                
                if(nodeMinEdge != null)
                {
                    if(minEdge == null || minEdge.weight > nodeMinEdge.weight)
                        minEdge = nodeMinEdge;
                }
            }
            
            sum += minEdge.weight;
            coveredNodes.add(minEdge.dest);
        }
        
        return sum;
        
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

        int start = Integer.parseInt(bufferedReader.readLine().trim());

        int result = Result.prims(n, edges, start);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
