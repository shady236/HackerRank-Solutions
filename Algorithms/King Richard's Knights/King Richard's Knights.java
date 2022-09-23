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
     * Complete the 'kingRichardKnights' function below.
     *
     * The function is expected to return a 2D_INTEGER_ARRAY.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. INTEGER s
     *  3. INTEGER_ARRAY knights
     */

    public static List<List<Integer>> kingRichardKnights(int n, int s, List<List<Integer>> commands, List<Long> knights) {
        // Write your code here
        List<List<Integer>> res = new ArrayList<>();
        for(int i = 0; i < knights.size(); i++)
            res.add(new ArrayList<>());
        
        List<Integer> rowMap = new ArrayList<>();
        List<Integer> colMap = new ArrayList<>();
        
        int firstCmdStrtRow = commands.get(0).get(0) - 1;
        int firstCmdStrtCol = commands.get(0).get(1) - 1;
        int firstCmdEndRow  = firstCmdStrtRow + commands.get(0).get(2);
        int firstCmdEndCol  = firstCmdStrtCol + commands.get(0).get(2);
        
        rowMap.add(firstCmdStrtRow - firstCmdStrtCol);
        colMap.add(firstCmdStrtRow + firstCmdEndCol);
        
        for(int i = 1; i < commands.size(); i++)
        {
            int strtRow = commands.get(i).get(0) - 1;
            int strtCol = commands.get(i).get(1) - 1;
            int endCol  = strtCol + commands.get(i).get(2);
            
            int prevRowMap = rowMap.get(i - 1);
            int prevColMap = colMap.get(i - 1);
            
            int currRowMap = strtRow + prevColMap - strtCol;
            int currColMap = endCol  - prevRowMap + strtRow;
            
            rowMap.add(currRowMap);
            colMap.add(currColMap);
        }
        
        
        for(int i = 0; i < knights.size(); i++)
        {
            int r = (int) (knights.get(i) / n);
            int c = (int) (knights.get(i) % n);
            
            int resRow = r, resCol = c;
            int left = 0, right = commands.size() - 1, mid;
            
            while(left <= right)
            {
                mid = left + ((right - left)>>1);
                
                int strtRow = commands.get(mid).get(0) - 1;
                int strtCol = commands.get(mid).get(1) - 1;
                int endRow  = strtRow + commands.get(mid).get(2);
                int endCol  = strtCol + commands.get(mid).get(2);
                
                int row, col;
                
                if(mid % 2 == 0)
                {
                    if(((mid + 1) >> 1) % 2 == 0)
                        row = rowMap.get(mid) + c;
                    else 
                        row = rowMap.get(mid) - c;
                    
                    if((mid >> 1) % 2 == 0)
                        col = colMap.get(mid) - r;
                    else 
                        col = colMap.get(mid) + r;
                }
                else
                {
                    if(((mid + 1) >> 1) % 2 == 0)
                        row = rowMap.get(mid) + r;
                    else 
                        row = rowMap.get(mid) - r;
                    
                    if((mid >> 1) % 2 == 0)
                        col = colMap.get(mid) - c;
                    else 
                        col = colMap.get(mid) + c;
                }
                
                if(row < strtRow || row > endRow || col < strtCol || col > endCol)
                    right = mid - 1;
                else 
                {
                    resRow = row;
                    resCol = col;
                    left = mid + 1;
                }
            }
            
            res.get(i).add(resRow + 1);
            res.get(i).add(resCol + 1);
        }
        
        return res;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        int s = Integer.parseInt(bufferedReader.readLine().trim());

        List<List<Integer>> commands = new ArrayList<>();

        IntStream.range(0, s).forEach(i -> {
            try {
                commands.add(
                    Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                        .map(Integer::parseInt)
                        .collect(toList())
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        int knightsCount = Integer.parseInt(bufferedReader.readLine().trim());

        List<Long> knights = IntStream.range(0, knightsCount).mapToObj(i -> {
            try {
                return bufferedReader.readLine().replaceAll("\\s+$", "");
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        })
            .map(String::trim)
            .map(Long::parseLong)
            .collect(toList());

        List<List<Integer>> result = Result.kingRichardKnights(n, s, commands, knights);

        result.stream()
            .map(
                r -> r.stream()
                    .map(Object::toString)
                    .collect(joining(" "))
            )
            .map(r -> r + "\n")
            .collect(toList())
            .forEach(e -> {
                try {
                    bufferedWriter.write(e);
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
