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
    static class Edge {
        int dst, time;
        Edge(int d, int t) {
            dst  = d;
            time = t;
        }
    }
    
    static class NodeTimePair implements Comparable<NodeTimePair> {
        int node, time;
        
        NodeTimePair(int n, int t) {
            node = n;
            time = t;
        }
        
        @Override
        public int compareTo(Result.NodeTimePair o) {
            return Integer.compare(this.time, o.time);
        }
    }

    /*
     * Complete the 'shop' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. INTEGER k
     *  3. STRING_ARRAY centers
     *  4. 2D_INTEGER_ARRAY roads
     */

    public static int shop(int n, int k, List<String> centers, List<List<Integer>> roads) {
        // Write your code here
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (List<Integer> road : roads) {
            int u = road.get(0) - 1;
            int v = road.get(1) - 1;
            int t = road.get(2);
            
            graph.get(u).add(new Edge(v, t));
            graph.get(v).add(new Edge(u, t));
        }
        
        // providers[<fish>] is a set of centers that provide <fish>
        List<HashSet<Integer>> providers = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            providers.add(new HashSet<>());
        }
        
        for (int center = 0; center < n; center++) {
            String[] fishes = centers.get(center).split(" ");
            for (int j = 1; j < fishes.length; j++) {
                int fish = Integer.parseInt(fishes[j]) - 1;
                providers.get(fish).add(center);
            }
        }
        
        int[] availbleFishes = new int[n];
        for (int center = 0; center < n; center++) {
            String[] fishes = centers.get(center).split(" ");
            availbleFishes[center] = 0;
            
            for (int j = 1; j < fishes.length; j++) {
                int fish = Integer.parseInt(fishes[j]) - 1;
                availbleFishes[center] |= 1<<fish;
            }
        }
        
        
        int maxKMask = (1<<k) - 1;
        // minTime[src][kMask] is min time to geet from src to node n and get fishes of kMask
        int[][] minTime = new int[n][maxKMask + 1];
        for (int i = 0; i < n; i++) {
            Arrays.fill(minTime[i], Integer.MAX_VALUE);
        }
        
        for (int kMask = 0; kMask <= maxKMask; kMask++) {
            PriorityQueue<NodeTimePair> q = new PriorityQueue<>();
            
            if (kMask == 0) {
                minTime[n - 1][kMask] = 0;
                q.add(new NodeTimePair(n - 1, 0));
            }
            else {
                int newFish = msb(kMask);
                int kMaskWithoutNewFish = kMask ^ (1 << newFish);
                
                for (int provider : providers.get(newFish)) {
                    minTime[provider][kMask] = minTime[provider][kMaskWithoutNewFish];
                    q.add(new NodeTimePair(provider, minTime[provider][kMask]));
                }
            }
            
            while (!q.isEmpty()) {
                NodeTimePair min = q.poll();
                int node = min.node;
                
                for (Edge edge : graph.get(node)) {
                    int adj = edge.dst;
                    int newMask = kMask & (~availbleFishes[adj]);
                    int newTime = edge.time + minTime[node][newMask];
                    if (minTime[adj][kMask] > newTime) {
                        minTime[adj][kMask] = newTime;
                        q.add(new NodeTimePair(adj, newTime));
                    }
                }
            }
        }
        
        int resTime = Integer.MAX_VALUE;
        
        for (int cat1Mask = 0; cat1Mask <= maxKMask; cat1Mask++) {
            int cat2Mask = maxKMask ^ cat1Mask;
            int time = Math.max(minTime[0][cat1Mask], minTime[0][cat2Mask]);
            resTime  = Math.min(resTime, time);
        }
        
        return resTime;
    }
    
    static int msb(int num) {
        for (int i = 31; i >= 0; i--) {
            if (((num >> i) & 1) == 1) {
                return i;
            }
        }
        return -1;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(firstMultipleInput[0]);

        int m = Integer.parseInt(firstMultipleInput[1]);

        int k = Integer.parseInt(firstMultipleInput[2]);

        List<String> centers = IntStream.range(0, n).mapToObj(i -> {
            try {
                return bufferedReader.readLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        })
            .collect(toList());

        List<List<Integer>> roads = new ArrayList<>();

        IntStream.range(0, m).forEach(i -> {
            try {
                roads.add(
                    Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                        .map(Integer::parseInt)
                        .collect(toList())
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        int res = Result.shop(n, k, centers, roads);

        bufferedWriter.write(String.valueOf(res));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
