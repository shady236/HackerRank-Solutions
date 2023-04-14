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
    
    public Edge(int dest, int w) {
        this.dest = dest;
        this.weight = w;
    }
}


class NodeDistance implements Comparable<NodeDistance> {
    int node;
    int distance;
    
    NodeDistance(int node, int distance) {
        this.node = node;
        this.distance = distance;
    }
    
    @Override
    public int compareTo(NodeDistance o) {
        return distance - o.distance;
    }
    
    @Override
    public boolean equals(Object obj) {
        NodeDistance o = (NodeDistance) obj;
        return node == o.node;
    }
}


class Result {

    /*
     * Complete the 'getCost' function below.
     *
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

    public static void getCost(int gNodes, List<Integer> gFrom, List<Integer> gTo, List<Integer> gWeight) {
        // Print your answer within the function and return nothing
        
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < gNodes; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int i = 0; i < gTo.size(); i++) {
            int u = gFrom.get(i) - 1;
            int v = gTo.get(i)   - 1;
            int w = gWeight.get(i);
            
            // check if u & v are connected
            boolean isConn = false;
            for (Edge e : graph.get(u)) {
                if (e.dest == v) {
                    e.weight = Math.min(e.weight, w);
                    isConn = true;
                    break;
                }
            }
            
            if (isConn)
            for (Edge e : graph.get(v)) {
                if (e.dest == u) {
                    e.weight = Math.min(e.weight, w);
                    break;
                }
            }
            
            if (!isConn) {
                graph.get(u).add(new Edge(v, w));
                graph.get(v).add(new Edge(u, w));
            }
        }
        
        int[] minDistance = new int[gNodes];
        for (int i = 0; i < gNodes; i++) {
            minDistance[i] = Integer.MAX_VALUE;
        }
        
        PriorityQueue<NodeDistance> nodesDistances = new PriorityQueue<>();
        minDistance[0] = 0;
        nodesDistances.add(new NodeDistance(0, 0));
        
        while (!nodesDistances.isEmpty()) {
            NodeDistance nearest = nodesDistances.poll();
            
            if (nearest.distance > minDistance[nearest.node]) {
                continue;
            }
            
            for (Edge e : graph.get(nearest.node)) {
                int node = e.dest;
                int orgDist = minDistance[node];
                int newDist = Math.max(e.weight, nearest.distance);
                
                if (newDist < orgDist) {
                    minDistance[node] = newDist;
                    nodesDistances.add(new NodeDistance(node, newDist));
                }
            }
        }
        
        
        if (minDistance[gNodes - 1] == Integer.MAX_VALUE)
            System.out.println("NO PATH EXISTS");
        else 
            System.out.println(minDistance[gNodes - 1]);
    }
}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

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

        Result.getCost(gNodes, gFrom, gTo, gWeight);

        bufferedReader.close();
    }
}
