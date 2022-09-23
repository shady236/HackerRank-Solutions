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
    public static final int INPUT  = 0;
    public static final int OUTPUT = 1;
    
    public int connectedNode;
    public int direction;
    public int weight;
    
    public Edge(int connectedNode, int direction, int weight)
    {
        this.connectedNode = connectedNode;
        this.direction = direction;
        this.weight = weight;
    }
}


class Result {
    
    private static int[][] minDistane;
    private static final int INFTY = Integer.MAX_VALUE >> 1;
    
    private static int idxOf(List<Edge> arr, int connectedNode, int direction)
    {
        for (int i = 0; i < arr.size(); i++) 
        {
            if(arr.get(i).connectedNode == connectedNode && arr.get(i).direction == direction)
                return i;
        }
        
        return -1;
    }
    
    
    private static List<List<Edge>> constructGraph(int n, List<Integer> roadFrom, List<Integer> roadTo, List<Integer> roadWeight)
    {
        List<List<Edge>> graph = new ArrayList<>();
        for(int i = 0; i < n; i++)
            graph.add(new ArrayList<>());
        
        for(int i = 0; i < roadFrom.size(); i++)
        {
            int u = roadFrom.get(i) - 1;
            int v = roadTo.get(i) - 1;
            int w = roadWeight.get(i);
            
            int idx = idxOf(graph.get(u), v, Edge.OUTPUT);
            
            if(idx == -1)
            {
                graph.get(u).add(new Edge(v, Edge.OUTPUT, w));
                graph.get(v).add(new Edge(u, Edge.INPUT, w));
            }
            else 
            {
                graph.get(u).get(idx).weight = w;
                
                idx = idxOf(graph.get(v), u, Edge.INPUT);
                graph.get(v).get(idx).weight = w;
            }
        }
        
        return graph;
    }
    
    
    public static void init(int n, List<Integer> roadFrom, List<Integer> roadTo, List<Integer> roadWeight)
    {
        List<List<Edge>> graph = constructGraph(n, roadFrom, roadTo, roadWeight);
        
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
                else 
                {
                    int idx = idxOf(graph.get(u), v, Edge.OUTPUT);
                    
                    if(idx == -1)
                        minPrefixDistane[0][u][v] = INFTY;
                    else 
                        minPrefixDistane[0][u][v] = graph.get(u).get(idx).weight;
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
                }
            }
        }
        
        minDistane = minPrefixDistane[n];
    }
    
    
    public static int solve(int u, int v) {
        if(minDistane[u - 1][v - 1] < INFTY)
            return minDistane[u - 1][v - 1];
        return -1;
    }

}


public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        String[] roadNodesEdges = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int roadNodes = Integer.parseInt(roadNodesEdges[0]);
        int roadEdges = Integer.parseInt(roadNodesEdges[1]);

        List<Integer> roadFrom = new ArrayList<>();
        List<Integer> roadTo = new ArrayList<>();
        List<Integer> roadWeight = new ArrayList<>();

        IntStream.range(0, roadEdges).forEach(i -> {
            try {
                String[] roadFromToWeight = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                roadFrom.add(Integer.parseInt(roadFromToWeight[0]));
                roadTo.add(Integer.parseInt(roadFromToWeight[1]));
                roadWeight.add(Integer.parseInt(roadFromToWeight[2]));
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });
        
        Result.init(roadNodes, roadFrom, roadTo, roadWeight);

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int x = Integer.parseInt(firstMultipleInput[0]);

                int y = Integer.parseInt(firstMultipleInput[1]);
                
                int result = Result.solve(x, y);
                
                System.out.println(result);
                
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
    }
}
