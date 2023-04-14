import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;

public class Solution {
    
    /*
     * Complete the rustMurdered function below.
     */
    static int[] rustMurderer(int n, int[][] roads, int s) {
        /*
         * Write your code here.
         */
        
        s--;
        
        List<HashSet<Integer>> graph = new ArrayList<>();
        for(int i = 0; i < n; i++) {
            graph.add(new HashSet<>());
        }
        
        for(int i = 0; i < roads.length; i++) {
            int u = roads[i][0] - 1;
            int v = roads[i][1] - 1;
            
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        
        Queue<Integer> nodesQueue = new LinkedList<>();
        HashSet<Integer> notDiscoverd = new HashSet<>();
        int[] minDistance = new int[n];
        
        for(int i = 0; i < n; i++) {
            minDistance[i] = Integer.MAX_VALUE;
            notDiscoverd.add(i);
        }
        
        minDistance[s] = 0;
        nodesQueue.add(s);
        notDiscoverd.remove(s);
        
        while (!nodesQueue.isEmpty() && !notDiscoverd.isEmpty()) {
            int nearest = nodesQueue.poll();
            List<Integer> discovered = new ArrayList<>();
            
            for (int node : notDiscoverd) {
                if (!graph.get(nearest).contains(node)) {
                    minDistance[node] = minDistance[nearest] + 1;
                    discovered.add(node);
                    nodesQueue.add(node);
                }
            }
            
            for (int node : discovered) {
                notDiscoverd.remove(node);
            }
        }
        
        int[] res = new int[n - 1];
        
        for(int i = 0; i < n; i++) {
            if(i == s)
                continue;
            else if(i < s)
                res[i] = minDistance[i];
            else 
                res[i - 1] = minDistance[i];
        }
        
        return res;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int t = Integer.parseInt(scanner.nextLine().trim());

        for (int tItr = 0; tItr < t; tItr++) {
            String[] nm = scanner.nextLine().split(" ");

            int n = Integer.parseInt(nm[0].trim());

            int m = Integer.parseInt(nm[1].trim());

            int[][] roads = new int[m][2];

            for (int roadsRowItr = 0; roadsRowItr < m; roadsRowItr++) {
                String[] roadsRowItems = scanner.nextLine().split(" ");

                for (int roadsColumnItr = 0; roadsColumnItr < 2; roadsColumnItr++) {
                    int roadsItem = Integer.parseInt(roadsRowItems[roadsColumnItr].trim());
                    roads[roadsRowItr][roadsColumnItr] = roadsItem;
                }
            }

            int s = Integer.parseInt(scanner.nextLine().trim());

            int[] result = rustMurderer(n, roads, s);

            for (int resultItr = 0; resultItr < result.length; resultItr++) {
                bufferedWriter.write(String.valueOf(result[resultItr]));

                if (resultItr != result.length - 1) {
                    bufferedWriter.write(" ");
                }
            }

            bufferedWriter.newLine();
        }

        bufferedWriter.close();
    }
}
