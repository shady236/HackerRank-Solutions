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


class Node {
    public List<Integer> childs;
    public int subtreeCnfgCntLikePrnt;
    public int subtreeCnfgCntUnlikePrnt;
    
    public Node() {
        childs = new ArrayList<>();
    }
    
    public void addChild(int ch) {
        childs.add(ch);
    }
    
    public int childsCnt() {
        return childs.size();
    }
    
    public boolean hasAChild(int ch) {
        return childs.contains(ch);
    }
}


class Result {
    
    public static final int MOD = 1000000007;
    
    private static void addChilds(List<List<Integer>> graph, Node[] tree, int node) {
        for (int child : graph.get(node)) {
            if (!tree[child].hasAChild(node)) {
                tree[node].addChild(child);
                addChilds(graph, tree, child);
            }
        }
    }
    
    
    private static Node[] buildTree(int n, List<List<Integer>> edges) {
        
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (List<Integer> edge : edges) {
            int u = edge.get(0) - 1;
            int v = edge.get(1) - 1;
            
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        
        
        Node[] tree = new Node[n];
        for (int i = 0; i < tree.length; i++) {
            tree[i] = new Node();
        }
        
        addChilds(graph, tree, 0);
        
        return tree;
    }
    
    
    private static void initCnfgCnt(Node[] tree, int root) {
        if (tree[root].childsCnt() == 0) {
            tree[root].subtreeCnfgCntLikePrnt = 1;
            tree[root].subtreeCnfgCntUnlikePrnt = 0;
            
            return;
        }
        
        for (int child : tree[root].childs) {
            initCnfgCnt(tree, child);
        }
        
        long likeCnt = 1;
        for (int child : tree[root].childs) {
            likeCnt = (
                likeCnt * 
                ((
                    (long) tree[child].subtreeCnfgCntLikePrnt +
                    (long) tree[child].subtreeCnfgCntUnlikePrnt
                ) % MOD)
            ) % MOD;
        }
        tree[root].subtreeCnfgCntLikePrnt = (int) likeCnt;
        
        
        long unlikeCnt = 0;
        
        for (int i = 0; i < tree[root].childsCnt(); i++) {
            long cnt = 1;
            int  ch;
            
            for (int j = 0; j < i; j++) {
                ch = tree[root].childs.get(j);
                cnt = (cnt * tree[ch].subtreeCnfgCntUnlikePrnt) % MOD;
            }
            
            ch = tree[root].childs.get(i);
            cnt = (cnt * tree[ch].subtreeCnfgCntLikePrnt) % MOD;
            
            for (int j = i + 1; j < tree[root].childsCnt(); j++) {
                ch = tree[root].childs.get(j);
                cnt = (cnt * ((
                    (long) tree[ch].subtreeCnfgCntLikePrnt +
                    (long) tree[ch].subtreeCnfgCntUnlikePrnt
                    ) % MOD) 
                ) % MOD;
            }
            
            unlikeCnt = (unlikeCnt + cnt) % MOD;
        }
        
        tree[root].subtreeCnfgCntUnlikePrnt = (int) unlikeCnt;
    }

    /*
     * Complete the 'kingdomDivision' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. 2D_INTEGER_ARRAY roads
     */

    public static int kingdomDivision(int n, List<List<Integer>> roads) {
        // Write your code here
        Node[] tree = buildTree(n, roads);
        initCnfgCnt(tree, 0);
        return (int) (
            (
                ((long) tree[0].subtreeCnfgCntUnlikePrnt) << 1
            ) % MOD
        );
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        List<List<Integer>> roads = new ArrayList<>();

        IntStream.range(0, n - 1).forEach(i -> {
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

        int result = Result.kingdomDivision(n, roads);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
