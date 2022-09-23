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
     * Complete the 'kruskals' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
     */

    /*
     * For the weighted graph, <name>:
     *
     * 1. The number of nodes is <name>Nodes.
     * 2. The number of edges is <name>Edges.
     * 3. An edge exists between <name>From[i] and <name>To[i]. The weight of the edge is <name>Weight[i].
     *
     */

    public static int kruskals(int gNodes, List<Integer> gFrom, List<Integer> gTo, List<Integer> gWeight) 
    {
        List<List<Edge>> nodeEdges = new ArrayList<>();
        for(int i = 0; i < gNodes; i++)
            nodeEdges.add(new ArrayList<>());
        
        for (int i = 0; i < gFrom.size(); i++) 
        {
            int u = gFrom.get(i) - 1;
            int v = gTo.get(i) - 1;
            int w = gWeight.get(i);
            
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
        
        
        int strt = 0;
        for (int i = 1; i < nodeEdges.size(); i++) {
            if(nodeEdges.get(i).get(0).weight < nodeEdges.get(strt).get(0).weight)
                strt = i;
        }
        
        int sum = 0;
        List<Integer> coveredNodes = new ArrayList<>();
        coveredNodes.add(strt);
        
        while (coveredNodes.size() < gNodes) 
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

        String[] gNodesEdges = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int gNodes = Integer.parseInt(gNodesEdges[0]);
        int gEdges = Integer.parseInt(gNodesEdges[1]);

        List<Integer> gFrom = new ArrayList<>();
        List<Integer> gTo = new ArrayList<>();
        List<Integer> gWeight = new ArrayList<>();

        IntStream.range(0, gEdges).forEach(i -> {
            try {
                String[] gFromToWeight = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                gFrom.add(Integer.parseInt(gFromToWeight[0]));
                gTo.add(Integer.parseInt(gFromToWeight[1]));
                gWeight.add(Integer.parseInt(gFromToWeight[2]));
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        int res = Result.kruskals(gNodes, gFrom, gTo, gWeight);

        // Write your code here.
        bufferedWriter.write(String.valueOf(res));

        bufferedReader.close();
        bufferedWriter.close();
    }
}
